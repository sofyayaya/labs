#include <iostream>
#include <chrono>
#include <windows.h>

double formula_1(double x) {
    return x*x - x*x + 4*x - 5*x + x + x;
}

double formula_2(double x) {
    return x + x;
}

int main() {
    double x = 1.234;

    //10 000 итераций ============

    auto start_10000 = std::chrono::high_resolution_clock::now();

    HANDLE file_10000 = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(double) * 10000 * 2,
        "MemoryFor10000"
    );

    double* shared = (double*)MapViewOfFile(
        file_10000,
        FILE_MAP_ALL_ACCESS,
        0, 0,
        sizeof(double) * 10000 * 2
    );

    STARTUPINFOA si1 = {sizeof(si1)};
    PROCESS_INFORMATION pi1;
    CreateProcessA(
        NULL,
        (LPSTR)"child.exe 1 10000",
        NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1
    );

    STARTUPINFOA si2 = {sizeof(si2)};
    PROCESS_INFORMATION pi2;
    CreateProcessA(
        NULL,
        (LPSTR)"child.exe 2 10000",
        NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2
    );

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    volatile double r3_10000 = 0;
    for (int i = 0; i < 10000; i++) {
        double r1 = shared[i];
        double r2 = shared[i + 10000];
        r3_10000 = r1 + r2 - r1;
    }

    auto end_10000 = std::chrono::high_resolution_clock::now();

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);
    UnmapViewOfFile(shared);
    CloseHandle(file_10000);

    //100 000 итераций

    auto start_100000 = std::chrono::high_resolution_clock::now();

    HANDLE file_100000 = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(double) * 100000 * 2,
        "MemoryFor100000"
    );

    double* shared2 = (double*)MapViewOfFile(
        file_100000,
        FILE_MAP_ALL_ACCESS,
        0, 0,
        sizeof(double) * 100000 * 2
    );

    STARTUPINFOA si3 = {sizeof(si3)};
    PROCESS_INFORMATION pi3;
    CreateProcessA(
        NULL,
        (LPSTR)"child.exe 1 100000",
        NULL, NULL, FALSE, 0, NULL, NULL, &si3, &pi3
    );

    STARTUPINFOA si4 = {sizeof(si4)};
    PROCESS_INFORMATION pi4;
    CreateProcessA(
        NULL,
        (LPSTR)"child.exe 2 100000",
        NULL, NULL, FALSE, 0, NULL, NULL, &si4, &pi4
    );

    WaitForSingleObject(pi3.hProcess, INFINITE);
    WaitForSingleObject(pi4.hProcess, INFINITE);

    volatile double r3_100000 = 0;
    for (int i = 0; i < 100000; i++) {
        double r1 = shared2[i];
        double r2 = shared2[i + 100000];
        r3_100000 = r1 + r2 - r1;
    }

    auto end_100000 = std::chrono::high_resolution_clock::now();

    CloseHandle(pi3.hProcess);
    CloseHandle(pi3.hThread);
    CloseHandle(pi4.hProcess);
    CloseHandle(pi4.hThread);
    UnmapViewOfFile(shared2);
    CloseHandle(file_100000);

    std::chrono::duration<double> time_10000 = end_10000 - start_10000;
    std::chrono::duration<double> time_100000 = end_100000 - start_100000;

    std::cout << "10.000 iterations processes " << time_10000.count() << " seconds" << std::endl;
    std::cout << "100.000 iterations processes " << time_100000.count() << " seconds" << std::endl;

    return 0;
}