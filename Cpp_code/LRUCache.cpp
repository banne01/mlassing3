#include<iostream>
#include<map>
#include<list>
#include<string>

#include<pthread.h>


// Its proper to specify the no of slots in the template it
// self 
using namespace std;


/*
template < class Objtype>
class CircularList{
  private :
    Objtype * Head;
    private  Objtype * next;
    private  Objtype * prev;
}*/

template <class Objtype>
class ObjCache{

    public :
        typedef list< Objtype > ObjList; 
        typedef typename list<Objtype>::iterator ListIter; 
        typedef map<string,ListIter> ObjHash; // hash to identify object list entries
        typedef typename map<string,ListIter>::iterator MapIter; //

        ObjCache(int max){
            //constructor
            maxslots = max;
            usedslot = 0;
            pthread_mutex_init(&Cmutex,0);
        }
        ~ObjCache(){
            //destructor
        }
        void insert(string & key,Objtype &nobj); 
        Objtype* find(string& key);
        int remove(const string &key );
        void printcache(){
        ListIter it = Clist.begin();
        while(it != Clist.end()){
         cout<<*it;
         cout<<endl;
         it++;
        }
        return ;
        }
        
        void getlock(){
        
        }
        void trylock(){
        
        }
        void putlock(){
        
        }
    private :
        int usedslot;
        int maxslots;
        ObjList Clist;
        ObjHash Cmap; 
        pthread_mutex_t Cmutex; 
};

template <class Objtype>
void ObjCache<Objtype>::insert(string& key, Objtype& nobj){
    MapIter mitr = Cmap.find(key);    
    if(mitr != Cmap.end()){ // element present int the list 
      ListIter litr = mitr->second;
      Clist.erase(litr);  // remove the element
      Cmap.erase(mitr);
      Clist.push_front(nobj); // push front
      litr = Clist.begin(); // take the new iterator
      Cmap.insert(make_pair(key,litr)); // insert back in map
    }
    else{ //create an element and insert at head
          // This preservers the iterator becuase we insert at head
        Clist.push_front(nobj); // push front
        ListIter litr = Clist.begin(); // take the new iterator
        Cmap.insert(make_pair(key,litr)); // insert back in map
    }
return;     
}


template <class Objtype>
Objtype* ObjCache<Objtype>::find(string& key){

    MapIter mitr = Cmap.find(key);    
    if(mitr == Cmap.end())
        return NULL;
    ListIter litr = mitr->second;
    Clist.erase(litr);  // remove the element
    Cmap.erase(mitr);
    Clist.push_front(*litr); // push front
    litr = Clist.begin(); // take the new iterator
    Cmap.insert(make_pair(key,litr)); // insert back in map
    return &(*litr);
}



template <class Objtype>
int ObjCache<Objtype>::remove(const string &key ){
    MapIter mitr = Cmap.find(key);    
    if(mitr == Cmap.end())
        return 0;
    ListIter litr = mitr->second;
    Clist.erase(litr);  // remove the element

return 1;
}

int main(){

 ObjCache<string> lrucache(20); 

 string s1("abc");
 string s1k("12");
 string s2k("344");
 string s2("sdwewer");
 string s3("dsfds");
 string s3k("1244");
 string s4k("23424");
 string s4("sdfsdfs");
   
 lrucache.insert(s1,s1k);
 lrucache.insert(s2,s2k);
 lrucache.insert(s3,s3k);
 lrucache.insert(s4,s4k);
 lrucache.printcache();
 
 string * temp = lrucache.find(s2);
 temp->append("###"); 
 lrucache.printcache();
 
 lrucache.remove(s2);   
 lrucache.printcache();
}


