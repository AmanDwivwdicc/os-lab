// Readers-Writers: many readers can read together, but a writer needs the data all to itself.
// Compile with:  g++ -std=c++17 -pthread 06_readers_writers.cpp -o rw
#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

class Semaphore {
    mutex m;
    condition_variable cv;
    int count;
public:
    Semaphore(int c) { count = c; }
    void wait() {
        unique_lock<mutex> lock(m);
        while (count == 0) cv.wait(lock);
        count--;
    }
    void signal() {
        { lock_guard<mutex> lock(m); count++; }
        cv.notify_one();
    }
};

Semaphore countLock(1);   // protects the readerCount variable
Semaphore dataLock(1);    // whoever holds this has the data (a writer, or the group of readers)
int readerCount = 0;
int data = 0;             // the shared data

void reader(int id) {
    countLock.wait();
    readerCount++;
    if (readerCount == 1) dataLock.wait();   // first reader blocks writers
    countLock.signal();

    printf("Reader %d reads data = %d\n", id, data);   // reading (many readers at once is fine)
    this_thread::sleep_for(chrono::milliseconds(200));

    countLock.wait();
    readerCount--;
    if (readerCount == 0) dataLock.signal(); // last reader lets writers in
    countLock.signal();
}

void writer(int id) {
    dataLock.wait();                         // writer needs exclusive access
    data++;
    printf("    Writer %d wrote data = %d\n", id, data);
    this_thread::sleep_for(chrono::milliseconds(200));
    dataLock.signal();
}

int main() {
    thread t[5];
    t[0] = thread(reader, 1);
    t[1] = thread(writer, 1);
    t[2] = thread(reader, 2);
    t[3] = thread(reader, 3);
    t[4] = thread(writer, 2);
    for (int i = 0; i < 5; i++) t[i].join();
    return 0;
}
