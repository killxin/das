#include "graph.c"
#include "circle.c"

/*
 Definition :
	Friend : if there are edges between two users, they are friends.
	ps: friends are in the same circle.
	Frequency : the add of edge's weight between two users.
	Association : how many common friends they have.
*/

_Bool Deal_Friend (Graph* pg, int start, int end) {
	/* if two users are friend, weight is 3.
	   if they have been friends, information is ignored*/
	return (Insert_Edge(pg, start, end, 3) && Insert(pg, end, start, 3));
}

_Bool Deal_At (Graph* pg, int start, int end) {
	/* if they aren't friend, weight is set to 1 
	   once one at the other, weight ++ */
	int w = Get_Weight(pg, start, end);
	if(w == -1) return Insert_Edge(pg, start, end, 1);
	else return Change_Weight(pg, start, end, w + 1);
}
	
_Bool Set_circle(Graph* pg, Circle* pc) {
	if(pc == NULL || pg == NULL) return false;
	int n = pg->num_ver;
	if(n == 0) return false;
	int* visit = (int *)malloc(sizeof(int)*n);
	int i = 0, j = 0;
	for(; i < n; i++) visit[i] = 0;
	Vertex* pv = pg->head;
	i = 0;
	for(; pv != NULL; pv = pv->next) {
		int v = pv->start;
		if(Judge_in_Visit(v, visit, i) == false){
			DFS(pg, v, visit, &i);
			if(Insert_Thead(pc, i-j) == false) return false;
			int k;
			for(k = 0; j < i; j++,k++) {
				pc->head->list[k] = visit[j];
			}
		}
	}
}

_Bool Judge_Friend (Circle* pc, int user1, int user2) {
	Thread* pt1 = Find_Circle(pc, user1);
	Thread* pt2 = Find_Circle(pc, user2);
	return pt1==pt2;
}

int Get_Frequency (Graph* pg, Circle* pc, int user1, int user2) {
	if(Judge_Friend(pc, user1, user2) == false) return -1;
	int weight12 = Get_Weight(pg, user1, user2);
	int weight21 = Get_Weight(pg, user2, user1);
	return weight12+weight21;
}
	
int Common_Friend (Circle* pc, int user1, user2) {
	if(Judge_Friend(pc, user1, user2)) return -1;
	Thread* pt1 = Find_Circle(pc, user1);
	Thread* pt2 = Find_Circle(pc, user2);
	int i, count = 0;
	int* pl1 = pt1->list;
	for(i = 0; i < pt1->num_user; i++)
		if(Judge_Friend(pc, pt1->list[i], user2))
			count++;
	for(i = 0; i < pt2->num_user; i++)
		if(Judge_Friend(pc, user1, pt2->list[i]))
			count++;
	return count;
}

