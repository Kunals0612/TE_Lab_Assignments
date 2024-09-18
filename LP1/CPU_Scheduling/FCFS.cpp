#include<bits/stdc++.h>
using namespace std;
void findCompletionTime(vector<int>& comp, vector<int>& BT)
{
    comp[0] = BT[0];
    for (int i = 1; i < BT.size(); i++)
    {
        comp[i] = comp[i - 1] + BT[i];
    }
}
void findTurnAroundTime(vector<int>& TAT, vector<int>& comp, vector<int>& AT)
{
    for (int i = 0; i < AT.size(); i++)
    {
        TAT[i] = comp[i] - AT[i];
    }
}
void findWeightTime(vector<int>& WT, vector<int>& TAT, vector<int>& BT)
{
    for (int i = 0; i < BT.size(); i++)
    {
        WT[i] = TAT[i] - BT[i];
    }
}
void findAvgTime(vector<int>& PID, vector<int>& BT, int n, vector<int> AT)
{
    vector<int> comp(n);
    vector<int> TAT(n);
    vector<int> WT(n);
    findCompletionTime(comp, BT);
    findTurnAroundTime(TAT, comp, AT);
    findWeightTime(WT, TAT, BT);
    float total_tat = 0;
    float total_wt = 0;
    cout << "PID" << "   " << "AT" << "   " << "BT" << "   " << "CT" << "   " << "TAT" << "   " << "WT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << PID[i] << "   " << AT[i] << "   " << BT[i] << "   " << comp[i] << "   " << TAT[i] << "   " << WT[i] << endl;
        total_tat += TAT[i];
        total_wt += WT[i];
    }
    cout << "AVG TAT: " << total_tat / n << endl;
    cout << "AVG WT: " << total_wt / n << endl;
}
void scheduleTask(vector<int>& schedule, vector<int>& AT, vector<int>& PID)
{
    vector<pair<int, int>> pr;
    for (int i = 0; i < PID.size(); i++)
    {
        pr.push_back(make_pair(AT[i], PID[i]));
    }
    for (int i = 0; i < pr.size(); i++)
    {
        cout << pr[i].first << " " << pr[i].second << endl;
    }
    sort(pr.begin(), pr.end());
    for (int i = 0; i < PID.size(); i++)
    {
        schedule.push_back(pr[i].second);
    }
    for (int i = 0; i < schedule.size(); i++)
    {
        cout << schedule[i] << " ";
    }
}
int main()
{
    vector<int> PID = {1, 2, 3};
    vector<int> AT = {7, 3, 7};
    vector<int> BT = {500, 100, 50};
    int n = PID.size();
    findAvgTime(PID, BT, n, AT);
    vector<int> schedule;
    scheduleTask(schedule, AT, PID);
    return 0;
}
