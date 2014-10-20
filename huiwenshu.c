#include <stdio.h>
#include <string.h>
#define MaxSize 20
typedef enum {false,true}bool;
int main(){
	char str[MaxSize];
	printf("please input the str(maxsize=%d)\n",MaxSize);
	gets(str);
	int i,n=strlen(str)-1;
	bool judge=true;
	for(i=0;i<=n/2;i++)
		if(str[i]!=str[n-i]){
			judge=false;
			break;
		}
	if(judge) printf("yes\n");
	else printf("no\n");
	return 0;
}
	

