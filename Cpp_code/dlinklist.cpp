#include<iostream>
#include<stdlib.h>
#include<queue>

using namespace std;

struct Linklist{
    struct Linklist * next;
    struct Linklist* prev;
    int data;
};
typedef struct Linklist* ListPtr;

/*template <typename LData>
class DLList{
     
    private:
    LData  data;   
    public: 
     DLLlist(){
    }  

};*/

//#define for_each_list() 

int ListInsert(int data, ListPtr * Head){
    ListPtr t = *Head;
    ListPtr tmp = (ListPtr)malloc(sizeof(struct Linklist));
    tmp->data = data;
    tmp->next = NULL;
    tmp->prev  = NULL;

    if(t==NULL){
        *Head =tmp;     
        return 1;
    }
    do{
        if(t->data >= data){

            if(t==*Head){ //First Node
                tmp->next = t;
                t->prev = tmp;
                *Head = tmp; 
            } 

            else{ // Intermediate Node 
                tmp->next = t;
                tmp->prev = t->prev;
                t->prev->next = tmp;
                t->prev = tmp;
            }
            break; 
        }
        else if (t->next==NULL){ // Last Node
            t->next = tmp;
            tmp->prev = t;
            break;
        }    
        t = t->next;
    }while(t!=NULL);

    return 1;
}


int ListDelete(int data,ListPtr * Head){
    ListPtr t = *Head;
    if(t==NULL)
        return 0;
    do{
        if(t->data == data){
            if(t==*Head){ //First Node
                *Head = t->next; 
                free(t);
            } 
            else if (t->next==NULL){ // Last Node
                t->prev->next = NULL;
                free(t);
            }    
            else{ // Intermediate Node 
                t->prev->next = t->next;
                t->next->prev = t->prev;
                free(t);
            }
            break; 
        } 
        t = t->next;
    }while(t!=NULL);

}
int ListCount(ListPtr Head){
  ListPtr t = Head; 
  int count = 0;
  while(t!=NULL){
     count++;
     t  = t->next;
 }
 return count;
}

int ListPrint(ListPtr Head){
  ListPtr t = Head; 
  int count = 0;
 while(t!=NULL){
     cout<<"\t "<<t->data;
     t  = t->next;
 }
 return count;
}

ListPtr findMiddle(ListPtr Head){
 ListPtr fast = Head;
 ListPtr slow = Head;
 while(fast != NULL && fast->next !=NULL){
 fast = fast->next->next;   
 slow = slow->next;
 }
return slow;
}


ListPtr ConvertListtoTree(ListPtr Head){

 if(!Head)
     return NULL;
 if(Head->next==NULL && Head->prev==NULL)
     return Head;

 ListPtr root = findMiddle(Head);
 
 if(root->next)
     root->next->prev =NULL;
 
 if(root->prev)
     root->prev->next =NULL;
 
 root->next = ConvertListtoTree(root->next);
 root->prev = ConvertListtoTree(Head);

 return root;

}

int InorderTraversal(ListPtr root){

 if(!root)
    return 0 ;
 InorderTraversal(root->prev);
 cout<<"\t"<<root->data;
 InorderTraversal(root->next);
return 0;
}


void Levelorder(ListPtr root){
 
 queue<ListPtr> LQueue;
 ListPtr tmp; 
 if(!root)
    return;
 LQueue.push(root);
 while(!LQueue.empty()){
  tmp = LQueue.front()  ;
  cout<<"\n \t"<<tmp->data;
  LQueue.pop();
  if(tmp->prev)
    LQueue.push(tmp->prev); 
  if(tmp->next)
    LQueue.push(tmp->next);
 }
return;
}


int main(){

 ListPtr Head = NULL;

 ListInsert(1,&Head);
 ListInsert(2,&Head);
 ListInsert(4,&Head);
 ListInsert(3,&Head);
 ListInsert(5,&Head);
 ListInsert(6,&Head);
 ListInsert(7,&Head);
 
 ListPrint(Head);

 cout<<"\n"<<ListCount(Head);

 ListPtr m = findMiddle(Head);

 cout<<"\n"<<m->data;

 ListPtr root = ConvertListtoTree(Head);
 InorderTraversal(root);
 Levelorder(root);

}



