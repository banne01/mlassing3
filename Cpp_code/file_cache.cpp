#include "file_cache.h"
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <map>
#include <fcntl.h>

// The problem is to implement a file cache in C++ that derives the interface
// given below in class FileCache. The typical usage is for a client to call
// 'PinFiles()' to pin a bunch of files in the cache and then either read or
// write to their in-memory contents in the cache. Writing to a cache entry
// makes that entry 'dirty'. Before a dirty entry can be evicted from the
// cache, it must be unpinned and has to be cleaned by writing the
// corresponding data to disk.
//
// All files are assumed to have size 10KB. If a file doesn't exist to begin
// with, it should be created and filled with zeros - the size should be 10KB.
//
// FileCache should be a thread-safe object that can be simultaneously
// accessed by multiple threads. If you are not comfortable with concurrent
// programming, then it may be single-threaded (see alternative in the
// PinFiles() comment). To implement the problem in its entirety may require
// use of third party libraries and headers. For the sake of convenience, it
// is permissible (although not preferred) to substitute external functions
// with stub implementations, but in doing so, please be clear what the
// intended behavior and side effects would be.
//
// Do not be overly concerned about portability. Pick your platform of choice
// (Nutanix develops on Linux) and be consistent. You may use C++11
// functionality.
//
// The problem is expected to take no longer than four hours (it is not
// necessary to work for that complete time). We'd rather see a stable and
// clean solution that implements a subset of the functionality than a
// complete but buggy one. There is no strict threshold on the time limit, so
// if you need a extra time to organize and improve the readability of your
// solution, please do so.
//
// If you have any questions, please email both brian@nutanix.com and
// bnc@nutanix.com. If no reply is received in a timely manner, please make a
// judgement call and state your assumptions in the code or response email.

#define FILE_SIZE  10*1028
//#define DEBUG 1

class FileObj{
  private : 
  std::string path;
  int refcount ;
  char *buff;
  int marktodel;
  int fd;
  public:
  // consturctor
  FileObj(std::string fpath){
    path = fpath;
    refcount = 1;
    marktodel = 0;
    ReadFileinMem();
  }    
  void ReadFileinMem(){
      // mmap the file in the memory ?? 
      // But the spec says to read it from the file
      fd = open(path.c_str(),O_RDWR);
          if(fd>0)  { 
              buff = new char[10*1028];
              if( read(fd,buff,FILE_SIZE)<FILE_SIZE)
                  std::cout<<"Could not read file for file size "<<path;
                 // throw excpetion
          } 
          else{
              fd = open(path.c_str(),O_RDWR|O_CREAT,644);
              if(fd<0){
                  std::cout<<"Could not create file "<<path;
                  // throw ececption
              }
              buff = new char[FILE_SIZE];
              memset(buff,0,FILE_SIZE);
          }
      }
  void WriteBufferToDisk(){
    if(write(fd,buff,FILE_SIZE)<FILE_SIZE)
         std::cout<<"Could not read file for file size "<<path;
         // throw excpetion

  }
  // destructor 
  ~FileObj(){
     WriteBufferToDisk(); 
      delete []buff;
    if(marktodel)
            unlink(path.c_str()); 
  }
  const char * GetBufferRDOnly(){
  return buff;
  }
  char * GetBufferRDWrite(){
  return buff; 
  }
  void IncrementRef(){
   refcount++;
   return ;
  }
  void DecrementRef(){
   refcount--;
   return ;
  }
  int GetRefCount(){
  return refcount;
  }
  void MarkforDeletion(){
   marktodel = 1;
  }
  void PrintObj(){
     std::cout<<" Path "<<path ;
     std::cout<<"Reference "<<refcount;
  return ;
  }
 
};


class FileCacheImp: public FileCache
{
    public:
        // List of file objects   
        typedef std::list<FileObj *> FileList; 
        // List Iterator
        typedef std::list<FileObj *>::iterator ListIter; 
        // Using Map as Hash Table
        typedef std::map<std::string,ListIter> FileHash; // hash to identify File Path
        // Hash Iter
        typedef std::map<std::string,ListIter>::iterator MapIter; //

        FileCacheImp(int max_cache, int dirty_time):FileCache(max_cache, dirty_time){
            current_cache_size =0; 
        }

        // Pins the given files in vector 'file_vec' in the cache. If any of these
        // files are not already cached, they are first read from the local
        // filesystem. If the cache is full, then some existing cache entries may be
        // evicted. If no entries can be evicted (e.g., if they are all pinned, or
        // dirty), then this method will block until a suitable number of cache
        // entries becomes available. It is fine if more than one thread pins the
        // same file, however the file should not become unpinned until both pins
        // have been removed from the file.
        //
        // Correct usage of PinFiles() is assumed to be the caller's responsibility,
        // and therefore deadlock avoidance doesn't need to be handled. The caller is
        // assumed to pin all the files it wants using one PinFiles() call and not
        // call multiple PinFiles() calls without unpinning those files in the
        // interim.
        //
        // If you are not comfortable with multi-threaded programming or
        // synchronization, this function may be modified to return a boolean if
        // the requested files cannot be pinned due to the cache being full. However,
        // note that entries in 'file_vec' may already be pinned and therefore even a
        // full cache may add additional pins to files.

