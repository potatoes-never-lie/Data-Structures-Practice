#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

class Stack{				
	public:
		Stack(int capacity){
		this->capacity=capacity;
		stack=new int[capacity];
		top_=-1;
		}
		void push(const int& item);
		void pop();
		int size() const;
		int empty() const;
		int& top();
	private: 
		int *stack;
		int top_;  //비어있으면 -1 
		int capacity;
		void ChangeSize(int *&a, const int oldSize, const int newSize);
};

int Stack::size() const{
	return top_+1; 
}

int Stack::empty() const{
	if (size()==0) {return 1;} 
	else {return 0;}
}

void Stack::ChangeSize(int *&a, const int oldSize, const int newSize){
	int *temp=new int[newSize];
	copy(a,a+oldSize,temp);
	delete []a;			//이전 메모리 해제 
	a=temp;
}

void Stack::push(const int& item){
	if (size()==capacity) {ChangeSize(stack, capacity, 2*capacity);}
	stack[++top_]=item;
}

void Stack::pop(){
	if (empty()) {cout<<-1<<endl;}
	else{cout<<stack[top_--]<<endl;}
}

int& Stack::top(){
	if (empty()) {return this->top_;}
	return stack[top_];
}


int main(void){
	int num; 
	cin>>num;  //input the number of commands 
	char command[10]; 
	int item;
	Stack stack_(num);
	for (int i=0; i<num; i++){
		cin>>command;
		if (strcmp(command,"push")==0) {cin>>item; stack_.push(item);}
		else if (strcmp(command,"pop")==0) {stack_.pop();}
		else if (strcmp(command,"size")==0) {cout<<stack_.size()<<endl;}
		else if (strcmp(command,"empty")==0) {cout<<stack_.empty()<<endl;}
		else if (strcmp(command,"top")==0) {cout<<stack_.top()<<endl;}
		else {cout<<"지원하지 않는 연산입니다"<<endl;}
	}
	return 0;
}