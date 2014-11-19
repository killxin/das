#include <stdio.h>
#include <malloc.h>
typedef struct{
	int de1;
	int de2;
}DE;

int find(int* Dset,int data){
	while(Dset[data]>=0) data=Dset[data];
	return data;
}

void set_Equivalence(int* Dset,DE* Eset,int Dsize,int Esize){
	int i;
	for(i=0;i<Esize;i++){
		int root1=find(Dset,Eset[i].de1);
		int root2=find(Dset,Eset[i].de2);
		if(root1!=root2){
			Dset[root1]+=Dset[root2];
			Dset[root2]=root1;
		}
	}
}

void print_Equivalence(int *Dset,int Dsize){
	int i;
	for(i=0;i<Dsize;i++) printf("%d\t",i);
	printf("\n");
	for(i=0;i<Dsize;i++) printf("%d\t",Dset[i]);
	printf("\n");
}

int main(){
	DE* Eset;
	int *Dset,Dsize,Esize,i;
	printf("please input the size of Dset\n");
	scanf("%d",&Dsize);
	Dset=(int *)malloc(Dsize*sizeof(int));
	for(i=0;i<Dsize;i++) Dset[i]=-1;
	printf("please input the size of Eset\n");
	scanf("%d",&Esize);
	Eset=(DE *)malloc(Esize*sizeof(DE));
	printf("please input the Eset\n");
	for(i=0;i<Esize;i++){
		scanf("%d",&Eset[i].de1);
		scanf("%d",&Eset[i].de2);
	}
	set_Equivalence(Dset,Eset,Dsize,Esize);
	print_Equivalence(Dset,Dsize);
	return 0;
}
