#include <iostream>
#include <thread>
#include <chrono>

int myrand(int min, int max)
{
    return rand() % (max - min) + min;
}

void lock(int& m)
{
    m = 1;
}

void unlock(int& m)
{
    m = 0;
}

void philosopher(int ph, int& ma, int& mb)
{
    while (true)
    {
        int duration = myrand(1000, 2000);
        std::cout << ph << " thinks " << duration << "ms" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));

        lock(ma);
        std::cout << "\t\t" << ph << " get first fork" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        lock(mb);
        std::cout << "\t\t" << ph << " get got second fork" << std::endl;

        duration = myrand(1000, 2000);
        std::cout << "\t\t\t\t" << ph << " eats " << duration << "ms" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));

        unlock(mb);
        unlock(ma);
    }
}

int main()
{
    srand(time(nullptr));

    int m1{ 0 }, m2{ 0 }, m3{ 0 }, m4{ 0 };


    std::thread t1([&] {philosopher(1, m1, m2);});
    std::thread t2([&] {philosopher(2, m2, m3);});
    std::thread t3([&] {philosopher(3, m3, m4);});
    std::thread t4([&] {philosopher(4, m4, m1);});

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
