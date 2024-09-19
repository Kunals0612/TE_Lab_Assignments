#include<bits/stdc++.h>
using namespace std;
void findWaitingTime(int process[], int n, int wt[], int burst_time[], int quantum)
{
    int remainingTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = burst_time[i];
    }
    int time = 0;
    while(1)
    {
        bool Taskdone = true;
        for (int i = 0; i < n; i++)
        {
            if (remainingTime[i] > 0)
            {
                Taskdone = false;
                if(remainingTime[i] > quantum)
                {
                    time += quantum;
                    remainingTime[i] -= quantum;
                }
                else
                {
                    time += remainingTime[i];

                    wt[i] = time - burst_time[i];

                    remainingTime[i] = 0;
                }
            }
        }
        if(Taskdone == true)
        {
            break;
        }
    }

}
void findTat(int process[], int n, int tat[], int burst_time[], int wt[], int quantum)
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = burst_time[i] + wt[i];
    }
}
void findAvgTime(int process[], int n, int burst_time[], int quantum)
{
    // cout<<"Hello"<<endl;
    int wt[n], tat[n], total_tat=0, total_wt=0;
    findWaitingTime(process, n, wt, burst_time, quantum);
    findTat(process, n, tat, burst_time, wt, quantum);

    cout << "Process \t" << "Burst_Time \t" << "Turn Around Time\t" << "Waiting Time \t" << endl;
    for(int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i + 1 << "\t\t" << burst_time[i] << "\t\t" << tat[i] << "\t\t\t" << wt[i]<<endl;
    }
    cout << "Average waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}
int main()
{
    int process[] = {1, 2, 3};
    int burst_time[] = {8, 7, 6};
    int quantum = 2;
    findAvgTime(process, 3, burst_time, quantum);
    return 0;
}