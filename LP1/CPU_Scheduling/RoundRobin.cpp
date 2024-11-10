#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int process_id;
    int burst_time;
    int arrival_time;

    Process(int id, int bt, int at) : process_id(id), burst_time(bt), arrival_time(at) {}
};

class RoundRobin {
    vector<Process> processes;
    int quantum;

public:
    RoundRobin(vector<Process>& procs, int q) : processes(procs), quantum(q) {}

    void findWaitingTime(vector<int>& wt) {
        int n = processes.size();
        vector<int> remainingTime(n);
        for (int i = 0; i < n; i++) {
            remainingTime[i] = processes[i].burst_time;
        }

        int time = 0;
        vector<pair<int, int>> ganttChart; // (Process ID, execution time slice)

        while (true) {
            bool taskDone = true;

            for (int i = 0; i < n; i++) {
                if (remainingTime[i] > 0) {
                    taskDone = false;

                    if (remainingTime[i] > quantum) {
                        time += quantum;
                        ganttChart.push_back({processes[i].process_id, quantum});
                        remainingTime[i] -= quantum;
                    } else {
                        time += remainingTime[i];
                        ganttChart.push_back({processes[i].process_id, remainingTime[i]});
                        remainingTime[i] = 0;
                    }
                }
            }

            if (taskDone)
                break;
        }

        // Display the Gantt Chart
        cout << "\nGantt Chart:\n";
       
        for (const auto& entry : ganttChart) {
            cout << "| P" << entry.first << " (" << entry.second << " ms) ";
        }
        cout << "|\n";
    
        cout << endl;
    }

    void findTurnAroundTime(const vector<int>& wt, vector<int>& tat) {
        int n = processes.size();
        for (int i = 0; i < n; i++) {
            tat[i] = processes[i].burst_time + wt[i];
        }
    }

    void findAvgTime() {
        int n = processes.size();
        vector<int> wt(n), tat(n);
        int total_wt = 0, total_tat = 0;

        findWaitingTime(wt);
        findTurnAroundTime(wt, tat);

        cout << "Process \tBurst_Time \tTurn Around Time\tWaiting Time\n";
        for (int i = 0; i < n; i++) {
            total_wt += wt[i];
            total_tat += tat[i];
            cout << " " << processes[i].process_id << "\t\t" << processes[i].burst_time
                 << "\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
        }

        cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
        cout << "Average turn around time = " << (float)total_tat / (float)n << endl;
    }
};

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter time quantum: ";
    cin >> quantum;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int id, burst_time, arrival_time;
        cout << "Enter Process Id, burst time and arrival time for process " << i + 1 << ": ";
        cin >> id >> burst_time >> arrival_time;
        processes.push_back(Process(id, burst_time, arrival_time));
    }

    RoundRobin rr(processes, quantum);
    rr.findAvgTime();

    return 0;
}
