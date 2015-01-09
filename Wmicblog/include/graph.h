#ifndef _GRAPH_
#define _GRAPH_

typedef struct Edge_Type {
	int end;
	int weight;
	struct Edge_Type* next;
}Edge;

typedef struct Vertex_Type {
	int start;
	int num_nebor;
	Edge* nebor;
	struct Vertex_Type* next;
}Vertex;

typedef struct Graph_Type {
	int num_ver;
	int num_edg;
	Vertex* head;
}Graph;

Graph* Create_Graph();
int Insert_Vertex (Graph* pg, int start);
int Insert_Edge(Graph* pg, int start, int end, int weight);
int Get_Weight (Graph* pg, int start, int end);
int Change_Weight (Graph* pg, int start, int end, int weight);
int Judge_in_Visit(int w, int* visi, int* i);
void DFS(Graph* pg, int v, int* visit, int *i);
Vertex* Find_Vertex (Vertex* head, int start);

#endif
