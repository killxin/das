#include "graph.c"


_Bool Set_circle(Graph* pg, int v) {
	if(pg == NULL) return false;
	int n = pg->num_ver;
	if(n == 0) return false;
	int* visit = (int *)malloc(sizeof(int)*n);
	int i = 0;
	for(; i < n; i++) visit[i] = 0;
	Vertex* pv = pg->head;
	for(i = 0; pv != NULL; pv = pv->next) {
		int v = pv->start;
		if(Judge_in_Visit(v, visit, i) == false){
			DFS(pg, v, visit, &i);
			
}
