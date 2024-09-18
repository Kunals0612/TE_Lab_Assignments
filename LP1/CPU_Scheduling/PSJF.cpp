#include <bits/stdc++.h>
using namespace std;
class Process
{
public:
    int id;
    int burst;
    int arrival;
};
void findTAT(Process processes[], int n, int tat[], int wt[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + processes[i].burst;
    }
}
void findWaitingTime(Process processes[], int n, int wt[])
{
 
    int currentTime = 0, completeTask = 0, minBurst = INT_MAX, shortestTask = 0, finishTime = 0;
    bool check = false;
    int remainingTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = processes[i].burst;
    }

    while (completeTask != n)
    {
        // minBurst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if ((processes[i].arrival <= currentTime) && (remainingTime[i] < minBurst) && (remainingTime[i] > 0))
            {
                shortestTask = i;
                check = true;
                minBurst = remainingTime[i];
            }
        }
 
        if (check == false)
        {
            currentTime++;
            continue;
        }
       
        remainingTime[shortestTask]--;
        minBurst = remainingTime[shortestTask];
        if(minBurst == 0)
        {
            minBurst = INT_MAX;
        }
        if (remainingTime[shortestTask] == 0)
        {
     
            completeTask++;
            check = false;

            finishTime = currentTime + 1;
            wt[shortestTask] = finishTime - processes[shortestTask].burst - processes[shortestTask].arrival;
            if (wt[shortestTask] < 0)
            {
                wt[shortestTask] = 0;
            }
        }
        currentTime++;
    }

    for (int i = 0; i < n; i++)
    {
        cout << " " << processes[i].id << "\t\t" << processes[i].burst << "\t\t" << processes[i].arrival << "\t\t" << wt[i] << "\t\t" << tat[i] << "\t\t\n";
        total_tat += tat[i];
        total_wt += wt[i];
    }
void PSJF(Process processes[], int n)
{
    int wt[n], tat[n], total_tat = 0, total_wt = 0;
    findWaitingTime(processes, n, wt);
    findTAT(processes, n, tat, wt);
    cout << "PTD\t\t" << "BT\t\t" << "AT\t\t" << "WT\t\t" << "TAT\t\t\n"
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << " " << processes[i].id << "\t\t" << processes[i].burst << "\t\t" << processes[i].arrival << "\t\t" << wt[i] << "\t\t" << tat[i] << "\t\t\n";
        total_tat += tat[i];
        total_wt += wt[i];

        for (int i = 0; i < n; i++)
        {
            cout << " " << processes[i].id << "\t\t" << processes[i].burst << "\t\t" << processes[i].arrival << "\t\t" << wt[i] << "\t\t" << tat[i] << "\t\t\n";
            total_tat += tat[i];
            total_wt += wt[i];
        }
        cout << "Avg TAT" << (float)total_tat / (float)n << endl;
        cout << "Avg WT" << (float)total_wt / (float)n << endl;
    }
int main()
{
    Process processes[] = {{1, 6, 2}, {2, 2, 5}, {3, 8, 0}};
    int n = 3;
    PSJF(processes, n);
    return 0;
}
