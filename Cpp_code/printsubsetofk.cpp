#include<iostream>
#include<stack>
using namespace std;

void  printstack(stack<int> &st){

 stack<int> tmp;
 while(!st.empty()){
  int t = st.top();
  st.pop();
  tmp.push(t);
 }
 while(!tmp.empty()){
  int t = tmp.top();
  tmp.pop();
 
  cout<<t<<"\t";
  st.push(t);
 }
}
void printsubk(int * arr, int idx, int k,int n,stack<int>&st)
{
    if(k<=0){
        printstack(st);
	cout<<"\n";
        return;
    } 
    for(int j = idx; j<=n-k+1; j++)
    {
       st.push(arr[j]);
	printsubk(arr, j+1,k-1,n,st);
       st.pop(); 
   }
 return ;
}

int main(){

    int arr[] = {1,2,3,4,5};
    stack<int> st;
     printsubk(arr,0,3,4,st); 
}

