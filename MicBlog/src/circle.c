#include <malloc.h> 
#include <assert.h>
#include <assert.h> 
#include "circle.h" 

static Thread* Create_Thread (int num_user) {
	Thread* pt = (Thread *)malloc(sizeof(Thread));
	assert(pt);
	pt->num_user = num_user;
	pt->list = (int *)malloc(sizeof(int)*num_user);
	assert(pt->list);
	pt->next = NULL;
	return pt;
}

Circle* Create_Circle() {
	Circle* pc = (Circle *)malloc(sizeof(Circle));
	assert(pc);
	pc->num_cir = 0;
	pc->head = NULL;
	return pc;
}

/* Insert from head */
int Insert_Thead (Circle* pc, int num_user) {
	if(pc == NULL) return 0;
	Thread* pt = pc->head;
	pc->head = Create_Thread(num_user);
	assert(pc->head);
	pc->num_cir++;
	pc->head->next = pt;
	return 1;
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
