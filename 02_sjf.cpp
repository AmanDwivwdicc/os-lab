// SJF (non-preemptive): among arrived processes, run the one with the shortest burst time.
#include <iostream>
using namespace std;

int main() {
    int n, at[20], bt[20], ct[20], tat[20], wt[20], done[20] = {0};

    cout << "Number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << " arrival time and burst time: ";
        cin >> at[i] >> bt[i];
    }

    int time = 0, count = 0;
    cout << "\nExecution order: ";
    while (count < n) {
        // Find the shortest job among processes that have arrived and are not finished
        int pick = -1;
        for (int i = 0; i < n; i++)
            if (done[i] == 0 && at[i] <= time)
                if (pick == -1 || bt[i] < bt[pick])
                    pick = i;

        if (pick == -1) { time++; continue; }   // nobody arrived yet: CPU idle

        time = time + bt[pick];                 // run the chosen process fully
        ct[pick]  = time;
        tat[pick] = ct[pick] - at[pick];
        wt[pick]  = tat[pick] - bt[pick];
        done[pick] = 1;
        count++;
        cout << "P" << pick + 1 << " ";
    }

    double totalWT = 0, totalTAT = 0;
    cout << "\n\nProcess  AT  BT  CT  TAT  WT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "       " << at[i] << "   " << bt[i] << "   " << ct[i]
             << "   " << tat[i] << "    " << wt[i] << "\n";
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    cout << "\nAverage waiting time    = " << totalWT / n;
    cout << "\nAverage turnaround time = " << totalTAT / n << "\n";
    return 0;
}
