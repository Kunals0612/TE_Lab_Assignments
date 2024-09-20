#include <bits/stdc++.h>
using namespace std;

// Define the Process class
class Process
{
public:
    int id;
    int burst;
    int arrival;
};

// Function to calculate Turnaround Time (TAT)
void findTAT(Process processes[], int n, int tat[], int wt[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + processes[i].burst;
    }
}

// Function to calculate Waiting Time (WT)
void findWaitingTime(Process processes[], int n, int wt[])
{
    int currentTime = 0, completeTask = 0, minBurst = INT_MAX, shortestTask = -1, finishTime = 0;
    bool check = false;
    int remainingTime[n];

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = processes[i].burst;
    }

    while (completeTask != n)
    {
        minBurst = INT_MAX; // Reset minBurst for each iteration
        shortestTask = -1;  // Reset shortestTask

        // Find the process with the smallest remaining time that's arrived
        for (int i = 0; i < n; i++)
        {
            if ((processes[i].arrival <= currentTime) && (remainingTime[i] < minBurst) && (remainingTime[i] > 0))
            {
                shortestTask = i;
                minBurst = remainingTime[i];
                check = true;
            }
        }

        if (shortestTask == -1)
        {
            // No process is ready to execute at the current time
            currentTime++;
            continue;
        }

        // Execute the found process
        remainingTime[shortestTask]--;
        currentTime++;

        if (remainingTime[shortestTask] == 0)
        {
            completeTask++;
            finishTime = currentTime;
            wt[shortestTask] = finishTime - processes[shortestTask].burst - processes[shortestTask].arrival;
            if (wt[shortestTask] < 0)
            {
                wt[shortestTask] = 0;
            }
        }
    }
}

// Function to perform PSJF scheduling and display results
void PSJF(Process processes[], int n)
{
    int wt[n], tat[n];
    int total_tat = 0, total_wt = 0;

    // Calculate Waiting Time and Turnaround Time
    findWaitingTime(processes, n, wt);
    findTAT(processes, n, tat, wt);

    // Display the results
    cout << "PID\tBT\tAT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].id << "\t" << processes[i].burst << "\t" << processes[i].arrival << "\t" << wt[i] << "\t" << tat[i] << "\n";
        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Calculate and display average TAT and WT
    cout << fixed << setprecision(2);
    cout << "Avg TAT: " << (float)total_tat / n << endl;
    cout << "Avg WT: " << (float)total_wt / n << endl;
}

int main()
{
    // Define the processes
    Process processes[] = {
        {1, 6, 2},
        {2, 2, 5},
        {3, 8, 0}};
    int n = 3;

    // Perform PSJF scheduling
    PSJF(processes, n);
    return 0;
}
