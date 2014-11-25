#include <stdio.h>
#include <malloc.h>
typedef struct{
	int data;
	int leftchild,rightchild;
}Bintree;

int array_size,list_size;

void set_bintree_list(int *array,Bintree *list){
	int i,*x_l2a,*x_a2l;
	x_l2a=(int *)malloc(sizeof(int)*array_size);
	x_a2l=(int *)malloc(sizeof(int)*array_size);
	for (i=1,list_size=1;i<array_size;i++){
		if(array[i]==0)continue;
		else{
			list[list_size].data=array[i];
			x_l2a[list_size]=i;
			x_a2l[i]=list_size;
			list_size++;
		}
	}
	for (i=1;i<list_size;i++){
		list[i].leftchild=((array[x_l2a[i]*2]==0||x_l2a[i]*2>=array_size) ? -1 : x_a2l[x_l2a[i]*2]);
		list[i].rightchild=((array[x_l2a[i]*2+1]==0||x_l2a[i]*2+1>=array_size) ? -1 : x_a2l[x_l2a[i]*2+1]);
	}
	free(x_l2a);
	free(x_a2l);
	list_size--;
}

void InOrder(Bintree* list,int x,int* &a,int &i){
	if(x<=list_size){
		if(list[x].leftchild!=-1)
			InOrder(list,list[x].leftchild,a,i);
		printf("%d ",list[x].data);
		a[i]=list[x].data;
		i++;
		if(list[x].rightchild!=-1)
			InOrder(list,list[x].rightchild,a,i);
	}
}

int JudgeSearch(Bintree *list){
	int* a=(int*)malloc(sizeof(int)*list_size);
	int i=0;
	InOrder(list,1,a,i);
	int temp=a[0];
	for (int j=1;j<list_size;j++){
		if(temp>=a[j])return 0;
		temp=a[j];
	}
	return 1;
}
	
int main(){
	int* array;
	Bintree* list;
	int i;
	printf("please input the high of bintree\n");
	scanf("%d",&array_size);
        array_size=1<<array_size;
	array=(int *)malloc(sizeof(int)*array_size);
	list=(Bintree *)malloc(sizeof(Bintree)*array_size);
	printf("please input the bintree(0 for nothing)\n");
	for (i=1;i<array_size;i++) scanf("%d",&array[i]);
	set_bintree_list(array,list);
	if(JudgeSearch(list)) printf("yes\n");
	else printf("no\n");
	return 0;
}
