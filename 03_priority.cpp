// Priority scheduling (non-preemptive): run the arrived process with the best priority.
// Here a SMALLER number means HIGHER priority (1 is the highest).
#include <iostream>
using namespace std;

int main() {
    int n, at[20], bt[20], pr[20], ct[20], tat[20], wt[20], done[20] = {0};

    cout << "Number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << " arrival time, burst time and priority: ";
        cin >> at[i] >> bt[i] >> pr[i];
    }

    int time = 0, count = 0;
    cout << "\nExecution order: ";
    while (count < n) {
        // Find the highest-priority process among those that have arrived
        int pick = -1;
        for (int i = 0; i < n; i++)
            if (done[i] == 0 && at[i] <= time)
                if (pick == -1 || pr[i] < pr[pick])
                    pick = i;

        if (pick == -1) { time++; continue; }   // CPU idle

        time = time + bt[pick];
        ct[pick]  = time;
        tat[pick] = ct[pick] - at[pick];
        wt[pick]  = tat[pick] - bt[pick];
        done[pick] = 1;
        count++;
        cout << "P" << pick + 1 << " ";
    }

    double totalWT = 0, totalTAT = 0;
    cout << "\n\nProcess  AT  BT  PR  CT  TAT  WT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "       " << at[i] << "   " << bt[i] << "   " << pr[i] << "   " << ct[i]
             << "   " << tat[i] << "    " << wt[i] << "\n";
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    cout << "\nAverage waiting time    = " << totalWT / n;
    cout << "\nAverage turnaround time = " << totalTAT / n << "\n";
    return 0;
}
