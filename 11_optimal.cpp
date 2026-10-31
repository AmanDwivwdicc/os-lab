// Optimal page replacement: remove the page that will not be needed for the longest time in the future.
#include <iostream>
using namespace std;

int main() {
    int n, f, pages[50], frames[10];

    cout << "Number of pages: ";
    cin >> n;
    cout << "Reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Number of frames: ";
    cin >> f;

    for (int i = 0; i < f; i++) frames[i] = -1;   // -1 = empty

    int faults = 0;
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = true;

        if (!found) {                          // page fault
            faults++;
            int victim = -1;
            for (int j = 0; j < f; j++)        // use an empty frame if there is one
                if (frames[j] == -1) { victim = j; break; }

            if (victim == -1) {                // all full: look into the future
                int farthest = -1;
                for (int j = 0; j < f; j++) {
                    int next = i + 1;
                    while (next < n && pages[next] != frames[j]) next++;   // when is it used next?
                    // next == n means "never used again" -> best one to remove
                    if (next > farthest) { farthest = next; victim = j; }
                }
            }
            frames[victim] = pages[i];
        }

        cout << "Page " << pages[i] << ": ";
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1) cout << "- ";
            else cout << frames[j] << " ";
        }
        cout << (found ? "(hit)" : "(fault)") << "\n";
    }
    cout << "\nTotal page faults = " << faults << "\n";
    cout << "Total page hits   = " << n - faults << "\n";
    return 0;
}
