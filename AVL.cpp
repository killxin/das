#include <iostream>
#include <assert.h>
using namespace std;
template <typename E>
struct AVLNode {
	E data;
	int bf;
	AVLNode<E> *left,*right;
};
template <typename E>
class AVL {
public:
	AVL(){ root=NULL; }
	void Insert(E d){ Insert(d,root); }
	void InOrder(){ InOrder(root); }
	void PreOrder(){ PreOrder(root); }
private:
	AVLNode<E>* root;
	void RotateL(AVLNode<E>* &p);
	void RotateR(AVLNode<E>* &p);
	void RotateLR(AVLNode<E>* &p);
	void RotateRL(AVLNode<E>* &p);
	void Insert(E d,AVLNode<E>* &p);
	int Height(AVLNode<E>* p);
	int Bf(AVLNode<E>* p);
	void SetNode(E d,AVLNode<E>* &p);
	void InOrder(AVLNode<E>* p);
	void PreOrder(AVLNode<E>* p);
};
template <typename E>
void AVL<E>::RotateL(AVLNode<E>* &p) {
	AVLNode<E> *subL=p;
	p=subL->right;
	subL->right=p->left;
	p->left=subL ;
	p->bf=Bf(p);
	subL->bf=Bf(subL);
};
template <typename E>
void AVL<E>::RotateR(AVLNode<E>* &p) {
	AVLNode<E> *subR=p;
	p=subR->left;
	subR->left=p->right;
	p->right=subR;
	p->bf=Bf(p);
	subR->bf=Bf(subR);
};
template <typename E>
void AVL<E>::RotateLR(AVLNode<E>* &p) {
	RotateL(p->left);
	RotateR(p);
};
template <typename E>
void AVL<E>::RotateRL(AVLNode<E>* &p) {
	RotateR(p->right);
	RotateL(p);	
};
template <typename E>
int AVL<E>::Height(AVLNode<E>* p) {
	int ldep,rdep,dep=0;
	if(p!=NULL) {
		ldep=Height(p->left);
		rdep=Height(p->right);
		dep=(ldep>rdep? ldep : rdep);
		dep++;
	}
	return dep;
};
template <typename E>
int AVL<E>::Bf(AVLNode<E>* p) {
	if(p==NULL) return 0;
	else return Height(p->right)-Height(p->left);
};
template <typename E>
void AVL<E>::SetNode(E d,AVLNode<E>* &p) {
	p=new AVLNode<E>;
	assert(p);
	p->data=d;
	p->left=NULL;
	p->right=NULL;
	p->bf=0;
};
template <typename E>
void AVL<E>::Insert(E d,AVLNode<E>* &p) {
	if(!p) { SetNode(d,p);return; }
	if(d<p->data){
		Insert(d,p->left);
		if(Bf(p)==-2)
			if(d<p->left->data) RotateR(p);
			else RotateLR(p);
	}
	else if(d>p->data) {
		Insert(d,p->right);
		if(Bf(p)==2)
			if(d>p->right->data) RotateL(p);
			else RotateRL(p);
	}
	else cout<<d<<" exists"<<endl;
	p->bf=Bf(p);
};
template <typename E>
void AVL<E>::InOrder(AVLNode<E> *p) {
	if(p!=NULL){
		InOrder(p->left);
		cout<<p->data;
		cout<<"("<<p->bf<<")"<<" ";
		InOrder(p->right);
	}
};
template <typename E>
void AVL<E>::PreOrder(AVLNode<E> *p) {
	if(p!=NULL){
		cout<<p->data<<" ";
		PreOrder(p->left);
		PreOrder(p->right);
	}
};

int main() {
	AVL<int> A;
	int n=0;
	cout<<"please input elements"<<endl;
	cin>>n;
	while(n!=-1){
		A.Insert(n);
		cin>>n;
	}
	A.InOrder();
	cout<<endl;
	A.PreOrder();
	cout<<endl;
	return 0;
}

