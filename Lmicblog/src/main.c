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

Graph* graph;
Circle* circle;
int blog_state;
int n_user;
Vertex* p_user;
Thread* p_circle;
int n_fre, n_ass;
Rela *p_fre, *p_ass;
char* p;

char* rl_gets() {
	static char *line_read = NULL;
	if (line_read) {
		free(line_read);
		line_read = NULL;
	}
	if(blog_state == S_GRAPH){ line_read = readline("(graph) "); }
	else if(blog_state == S_USER){ line_read = readline("(user) "); }
	else if(blog_state == S_CIRCLE){ line_read = readline("(circle) "); } 
	else { assert(0); }
	if (line_read && *line_read) { add_history(line_read); }
	return line_read;
}

void graph_2_user() {
	p = strtok(NULL, " ");
	if(p == NULL){ printf("userid\n"); }
	else {
		n_user = atoi(p);
		p_user = Find_Vertex(graph->head, n_user);
		if(p_user) {
			blog_state = S_USER;
			printf("Userid: %d friend: %d\n", n_user, p_user->num_nebor);
		}
		else { printf("User isn't exist\n"); }
	}
}

void user_2_circle() {
	p_circle = Find_Circle(circle, n_user);
	assert(p_circle);
	blog_state = S_CIRCLE;
	printf("Circle user: %d\n", p_circle->num_user);
}

void graph_association() {
	p = strtok(NULL, " ");
	p_ass = Top_Association(graph, &n_ass);
	assert(p_ass);
	int n = n_ass;
	if(p != NULL) {
		int m = atoi(p);
		if(m == 0) printf("n error\n");
		else n = (n > m ? m : n);
	}
	else { printf("n is %d default\n", n_ass); }
	int i = 0;
	for(; i < n; i++){
		printf("Top Association %d:\t%d--%d(%d)\n", i+1, p_ass[i].start, p_ass[i].end, p_ass[i].weight);
	}
	free(p_ass);
}

void user_association() {
	p = strtok(NULL, " ");
	p_ass = User_Association(graph, p_user, &n_ass);
	assert(p_ass);
	int n = n_ass;
	if(p != NULL) {
		int m = atoi(p);
		if(m == 0) printf("n error\n");
		else n = (n > m ? m : n);
	}
	else { printf("n is %d default\n", n_ass); }
	int i = 0;
	for(; i < n; i++){
		printf("User Association %d:\t%d--%d(%d)\n", i+1, p_ass[i].start, p_ass[i].end, p_ass[i].weight);
	}
	free(p_ass);
}

void user_frequency() {
	p = strtok(NULL, " ");
	p_fre = User_Frequency(p_user, &n_fre);
	int n = n_fre;
	if(p != NULL) {
		int m = atoi(p);
		if(m == 0) printf("n error\n");
		else n = (n > m ? m : n);
	}
	else { printf("n is %d default\n", n_fre); }
	int i = 0;
	for(; i < n; i++){
		printf("User Frequency %d:\t%d--%d(%d)\n", i+1, p_fre[i].start, p_fre[i].end, p_fre[i].weight);
	}
	free(p_fre);
}

void circle_frequency() {
	p = strtok(NULL, " ");
	p_fre = Top_Frequency(graph, circle->head, &n_fre);
	int n = n_fre;
	if(p != NULL) {
		int m = atoi(p);
		if(m == 0) printf("n error\n");
		else n = (n > m ? m : n);
	}
	else { printf("n is %d default\n", n_fre); }
	int i = 0;
	for(; i < n; i++){
		printf("Top Frequency %d:\t%d--%d(%d)\n", i+1, p_fre[i].start, p_fre[i].end, p_fre[i].weight);
	}
	free(p_fre);
}

void main_loop(Graph* graph, Circle* circle) {
	char *cmd;
	blog_state = S_GRAPH;
	printf("Graph vertex: %d edge: %d circlr: %d\n", graph->num_ver, graph->num_edg, circle->num_cir);
	while(1) {
		cmd = rl_gets();
		p = strtok(cmd, " ");
		if(p  == NULL) { continue; }
		if(strcmp(p, "exit") == 0) { break; }
		if(blog_state == S_GRAPH) {
			if(strcmp(p, "user") == 0) { graph_2_user(); }
			else if(strcmp(p, "info") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL) { printf("v for vertex, e for edge\n"); }
				else if(strcmp(p, "v") == 0) { Get_Vertexlist(graph); }
				else if(strcmp(p, "e") == 0) { Get_Edgelist(graph); }
				else { printf("v for vertex, e for edge\n"); }
			}
			else if(strcmp(p, "top") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL) { printf("a n for Top n Association\n"); }
				else if(strcmp(p, "a") == 0) { graph_association(); }
				else { printf("a n for Top n Association"); }
			}
			else if(strcmp(p, "q") == 0) { break; }
			else {
				printf("Unknown command '%s'\n", p);
				printf("user\ninfo\ntop\nq\nexit\n");
			}
		}
		else if(blog_state == S_USER) {
			if(strcmp(p, "q") == 0) {
				blog_state = S_GRAPH;
				printf("Graph vertex: %d edge: %d circlr: %d\n", graph->num_ver, graph->num_edg, circle->num_cir);
			}
			else if(strcmp(p, "circle") == 0) { user_2_circle(); }
			else if(strcmp(p, "info") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL){ printf("a for association or f for frequency\n"); }
				else if(strcmp(p, "a") == 0) { user_association(); }
				else if(strcmp(p, "f") == 0) { user_frequency(); }
				else{ printf("a for association or f for frequency\n"); }
			}
			else {
				printf("Unknown command '%s'\n", p);
				printf("circle\ninfo\nq\nexit\n");
			}
		}
		else if(blog_state == S_CIRCLE) {
			if(strcmp(p, "q") == 0) {
				blog_state = S_USER;
				printf("Userid: %d friend: %d\n", n_user, p_user->num_nebor);
			}
			else if(strcmp(p, "info") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL) { printf("u for userid in circle\n"); }
				else if(strcmp(p, "u") == 0) { Get_Circlelist(p_circle); }
				else { printf("u for userid in circle\n"); }
			}
			else if(strcmp(p, "top") == 0) {
				p = strtok(NULL, " ");
				if(p == NULL) { printf("f n for Top n Frequency\n"); }
				else if(strcmp(p, "f") == 0) { circle_frequency(); }
				else { printf("f n for Top n Frequency\n"); }
			}
			else {
				printf("Unknown command '%s'\n", p);
				printf("info\ntop\nq\nexit\n");
			}
		}
		else { assert(0); }
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
	graph = Create_Graph();
	circle = Create_Circle();
	unsigned u1, u2;
	while (1) {
		fscanf(fri, "%d %d", &u1, &u2);
		if(feof(fri)) break;
		assert(Deal_Friend(graph, u1, u2));
	}
	while (1) {
		fscanf(fat, "%d@%d", &u1, &u2);
		if(feof(fat)) break;
		assert(Deal_At(graph, u1, u2));
	}
	fclose(fri);
	fclose(fat);
	assert(Set_Circle(graph, circle));
	main_loop(graph, circle);
	return 0;
}

