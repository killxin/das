#include <iostream>
#include <assert.h>
using namespace std;
#define MAXSIZE 10
int *push_array;
int *pop_array;
int push_top;
int m;
class SeqStack{
public:
	SeqStack(){
		maxSize=MAXSIZE;
		elements=new int[maxSize];
		assert(elements!=NULL);
	}
	bool getTop(int &x){
		if(IsEmpty())return false;
		x=elements[top];
		return true;
	}
	bool Push(const int &x){
		if(top==maxSize-1)return false;
		elements[++top]=x;
		return true;
	}
	bool Pop(int &x){
		if(IsEmpty()==true)return false;
		x=elements[top--];
		return true;
	}
	bool IsEmpty(){return (top==-1)?true:false;}
	void MakeEmpty(){top=-1;}
private:
	int *elements;
	int top;
	int maxSize;
}stack;
bool judge(int ipop,int n){
	int stack_top;
	bool top_state=stack.getTop(stack_top);
	if(ipop==n-1){
		if(top_state){
			if(stack_top==pop_array[ipop]){
				cout<<"pop"<<endl;
				return true;
			}
			else return false;
		}
		else{
			if(push_array[push_top]==pop_array[ipop]){
				cout<<"push "<<push_array[push_top]<<endl;
				cout<<"pop"<<endl;
				return true;
			}
			else return false;
		}
	}
	if(top_state==true&&(stack_top==pop_array[ipop])){
		int k;
		stack.Pop(k);
		cout<<"pop"<<endl;
		if (judge(ipop+1,n))return true;
	}
	for(int ipush=push_top;ipush<n;ipush++){
		if(push_array[ipush]==pop_array[ipop]){
			for(int i=push_top;i<ipush;i++){
				stack.Push(push_array[i]);
				cout<<"push "<<push_array[i]<<endl;
			}
			cout<<"push "<<push_array[ipush]<<endl;
			cout<<"pop"<<endl;
			int r_push_top=push_top; 
			push_top=ipush+1;
			if(judge(ipop+1,n))return true;
			else{
				cout<<"error"<<endl;
				push_top=r_push_top;
				int k;
				for(int i=push_top;i<ipush;i++)
					stack.Pop(k);
			}
		}
	}
	return false;
}
int main(){
	int n;
	cout<<"please input the number of your inputs(<10,input 0 to exit)"<<endl;
	cin>>n;
	while (n!=0){
		push_array=new int[n];
	    pop_array=new int[n];
	    cout<<"please input the push line"<<endl;
	    for(int i=0;i<n;i++)cin>>push_array[i];
	    cout<<"please input the pop line"<<endl;
	    for(int i=0;i<n;i++)cin>>pop_array[i];
	    push_top=0;
	    stack.MakeEmpty();
	    if(judge(0,n))cout<<"success"<<endl;
	    else cout<<"fail"<<endl;
	    cout<<"please input the number of your inputs(<10,input 0 to exit)"<<endl;
	    cin>>n;
	}
	return 0;
}

