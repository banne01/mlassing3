#include<iostream>
#include<cmath>

int main(){

    using namespace std ;
    double i ;
    double low , high,mid ; 
    cout<<"enter no";
    cin>>i;
    if(i<0){
        cout<<"FU bitch";
    }
    if(i>1) {
        low = 1;
        high = i;
    }
    else{
        low = i;
        high = 1;
    }
    while(1){
        mid = (low + high)/2 ;
        if(abs(mid*mid*mid - i) < .0001)
            break;
        else if(mid*mid*mid > i)
        {
            high = mid;
        }    
        else {
            low = mid;
        } 
    } 
    cout<<mid;
}
