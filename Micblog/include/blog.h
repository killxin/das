#ifndef _BLOG_
#define _BLOG_

#include "graph.h"
#include "circle.h"

int Deal_Friend (Graph* pg, int start, int end);
int Deal_At (Graph* pg, int start, int end);
int Set_Circle(Graph* pg, Circle* pc);
void Get_Vertexlist(Graph* pg);
void Get_Edgelist(Graph* pg);
Vertex* Find_User(Graph* pg, int user);
Thread* Find_Circle(Circle* pc, int uid);
int Judge_Friend (Vertex* pv, int user);
void Get_Circlelist(Thread* pt);
//int Get_Frequency (Graph* pg, Circle* pc, int user1, int user2);
//int Common_Friend (Circle* pc, int user1, int user2);

#endif
