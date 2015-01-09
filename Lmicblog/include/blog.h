#ifndef _BLOG_
#define _BLOG_

#include "graph.h"
#include "circle.h"

typedef struct Rela_Type {
	int start;
	int end;
	int weight;
}Rela;

int Deal_Friend (Graph* pg, int start, int end);
int Deal_At (Graph* pg, int start, int end);
int Set_Circle(Graph* pg, Circle* pc);
void Get_Vertexlist(Graph* pg);
void Get_Edgelist(Graph* pg);
Thread* Find_Circle(Circle* pc, int uid);
void Get_Circlelist(Thread* pt);
Rela* Top_Frequency (Graph* pg, Thread* pt, int* n);
Rela* Top_Association(Graph* pg, int* n);
Rela* User_Frequency(Vertex* pv, int* n);
Rela* User_Association(Graph* pg, Vertex* pv, int* n);

#endif
