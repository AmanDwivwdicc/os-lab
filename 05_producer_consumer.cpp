// Producer-Consumer: a producer puts items in a small buffer, a consumer takes them out.
// Semaphores make sure: producer waits if buffer is full, consumer waits if it is empty.
// Compile with:  g++ -std=c++17 -pthread 05_producer_consumer.cpp -o pc
#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

// A tiny semaphore: wait() = take one (sleep if none), signal() = give one back.
class Semaphore {
    mutex m;
    condition_variable cv;
    int count;
public:
    Semaphore(int c) { count = c; }
    void wait() {
        unique_lock<mutex> lock(m);
        while (count == 0) cv.wait(lock);   // sleep until someone signals
        count--;
    }
    void signal() {
        { lock_guard<mutex> lock(m); count++; }
        cv.notify_one();
    }
};

const int SIZE = 3;          // buffer size
int buffer[SIZE];
int in = 0, out = 0;         // where to put / take the next item
Semaphore emptySlots(SIZE);  // how many free slots
Semaphore fullSlots(0);      // how many filled slots
Semaphore lockBuf(1);        // only one thread touches buffer at a time

void producer() {
    for (int item = 1; item <= 8; item++) {
        emptySlots.wait();               // wait for a free slot
        lockBuf.wait();
        buffer[in] = item;               // put item
        in = (in + 1) % SIZE;
        printf("Produced %d\n", item);
        lockBuf.signal();
        fullSlots.signal();              // one more filled slot
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer() {
    for (int i = 1; i <= 8; i++) {
        fullSlots.wait();                // wait for an item
        lockBuf.wait();
        int item = buffer[out];          // take item
        out = (out + 1) % SIZE;
        printf("    Consumed %d\n", item);
        lockBuf.signal();
        emptySlots.signal();             // one more free slot
        this_thread::sleep_for(chrono::milliseconds(250));   // slow consumer so buffer fills up
    }
}

int main() {
    thread p(producer), c(consumer);
    p.join();
    c.join();
    return 0;
}
