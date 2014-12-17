#include <malloc.h>
#include <assert.h>
#include "graph.h"

/* there are functions about graph */
static Vertex* Create_Vertex (int start) {
	Vertex *pv = (Vertex *)malloc(sizeof(Vertex));
	assert(pv);
	pv->start = start;
	pv->num_nebor = 0;
	pv->nebor = NULL;
	pv->next = NULL;
	return pv;
}

static Edge* Create_Edge (int end, int weight) {
	Edge *pe = (Edge *)malloc(sizeof(Edge));
	assert(pe);
	pe->end = end;
	pe->weight = weight;
	pe->next = NULL;
	return pe;
}

static Vertex* Find_Vertex (Vertex* head, int strat) {
	Vertex* pv = head;
	for(; pv != NULL; pv = pv->next)
		if(pv->start == start) break;
	return pv;
}

static Edge* Find_Edge (Edge* nebor, int end) {
	Edge* pe = nebor;
	for(; pe != NULL; pe = pe->next)
		if(pe->end == end) break;
	return pe;
}

Graph* Create_Graph() {
	Graph* pg = (Graph *)malloc(sizeof(Graph));
	assert(pg);
	pg->num_ver = 0;
	pg->num_edg = 0;
	pg->head = NULL;
	return pg;
}

/* Insert from head */
_Bool Insert_Vertex (Graph* pg, int start) {
	if(pg == NULL) return false;
	if(Find_Vertex(pg->head, start) == NULL) {
		pg->num_ver++;
		Vertex* pv = pg->head;
		pg->head = Create_Vertex(start);
		assert(pg->head);
		pg->head->next = pv;
	}
	return true;
}

/* Insert from head */
_Bool Insert_Edge(Graph* pg, int start, int end, int weight) {
	if(pg == NULL) return false;
	if(Insert_Vertex(pg, start) == false) return false;
	if(Insert_Vertex(pg, end) == false) return false;
	vertex* pv = Find_Vertex(pg->head, start);
	assert(pv);
	if(Find_Edge(pv->nebor, end) == NULL) {
		pg->num_edg++;
		pv->num_nebor++;
		Edge* pe = pv->nebor;
		pv->nebor = Creat_Edge(end, weight);
		assert(pv->nebor);
		pv->nebor->next = pe;
	}
	return true;
}

int Get_Weight (Graph* pg, int start, int end) {
	Vertex* pv = Find_Vertex(pg->head, start);
	if(pv == NULL) return -1;
	Edge* pe = Find_Edge(pv->nebor, end);
	if(pe == NULL) return -1;
	else return pe->weight;
}

_Bool Change_Weight (Graph* pg, int start, int end, int weight) {
	Vertex* pv = Find_Vertex(pg->head, start);
	if(pv == NULL) return false;
	Edge* pe = Find_Edge(pv->nebor, end);
	if(pe == NULL) return false;
	else {
		pe->weight = weight;
		return true;
	}
}

static int Get_FirstNebor (Graph* pg, int start) {
	Vertex* pv = Find_Vertex(pg->head, start);
	if(pv == NULL) return -1;
	Edge* pe = pv->nebor;
	if(pe == NULL) return -1;
	else return pe->end;
}

static int Get_NextNebor (Graph* pg, int start, int end) {
	Vertex* pv = Find_Vertex(pg->head, start);
	if(pv == NULL) return -1;
	Edge* pe = Find_Edge(pv->nebor, end);
	if(pe == NULL) return -1;
	pe = pe->next;
	if(pe == NULL) return -1;
	else return pe->end;
}

static _Bool Judge_in_Visit(int w, int visit[], int* i) {
	int j = 0;
	for(; j < *i; j++) if(visit[j] == w) return true;
	return false;
}

void DFS(Graph* pg, int v, int visit[], int *i) {
	/* Push to visit */
	visit[*i] = v; *i++;
	int w = Get_FirstNebor(pg, v);
	while(w != -1) {
		if(Judge_in_Visit(w, visit, i) == false) DFS(pg, w, visit, i);
		w = Get_NextNebor(pg, v, w);
	}
}
