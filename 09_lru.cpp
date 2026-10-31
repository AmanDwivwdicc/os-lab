// LRU page replacement: remove the page that was used longest ago.
#include <iostream>
using namespace std;

int main() {
    int n, f, pages[50], frames[10], lastUsed[10];

    cout << "Number of pages: ";
    cin >> n;
    cout << "Reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Number of frames: ";
    cin >> f;

    for (int i = 0; i < f; i++) { frames[i] = -1; lastUsed[i] = -1; }   // -1 = empty

    int faults = 0;
    for (int i = 0; i < n; i++) {
        // Look for the page in the frames
        int pos = -1;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) pos = j;

        if (pos != -1) {
            lastUsed[pos] = i;                 // hit: remember when it was used
        } else {                               // page fault
            faults++;
            // Choose the frame with the smallest lastUsed (empty frames have -1, so they go first)
            int victim = 0;
            for (int j = 1; j < f; j++)
                if (lastUsed[j] < lastUsed[victim]) victim = j;
            frames[victim] = pages[i];
            lastUsed[victim] = i;
        }

        cout << "Page " << pages[i] << ": ";
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1) cout << "- ";
            else cout << frames[j] << " ";
        }
        cout << (pos != -1 ? "(hit)" : "(fault)") << "\n";
    }
    cout << "\nTotal page faults = " << faults << "\n";
    cout << "Total page hits   = " << n - faults << "\n";
    return 0;
}
