#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

mutex forks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    while(true) {
        cout << "Philosopher " << id << " is thinking." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "Philosopher " << id << " is hungry." << endl;

        forks[left_fork].lock();
        forks[right_fork].lock();

        cout << "Philosopher " << id << " is eating." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        forks[right_fork].unlock();
        forks[left_fork].unlock();
    }
}

int main() {
    thread philosophers[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i] = thread(philosopher, i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].join();
    }
    return 0;
}
