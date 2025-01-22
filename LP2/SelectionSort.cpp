#include<bits/stdc++.h>
using namespace std;

class Sort{
    vector<int> arr;  // Vector to store the array elements
    int size;         // Variable to store the size of the array

    public:
        // Constructor to initialize the array with given size and input values
        Sort(int size){
            this->size = size;  // Set the size of the array
            arr.resize(size);   // Resize the array to the specified size
            cout<<"Enter the elements of the array: "<<endl;
            for(int i=0; i<size; i++){
                cin>>arr[i];  // Input each element of the array
            }
            selectionSort(arr, size);  // Call the selection sort function
        }

    private:
        // Function to perform selection sort on the array
        void selectionSort(vector<int>& arr, int size){
            int minIdx;  // Index of the minimum element in the unsorted part of the array
            for(int i=0; i<size-1; i++){
                minIdx = i;  // Assume the current element is the minimum
                // Inner loop to find the minimum element in the remaining unsorted array
                for(int j=i+1; j<size; j++){
                    if(arr[j] < arr[minIdx]){  // If a smaller element is found, update minIdx
                        minIdx = j;
                    }
                }
                swap(arr[minIdx], arr[i]);  // Swap the minimum element with the element at position i
            }
            printArr(arr);  // Print the sorted array
        }

        // Function to print the array elements
        void printArr(vector<int> arr){
            cout<<"Sorted Array: "<<endl;
            for(int i=0; i<arr.size(); i++){
                cout<<arr[i]<<" ";  // Print each element of the sorted array
            }
            cout<<endl;  // Print a newline at the end
        }
};

int main(){
    int size;
    cout<<"Enter the size of the array: "<<endl;
    cin>>size;  // Input the size of the array
    Sort s(size);  // Create an object of Sort class to sort the array
    return 0;
}
