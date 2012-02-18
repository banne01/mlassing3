#include <iostream>
#include <vector>

using namespace std;

void printvector(vector<char> &st){
  vector<char>::iterator it ;
  cout<<"\n";
  for(it = st.begin(); (it != st.end());++it)
   cout <<*it; 
}


int printallparen(vector<char>& st,int left , int right){

    if(left>0){
        st.push_back('<');
        printallparen(st,left-1,right+1);
        st.pop_back();
    }
   if(right>0){
        st.push_back('>');
        printallparen(st,left,right-1);
        st.pop_back();
   }  
  if(left ==0 && right ==0)
       printvector(st);
}



int main(){

    vector<char> st(6); 
   printallparen(st,3,0); 
   
}

