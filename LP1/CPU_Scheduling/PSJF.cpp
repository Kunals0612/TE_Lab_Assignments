#include <bits/stdc++.h>
using namespace std;

// Define the Process class
class Process {
public:
    int id;
    int arrival;
    int burst;

    Process(int id, int burst, int arrival) : id(id), arrival(arrival), burst(burst) {}
};

// Define the PSJF (Preemptive Shortest Job First) scheduling class
class PSJF {
public:
    vector<Process> processes;
    vector<pair<int, pair<int, int>>> ganttChart; // Stores (Process ID, (Start Time, End Time))

    PSJF(vector<Process> procs) : processes(procs) {}

    // Function to calculate Turnaround Time (TAT)
    void findTAT(vector<int>& tat, const vector<int>& wt) {
        for (int i = 0; i < processes.size(); i++) {
            tat[i] = wt[i] + processes[i].burst;
        }
    }

    // Function to calculate Waiting Time (WT)
    void findWaitingTime(vector<int>& wt) {
        int n = processes.size();
        int currentTime = 0, completeTask = 0, minBurst = INT_MAX, shortestTask = -1;
        vector<int> remainingTime(n);
        wt.assign(n, 0);

        // Initialize remaining time for all processes
        for (int i = 0; i < n; i++) {
            remainingTime[i] = processes[i].burst;
        }

        while (completeTask != n) {
            minBurst = INT_MAX;
            shortestTask = -1;

            // Check each process to find the shortest remaining time
            for (int i = 0; i < n; i++) {
                if ((processes[i].arrival <= currentTime) && (remainingTime[i] < minBurst) && (remainingTime[i] > 0)) {
                    shortestTask = i;
                    minBurst = remainingTime[i];
                }
            }

            if (shortestTask == -1) {
                // No process is ready to execute at the current time
                currentTime++;
                continue;
            }

            // Preemptively execute the process with the shortest remaining time
            ganttChart.push_back({processes[shortestTask].id, {currentTime, currentTime + 1}});
            remainingTime[shortestTask]--;
            currentTime++;

            // If the process has completed execution
            if (remainingTime[shortestTask] == 0) {
                completeTask++;
                int finishTime = currentTime;
                wt[shortestTask] = finishTime - processes[shortestTask].burst - processes[shortestTask].arrival;
                if (wt[shortestTask] < 0) {
                    wt[shortestTask] = 0;
                }
            }
        }
    }

    // Function to perform PSJF scheduling and display results
    void schedule() {
        int n = processes.size();
        vector<int> wt(n), tat(n);
        int total_tat = 0, total_wt = 0;

        // Calculate Waiting Time and Turnaround Time
        findWaitingTime(wt);
        findTAT(tat, wt);

        // Display the results
        cout << "PID\tBT\tAT\tWT\tTAT\n";
        for (int i = 0; i < n; i++) {
            cout << processes[i].id << "\t" << processes[i].burst << "\t" << processes[i].arrival << "\t" 
                 << wt[i] << "\t" << tat[i] << "\n";
            total_tat += tat[i];
            total_wt += wt[i];
        }

        // Calculate and display average TAT and WT
        cout << fixed << setprecision(2);
        cout << "Avg TAT: " << (float)total_tat / n << endl;
        cout << "Avg WT: " << (float)total_wt / n << endl;

        // Display Gantt Chart
        cout << "\nGantt Chart:\n";
        for (const auto& slot : ganttChart) {
            cout << "Process " << slot.first << " executed from " << slot.second.first << " to " << slot.second.second << "\n";
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int id, burst, arrival;
        cout << "Enter Process ID, Arrival Time, and Burst Time for Process " << i + 1 << ": ";
        cin >> id >> burst >> arrival;
        processes.emplace_back(Process(id, arrival, burst));
    }

    // Create PSJF scheduler and perform scheduling
    PSJF scheduler(processes);
    scheduler.schedule();

    return 0;
}
