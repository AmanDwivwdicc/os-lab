// FIFO page replacement: when frames are full, remove the page that has been in memory the longest.
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

    for (int i = 0; i < f; i++) frames[i] = -1;   // -1 means the frame is empty

    int oldest = 0;      // index of the frame holding the oldest page
    int faults = 0;

    for (int i = 0; i < n; i++) {
        // Is the page already in a frame?
        bool found = false;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = true;

        if (!found) {                          // page fault
            frames[oldest] = pages[i];         // replace the oldest page
            oldest = (oldest + 1) % f;         // next oldest is the next frame
            faults++;
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
