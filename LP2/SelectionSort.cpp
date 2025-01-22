#include<bits/stdc++.h>
using namespace std;
class Sort{
    vector<int> arr;
    int size;
    public:
        Sort(int size){
            this->size = size;
            arr.resize(size);
            cout<<"Enter the elements of the array: "<<endl;
            for(int i=0; i<size; i++){
                cin>>arr[i];
            }
            selectionSort(arr,size);
        }
    private:
        void selectionSort(vector<int>& arr,int size){
            int minIdx;
            for(int i=0; i<size-1; i++){
                minIdx = i;
                for(int j=i+1; j<size; j++){
                    if(arr[j] < arr[minIdx]){
                        minIdx = j;
                    }
                }
                swap(arr[minIdx],arr[i]);
            }
            printArr(arr);
        }
        void printArr(vector<int> arr){
            cout<<"Sorted Array: "<<endl;
            for(int i=0; i<arr.size(); i++){
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
};
int main(){
    int size;
    cout<<"Enter the size of the array: "<<endl;
    cin>>size;
    Sort s(size);
    return 0;
}