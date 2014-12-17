#ifndef _GRAPH_
#define _GRAPH_

struct Edge {
	int end;
	int weight;
	Edge* next;
};
struct Vertex {
	int start;
	int num_nebor;
	Edge* nebor;
	Vertex* next;
};
struct Graph {
	int num_ver;
	int num_edg;
	Vertex* head;
};
Graph* Create_Graph();
_Bool Insert_Vertex (Graph* pg, int start);
_Bool Insert_Edge(Graph* pg, int start, int end, int weight);
int Get_Weight (Graph* pg, int start, int end);
_Bool Change_Weight (Graph* pg, int start, int end, int weight);
void DFS(Graph* pg, int v, int visit[], int *i);

#endif
