#include <iostream> 	
#include <utility>
using namespace std;

template <class K, class E> class BST;

template <class T>
struct TreeNode{
		T data;
		TreeNode<T> *leftChild;
		TreeNode<T> *rightChild;
		TreeNode(T data_=0, TreeNode<T> *left=0, TreeNode<T> *right=0): data(data_), leftChild(left), rightChild(right){}
};

template <class K, class E>
class BST{
	public:
		BST(){ 
			root=0;
		}
		void Insert(const pair<K,E> &thePair); 
		void Inorder();
		void Inorder(TreeNode<pair<K,E> > *currentNode);
		void Delete(const K &key); 
		pair<K,E>* Get(const K& key);
	private:
		TreeNode<pair<K,E> > *root;
}; 

template <class K, class E>
void BST<K,E>::Insert(const pair<K,E>& thePair)
{
   TreeNode<pair<K,E> > *p = root, *pp = 0;
   while (p) {
      pp = p;
      if (thePair.first < p->data.first) p = p->leftChild;
      else if (thePair.first > p->data.first) p = p->rightChild;
      else 
        {p->data.second = thePair.second; return;}
   }
  p = new TreeNode<pair<K,E> > (thePair);
   if (root)  
      if (thePair.first < pp->data.first) pp->leftChild = p;
      else pp->rightChild = p;
   else root = p; 
}

template <class K, class E>
void BST<K,E>::Inorder(){
	Inorder(root);
	cout<<endl;
}

template <class K, class E>
void BST<K,E>::Inorder(TreeNode<pair<K,E> > *currentNode){ //LVR
	if (currentNode){
		Inorder(currentNode->leftChild);
		cout<<currentNode->data.second;
		cout<<" ";
		Inorder(currentNode->rightChild);
	}
}

template <class K, class E>  // Iterative version
pair<K,E>* BST<K,E>::Get(const K& key)
{
  TreeNode<pair<K,E> > *currentNode = root;
  while (currentNode){
    if (key < currentNode->data.first)
      currentNode = currentNode->leftChild;
    else if (key > currentNode->data.first)
      currentNode = currentNode->rightChild;
    else return &currentNode->data;
  }
  throw 0;
}

template <class K, class E>		//K값 존재하지 않을 경우 짜주기.
void BST<K,E>::Delete(const K &key){
	TreeNode<pair<K,E> > *currentNode = root, *follow=0, *max=0, *iterNode=0;
	int mark=0; //1->왼, 2->오
	int count=0;
	while(currentNode){
		if (key<currentNode->data.first) {follow=currentNode;currentNode=currentNode->leftChild; mark=1;}
		else if (key>currentNode->data.first) {follow=currentNode;currentNode=currentNode->rightChild; mark=2;}
		else{
			if (currentNode->leftChild==0 && currentNode->rightChild==0){		//리프 원소일때
				delete currentNode;
				currentNode=0;
				if (mark==1) {follow->leftChild=0;}
				else if (mark==2) {follow->rightChild=0;}

			}
			else if (currentNode->leftChild!=0 && currentNode->rightChild!=0){ //2개의 자식 가질때
				iterNode=currentNode->leftChild;
				while (iterNode){
					max=iterNode;
					iterNode=iterNode->rightChild;
					count++;
				}
				currentNode->data.first=max->data.first;
				currentNode->data.second=max->data.second;
				for (int i=1; i<count; i++){
					currentNode=currentNode->leftChild;
				} 
				delete max; max=0; currentNode->rightChild=0; currentNode=0; //종료
			}
			else{ //1개의 자식 가질때
				if (currentNode->leftChild!=0){		//1개의 자식이 왼쪽일때
					if (mark==1){follow->leftChild=currentNode->leftChild;}
					else if (mark==2){follow->rightChild=currentNode->leftChild;}
				}
				else{	//1개의 자식이 오른쪽일때
					if (mark==1){follow->leftChild=currentNode->rightChild;}
					else if (mark==2){follow->rightChild=currentNode->rightChild;}
				} 
				delete currentNode; currentNode=0;
			} 
		}
	} 
}



int main(void){
	pair <int,int> PAIR1(1,11); pair <int,int> PAIR2(2,22); pair <int,int> PAIR3(3,33); pair <int,int> PAIR4(4,44);
	pair <int,int> PAIR5(5,55); pair <int,int> PAIR6(6,66); pair <int,int> PAIR7(7,77); pair <int,int> PAIR8(8,88); pair <int,int> PAIR9(9,99);
	BST<int,int> TREE;
	TREE.Insert(PAIR8); TREE.Insert(PAIR4); TREE.Insert(PAIR9);TREE.Insert(PAIR2);
	TREE.Insert(PAIR1);TREE.Insert(PAIR6); TREE.Insert(PAIR3);TREE.Insert(PAIR5);TREE.Insert(PAIR7); //1
	TREE.Inorder();  //2
	TREE.Delete(4);	 //3
	TREE.Inorder();	 //4
	TREE.Delete(5);	 //5
	TREE.Inorder();	 //6
	TREE.Delete(2);  //7
	TREE.Inorder();  //8
	try{
	cout<<TREE.Get(2)->second<<endl;}
	catch(int zero){
		cout<<"해당 노드의 second 결과가 없습니다."<<endl;
	}
	try{
	cout<<TREE.Get(9)->second<<endl;}
	catch(int zero){
		cout<<"해당 노드의 second 결과가 없습니다."<<endl;
	} 

	return 0;
}
