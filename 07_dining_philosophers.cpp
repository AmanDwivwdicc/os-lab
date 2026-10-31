// Dining Philosophers: 5 philosophers, 5 forks. A philosopher needs BOTH neighbouring forks to eat.
// To avoid deadlock, at most 4 philosophers are allowed to pick up forks at the same time.
// Compile with:  g++ -std=c++17 -pthread 07_dining_philosophers.cpp -o dp
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

Semaphore fork[5] = {Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1)};
Semaphore room(4);   // only 4 philosophers may try to eat at once -> no deadlock

void philosopher(int i) {
    int left = i, right = (i + 1) % 5;
    for (int meal = 1; meal <= 2; meal++) {
        printf("Philosopher %d is thinking\n", i);
        this_thread::sleep_for(chrono::milliseconds(100 * i));

        room.wait();          // enter the room
        fork[left].wait();    // pick up left fork
        fork[right].wait();   // pick up right fork

        printf("    Philosopher %d is eating (meal %d)\n", i, meal);
        this_thread::sleep_for(chrono::milliseconds(300));

        fork[right].signal(); // put down both forks
        fork[left].signal();
        room.signal();        // leave the room
    }
}

int main() {
    thread t[5];
    for (int i = 0; i < 5; i++) t[i] = thread(philosopher, i);
    for (int i = 0; i < 5; i++) t[i].join();
    printf("Everyone finished eating. No deadlock!\n");
    return 0;
}
