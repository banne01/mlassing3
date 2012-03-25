#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<utility>
#include<cstring>

using namespace std;

int main()
{
    vector<string> Ivect ;
    map< string , int > Htable;
	Ivect.push_back("ab");
	Ivect.push_back("bc");
	Ivect.push_back("ac");
	Ivect.push_back("de");
	Ivect.push_back("ef");
	vector<string>::iterator it;
	
	for(it = Ivect.begin(); it!=Ivect.end(); ++it){
       Htable.insert(make_pair(*it,0));
	}
   char str[] = "abaf";
   bool checkstr = true; 
   int Len = Ivect[0].length();   

  for(int i = 0 ; i<strlen(str); i = i + Len)   
  {
   char *p = str+i;
   char temp = str[i+Len];
   str[i+Len] = '\0';
  map<string,int>::iterator it = Htable.find(string(p));
  if(it == Htable.end()){
	 cout<<"Could not find combo"; 	
     checkstr=false;
	  break;
	}
   str[i+Len] = temp;
  }
 if(checkstr){
   cout<<"String present";	
  }
	 
}



