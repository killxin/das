#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "graph.h"
#include "circle.h"
#include "blog.h"

enum {S_GRAPH, S_USER, S_CIRCLE};

char* rl_gets(int blog_state) {
	static char *line_read = NULL;
	if (line_read) {
		free(line_read);
		line_read = NULL;
	}
	if(blog_state == S_GRAPH){ line_read = readline("(graph) "); }
	else if(blog_state == S_USER){ line_read = readline("(user) "); }
	else if(blog_state == S_CIRCLE){ line_read = readline("(circle) "); } 
	else { assert(0); }
	if (line_read && *line_read) {
		add_history(line_read);
	}
	return line_read;
}

void main_loop(Graph* graph, Circle* circle) {
	char *cmd;
	int blog_state = S_GRAPH;
	int n_user;
	Vertex* p_user;
	Thread* p_circle;
	printf("Graph vertex: %d edge: %d circlr: %d\n", graph->num_ver, graph->num_edg, circle->num_cir);
	while(1) {
		cmd = rl_gets(blog_state);
		char *p = strtok(cmd, " ");
		if(p  == NULL) { continue; }
		if(strcmp(p, "exit") == 0) { break; }
		if(blog_state == S_GRAPH) {
			if(strcmp(p, "user") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL){ printf("userid\n"); }
				else {
					n_user = atoi(p);
					p_user = Find_User(graph, n_user);
					if(p_user) {
						blog_state = S_USER;
						printf("Userid: %d friend: %d\n", n_user, p_user->num_nebor);
					}
					else { printf("User isn't exist\n"); }
				}
			}
			else if(strcmp(p, "info") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL) { printf("v for vertex, e for edge\n"); }
				else if(strcmp(p, "v") == 0) { Get_Vertexlist(graph); }
				else if(strcmp(p, "e") == 0) { Get_Edgelist(graph); }
				else { printf("v for vertex, e for edge\n"); }
			}
			else if(strcmp(p, "q") == 0) { printf("exit to quit\n"); }
			else { printf("Unknown command '%s'\n", p); }
		}
		else if(blog_state == S_USER) {
			if(strcmp(p, "q") == 0) { blog_state = S_GRAPH; }
			else if(strcmp(p, "circle") == 0) {
				p_circle = Find_Circle(circle, n_user);
				if (p_circle) {
					blog_state = S_CIRCLE;
					printf("Circle user: %d\n", p_circle->num_user);
				}
				else { assert(0); }
			}
			else if(strcmp(p, "friend") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL){ printf("userid\n"); }
				else {
					int user = atoi(p);
					if(user == 0) { printf("userid\n"); }
					else if(Judge_Friend(p_user, user)){ printf("%d is %d's friend\n", user, n_user); }
					else { printf("%d isn't %d's friend\n", user, n_user); }
				}
			}
			else { printf("Unknown command '%s'\n", p); }
		}
		else {
			if(strcmp(p, "q") == 0) { blog_state = S_USER; }
			else if(strcmp(p, "info") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL) { printf("u for userid in circle\n"); }
				else if(strcmp(p, "u") == 0) { Get_Circlelist(p_circle); }
				else { printf("u for userid in circle\n"); }
			}
		}
	}
}


/* argv[1] is newfriends, argv[2] is at */
int main(int argc, char *argv[]) {
	FILE *fri, *fat;
	if(argc == 3) {
	 	if(!(fri = fopen(argv[1], "r"))) {
			printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
			exit(8);
		}
	 	if(!(fat = fopen(argv[2], "r"))) {
			printf("%s: Error: Couldn't open %s\n", argv[0], argv[2]);
			exit(8);
		}
	}
	else {
		printf("Usage: %s [<input_file> <input_file>]\n", argv[0]);
		exit(8);
	}
	printf("loading......\n");
	Graph* graph = Create_Graph();
	Circle* circle = Create_Circle();
	unsigned u1, u2;
	char at;
	int n = 10;
	while (!feof(fri)) {
		fscanf(fri, "%d %d", &u1, &u2);
		assert(Deal_Friend(graph, u1, u2));
	}
	while (!feof(fat)) {
		fscanf(fat, "%d@%d", &u1, &u2);
		assert(Deal_At(graph, u1, u2));
	}
	assert(Set_Circle(graph, circle));
	main_loop(graph, circle);
	return 0;
}

