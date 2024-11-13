#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Process{
    private:
       int id;
    public:
        Process(){
            id = 0;
        }
        
        Process(int id){
            this->id = id;
        }

    friend class Election;
};
class Election{
    private:
        Process *p;
        int *flag;
        int size;
    public:
        Election(int size){
            this->size = size;
            this->flag = new int[size];
            this->p = new Process[size];
            for(int i=0; i<size; i++){
                p[i].id = i;
                cout<<"Process is: "<<p[i].id<<endl;
            }
            cout<<endl;
        }
        Process Bully(Process coordinator, int crashed){
            for(int i=0; i<size; i++){
                flag[i] = 0;
            }

            flag[crashed] = 1;
            for(int i=coordinator.id; i<size; i++){
                for(int j=i+1; j<size && flag[i]==0; j++){
                    if(p[i].id >= coordinator.id){
                        cout<<"Message from: "<<i<<" Sent to: "<<j<<endl;
                        if(flag[j] != 1){
                            cout<<"Ok response received from: "<<j<<" to: "<<i<<endl;
                        }else{
                            cout<<"No response received from: "<<j<<endl;
                        }
                    }
                }
                if(!flag[i+1] && ((i+1) < size)){
                    cout<<"Now coordinator is: "<<i+1<<endl;
                    coordinator = p[i+1];
                }
            }
            cout<<"Final coordinator is: "<<coordinator.id<<endl;
            return coordinator;
        }
        void Ring(Process coordinator, int crashed){
            int count = 0;
            vector<int> vec;
            int pos = coordinator.id;
            int i = pos;
            while(count < size){
                if(i != crashed){
                    vec.push_back(p[i].id);
                    cout<<"Vec send to: "<<p[i+1].id<<" from: "<<p[i].id<<endl;
                    for(int i=0; i<vec.size(); i++){
                        cout<<vec[i]<<" ";
                    }
                    cout<<endl;
                }
                i = (i+1) % size;
                count++;
            }
            int finalCoordinator = *max_element(vec.begin(), vec.end());
            cout<<"Final coordinator is: "<<finalCoordinator<<endl;
        }
};
int main(){
    Election e(5);
    Process detectedNode(1);
    e.Bully(detectedNode,4);
    return 0;
}