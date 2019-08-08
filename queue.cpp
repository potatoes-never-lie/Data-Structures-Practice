#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

class Queue{
private:
	int* queue;
	int front, rear, capacity;
public:
	Queue(int queueCapacity): capacity(queueCapacity){
		queue=new int[capacity];
		front=rear=0;
	}
	void push(const int& x);
	void pop();
	int size();
	int empty();
	int Front();
	int Back();
};

void Queue::push(const int &x){
	if ((rear+1)%capacity==front) {			//change the size if queue was full
		int *newQueue=new int[capacity*2];
		copy(queue+front+1, queue+capacity, newQueue);	
		copy(queue, queue+rear+1, newQueue+capacity-front-1);
		int prevSize=size();
		rear=prevSize-1; front=(capacity*2)-1; 
		queue=newQueue; capacity=capacity*2;  
	}
	rear=(rear+1)%capacity;
	queue[rear]=x;
}

void Queue::pop(){
	if (empty()) {cout<<-1<<endl;}
	else{ cout<<Front()<<endl;
	front=(front+1)%capacity; }
}

int Queue::size(){
	int temp_front=front; int count=0;
	if (empty()) {return 0;}
	else{
		while (((temp_front)%capacity)!=rear){
			temp_front++;
			count++; 
		}
		return count;
	}
}

int Queue::empty(){
	if (front==rear){return 1;}
	else{return 0;}
}

int Queue::Front(){
	if (empty()) {return -1;}
	else {return queue[(front+1)%capacity];}
}

int Queue::Back(){
	if (empty()) {return -1;}
	else {return queue[rear];}
}

int main(void){
	int num; int item;
	cin>>num;
	char command[10];
	Queue queue(3);
	for (int i=0; i<num; i++){
		cin>>command;
		if (strcmp(command,"push")==0) {cin>>item; queue.push(item);}
		else if (strcmp(command,"pop")==0) {queue.pop();}
		else if (strcmp(command,"size")==0) {cout<<queue.size()<<endl;}
		else if (strcmp(command,"empty")==0) {cout<<queue.empty()<<endl;}
		else if (strcmp(command,"front")==0) {cout<<queue.Front()<<endl;}
		else if (strcmp(command,"back")==0) {cout<<queue.Back()<<endl;}
	}
	return 0;
}


/* baekjoon #10845 */
