#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

int main(){
 
    int i ;
    string s = "1";   
    for(int i = 0 ; i < 6 ;i++){
        string rlc ;
        for(int j=0 ; j < s.length();j++){
            int count = 1;
            int begin = j;
            while(j < s.length() && s[j]==s[j+1]){
               count++;
               j++;
            }    
           rlc.push_back(count+ '0');
           rlc.push_back(s[j]);
        }
        cout<<rlc<<"\n";
        s = rlc;
    }  
    //for_each(seq.begin(); seq.end();std::cout);
}

