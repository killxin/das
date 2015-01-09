#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "graph.h"
#include "circle.h"
#include "blog.h"

/*
 Definition :
	Friend : if there are edges between two users, they are friends.
	Frequency : the add of edge's weight between two users.
	Association : how many common friends they have.
*/

#define _FW 3
#define _AW 1

int Deal_Friend (Graph* pg, int start, int end) {
	/* if two users are friend, weight is _FW.
	   if they have already been friends, information is ignored */
	return (Insert_Edge(pg, start, end, _FW) && Insert_Edge(pg, end, start, _FW));
}

int Deal_At (Graph* pg, int start, int end) {
	/* if they aren't friend, weight is _AW.
	   once one at the other, weight adds _AW */
	int w = Get_Weight(pg, start, end);
	if(w == -1) {
		return (Insert_Edge(pg, start, end, _AW) && Insert_Edge(pg, end, start, _AW));
	}
	else {
		return (Change_Weight(pg, start, end, w + _AW) && Change_Weight(pg, end, start, w + _AW));
	}
}

int Set_Circle(Graph* pg, Circle* pc) {
	if(pc == NULL || pg == NULL) return 0;
	int n = pg->num_ver;
	if(n == 0) return 0;
	int* visit = (int *)malloc(sizeof(int)*n);
	int i = 0, j = 0;
	for(; i < n; i++) visit[i] = 0;
	Vertex* pv = pg->head;
	i = 0;
	for(; pv != NULL; pv = pv->next) {
		int v = pv->start;
		if(Judge_in_Visit(v, visit, &i) == 0){
			DFS(pg, v, visit, &i);
			assert(Insert_Thead(pc, i-j));
			int k;
			for(k = 0; j < i; j++,k++) {
				/* visit [j] ~ visit[i-1] is a circle */
				pc->head->list[k] = visit[j];
			}
		}
	}
	return 1;
}

void Get_Vertexlist(Graph* pg) {
	Vertex* vertexlist = pg->head;
	int n = 1;
	for(; vertexlist != NULL; vertexlist = vertexlist->next, n++)
		printf("No.%d	%d\n",n,vertexlist->start);
}

void Get_Edgelist(Graph* pg) {
	Vertex* vertexlist = pg->head;
	int n = 1;
	for(; vertexlist != NULL; vertexlist = vertexlist->next){
		Edge* edgelist = vertexlist->nebor;
		for(; edgelist != NULL; edgelist = edgelist->next, n++){
			printf("No.%d	%d -> %d (%d)\n", n, vertexlist->start, edgelist->end, edgelist->weight);
		}
	}
}

Thread* Find_Circle (Circle* pc, int uid) {
	Thread* pt = pc->head;
	for(; pt != NULL; pt = pt->next) {
		int j = 0;
		for(; j < pt->num_user; j++){
			if(pt->list[j] == uid) return pt;
		}
	}
	return pt;
}

void Get_Circlelist(Thread* pt) {
	int m = 0;
	for(; m < pt->num_user; m++){
		printf("No.%d	%d\n",m+1,pt->list[m]);
	}
}

/* use heap sort */
static Shift_Down (Rela* pr, int start, int m) {
	int i = start, j = 2 * i + 1;
	Rela temp;
	temp.start = pr[i].start;
	temp.end = pr[i].end;
	temp.weight = pr[i].weight;
	while(j <= m) {
		if(j < m && pr[j].weight > pr[j + 1].weight) j++;
		if(temp.weight <= pr[j].weight) break;
		else {
			pr[i].start = pr[j].start;
			pr[i].end = pr[j].end;
			pr[i].weight = pr[j].weight;
			i = j;
			j = 2 * i + 1;
		}
	}
	pr[i].start = temp.start;
	pr[i].end = temp.end;
	pr[i].weight = temp.weight;
}

static void Rela_Sort(Rela* pr, int num) {
	int i = (num - 2) / 2;
	Rela temp;
	/* set heap */
	for(; i >= 0; i--) Shift_Down(pr, i, num - 1);
	/* heapsort */
	for(i = num - 1; i >= 0; i--) {
		temp.start = pr[0].start;
		temp.end = pr[0].end;
		temp.weight = pr[0].weight;
		pr[0].start = pr[i].start;
		pr[0].end = pr[i].end;
		pr[0].weight = pr[i].weight;
		pr[i].start = temp.start;
		pr[i].end = temp.end;
		pr[i].weight = temp.weight;
		Shift_Down(pr, 0, i - 1);
	}
}

Rela* Top_Frequency (Graph* pg, Thread* pt, int* n) {
	int num = pt->num_user * (pt->num_user - 1) / 2;
	Rela* pr = (Rela*)malloc(sizeof(Rela)*num);
	assert(pr);
	int i = 0, j = 0;
	num = 0;
	for(; i < pt->num_user; i++)
		for(j = i + 1; j < pt->num_user; j++) {
			int w = Get_Weight(pg, pt->list[i], pt->list[j]);
			if(w != -1) {
				pr[num].start = pt->list[i];
				pr[num].end = pt->list[j];
				pr[num].weight = w * 2;
				num++;
			}
		}
	Rela_Sort(pr, num);
	/* n is the number of relations */
	*n = num;
	return pr;
}

static int Get_Association (Vertex* pv1, Vertex* pv2) {
	int count = 0;
	if(pv1 == NULL || pv2 == NULL) return -1;
	Edge *pe1, *pe2;
	for(pe1 = pv1->nebor; pe1 != NULL; pe1 = pe1->next)
		for(pe2 = pv2->nebor; pe2 != NULL; pe2 = pe2->next) {
			if(pe1->end == pe2->end) {
				count++;
				break;
			}
		}
	return count;
}

Rela* Top_Association(Graph* pg, int* n) {
	int size = pg->num_ver * (pg->num_ver - 1) / 2;
	Rela* pr = (Rela*)malloc(sizeof(Rela)*size);
	assert(pr);
	int num = 0;
	Vertex *pv1, *pv2;
	for(pv1 = pg->head; pv1 != NULL; pv1 = pv1->next)
		for(pv2 = pv1->next; pv2 != NULL; pv2 = pv2->next) {
			int w = Get_Association(pv1, pv2);
			if(w != -1) {
				assert(num < size);
				pr[num].start = pv1->start;
				pr[num].end = pv2->start;
				pr[num].weight = w;
				num++;
			}
		}
	Rela_Sort(pr, num);
	*n = num;
	return pr;
}

Rela* User_Frequency(Vertex* pv, int* n) {
	int size = pv->num_nebor;
	Rela* pr = (Rela*)malloc(sizeof(Rela)*size);
	assert(pr);
	int num = 0;
	Edge* pe = pv->nebor;
	for(; pe != NULL; pe = pe->next, num++) {
		pr[num].start = pv->start;
		pr[num].end = pe->end;
		pr[num].weight = pe->weight * 2;
	}
	Rela_Sort(pr, num);
	*n = num;
	return pr;
}

Rela* User_Association(Graph* pg, Vertex* pv, int* n) {
	int size = pg->num_ver - 1;
	Rela* pr = (Rela*)malloc(sizeof(Rela)*size);
	assert(pr);
	int num = 0;
	Vertex* pv1 = pg->head;
	for(; pv1 != NULL; pv1 = pv1->next) {
		if(pv == pv1) continue;
		int w = Get_Association(pv, pv1);
		if(w != -1) {
			pr[num].start = pv->start;
			pr[num].end = pv1->start;
			pr[num].weight = w;
			num++;
		}
	}
	Rela_Sort(pr, num);
	*n = num;
	return pr;
}
