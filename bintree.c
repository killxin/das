#include <stdio.h>
#include <malloc.h>
typedef struct{
	char data;
	int leftchild,rightchild;
}Bintree;

int asize,bsize;

void set_bintree_list(char *a,Bintree *b){
	int i,*x_b2a,*x_a2b;
	x_b2a=(int *)malloc(sizeof(int)*asize);
	x_a2b=(int *)malloc(sizeof(int)*asize);
	for (i=1,bsize=1;i<asize;i++){
		if(a[i]==' ')continue;
		else{
			b[bsize].data=a[i];
			x_b2a[bsize]=i;
			x_a2b[i]=bsize;
			bsize++;
		}
	}
	for (i=1;i<bsize;i++){
		b[i].leftchild=((a[x_b2a[i]*2]==' '||x_b2a[i]*2>=asize) ? -1 : x_a2b[x_b2a[i]*2]);
		b[i].rightchild=((a[x_b2a[i]*2+1]==' '||x_b2a[i]*2+1>=asize) ? -1 : x_a2b[x_b2a[i]*2+1]);
	}
	bsize--;
}

void preorder(Bintree* b,int x){
	if(x<=bsize){
		putchar(b[x].data);
		if(b[x].leftchild!=-1)
			preorder(b,b[x].leftchild);
		if(b[x].rightchild!=-1)
		 	preorder(b,b[x].rightchild);
	}
}

int main(){
	char* a;
	Bintree* b;
	int i;
	printf("please input the high of bintree\n");
	scanf("%d",&asize);
        asize=1<<asize;
	a=(char *)malloc(sizeof(char)*asize);
	b=(Bintree *)malloc(sizeof(Bintree)*asize);
	printf("please input the bintree(whitespace for nothing)\n");
	while (getchar()!='\n');
	for (i=1;i<asize;i++) a[i]=getchar();
	set_bintree_list(a,b);
	preorder(b,1);
	return 0;
}



