#include<iostream>
#include<stdlib.h>
#include<queue>
#include<stack>

using namespace std;

struct Linklist{
    struct Linklist * next;
    struct Linklist* prev;
    int data;
};
typedef struct Linklist* ListPtr;

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

//  Following does not work why ?
//  Because Right is at the end of the list

/*ListPtr _converTreeToList(ListPtr Root ){

 if(!Root)
     return NULL;

 ListPtr Left = _converTreeToList(Root->prev); 
  
 ListPtr Right = _converTreeToList(Root->next);

 if(Left)
     Left->next = Root;
 Root->prev = Left;
 Root->next = Right;
 if(Right){
      Right->prev = Root;
      return Right; 
 }
 return Root;
}*/

void _coverTreetoList(ListPtr root, ListPtr* predecssor){

 if(!root)
     return ;
 if(root->prev)
     _coverTreetoList(root->prev,predecssor);
  if(*predecssor){
      (*predecssor)->next = root;
      root->prev = *predecssor;
  }
  *predecssor = root;
  if(root->next)  
    _coverTreetoList(root->next,predecssor);
return;
}



ListPtr ConverTreeToList(ListPtr root ){

  ListPtr list = NULL;
  _coverTreetoList(root,&list);
  while(list->prev)
      list = list->prev;
  return list;
}

void Listreverse(ListPtr* Head){

 ListPtr p = *Head;
 ListPtr r = NULL;
   
 while(p){
 p->prev = p->next; 
 p->next = r;
 r = p;
 p = p->prev;
 }
*Head = r;

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
 LQueue.push(NULL);
 while(!LQueue.empty()){
  tmp = LQueue.front() ;
  if(tmp ==NULL){
      LQueue.pop();
      if(!LQueue.empty()){ 
            LQueue.push(NULL);    
            cout<<"\n";
            continue;
      }  
      else
          break;
  }
  LQueue.pop();
  cout<<"\t " <<tmp->data;
  if(tmp->prev)
    LQueue.push(tmp->prev); 
  if(tmp->next)
    LQueue.push(tmp->next);
 }
return;
}


void BottomUp(ListPtr root){
 
 queue<ListPtr> LQueue;
 ListPtr tmp; 
 if(!root)
    return;
 stack<ListPtr> Stack;
 LQueue.push(root);
 LQueue.push(NULL);
 while(!LQueue.empty()){
  tmp = LQueue.front() ;
  if(tmp ==NULL){
      LQueue.pop();
      if(!LQueue.empty()){ 
            LQueue.push(NULL);    
            cout<<"\n";
            Stack.push(tmp);
            continue;
      }  
      else
          break;
  }
  LQueue.pop();
  Stack.push(tmp);
  //cout<<"\t " <<tmp->data;
  if(tmp->next) // right
    LQueue.push(tmp->next);
  if(tmp->prev) // left
    LQueue.push(tmp->prev); 
 }
 while(!Stack.empty())
 {
   tmp = Stack.top();
   if(tmp==NULL)
       cout<<"\n";
   else
       cout<<"\t"<<tmp->data;
   Stack.pop();  
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
 BottomUp(root);

 cout<<"\n Converting to List \n";

 ListPtr nHead = ConverTreeToList(root);

 ListPrint(nHead);
 
 Listreverse(&nHead);

 cout<<"\n Reverse the List \n";
 
 ListPrint(nHead);
}



