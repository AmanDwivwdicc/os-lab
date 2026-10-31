// FCFS: the process that arrives first runs first.
#include <iostream>
using namespace std;

int main() {
    int n, id[20], at[20], bt[20], ct[20], tat[20], wt[20];
    // at = arrival time, bt = burst time (CPU time needed)
    // ct = completion time, tat = turnaround time, wt = waiting time

    cout << "Number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        cout << "P" << id[i] << " arrival time and burst time: ";
        cin >> at[i] >> bt[i];
    }

    // Step 1: sort processes by arrival time (bubble sort)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(id[j], id[j + 1]);
            }

    // Step 2: run them one by one in that order
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];   // CPU waits if process hasn't arrived yet
        time = time + bt[i];              // process runs till it finishes
        ct[i]  = time;
        tat[i] = ct[i] - at[i];           // turnaround = completion - arrival
        wt[i]  = tat[i] - bt[i];          // waiting    = turnaround - burst
    }

    // Step 3: print results
    double totalWT = 0, totalTAT = 0;
    cout << "\nProcess  AT  BT  CT  TAT  WT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << id[i] << "       " << at[i] << "   " << bt[i] << "   " << ct[i]
             << "   " << tat[i] << "    " << wt[i] << "\n";
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    cout << "\nAverage waiting time    = " << totalWT / n;
    cout << "\nAverage turnaround time = " << totalTAT / n << "\n";
    return 0;
}
