#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include "graph.h"
#include "circle.h"
#include "blog.h"

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
	Get_Userlist(graph);
	Get_Usernumber(graph);
	Get_Circlelist(circle);
	Get_Circlenumber(circle);
	return 0;
}

