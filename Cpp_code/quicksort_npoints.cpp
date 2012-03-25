#include<iostream>

void swap_fun(int * array, int i , int j){
     
     array[0]  = array[j] ; // swap
     array[j]  = array[i];   //swap
     array[i]  = array[0]; // swap
}

int q_part(int * array, int left, int right);

int qsort(int* array,int left, int right){
   
    if(left < right){
       int part  = q_part(array,left,right);
       qsort(array,left,part-1);
       qsort(array,part+1,right); 
    }
return 0;
}

int q_part(int * array, int left, int right){
 int pivot = left;
 
 int i = left+ 1 ;
 int j = right;
 while(i < j){
    while(array[i]< array[pivot])
       i++;
    while(array[j] > array[pivot])
        j--;
    if(i < j){
       swap_fun(array,i,j);
   }
 }
 swap_fun(array,pivot,j); 
 return j;
}

int main(){
    
int array[6];

using namespace std;

for(int i = 0 ; i < 6 ; i++){
 cin>>array[i];
 }
 qsort(array,1,5);
for(int i = 0 ; i < 6 ; i++){
 cout<<array[i];
 }
}
