#include <iostream>
#include <chrono>
#include <thread>

double formula_1(double x) {
    return x*x - x*x + 4*x - 5*x + x + x;
}

double formula_2(double x) {
    return x + x;
}

double formula_3(double x) {
    return formula_1(x) + formula_2(x) - formula_1(x);
}

int main() {

    double x = 1.234;
    volatile double result = 0;

    //10 000 итераций

    auto start_10000 = std::chrono::high_resolution_clock::now();

    std::thread t1([&]() {
        for (int i = 1; i <= 10000; i++) {
            result = formula_1(x);
        }
    });

    std::thread t2([&]() {
        for (int i = 1; i <= 10000; i++) {
            result = formula_2(x);
        }
    });

    std::thread t3([&]() {
        for (int i = 1; i <= 10000; i++) {
            result = formula_3(x);
        }
    });

    t1.join();
    t2.join();
    t3.join();

    auto end_10000 = std::chrono::high_resolution_clock::now();

    //100 000 итераций

    auto start_100000 = std::chrono::high_resolution_clock::now();

    std::thread t4([&]() {
        for (int i = 1; i <= 100000; i++) {
            result = formula_1(x);
        }
    });

    std::thread t5([&]() {
        for (int i = 1; i <= 100000; i++) {
            result = formula_2(x);
        }
    });

    std::thread t6([&]() {
        for (int i = 1; i <= 100000; i++) {
            result = formula_3(x);
        }
    });

    t4.join();
    t5.join();
    t6.join();

    auto end_100000 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> iterations_10000 = end_10000 - start_10000;
    std::chrono::duration<double> iterations_100000 = end_100000 - start_100000;

    std::cout << "10.000 iterations parallel " << iterations_10000.count() << " seconds" << std::endl;
    std::cout << "100.000 iterations parallel " << iterations_100000.count() << " seconds" << std::endl;

    return 0;
}