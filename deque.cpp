#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class Node{
private:
	T data;
	Node<T>* prev;
	Node<T>* next;
public:
	Node(T data, Node* p=0, Node* n=0) {this->data=data; prev=p; next=n;}
	Node<T>* getPrev() const{return this->prev;}
	Node<T>* getNext() const{return this->next;}
	T& getData() {return data;}
	void setPrev(Node *prev){this->prev=prev;}
	void setNext(Node *next){this->next=next;}
};

template <typename T>
class Deque{
private:
	Node<T>* front;
	Node<T>* back;
public:
	Deque() {front=0; back=0;}
	~Deque(){
		Node<T> *temp=0;
		while(!empty()){
			temp=front;
			front=front->getNext();
			delete temp;
		}
	}
	void push_front(T data){
		if (empty()){
			front=new Node<T>(data);
			back=front;
		}
		else{
			front->setPrev(new Node<T>(data));
			front->getPrev()->setNext(front);
			front=front->getPrev();
		}
	}
	void push_back(T data){
		if (empty()){
			back=new Node<T>(data);
			front=back;
		}
		else{
			back->setNext(new Node<T>(data));
			back->getNext()->setPrev(back);
			back=back->getNext();
		}
	}
	void pop_front(){
		Node<T> *del;
		if (empty()) {cout<<-1<<endl;}
		else{
			cout<<front_()<<endl;
			del=front;
			if (front==back){
				front=back=0;
				delete del; 
			}
			else{
				front=front->getNext();
				front->setPrev(0);
				delete del;
			}
		}
	}
	void pop_back(){
		Node<T> *del;
		if (empty()) {cout<<-1<<endl;}
		else{
			cout<<back_()<<endl;
			del=back;
			if (front==back){
				back=front=0;
				delete del;
			}
			else{
				back=back->getPrev();
				back->setNext(0);
				delete del;
			}
		}
	}
	T front_() {
		if (empty()) {return -1;}
		return front->getData();
	}
	T back_() {
		if (empty()) {return -1;}
		return back->getData();
	}
	void size(){
		int count=0;
		Node<T>* temp=front;
		while(temp!=0){
			count++;
			temp=temp->getNext();
		}
		cout<<count<<endl;
	}
	int empty(){
		if (front==NULL) {return 1;}
		else {return 0;}
	}
};

int main(void){
	int num,item; cin>>num;
	char command[50];
	Deque<int> deque;
	for (int i=0; i<num; i++){
		cin>>command; 
		if (strcmp(command,"push_front")==0) {cin>>item; deque.push_front(item);}
		else if (strcmp(command,"push_back")==0) {cin>>item; deque.push_back(item);}
		else if (strcmp(command,"pop_front")==0) {deque.pop_front();}
		else if (strcmp(command,"pop_back")==0) {deque.pop_back();}
		else if (strcmp(command,"size")==0) {deque.size();}
		else if (strcmp(command,"empty")==0) {cout<<deque.empty()<<endl;}
		else if (strcmp(command,"front")==0) {cout<<deque.front_()<<endl;}
		else if (strcmp(command,"back")==0) {cout<<deque.back_()<<endl;}
	}
	return 0;
}

/* baekjoon 10866*/