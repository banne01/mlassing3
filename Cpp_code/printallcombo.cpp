#include<iostream>
#include<string>
using namespace std;

void swap(string &s, int i , int j){
  char temp = s[i];
  s[i] = s[j];
  s[j] = temp;
return ;
}
void permute(string &s,int len){
  if(len<=0)
    cout<<"\t"<<"\n"<<s;
  else {
    for(int j = 0 ; j<=len; j++){
     swap(s,len,j);
     permute(s,len-1);
     swap(s,j,len);
    }
  }
return;
}

int main(){
 string s("abcd");
 int n = s.length();
 permute(s,n-1);

}
