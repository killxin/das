#include <iostream>
#include <assert.h>
using namespace std;
template <class E>
struct BSTNode{
	E data;
	BSTNode<E> *left,*right;
};
template <typename E>
class BST {
public:
	BST(E* a,int n);
	void Insert(E d,BSTNode<E>* &p);
	void InOrder(E* a,int &i,BSTNode<E>* p);
	void InOrder(E* a,int &i) { InOrder(a,i,root); }
private:
	BSTNode<E>* root;
};
template <typename E>
BST<E>::BST(E* a,int n) {
	int i=0;
	root=NULL;
	for(;i<n;i++) Insert(a[i],root);
};
template <typename E>
void BST<E>::Insert(E d,BSTNode<E>* &p) {
	if(p==NULL) {
		p=new BSTNode<E>;
		assert(p);
		p->data=d;
		p->left=NULL;
		p->right=NULL;
		return;
	}
	else if(d<p->data)  Insert(d,p->left);
		else if(d>p->data) Insert(d,p->right);
			else { cout<<d<<" exits"<<endl;return; }
};
template <typename E>
void BST<E>::InOrder(E* a,int &i,BSTNode<E>* p) {
	if(p!=NULL) {
		InOrder(a,i,p->left);
		a[i]=p->data;
		i++;
		InOrder(a,i,p->right);
	}
};

int main() {
	int n;
	cout<<"please input the number of elements"<<endl;
	cin>>n;
	int *a=new int[n];
	cout<<"please input the elements"<<endl;
	int i=0;
	for(;i<n;i++) cin>>a[i];
	BST<int> b(a,n);
	i=0;
	b.InOrder(a,i);
	for(i=0;i<n;i++) cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}

