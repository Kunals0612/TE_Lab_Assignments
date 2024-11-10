#include <bits/stdc++.h>

using namespace std;

class Process {
public:
    int id;
    int burstTime;
    int arrivalTime;
    int priority;
    Process(int id, int burstTime, int arrivalTime, int priority)
        : id(id), burstTime(burstTime), arrivalTime(arrivalTime), priority(priority) {}
};

class PrioritySchedule {
public:
    vector<Process> processes;
    int totalProcesses;
    PrioritySchedule(vector<Process> processes) : processes(processes), totalProcesses(processes.size()){}

    static bool compare(Process a, Process b) {
        if (a.arrivalTime == b.arrivalTime) {
            return a.priority < b.priority;
        } else {
            return a.arrivalTime < b.arrivalTime;
        }
    }

    void getWaitingTime(vector<int>& wt) {
        vector<int> service(totalProcesses);
        service[0] = processes[0].arrivalTime;
        wt[0] = 0;

        for (int i = 1; i < totalProcesses; i++) {
            service[i] = processes[i - 1].burstTime + service[i - 1];
            wt[i] = service[i] - processes[i].arrivalTime;

            if (wt[i] < 0) {
                wt[i] = 0;
            }
        }
    }

    void getTurnAroundTime(vector<int>& tat, const vector<int>& wt) {
        for (int i = 0; i < totalProcesses; i++) {
            tat[i] = processes[i].burstTime + wt[i];
        }
    }

    void displayGanttChart(const vector<int>& stime, const vector<int>& ctime) {
        cout << "\nGantt Chart\n";
        for (int i = 0; i < totalProcesses; i++) {
            cout << "| P" << processes[i].id << " ";
        }
        cout << "|" << endl;

        for (int i = 0; i < totalProcesses; i++) {
            cout << stime[i] << "\t";
        }
        cout << ctime[totalProcesses - 1] << endl;
    }

    void findGc() {
        vector<int> wt(totalProcesses), tat(totalProcesses);
        double wAvg = 0, tAvg = 0;

        getWaitingTime(wt);
        getTurnAroundTime(tat, wt);

        vector<int> stime(totalProcesses), ctime(totalProcesses);
        stime[0] = processes[0].arrivalTime;
        ctime[0] = stime[0] + tat[0];

        for (int i = 1; i < totalProcesses; i++) {
            stime[i] = ctime[i - 1];
            ctime[i] = stime[i] + tat[i] - wt[i];
        }

        cout << "Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time" << endl;

        for (int i = 0; i < totalProcesses; i++) {
            wAvg += wt[i];
            tAvg += tat[i];

            cout << processes[i].id << "\t\t" << stime[i] << "\t\t" << ctime[i] << "\t\t"
                 << tat[i] << "\t\t\t" << wt[i] << endl;
        }

        cout << "Average waiting time is: " << wAvg / (float)totalProcesses << endl;
        cout << "Average turnaround time: " << tAvg / (float)totalProcesses << endl;

        displayGanttChart(stime, ctime);
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes;
    

    // Taking input for processes directly in main function
    for (int i = 0; i < n; i++) {
        int id, burstTime, arrivalTime, priority;
        cout << "Enter Process ID, Arrival Time, Burst Time, and Priority for Process " << i + 1 << ": ";
        cin >> id >> burstTime >> arrivalTime >> priority;
        processes.emplace_back(Process(id, burstTime, arrivalTime, priority));
    }

    PrioritySchedule scheduler(processes);
    
    sort(scheduler.processes.begin(), scheduler.processes.end(), PrioritySchedule::compare);

    scheduler.findGc();

    return 0;
}
