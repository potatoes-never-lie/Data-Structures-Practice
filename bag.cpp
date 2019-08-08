#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

class Bizcard{
	private: 
		char *name;
		char *phone;
	public:
		Bizcard(){
			name=NULL;
			phone=NULL;
		}
		Bizcard(const char *name, const char *phone){
			this->name=new char[strlen(name)+1];
			strcpy(this->name,name);
			this->phone=new char[strlen(phone)+1];
			strcpy(this->phone,phone);
		}
		Bizcard(const Bizcard& copy){
			name=new char[strlen(copy.name)+1];
			strcpy(name,copy.name);
			phone=new char[strlen(copy.phone)+1];
			strcpy(phone,copy.phone);
	   	}
	   	Bizcard& operator=(const Bizcard& ref){
	   		delete []name;
	   		delete []phone;
	   		name=new char[strlen(ref.name)+1];
	   		strcpy(name,ref.name);
	   		phone=new char[strlen(ref.phone)+1];
	   		strcpy(phone,ref.phone);
	   		return *this;
	   	}
	   	void ShowInfo() const{
	   		cout<<"이름: "<<name<<endl;
	   		cout<<"전화번호: "<<phone<<endl;
	   	}
	   	~Bizcard(){
	   		delete []name;
	   		delete []phone;
			name=NULL;
			phone=NULL;
	   	}
};

template <class T>
class Bag{
	public:
  		Bag (int bagCapacity = 3);
  		~Bag(); 
  		void ChangeSize1D(T*&a, const int oldSize, const int newSize);
  		int Size() const;  
  		bool IsEmpty() const; 
  		T& Element() const;  
  		void Push(const T&); 
 		void Pop(); 
 	private:
 		T *array;
  		int capacity; 
  		int top; 
 };


template <class T>
Bag<T>::Bag (int bagCapacity): capacity(bagCapacity) {
  if (capacity < 1) throw "Capacity must be > 0";
  array = new T[capacity];
  top = -1;
}

template <class T>
Bag<T>::~Bag() {delete [] array;}

template <class T>
void Bag<T>::ChangeSize1D(T*&a, const int oldSize, const int newSize){
  if (newSize < 0) throw "New length must be >= 0";
  T* temp = new T[newSize];                                  
  int number = min(oldSize, newSize); 
  copy(a, a + number, temp);
  delete [] a;                             
  a = temp;
}

template <class T>
int Bag<T>::Size() const{		
		return top+1;
}

template <class T>
bool Bag<T>::IsEmpty() const{
	if (Size()==0)
		return true;
	else
		return false;
}

template <class T>
T& Bag<T>::Element() const{				
	if (IsEmpty())
		throw "Bag is Empty";
	srand((unsigned int)time(NULL));
	return array[rand()%(top+1)]; 
}

template <class T>
void Bag<T>::Push(const T& x) {
  if (capacity ==top+1) 
  {
  	try{
    	ChangeSize1D(array, capacity, 2 * capacity);
    	capacity *=2;
    }
    catch(const char *msg){
    	cout<<msg<<endl;
    }
  }
  array[++top] = x;			
}

template <class T>
void Bag<T>::Pop() {							
  if (IsEmpty()) throw "Bag is empty, cannot delete";
  srand((unsigned int)time(NULL));
  int deletePos = rand()%(top+1);
  copy(array+deletePos+1,array+top+1,array+deletePos); 
  array[top--].~T();
}

int main(void){
	Bag<Bizcard> bag1;
	Bizcard show;
	Bizcard b1("징징이","010-8872-7535");	Bizcard b2("스폰지밥","010-3533-7536"); Bizcard b3("뚱이","010-1234-5678");
	Bizcard b4("레몬그랩","010-8873-7535");	Bizcard b5("다람이","010-3534-7536"); Bizcard b6("밍밍","010-1235-5678"); Bizcard b7("김땡땡","010-1111-1111");

	cout<<"빈 Bag에 대한 연산"<<endl;
	cout<<"Size(): ";
	cout<<bag1.Size()<<endl;
	cout<<"IsEmpty(): ";
	cout<<bag1.IsEmpty()<<endl;
	cout<<"Element(): ";
	try{
		bag1.Element();
	}
	catch(const char *msg){
		cout<<msg<<endl;
	}
	
	bag1.Push(b1); bag1.Push(b2); bag1.Push(b3);
	cout<<endl;
	cout<<"Push 연산 3번 수행 결과"<<endl;
	cout<<"Size(): ";
	cout<<bag1.Size()<<endl;
	cout<<"IsEmpty(): ";
	cout<<bag1.IsEmpty()<<endl;
	cout<<"Element(): ";
	show=bag1.Element(); show.ShowInfo();
	cout<<endl;

	cout<<endl;
	cout<<"Push 연산 4번 수행 결과"<<endl;
	bag1.Push(b4); bag1.Push(b5); bag1.Push(b6); bag1.Push(b7);
	cout<<"Size(): ";
	cout<<bag1.Size()<<endl;
	cout<<"IsEmpty(): ";
	cout<<bag1.IsEmpty()<<endl;
	cout<<"Element(): ";
	show=bag1.Element(); show.ShowInfo();

	cout<<endl;
	cout<<"Pop연산 2번 수행 결과"<<endl;
	bag1.Pop(); bag1.Pop();
	cout<<"Size(): ";
	cout<<bag1.Size()<<endl;
	cout<<"IsEmpty(): ";
	cout<<bag1.IsEmpty()<<endl;
	cout<<"Element(): ";
	show=bag1.Element(); show.ShowInfo(); 
	return 0;
}
