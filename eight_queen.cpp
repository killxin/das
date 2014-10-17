#include <stdio.h>
int a[8][8];
int count=0;
void print_eightqueen(int a[][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(a[i][j]==1)
				printf("& ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
	count++;
}
void set_judge(int n,int i){
	for(int j=n+1;j<8;j++){
		if(a[j][i]==0)
			a[j][i]=-n-1;
	}
	for(int p=n+1,q=i+1;p<8&&q<8;p++,q++){
		if(a[p][q]==0)
			a[p][q]=-n-1;
	}
	for(int p=n+1,q=i-1;p<8&&q>=0;p++,q--){
		if(a[p][q]==0)
			a[p][q]=-n-1;
	}
}
void delete_judge(int n,int i){
	for(int j=n+1;j<8;j++){
		if(a[j][i]==(-n-1))
			a[j][i]=0;
	}
	for(int p=n+1,q=i+1;p<8&&q<8;p++,q++){
		if(a[p][q]==(-n-1))
			a[p][q]=0;
	}
	for(int p=n+1,q=i-1;p<8&&q>=0;p++,q--){
		if(a[p][q]==(-n-1))
			a[p][q]=0;
	}
}
void eightqueen(int a[][8],int n){
	if(n==7){
		for (int i=0;i<8;i++)
			if(a[n][i]==0){
				a[n][i]=1;
				print_eightqueen(a);
				a[n][i]=0;
				return;
			}
	}
	else{
		for(int i=0;i<8;i++){
			if(a[n][i]==0){
				a[n][i]=1;
				set_judge(n,i);
			    eightqueen(a,n+1);
			    delete_judge(n,i);
			    a[n][i]=0;
			}
		}
	}
}
int main(){
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			a[i][j]=0;
	eightqueen(a,0);
	printf("%d\n",count);
	return 0;
}
		


