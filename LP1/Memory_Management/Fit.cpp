#include <iostream>
#include <vector>
using namespace std;

void printAllocations(const vector<int>& allocation, const string& methodName) {
    cout << "\n" << methodName << " Allocation:\n";
    for (int i = 0; i < allocation.size(); i++) {
        if (allocation[i] != -1)
            cout << "Task " << i + 1 << " allocated to block " << allocation[i] + 1 << "\n";
        else
            cout << "Task " << i + 1 << " not allocated\n";
    }
}

void firstFit(vector<int>& blockSize, vector<int>& taskSize) {
    vector<int> allocation(taskSize.size(), -1);
    vector<bool> blockAllocated(blockSize.size(), false);
    
    for (int i = 0; i < taskSize.size(); i++) {
        for (int j = 0; j < blockSize.size(); j++) {
            if (!blockAllocated[j] && blockSize[j] >= taskSize[i]) {
                allocation[i] = j;
                blockAllocated[j] = true; 
                break;
            }
        }
    }
    printAllocations(allocation, "First Fit");
}

void bestFit(vector<int>& blockSize, vector<int>& taskSize) {
    vector<int> allocation(taskSize.size(), -1);
    vector<bool> blockAllocated(blockSize.size(), false);
    
    for (int i = 0; i < taskSize.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (!blockAllocated[j] && blockSize[j] >= taskSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockAllocated[bestIdx] = true; 
        }
    }
    printAllocations(allocation, "Best Fit");
}

void worstFit(vector<int>& blockSize, vector<int>& taskSize) {
    vector<int> allocation(taskSize.size(), -1);
    vector<bool> blockAllocated(blockSize.size(), false);
    
    for (int i = 0; i < taskSize.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (!blockAllocated[j] && blockSize[j] >= taskSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockAllocated[worstIdx] = true; 
        }
    }
    printAllocations(allocation, "Worst Fit");
}

void nextFit(vector<int>& blockSize, vector<int>& taskSize) {
    vector<int> allocation(taskSize.size(), -1);
    vector<bool> blockAllocated(blockSize.size(), false);
    int j = 0; 
    
    for (int i = 0; i < taskSize.size(); i++) {
        // bool allocated = false;
        for (int count = 0; count < blockSize.size(); count++) {
            if (!blockAllocated[j] && blockSize[j] >= taskSize[i]) {
                allocation[i] = j;
                blockAllocated[j] = true; 
                // allocated = true;
                break;
            }
            j = (j + 1) % blockSize.size(); 
        }
    }
    printAllocations(allocation, "Next Fit");
}

int main() {
    int numBlocks, numTasks;
 
    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;
    vector<int> blockSize(numBlocks);
    cout << "Enter the size of each block:\n";
    for (int i = 0; i < numBlocks; i++) {
        cout << "Block " << i + 1 << ": ";
        cin >> blockSize[i];
    }

    cout << "Enter number of tasks: ";
    cin >> numTasks;
    vector<int> taskSize(numTasks);
    cout << "Enter the size of each task:\n";
    for (int i = 0; i < numTasks; i++) {
        cout << "Task " << i + 1 << ": ";
        cin >> taskSize[i];
    }

    vector<int> copyBlockSize = blockSize; 
    firstFit(copyBlockSize, taskSize);

    copyBlockSize = blockSize; 
    bestFit(copyBlockSize, taskSize);

    copyBlockSize = blockSize; 
    worstFit(copyBlockSize, taskSize);

    copyBlockSize = blockSize;
    nextFit(copyBlockSize, taskSize);

    return 0;
}
