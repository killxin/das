#ifndef _CIRCLE_
#define _CIRCLE_

struct Thread {
	int num_user;
	int* list;
	Thread* next;
};
struct Circle {
	int num_cir;
	Thread* head;
};
Circle* Create_Circle();
_Bool Insert_Thread(Circle* pc, int num_user);
Thread* Find_Circle(Circle* pc, int uid);

#endif
