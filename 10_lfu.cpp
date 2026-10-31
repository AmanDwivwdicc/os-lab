// LFU page replacement: remove the page that has been used the fewest times.
// If two pages are tied, remove the one that was loaded earlier.
#include <iostream>
using namespace std;

int main() {
    int n, f, pages[50], frames[10], count[10], loadedAt[10];
    // count[j] = how many times the page in frame j was used, loadedAt[j] = when it was loaded

    cout << "Number of pages: ";
    cin >> n;
    cout << "Reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Number of frames: ";
    cin >> f;

    for (int i = 0; i < f; i++) { frames[i] = -1; count[i] = 0; loadedAt[i] = -1; }

    int faults = 0;
    for (int i = 0; i < n; i++) {
        int pos = -1;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) pos = j;

        if (pos != -1) {
            count[pos]++;                      // hit: page used once more
        } else {                               // page fault
            faults++;
            int victim = -1;
            for (int j = 0; j < f; j++)        // use an empty frame if there is one
                if (frames[j] == -1) { victim = j; break; }

            if (victim == -1) {                // all full: find least frequently used
                victim = 0;
                for (int j = 1; j < f; j++) {
                    if (count[j] < count[victim]) victim = j;
                    else if (count[j] == count[victim] && loadedAt[j] < loadedAt[victim]) victim = j;
                }
            }
            frames[victim] = pages[i];
            count[victim] = 1;
            loadedAt[victim] = i;
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
