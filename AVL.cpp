#include <iostream>
#include <assert.h>
using namespace std;
template <typename E>
struct AVLNode {
	E data;
	int bf;
	AVLNode<E> *left,*right,*parent;
};
template <typename E>
class AVL {
public:
	AVL(){ root=NULL; }
	void Insert(E d);
	void InOrder(AVLNode<E>* p);
	void PreOrder(AVLNode<E>* p);
	void InOrder(){ InOrder(root); }
	void PreOrder(){ PreOrder(root); }
private:
	AVLNode<E>* root;
	void RotateL(AVLNode<E>* p);
	void RotateR(AVLNode<E>* p);
	void RotateLR(AVLNode<E>* p);
	void RotateRL(AVLNode<E>* p);
	int Height(AVLNode<E>* p);
	int Bf(AVLNode<E>* p);
	void SetNode(E d,AVLNode<E>* &p);
};
template <typename E>
void AVL<E>::RotateL(AVLNode<E>* p) {
	AVLNode<E> *subL=p;
	AVLNode<E> *par=subL->parent;
	p=subL->right;
	subL->right=p->left;
	p->left->parent=subL;
	p->left=subL;
	subL->parent=p;
	p->parent=par;
	p->bf=subL->bf=0;
};
template <typename E>
void AVL<E>::RotateR(AVLNode<E>* p) {
	AVLNode<E> *subR=p;
	AVLNode<E> *par=subR->parent;
	p=subR->left;
	subR->left=p->right;
	p->right->parent=subR;
	p->right=subR;
	subR->parent=p;
	p->parent=par;
	p->bf=subR->bf=0;
};
template <typename E>
void AVL<E>::RotateLR(AVLNode<E>* p) {
	AVLNode<E> *subR=p,*subL=subR->left;
	AVLNode<E> *par=subR->parent;
	p=subL->right;
	subL->right=p->left;
	p->left->parent=subL;
	p->left=subL;
	subL->parent=p;
	if(p->bf<=0)subL->bf=0;
	else subL->bf=-1;
	subR->left=p->right;
	p->right->parent=subR;
	p->right=subR;
	subR->parent=p;
	if(p->bf==-1) subR->bf=1;
	else subR->bf=0;
	p->parent=par;
	p->bf=0;
};
template <typename E>
void AVL<E>::RotateRL(AVLNode<E>* p) {
	AVLNode<E> *subL=p,*subR=subL->left;
	AVLNode<E> *par=subL->parent;
	p=subR->left;
	subR->left=p->right;
	p->right->parent=subR;
	p->right=subR;
	subR->parent=p;
	if(p->bf>=0)subR->bf=0;
	else subR->bf=1;
	subL->right=p->left;
	p->left->parent=subL;
	p->left=subL;
	subL->parent=p;
	if(p->bf==1) subR->bf=-1;
	else subR->bf=0;
	p->parent=par;
	p->bf=0;
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
	p->parent=NULL;
	p->bf=0;
};
template <typename E>
void AVL<E>::Insert(E d) {
	AVLNode<E>* p=root;
	if(root==NULL) { SetNode(d,root);p=root; }
	else {
		while(p!=NULL) {
			if(d<p->data) {
				if(p->left==NULL) {
					SetNode(d,p->left);
					p->left->parent=p;
					break;
				}
				else p=p->left;
			}
			else if(d>p->data) {
				if(p->right==NULL) {
					SetNode(d,p->right);
					p->right->parent=p;
					break;
				}
				else p=p->right;
			}
			else { cout<<d<<" exists"<<endl; break; }
		}
	}
	while(p!=NULL) {
		int b=Bf(p);
		if(b==0) return;
		else if(b==1||b==-1) { p=p->parent;continue; }
		else if(b==2) {
			int d=Bf(p->right);
			bool tag;
			AVLNode<E>* par=p->parent;
			tag=(par->left==p ? 0 : 1);
			if(d==1)RotateL(p);
			else RotateLR(p);
			if(tag) par->right=p;
			else par->left=p;
		}
		else {
			int d=Bf(p->left);
			bool tag;
			AVLNode<E>* par=p->parent;
			tag=(par->left==p ? 0 : 1);
			if(d==1)RotateR(p);
			else RotateRL(p);
			if(tag) par->right=p;
			else par->left=p;
		}
	}
};
template <typename E>
void AVL<E>::InOrder(AVLNode<E> *p) {
	if(p!=NULL){
		InOrder(p->left);
		cout<<p->data<<" ";
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

