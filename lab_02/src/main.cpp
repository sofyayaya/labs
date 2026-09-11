#include <iostream>
#include <chrono>
#include <string>
#include <cctype>
double compute(double x) {
    return x*x- x*x + x*4- x*5 + x + x;
}
int main() {
    std::string input;
    while (true) {
    std::cout << "Enter number of iterations (or non-number to exit): ";
    std::cin >> input;
    bool is_number = true;
    for (char c : input) {
        if (!std::isdigit(c)) {
        is_number = false;
        break;
        }
    }
    if (!is_number) {
        std::cout << "Non-numeric input. Exiting." << std::endl;
        break;
    }
    long long n = std::stoll(input);
    volatile double x = 1.234;
    auto start = std::chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; ++i) {
        compute(x);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end- start;
    std::cout << "Time for " << n << " iterations: " << elapsed.count() <<
    "seconds" << std::endl;
    }
return 0;
}