#include <stdio.h>
#define MaxSize 20
int main(){
	char str1[MaxSize],str2[MaxSize];
	printf("please input string1(maxsize=%d)\n",MaxSize);
	gets(str1);
	printf("please input string2(maxsize=%d)\n",MaxSize);
	gets(str2);
	int len=0,op=0;
        int i,j,k;
	for(i=0;str1[i]!='\0';i++)
		for(j=0;str2[j]!='\0';j++){
			if(str2[j]==str1[i]){
				for(k=1;str2[j+k]==str1[i+k];k++)
					if(str1[i+k]=='\0') break;
				if(len<k){ 
					len=k;
					op=i;
				}
			}
		}
	printf("the max_common_str is ");
	for(i=0;i<len;i++) printf("%c",str1[op+i]);
	printf(",the length is %d\n",len);
	return 0;
}




