#include<iostream>

using namespace std;


int main(){

int arr[] = {1,-3,2,4,7,10,-23,15,24,22,-13,19,-27-5 , -10 ,-11,13,12,15,-17,23};

int max_sum=0, sum = 0;
int max_start =0, curr_start=0;

int max_end = 0;

for (int i = 0 ; i<sizeof(arr)/sizeof(int) ; i++){

   sum = sum+arr[i];
   if(sum>max_sum){
    max_sum = sum;
    max_start = curr_start;
    max_end = i;
   }
  else if(sum<0){
      sum = 0;
      curr_start = i+1;      
  } 
}

cout<<"Max Sum "<<max_sum<<" start "<<max_start<<" end"<<max_end<<"\n" ;

}

