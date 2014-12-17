#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "circle.h"
#include "blog.h"

/* argv[1] is newfriends, argv[2] is at */
int main(int argc, char *argv[]) {
	FILE *fri, *fat;
	if(argc == 3) {
	 	if(!(fri = fopen(argv[1], "rt"))) {
			printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
			exit(8);
		}
	 	if(!(fat = fopen(argv[2], "rt"))) {
			printf("%s: Error: Couldn't open %s\n", argv[0], argv[2]);
			exit(8);
		}
	}
	else {
		printf("Usage: %s [<input_file> <input_file>]\n", argv[0]);
		exit(8);
	}

