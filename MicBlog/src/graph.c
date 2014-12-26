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

static Vertex* Find_Vertex (Vertex* head, int start) {
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
int Insert_Vertex (Graph* pg, int start) {
	if(pg == NULL) return 0;
	if(Find_Vertex(pg->head, start) == NULL) {
		pg->num_ver++;
		Vertex* pv = pg->head;
		pg->head = Create_Vertex(start);
		assert(pg->head);
		pg->head->next = pv;
	}
	return 1;
}

/* Insert from head */
int Insert_Edge(Graph* pg, int start, int end, int weight) {
	if(pg == NULL) return 0;
	if(Insert_Vertex(pg, start) == 0) return 0;
	if(Insert_Vertex(pg, end) == 0) return 0;
	Vertex* pv = Find_Vertex(pg->head, start);
	assert(pv);
	if(Find_Edge(pv->nebor, end) == NULL) {
		pg->num_edg++;
		pv->num_nebor++;
		Edge* pe = pv->nebor;
		pv->nebor = Create_Edge(end, weight);
		assert(pv->nebor);
		pv->nebor->next = pe;
	}
	return 1;
}

int Get_Weight (Graph* pg, int start, int end) {
	Vertex* pv = Find_Vertex(pg->head, start);
	if(pv == NULL) return -1;
	Edge* pe = Find_Edge(pv->nebor, end);
	if(pe == NULL) return -1;
	else return pe->weight;
}

int Change_Weight (Graph* pg, int start, int end, int weight) {
	Vertex* pv = Find_Vertex(pg->head, start);
	if(pv == NULL) return 0;
	Edge* pe = Find_Edge(pv->nebor, end);
	if(pe == NULL) return 0;
	else {
		pe->weight = weight;
		return 1;
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

int Judge_in_Visit(int w, int* visit, int* i) {
	int k = 0;
	for(; k < *i; k++) {
		if(visit[k] == w) return 1;
	}
	return 0;
}

void DFS(Graph* pg, int v, int* visit, int *i) {
	/* Push to visit */
	visit[*i] = v;
	(*i)++;
	int w = Get_FirstNebor(pg, v);
	while(w != -1) {
		if(Judge_in_Visit(w, visit, i) == 0) {
			DFS(pg, w, visit, i);
		}
		w = Get_NextNebor(pg, v, w);
	}
}
