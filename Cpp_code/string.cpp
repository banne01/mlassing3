#include<iostream>
#include<cstring>


int reversestr(char * s,int start,int end){

  while(start < end){
      char temp = s[start];
      s[start] = s[end];
      s[end] = temp; 
      start++;
      end--;
  }
return 0;
}


int main(){

    char s[] = "  Nehal Kumar Bandi is Having a PArty  ";
    char look[] = "PArty";
    char * f = strstr(s,look);
    if(f)
        std::cout<<f;
    else
        std::cout<<"not found" ;

   /* std::cout<<"***";    
    std::cout<<s;
    std::cout<<"***";    
    std::cout<<"\n";    
    int len = strlen(s);
    reversestr(s,0,len-1); 
    int end=0;
    while(s[end] != ' ')
        end++;
    
   int start = end;
    for(;end<len; end++){
        if(s[end] == ' '){
            reversestr(s,start,end);
            start = end+1;
        }
    }
    if(start<end)
        reversestr(s,start,end-1);

    std::cout<<"***";    
    std::cout<<s;
    std::cout<<"***";    
    std::cout<<"\n";    
    return 0;*/

}

const char * strstr(const char * str,const char* look){

 int n = strlen(str);
 int s = strlen(look);
 for(int i = 0 ; i < n -s ; i++){
     if(strncmp(str+i,look,s)==0)
      return str+i;
 } 
return NULL;
}




