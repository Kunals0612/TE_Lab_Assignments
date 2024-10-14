#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<climits>
using namespace std;
class PageReplacement{
   private:
   int capacity;
   int size;
   vector<int> pages;
   public:
   PageReplacement(int capacity, int size){
      this->capacity = capacity;
      this->size = size;
      getPages();
   }
   void getPages(){
      pages.resize(size);
      for(int i=0; i<size; i++){
         cout<<"Enter Page number: "<<i<<endl;
         cin>>pages[i];
      }
   }
   void firstInFirstOut(){
      set<int> s;
      queue<int> indices;
      int pageFault = 0;
      for(int i=0; i<size; i++){
         if(s.size() < capacity){
            if(s.find(pages[i]) == s.end()){
                s.insert(pages[i]);
                indices.push(pages[i]);
                pageFault++;

            }
         }else{
            if(s.find(pages[i]) == s.end()){
                int val = indices.front();
                indices.pop();
                s.erase(val);
                s.insert(pages[i]);
                indices.push(pages[i]);
                pageFault++;
            }
         }
      }
      getMemoryQueue(indices, pageFault);
   }
   bool search(int key, vector<int> frames){
      for(int i=0; i<frames.size(); i++){
         if(frames[i] == key){
            return true;
         }
      }
      return false;
   }
   int predict(vector<int> frames, int index){
       int res = -1, farthest = index;
       for(int i=0; i<frames.size(); i++){
          int j;
          for(j = index; j<pages.size(); j++){
              if(frames[i] == pages[j]){
                if(j > farthest){
                    farthest = j;
                    res = i;
                }
                break;
              }
          }
          if(j == pages.size()){
             return i;
          }
       }
       return (res == -1) ? 0 : res;
   }
   void optimalPage(){
       vector<int> frames;
       int hit =0, miss = 0;
       for(int i=0; i<size; i++){
           if(search(pages[i], frames)){
              hit++;
              continue;
           }
           if(frames.size() < capacity){
              frames.push_back(pages[i]);
           }else{
              int j = predict(frames,i+1);
              frames[j] = pages[j];
           }
       }
       cout<<"No. of hits: "<<hit<<endl;
       cout<<"No. of miss: "<<miss<<endl;
       cout<<"Memory Queue is: ";
       for(int i=0; i<frames.size(); i++){
          cout<<frames[i]<<" ";
       }
   }
   void getMemoryQueue(queue<int> q, int p){
      cout<<"Memory Queue: ";
      while(!q.empty()){
        cout<<q.front()<<" ";
        q.pop();
      }
      cout<<"Page Faults: "<<p<<endl;
   }
   int leastRecentlyUsed(){
      set<int> s;
      map<int,int> indices;
      int pageFault = 0;
      for(int i=0; i<size; i++){
         if(s.size() < capacity){
            if(s.find(pages[i]) == s.end()){
               s.insert(pages[i]);
               pageFault++;
            }
            indices[pages[i]] = i;
         }else{
            int leastUsed = INT_MAX, val;
            if(s.find(pages[i]) == s.end()){
               for(auto it=s.begin(); it!=s.end(); it++){
                  if(indices[*it] < leastUsed){
                     leastUsed = indices[*it];
                     val = *it;
                  }
               }
               s.erase(val);
               s.insert(pages[i]);
               pageFault++;
            }
            indices[pages[i]] = i;
         }
      }
   return pageFault;
   }
};
int main(){


    int size;
    int capacity;
    cout<<"Enter number of pages: ";
    cin>>size;
    cout<<"Enter size of memory queue: ";
    cin>>capacity;

    PageReplacement pg(capacity,size);

    cout<<"1. First In First Out "<<endl;
    cout<<"2. Optimal Page Replacement: "<<endl;
    cout<<"3. Least Used Page Replacement: "<<endl;

    int choice;
    cout<<"Enter the choice: ";
    cin>>choice;
    
    switch(choice){
        case 1: 
            pg.firstInFirstOut();
            break;
        case 2:
            pg.optimalPage();
            break;
        case 3:
            pg.leastRecentlyUsed();
            break;
        default:
            cout<<"Enter the valid Choice "<<endl;
            break; 
    }
    
}