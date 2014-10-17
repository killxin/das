#include <iostream>
using namespace std;
int stair_1(int n){
	if(n==1) return 1;
    if(n==2) return 2;
	else return stair_1(n-1)+stair_1(n-2);
}
int stair_2(int n){
	int i=1,j=2;
	for(int k=1;k<n;k++){
		j=i+j;
		i=j-i;
	}
	return i;
}
int main(){
	int n;
	cout<<"please input the stairs' number"<<endl;
	cin>>n;
	cout<<stair_1(n)<<endl<<stair_2(n)<<endl;
	return 0;
}
