#include<iostream>
#include<vector>
using namespace std;


class Heap{
  
    private:
        int size;
        vector<int> *heap; 
    Heap(Heap &h);
    Heap operator =(Heap &h);
    void swap(int i ,int j){
    int temp = heap->at(i);
    heap->at(i)= heap->at(j);
    heap->at(j) = temp;
    }
    public :

    Heap(int s){
        size = s;
        heap = new vector<int>(size);
    }

    Heap(){
        size = 0;
        heap = new vector<int>;
    }
   int getsize(){
       return size;
   }
   int insert(int val);
   int getmax();
   int makeHeap();
   void heapify(int i);
   int printall(){
   vector<int>::iterator it ;
   for(it = (*heap).begin();it!=(*heap).end();it++)
       cout<<"\t"<<*it;
   }

   int remove();
   
   friend ostream & operator << ( ostream & ios, Heap &s);

};

ostream & operator << ( ostream & ios, Heap &s){
    
    vector<int>::iterator it ;
    int temp = s.size ;
    for(it = s.heap->begin();temp>0; it++,temp--){
       ios<<"\t"<<*it;

    }   
  return ios;
}


int Heap::insert(int val){
  (*heap).push_back(val);
   size++;
}

void Heap::heapify(int i){
   
    if(i >= size)
        return;
   int left =  2*i+1; 
   int right = 2*i+2;
   int largest = i;
   if(left <= size && (*heap)[left] > (*heap)[i]){
       largest = left;
   }
   if(right <= size && (*heap)[right] > (*heap)[largest]){
       largest = right;
   }      
   if(largest != i){
         swap(i,largest);
         heapify(largest);
   }
   return ; 
}

int Heap::getmax(){
  return (*heap)[0];  
 
}

int Heap::makeHeap(){
    for (int i = size/2; i >= 0; i--)
         heapify(i); 
}

int Heap::remove(){
 swap(0,size-1);
 size--;
 heapify(0);
}




int main(){
 Heap my_heap;
 for(int i=1;i<=10;i++)
     my_heap.insert(i);
 my_heap.makeHeap();  
 
 cout<<my_heap.getmax()<<" max \n";
 cout<<my_heap;
 my_heap.remove();
 cout<<my_heap.getmax()<<" max \n";
 my_heap.remove();
 cout<<my_heap.getmax()<<" max \n";
 my_heap.remove();
 cout<<my_heap.getmax()<<" max \n";
 my_heap.remove();
 cout<<my_heap.getmax()<<" max \n";

 cout<<my_heap;
}




