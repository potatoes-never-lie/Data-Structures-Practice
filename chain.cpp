#include <iostream> 	
#include <numeric>
using namespace std;
template <class T> class Chain; 

template <class T>
class ChainNode {					
friend class Chain<T>;		
public:
	ChainNode(){
		link=0;
	}
 	ChainNode(const T& data, ChainNode<T> *link=0){
 		this->data=data;
 		this->link=link;
 	}					
private:
  T data;
  ChainNode<T> *link;
};

template <class T>
class Chain {
public: //반복자 정의
class ChainIterator {
	public:
  	ChainIterator(ChainNode<T>* startNode = 0)
    {current = startNode;}
  	T& operator*() const {return current->data;}
  	T* operator->() const {return &current->data;}
  	ChainIterator& operator++()   
    	{current = current->link; return *this;}
  	ChainIterator operator++(int) 
    {
      	ChainIterator old = *this;
      	current = current->link;
      	return old;
    }
  	bool operator!=(const ChainIterator right) const
    	{return current != right.current;}
 	bool operator==(const ChainIterator right) const
    	{return current == right.current;}
	private:
    	ChainNode<T>* current;
};

public:
  Chain(){
  	first=0; last=0; 
  }
  ~Chain(){
  	ChainNode<T> *current=first;
  	ChainNode<T> *temp=0;
  	while(current){
  		temp=current->link;
  		delete current;
  		current=temp;
  	}
  }
  ChainIterator begin(){return ChainIterator(first);}
  ChainIterator end(){return ChainIterator(0);}
  void InsertFront(const T& data);
  void InsertBack(const T& data);
  T& Front(){						
	if (first){
  	return first->data;}
  }
  T& Back(){
	if (last){
  	return last->data;}
  }
  T& Get(int i);
  void RemoveFront();
  void RemoveBack(); 
  void Inserti(int i, const T& data);
  void Removei(int i);
  void printNode(){
  	ChainIterator yi;
	for (yi=begin();yi!=end();yi++){cout<<*yi<<' ';} cout<<endl;
  }

private:
  ChainNode<T> *first;
  ChainNode<T> *last;
}; 

template <class T>
void Chain<T>::InsertFront(const T& data){
	if(first)
		first=new ChainNode<T>(data,first);
	else
		first=last=new ChainNode<T>(data);
}

template <class T>
void Chain<T>::InsertBack(const T& data){		
	if(first){
		last->link=new ChainNode<T>(data);
		last=last->link;
	}
	else
		first=last=new ChainNode<T>(data);
}

template <class T>
T& Chain<T>::Get(int i){
	if (first){
		ChainNode<T> *current=first;
		for (int count=0;count<i;count++){
			current=current->link;
		}
		return current->data;
	} 
}

template <class T>
void Chain<T>::RemoveFront(){
	if (first){
		ChainNode<T> *temp=first;
		first=first->link;
		if (temp==last)
			last=0;
		delete temp;
	}
}

template <class T>		 
void Chain<T>::RemoveBack(){	
	if (last){
		ChainNode<T> *before=first;
		while ((before->link)!=last){
			before=before->link;
		}
		ChainNode<T> *del=last;
		last=before;
		delete del;
		before->link=0;
	} 
}

template <class T>
void Chain<T>::Inserti(int i,const T& data){					
	if (first){
		ChainNode<T> *current=first;
		for (int count=0;count<i;count++){
			current=current->link;
		}
		ChainNode<T> *insertNode=new ChainNode<T>(data,current->link);
		current->link=insertNode;
		if (last==current)
			last=current->link;
	}
}

template <class T>					
void Chain<T>::Removei(int i){
	if(first){
		ChainNode<T> *current=first;
		ChainNode<T> *before=0;
		for (int count=0;count<i;count++){
			before=current;
			current=current->link;
		}
		if (first==current)
			RemoveFront();
		else if (last==current)
			RemoveBack();
		else{										
			ChainNode<T> *deleteNode=current;
			before->link=current->link;
			delete deleteNode;
		}
	}
}

class Number{
private:
	int num;
public:
	Number(int n=0): num(n){
		//cout<<"Number(int=0)"<<endl;
	}
	Number& operator=(const Number& ref){
		//cout<<"operator=()"<<endl;
		num=ref.num;
		return *this;
	}
	operator int(){
		return num;
	}
	void ShowNumber(){cout<<num<<endl;}
};

int main(void){
	Chain<Number> chain; 
	cout<<"1) 1부터 9까지의 정수를 갖는 노드 추가"<<endl;
	for (int i=1;i<10;i++){
		chain.InsertBack(i);
	}
	cout<<"2) 체인의 각 노드 순차적으로 출력"<<endl;
	chain.printNode();
	cout<<"3) 0을 맨 앞에 삽입"<<endl;
	chain.InsertFront(0);
	cout<<"4) 전체 노드의 값과 총합 출력"<<endl;
	chain.printNode();
	cout<<accumulate(chain.begin(), chain.end(), 0)<<endl;
	cout<<"5) 10을 맨 뒤에 삽입"<<endl;
	chain.InsertBack(10);
	cout<<"6) 전체 노드의 값과 총합 출력"<<endl;
	chain.printNode();
	cout<<accumulate(chain.begin(), chain.end(), 0)<<endl;
	cout<<"7) Front 호출"<<endl;
	chain.Front().ShowNumber();
	cout<<"8) Back 호출"<<endl;
	chain.Back().ShowNumber();
	cout<<"9) Get(2) 호출"<<endl;
	chain.Get(2).ShowNumber();
	cout<<"10) 맨 앞에 있는 0 삭제"<<endl;
	chain.RemoveFront();
	cout<<"11) 전체 노드의 값과 총합 출력"<<endl;
	chain.printNode();
	cout<<accumulate(chain.begin(), chain.end(), 0)<<endl;
	cout<<"12) 맨 뒤에 있는 10 삭제"<<endl;
	chain.RemoveBack();
	cout<<"13) 전체 노드의 값과 총합 출력"<<endl;
	chain.printNode();
	cout<<accumulate(chain.begin(), chain.end(), 0)<<endl;
	cout<<"14) 3과 4 노드 사이에 100을 삽입한다.(2번째 원소 뒤에 삽입)"<<endl;
	chain.Inserti(2,100);
	cout<<"15) 전체 노드의 값과 총합 출력"<<endl;
	chain.printNode();
	cout<<accumulate(chain.begin(), chain.end(), 0)<<endl;
	cout<<"16) 6을 삭제(6번째 원소 삭제)"<<endl;
	chain.Removei(6);
	cout<<"17) 전체 노드의 값과 총합 출력"<<endl;
	chain.printNode();
	cout<<accumulate(chain.begin(), chain.end(), 0)<<endl;
	return 0;
}