        void PinFiles(const std::vector<std::string>& file_vec) {
            int req_len = file_vec.size();
            if(max_cache_entries_ > req_len + current_cache_size){  // We are good as we dont have to purge now
                std::vector<std::string>::const_iterator fvec_iter = file_vec.begin();
                for( ; fvec_iter != file_vec.end(); fvec_iter++){
                    #ifdef DEBUG 
                        std::cout<<*fvec_iter; 
                    #endif
                    std::string abs_path = _create_abs_path(*fvec_iter);   
                    MapIter mitr = Fmap.find(abs_path);  
                    if(mitr != Fmap.end()){ // We found entry already
                        ListIter litr = mitr->second;     
                        FileObj *fobj = *litr ;
                        fobj->IncrementRef();
                        Flist.erase(litr);  // remove the element
                        Flist.push_front(fobj); // push front
                        litr = Flist.begin(); // take the new iterator
                        mitr->second = litr; 
                    }
                    else{ 
                        // create a file object 
                        // read it in to buffer
                        // store in the list of FileObjects   
                        // Update the map
                        FileObj *fobj = new FileObj(abs_path);
                        Flist.push_front(fobj); // push front
                        ListIter litr = Flist.begin(); // take the new iterator
                        Fmap.insert(make_pair(abs_path,litr)); // insert  in map
                        current_cache_size ++ ; 
                    }
                }
            }   
            else{
                // checks  if we can accomodate this request 
                // File might already be present in the map
                //or We should block
                std::vector<std::string>::const_iterator fvec_iter = file_vec.begin();
                for( ; fvec_iter != file_vec.end(); fvec_iter++){
                #ifdef DEBUG 
                    std::cout<<*fvec_iter; 
                #endif
                    MapIter mitr = Fmap.find(*fvec_iter);  
                } 
            } 
        }

        // Unpin one or more files that were previously pinned. It is ok to unpin
        // only a subset of the files that were previously pinned using PinFiles().
        // It is undefined behavior to unpin a file that wasn't pinned.
        void UnpinFiles(const std::vector<std::string>& file_vec) {
         std::vector<std::string>::const_iterator fvec_iter = file_vec.begin();
             for( ; fvec_iter != file_vec.end(); fvec_iter++){
                 std::string abs_path = _create_abs_path(*fvec_iter);   
                 MapIter mitr = Fmap.find(abs_path);  
                 #ifdef DEBUG 
                        std::cout<<*fvec_iter; 
                 #endif
                 if(mitr == Fmap.end())
                    continue;
                 ListIter litr = mitr->second;
                 FileObj *fobj = *litr ;
                 Flist.erase(litr);  // remove the element
                 fobj->DecrementRef();
                 Flist.push_back(fobj); // push front
                 litr = Flist.end(); // take the new iterator
                 mitr->second = (--litr);  // update the map
                                           // Dont free right now 
                 current_cache_size --; // This object goes in to memory
          }
        }

        // Provide read-only access to a pinned file's data in the cache.
        //
        // It is undefined behavior if the file is not pinned, or to access the
        // buffer when the file isn't pinned.
        const char *FileData(const std::string& file_name) {
          
               std::string abs_path = _create_abs_path(file_name);   
               MapIter mitr = Fmap.find(abs_path);  
               if(mitr == Fmap.end())
                    return NULL;
               ListIter litr = mitr->second;
               FileObj *fobj = *litr ;
               return fobj->GetBufferRDOnly();
        }

        // Provide write access to a pinned file's data in the cache. This call marks
        // the file's data as 'dirty'. The caller may update the contents of the file
        // by writing to the memory pointed by the returned value.
        //
        // It is undefined behavior if the file is not pinned, or to access the
        // buffer when the file is not pinned.
        char *MutableFileData(const std::string& file_name) {
               std::string abs_path = _create_abs_path(file_name);   
               MapIter mitr = Fmap.find(abs_path);  
               if(mitr == Fmap.end())
                    return NULL;
               ListIter litr = mitr->second;
               FileObj *fobj = *litr ;
               return fobj->GetBufferRDWrite();
        }

        // Mark a file for deletion from the local filesystem. It may or may not be
        // pinned. If it is pinned, then the deletion is delayed until after the file
        // is unpinned.
        void DeleteFile(const std::string& file_name) {
            std::string abs_path = _create_abs_path(file_name);   
               MapIter mitr = Fmap.find(abs_path);  
               if(mitr == Fmap.end()){
                 // Not in cache
                 // Go ahead unlink it
                 unlink(abs_path.c_str());
                 return;
               }
               ListIter litr = mitr->second;
               FileObj *fobj = *litr ;
                   
        }
        // Internal function to debug
        void printcache(){
            ListIter it = Flist.begin();
            while(it != Flist.end()){
                (*it)->PrintObj();
                std::cout<<"\n";
                it++;
            }
        }
   ~FileCacheImp(){ // We need to free file objects at the end
      
       ListIter it = Flist.begin();
        while(it != Flist.end()){
              delete *it;
            it++;
       }
    }
    private :
        int current_cache_size ;
        FileList Flist;
        FileHash Fmap; 
        pthread_mutex_t Cmutex;
        std::string _create_abs_path(const std::string & inpath){
            // check for abs path
            // Need to implement this
            std::string abs_path = inpath;
            return abs_path;
        }
         
};


int main(){
    FileCacheImp fcache(10,10);
    using namespace std;
    vector<string> new_files;
    string s1 = "f1.txt";
    string s2 = "f2.txt";
    string s3 = "f3.txt";

    new_files.push_back(s1);
    new_files.push_back(s2);
    new_files.push_back(s3);
    
    fcache.PinFiles(new_files); 

   fcache.printcache();
   
   vector<string> rm_files;
   rm_files.push_back(s2);
   fcache.UnpinFiles(rm_files);
   fcache.printcache();
}


