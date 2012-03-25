#include<iostream>
#include<vector>

using namespace std;

void
print_pass(vector<int> & passwd){

    vector<int>::iterator it;
    for(it = passwd.begin(); it != passwd.end() ; it++ )
    {
     cout<<*it; 
    }
    cout<<endl;
return;
}
void
generate_pass(int m ,int size,vector<int> & passwd )
{
    if(size==0){
    print_pass(passwd);
    return;
    }
 
    for(int i = m ; i <= 10 - size  ; i++ ){
       passwd.push_back(i);    
       generate_pass(i+1,size-1,passwd);
       passwd.pop_back();    
    }
}

int main(){

 vector<int> pass;   
 generate_pass(0,6,pass);

}
