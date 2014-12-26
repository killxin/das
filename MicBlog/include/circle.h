#ifndef _CIRCLE_
#define _CIRCLE_

#include "graph.h"

typedef struct Thread_Type {
	int num_user;
	int* list;
	struct Thread_Type* next;
}Thread;
typedef struct Circle_Type {
	int num_cir;
	Thread* head;
}Circle;
Circle* Create_Circle();
int Insert_Thread(Circle* pc, int num_user);
Thread* Find_Circle(Circle* pc, int uid);

#endif
