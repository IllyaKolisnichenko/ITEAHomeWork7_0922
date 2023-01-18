#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mtx;

void philosofer(int philosoferNumber, std::mutex& leftFork, std::mutex& rightFork) {
    while (true) {
        {
            std::lock_guard<std::mutex> ph(mtx);
            std::cout << "Philosofer " << philosoferNumber << " meditates " << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::lock_guard<std::mutex> left(leftFork);
        {
            std::lock_guard<std::mutex> ph(mtx);
            std::cout << "\t\t\t" << "Philosofer " << philosoferNumber << " take left for" << std::endl;
        }

        std::lock_guard<std::mutex> right(rightFork);
        {
            std::lock_guard<std::mutex> ph(mtx);
            std::cout << "\t\t\t" << "Philosofer " << philosoferNumber << " take right fork" << std::endl;
        }

        {
            std::lock_guard<std::mutex> ph(mtx);
            std::cout << "\t\t\t\t\t\t\t" << "Philosofer " << philosoferNumber << " eat spaghetti " << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}


int main() {
    std::mutex fork1, fork2, fork3, fork4, fork5;

    std::thread th1([&] {philosofer(1, fork1, fork2); });
    std::thread th2([&] {philosofer(2, fork2, fork3); });
    std::thread th3([&] {philosofer(3, fork3, fork4); });
    std::thread th4([&] {philosofer(4, fork4, fork5); });
    std::thread th5([&] {philosofer(5, fork1, fork5); });

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
}