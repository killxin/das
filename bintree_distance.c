#include <stdio.h>
#include <malloc.h>

typedef struct{
	char data;
	int leftchild,rightchild;
}Bintree;

int array_size,list_size;

void set_bintree_list(char *array,Bintree *list){
	int i,*x_l2a,*x_a2l;
	x_l2a=(int *)malloc(sizeof(int)*array_size);
	x_a2l=(int *)malloc(sizeof(int)*array_size);
	for (i=1,list_size=1;i<array_size;i++){
		if(array[i]==' ')continue;
		else{
			list[list_size].data=array[i];
			x_l2a[list_size]=i;
			x_a2l[i]=list_size;
			list_size++;
		}
	}
	for (i=1;i<list_size;i++){
		list[i].leftchild=((array[x_l2a[i]*2]==' '||x_l2a[i]*2>=array_size) ? -1 : x_a2l[x_l2a[i]*2]);
		list[i].rightchild=((array[x_l2a[i]*2+1]==' '||x_l2a[i]*2+1>=array_size) ? -1 : x_a2l[x_l2a[i]*2+1]);
	}
	free(x_l2a);
	free(x_a2l);
	list_size--;
}

int max_depth(Bintree *list,int index){
	int ldepth=0,rdepth=0,i=1,depth=0;
	if(index!=-1){
		ldepth=max_depth(list,list[index].leftchild);
		rdepth=max_depth(list,list[index].rightchild);
		depth=(ldepth>rdepth ? ldepth : rdepth);
		depth++;
	}
	return depth;
}
	
int max_distance(Bintree *list,int index){
	int ldepth=0,rdepth=0,distance=0;
	if(index!=-1){
		ldepth=max_depth(list,list[index].leftchild);
		rdepth=max_depth(list,list[index].rightchild);
		distance=ldepth+rdepth;
		distance=(distance>max_distance(list,list[index].leftchild) ? distance : max_distance(list,list[index].leftchild));
		distance=(distance>max_distance(list,list[index].rightchild) ? distance : max_distance(list,list[index].rightchild));
	}
	return distance;
}

int main(){
	char* array;
	Bintree* list;
	int i;
	printf("please input the high of bintree\n");
	scanf("%d",&array_size);
        array_size=1<<array_size;
	array=(char *)malloc(sizeof(char)*array_size);
	list=(Bintree *)malloc(sizeof(Bintree)*array_size);
	printf("please input the bintree(whitespace for nothing)\n");
	while (getchar()!='\n');
	for (i=1;i<array_size;i++) array[i]=getchar();
	set_bintree_list(array,list);
	printf("the max distance in bintree is %d\n",max_distance(list,1));
	return 0;
}

