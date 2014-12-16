#include <malloc.h>
#include <assert.h>

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

Vertex* Find_Vertex (Vertex* head, int strat) {
	Vertex* pv = head;
	for(; pv != NULL; pv = pv->next)
		if(pv->start == start) break;
	return pv;
}

Edge* Find_Edge (Edge* nebor, int end) {
	Edge* pe = nebor;
	for(; pe != NULL; pe = pe->next)
		if(pe->end == end) break;
	return pe;
}

_Bool Insert_Vertex (Graph* pg, int start) {
	if(pg == NULL) return false;
	if(Find_Vertex(pg->head, start) == NULL) {
		pg->num_ver++;
		if(pg->head == NULL) pg->head = Create_Vertex(start);
		else {
			Vertex* pv = pg->head;
			for(; pv->next != NULL; pv = pv->next);
			pv->next = Create_Vertex(start);
		}
	}
	return true;
}

_Bool Insert_Edge(Graph* pg, int start, int end, int weight) {
	if(pg == NULL) return false;
	if(Insert_Vertex(pg, start)==false) return false;
	if(Insert_Vertex(pg, end)==false) return false;
	vertex* pv = Find_Vertex(pg->head, start);
	assert(pv);
	if(Find_Edge(pv->nebor, end) == NULL) {
		pg->num_edg++;
		pv->num_nebor++;
		if(pv->nebor == NULL) pv->nebor = Create_Edge(end, weight);
		else {
			Edge* pe = pv->nebor;
			for(; pe->next != NULL; pe = pe->next);
			pe->next = Creat_Edge(end, weight);
		}
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
	for(; j <= *i; j++) if(visit[j] == w) return true;
	return false;
}

void DFS(Graph* pg, int v, int visit[], int *i) {
	visit[*i] = v; *i++;
	int w = Get_FirstNebor(pg, v);
	while(w != -1) {
		if(Judge_in_Visit(w, visit, i) == false) DFS(pg, w, visit, i);
		w = Get_NextNebor(pg, v, w);
	}
}
