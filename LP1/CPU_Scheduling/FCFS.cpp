#include <bits/stdc++.h>
using namespace std;

// Class to represent each process with ID, Arrival Time, and Burst Time
class Process {
public:
    int PID;   // Process ID
    int AT;    // Arrival Time
    int BT;    // Burst Time

    Process(int id, int arrival, int burst) : PID(id), AT(arrival), BT(burst) {}
};

// FCFS (First Come First Serve) scheduling class
class FCFS {
public:
    vector<Process> processes;

    FCFS(const vector<Process>& proc) : processes(proc) {}

    // Function to find completion times
    void findCompletionTime(vector<int>& comp) {
        comp[0] = processes[0].BT;
        for (int i = 1; i < processes.size(); i++) {
            comp[i] = comp[i - 1] + processes[i].BT;
        }
    }

    // Function to find Turn Around Time (TAT)
    void findTurnAroundTime(vector<int>& TAT, const vector<int>& comp) {
        for (int i = 0; i < processes.size(); i++) {
            TAT[i] = comp[i] - processes[i].AT;
        }
    }

    // Function to find Waiting Time (WT)
    void findWaitingTime(vector<int>& WT, const vector<int>& TAT) {
        for (int i = 0; i < processes.size(); i++) {
            WT[i] = TAT[i] - processes[i].BT;
        }
    }

    // Function to calculate and display the average Turn Around Time and Waiting Time
    void findAvgTime() {
        int n = processes.size();
        vector<int> comp(n), TAT(n), WT(n);
        
        findCompletionTime(comp);
        findTurnAroundTime(TAT, comp);
        findWaitingTime(WT, TAT);

        float total_tat = 0, total_wt = 0;
        cout << "PID" << "   " << "AT" << "   " << "BT" << "   " << "CT" << "   " << "TAT" << "   " << "WT" << endl;
        for (int i = 0; i < n; i++) {
            cout << processes[i].PID << "     " << processes[i].AT << "     " << processes[i].BT << "     " 
                 << comp[i] << "     " << TAT[i] << "     " << WT[i] << endl;
            total_tat += TAT[i];
            total_wt += WT[i];
        }
        cout << "AVG TAT: " << total_tat / n << endl;
        cout << "AVG WT: " << total_wt / n << endl;
    }

    // Function to schedule tasks by sorting by Arrival Time
    void scheduleTask(vector<int>& schedule) {
        vector<pair<int, int>> pr;
        for (const auto& p : processes) {
            pr.push_back({p.AT, p.PID});
        }

        // Sort by arrival time
        sort(pr.begin(), pr.end());
        
        for (const auto& p : pr) {
            schedule.push_back(p.second);
        }
        
        cout << "Scheduled Order (by PID): ";
        for (int pid : schedule) {
            cout << pid << " ";
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int pid, at, bt;
        cout << "Enter Process ID, Arrival Time, and Burst Time for Process " << i + 1 << ": ";
        cin >> pid >> at >> bt;
        processes.push_back(Process(pid, at, bt));
    }
    
    FCFS scheduler(processes);
    scheduler.findAvgTime();

    vector<int> schedule;
    scheduler.scheduleTask(schedule);
    
    return 0;
}
