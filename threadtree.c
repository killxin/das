#include <stdio.h>
#include <malloc.h>
typedef struct{
	int ltag,rtag;
	char data;
	int leftchild,rightchild;
}Bintree;

int array_size,thread_size;

void prethread(Bintree* thread,int cur,int *pre){
	if(cur!=-1){
		if(thread[cur].ltag==1)
			thread[cur].leftchild=*pre;
		if(*pre!=-1&&thread[*pre].rtag==1)
			thread[*pre].rightchild=cur;
		//this step is necessary
		*pre=cur;
		if(!thread[cur].ltag) prethread(thread,thread[cur].leftchild,pre);
		if(!thread[cur].rtag) prethread(thread,thread[cur].rightchild,pre);
	}
}

void set_bintree_thread(char *array,Bintree *thread){
	int i,*x_l2a,*x_a2l,pre;
	x_l2a=(int *)malloc(sizeof(int)*array_size);
	x_a2l=(int *)malloc(sizeof(int)*array_size);
	for (i=1,thread_size=1;i<array_size;i++){
		if(array[i]==' ')continue;
		else{
			thread[thread_size].data=array[i];
			x_l2a[thread_size]=i;
			x_a2l[i]=thread_size;
			thread_size++;
		}
	}
	for (i=1;i<thread_size;i++){
		thread[i].leftchild=((array[x_l2a[i]*2]==' '||x_l2a[i]*2>=array_size) ? -1 : x_a2l[x_l2a[i]*2]);
		thread[i].ltag=(thread[i].leftchild==-1);
		thread[i].rightchild=((array[x_l2a[i]*2+1]==' '||x_l2a[i]*2+1>=array_size) ? -1 : x_a2l[x_l2a[i]*2+1]);
		thread[i].rtag=(thread[i].rightchild==-1);
	}
	free(x_l2a);
	free(x_a2l);
	thread_size--;
	pre=-1;
	prethread(thread,1,&pre);
	thread[pre].rightchild=-1;
}

void preorder_by_thread(Bintree *thread){
	int i=1;
	while (thread[i].rightchild!=-1){
		putchar(thread[i].data);
		i=(thread[i].rtag|thread[i].ltag ? thread[i].rightchild : thread[i].leftchild);
	}
	putchar(thread[i].data);
}

int main(){
	char *array;
	Bintree *thread;
	int i;
	printf("please input the high of bintree\n");
	scanf("%d",&array_size);
        array_size=1<<array_size;
	array=(char *)malloc(sizeof(char)*array_size);
	thread=(Bintree *)malloc(sizeof(Bintree)*array_size);
	printf("please input the bintree(whitespace for nothing)\n");
	while (getchar()!='\n');
	for (i=1;i<array_size;i++) array[i]=getchar();
	set_bintree_thread(array,thread);
	preorder_by_thread(thread);
	return 1;
}

