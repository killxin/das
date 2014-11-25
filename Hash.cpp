#include <iostream>
#include <assert.h>
using namespace std;
const int defaultSize=100;
template <typename E, typename K>
struct ChainNode {
	K key;
	E data;
	ChainNode<E,K> *link;
};
template <typename E,typename K>
class HashTable {
public:
	HashTable(int d,int sz=defaultSize);
	~HashTable(){delete []ht;}
	bool Search(const K k1,E& e1);
	bool Insert(const K k1,const E el);
	bool Change(const K k1,const E e1);
	bool Remove(const K k1,E& e1);
	void Print();
private:
	int divisor;
	int TableSize;
	ChainNode<E,K> **ht;
	ChainNode<E,K> *FindPos(const K k1);
};
template <typename E,typename K>
HashTable<E,K>::HashTable(int d,int sz){
	divisor=d;
	TableSize=sz;
	ht=new ChainNode<E,K> *[sz];
	assert(ht!=NULL);
};
template <typename E,typename K>
ChainNode<E,K> *HashTable<E,K>::FindPos(const K k1) {
	int j=k1%divisor;
	ChainNode<E,K> *p=ht[j];
	while (p!=NULL&&p->key!=k1)p=p->link;
	return p;
};
template <typename E,typename K>
bool HashTable<E,K>::Search(const K k1,E &e1) {
	ChainNode<E,K> *p=FindPos(k1);
	if(p) {e1=p->data;return true;}
	else return false;
};
template <typename E,typename K>
bool HashTable<E,K>::Insert(const K k1,const E e1) {
	int j=k1%divisor;
	ChainNode<E,K> *p=ht[j];
	ChainNode<E,K> *q=new ChainNode<E,K>;
	if(!q) return false;
	q->key=k1;
	q->data=e1;
	q->link=NULL;
	if (p) {
		while (p->link!=NULL) p=p->link;
		p->link=q;
	}
	else ht[j]=q;
	return true;
};
template <typename E,typename K>
bool HashTable<E,K>::Change(const K k1,const E e1) {
	ChainNode<E,K>* p=FindPos(k1);
	if(p) {
		p->data=e1;
		return true;
	}
	else return false;
};
template <typename E,typename K>
bool HashTable<E,K>::Remove(const K k1,E& e1) {
	int j=k1%divisor;
	ChainNode<E,K> *p=ht[j];
	if(p){
		while (p->link!=NULL&&p->link->key!=k1)p=p->link;
		if(p->link) {
			ChainNode<E,K> *q=p->link;
			p->link=q->link;
			e1=q->data;
			delete q;
			return true;
		}
	}
	return false;
};
template <typename E,typename K>
void HashTable<E,K>::Print() {
	for (int i=0;i<divisor;i++){
		ChainNode<E,K> *p=ht[i];
		cout<<i<<':';
		while(p!=NULL) {
			cout<<'<'<<p->key<<','<<p->data<<"> ";
			p=p->link;
		}
		cout<<endl;
	}
};
int main() {
	int d,sz,key,data;
	cout<<"please input the divisor and the number of elements"<<endl;
	cin>>d>>sz;
	HashTable<int,int> hash(d,d);
	cout<<"please input the ChainNode"<<endl;
	//assum  data == key
	cin>>key;
	data=key;
	for(int i=0;i<sz-1;i++){
		if(hash.Insert(key,data)) { cin>>key;data=key; }
		else { cout<<"error"<<endl;break; }
	}
	if(!hash.Insert(key,data)) cout<<"error"<<endl;
	while (1){
		int index,key,data;
		cout<<"what to do next?"<<endl;
		cout<<"(1) Search,(2) Insert,(3) Change,(4) Remove,(5) Print,(0) Exit"<<endl;
		cin>>index;
		if(!index) break;
		else 
		switch(index){
			case 1:
				cout<<"please input the key"<<endl;
				cin>>key;
				if(hash.Search(key,data)) cout<<data<<endl;
				else cout<<"can't find"<<endl;
				break;
			case 2:
				cout<<"please input the key and data"<<endl;
				cin>>key>>data;
				if(hash.Insert(key,data)) cout<<"success"<<endl;
				else cout<<"fail"<<endl;
				break;
			case 3:
				cout<<"please input the key and data"<<endl;
				cin>>key>>data;
				if(hash.Change(key,data)) cout<<"success"<<endl;
				else cout<<"fail"<<endl;
				break;
			case 4:
				cout<<"please input the key"<<endl;
				cin>>key;
				if(hash.Remove(key,data)) cout<<data<<endl;
				else cout<<"can't find"<<endl;
				break;
			case 5:
				hash.Print();
				break;
			default: break;
		}
	}
	return 0;
}
