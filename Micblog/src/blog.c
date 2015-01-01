#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "graph.h"
#include "circle.h"
#include "blog.h"

/*
 Definition :
	Friend : if there are edges between two users, they are friends.
	ps: friends are in the same circle.
	Frequency : the add of edge's weight between two users.
	Association : how many common friends they have.
*/

int Deal_Friend (Graph* pg, int start, int end) {
	/* if two users are friend, weight is 3.
	   if they have been friends, information is ignored*/
	return (Insert_Edge(pg, start, end, 3) && Insert_Edge(pg, end, start, 3));
}

int Deal_At (Graph* pg, int start, int end) {
	/* if they aren't friend, weight is set to 1 
	   once one at the other, weight ++ */
	int w = Get_Weight(pg, start, end);
	if(w == -1) return Insert_Edge(pg, start, end, 1) && Insert_Edge(pg, end, start, 1);
	else return Change_Weight(pg, start, end, w + 1) && Change_Weight(pg, end, start, w + 1);
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

Vertex* Find_User(Graph* pg, int user) { return Find_Vertex(pg->head, user); }

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

int Judge_Friend (Vertex* pv, int user) {
	Edge* pe = pv->nebor;
	for(; pe != NULL; pe = pe->next){
		if(pe->end == user) return 1;
	}
	return 0;
}

void Get_Circlelist(Thread* pt) {
	int m = 0;
	for(; m < pt->num_user; m++){
		printf("No.%d	%d\n",m+1,pt->list[m]);
	}
}

void Get_Friendlist(Graph* pg, Vertex* pv) {
	Edge* pe = pv->nebor;
	int n = 1;
	for(; pe != NULL; pe = pe->next, n++) {
		printf("No.%d	%d (%d)\n", n, pe->end, Get_Weight(pg, pv->start, pe->end));
	}
}

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
	for(; i >= 0; i--) Shift_Down(pr, i, num - 1);
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
	
	
static int Get_Frequency (Graph* pg, int user1, int user2) {
	Vertex* pv = Find_Vertex(pg->head, user1);
	if(pv == NULL) return -1;
	if(Judge_Friend(pv, user2) == 0) return -1;
	int weight12 = Get_Weight(pg, user1, user2);
	int weight21 = Get_Weight(pg, user2, user1);
	return weight12+weight21;
}

Rela* Top_Frequency (Graph* pg, Thread* pt, int* n) {
	int num = pt->num_user * (pt->num_user - 1) / 2;
	Rela* pr = (Rela*)malloc(sizeof(Rela)*num);
	assert(pr);
	int i = 0, j = 0;
	num = 0;
	for(; i < pt->num_user; i++)
		for(j = i + 1; j < pt->num_user; j++) {
			int w = Get_Frequency(pg, pt->list[i], pt->list[j]);
			if(w != -1) {
				pr[num].start = pt->list[i];
				pr[num].end = pt->list[j];
				pr[num].weight = w;
				num++;
			}
		}
	Rela_Sort(pr, num);
	*n = num;
	return pr;
}

static int Get_Association (Graph* pg, int user1, int user2) {
	int count = 0;
	Vertex* pv1 = Find_Vertex(pg->head, user1);
	if(pv1 == NULL) return -1;
	Vertex* pv2 = Find_Vertex(pg->head, user2);
	if(pv2 == NULL) return -1;
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
			int w = Get_Association(pg, pv1->start, pv2->start);
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
