#include <iostream>
#include <windows.h>
#include <cstdlib>

double formula_1(double x) {
    return x*x - x*x + 4*x - 5*x + x + x;
}

double formula_2(double x) {
    return x + x;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: child.exe <formula> <iterations>" << std::endl;
        return 1;
    }

    int formula = atoi(argv[1]);
    int n = atoi(argv[2]);

    HANDLE hMap;
    if (n == 10000) {
        hMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "MemoryFor10000");
    } else {
        hMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "MemoryFor100000");
    }

    if (hMap == NULL) {
        std::cerr << "Не удалось открыть память" << std::endl;
        return 1;
    }

    double* shared = (double*)MapViewOfFile(
        hMap, FILE_MAP_ALL_ACCESS, 0, 0,
        sizeof(double) * n * 2
    );

    double x = 1.234;

    if (formula == 1) {
        for (int i = 0; i < n; i++) {
            shared[i] = formula_1(x);
        }
    } else {
        for (int i = 0; i < n; i++) {
            shared[i + n] = formula_2(x);
        }
    }

    UnmapViewOfFile(shared);
    CloseHandle(hMap);
    return 0;
}