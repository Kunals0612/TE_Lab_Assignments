#include<iostream>
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
        int num;
    public:
        Election(int num){
            this->num = num;
            this->p = new Process[num];
            for(int i=1; i<=num; i++){
                p[i].id = i;
            }
            this->flag = new int[5];
        }
        
        Process bully(Process coordinator, int crashed){
            

            for(int i=0; i<num; i++){
                flag[i] = 0;
            }

            flag[crashed] = 1;

            for(int i=1; i<=num; i++){
                if(p[i].id > coordinator.id){
                    if(flag[i] != 1){
                        cout<<"Election message sent to: "<<p[i].id<<endl;
                    }
                }else{
                    flag[i] = 1;
                }
            }

            for(int i=1; i<=num; i++){
                if(flag[i] != 1 && p[i].id > coordinator.id){
                    cout<<"The Process has been handovered to the "<<p[i].id<<endl;
                    flag[coordinator.id] = 1;
                    coordinator = p[i].id;
                }
            }

            for(int i=1; i<=num; i++){
                if(flag[i] == 0){
                    coordinator = bully(coordinator,crashed);
                }
            }

            return coordinator;
        }

        int findPosition(int id){
            for(int i=0; i<num; i++){
                if(p[i].id == id){
                    return i;
                }
            }
            return 0;
        }
        
        void ring(Process coordinator, int crashed){
            vector<int> vec;
            int pos = findPosition(coordinator.id);
            int count = 0, i = pos;
            while(count < num){
                if(i != crashed){
                    vec.push_back(p[i].id);
                }
                i = (i+1)%num;
                count++;
            }
            int coordinator_id = *max_element(vec.begin(), vec.end());
            int finalCoordinator = findPosition(coordinator_id);
            cout<<"Final coordinator is: "<<p[finalCoordinator].id<<endl;
        }

};

int main(){
    int num;

    cout<<"Enter the number of processes: "<<endl;
    cin>>num;
    
    Election e(num);

    int id;
    cout<<"Enter the id of node that detected the crash: "<<endl;
    cin>>id;


    int crashed;
    cout<<"Enter the crashed process: "<<endl;
    cin>>crashed;

    Process detectedNode(id);

    cout<<"1. Bully Algorithm"<<endl;
    cout<<"2. Ring Algorithm"<<endl;
    int choice;
    cout<<"Enter the choice: "<<endl;
    cin>>choice;
    switch(choice){
        case 1:
            e.bully(detectedNode,crashed);
            break;
        case 2:
            e.ring(detectedNode,crashed);
            break;
        default:
            cout<<"Enter valid choice !"<<endl;
            break;
    }


    return 0;
}