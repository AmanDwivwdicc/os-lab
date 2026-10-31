// Round Robin: every process gets the CPU for at most one time quantum, then the next one gets a turn.
#include <iostream>
using namespace std;

int main() {
    int n, tq, at[20], bt[20], rem[20], ct[20], tat[20], wt[20];
    // rem = remaining burst time of each process

    cout << "Number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << " arrival time and burst time: ";
        cin >> at[i] >> bt[i];
        rem[i] = bt[i];
    }
    cout << "Time quantum: ";
    cin >> tq;

    int time = 0, count = 0;
    cout << "\nGantt (process: start -> end)\n";
    while (count < n) {
        bool ranSomeone = false;
        for (int i = 0; i < n; i++) {                 // go through processes in a circle
            if (rem[i] > 0 && at[i] <= time) {        // arrived and not finished
                int run = tq;
                if (rem[i] < tq) run = rem[i];        // run for tq or less if it needs less
                cout << "P" << i + 1 << ": " << time << " -> " << time + run << "\n";
                time = time + run;
                rem[i] = rem[i] - run;
                ranSomeone = true;
                if (rem[i] == 0) {                    // process finished
                    ct[i]  = time;
                    tat[i] = ct[i] - at[i];
                    wt[i]  = tat[i] - bt[i];
                    count++;
                }
            }
        }
        if (!ranSomeone) time++;                      // nobody ready: CPU idle
    }

    double totalWT = 0, totalTAT = 0;
    cout << "\nProcess  AT  BT  CT  TAT  WT\n";
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
