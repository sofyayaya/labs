#include <iostream>
#include <string>

long long pow(long long operand_1, long long operand_2) {
    if (operand_1 == 0 and operand_2 == 0) {
        return 1;
    }
    if (operand_2 < 0) {
        std::cout << operand_2 << " must be > 0" << std::endl;
        return 0;
    }
    long long result = 1;
    for (int i = 1; i <= operand_2; i++) {
        result = result * operand_1;
    }
    return result;
}

long long calculate(long long operand_1, long long operand_2, char op) {
    if (op == '+') {
        return operand_1 + operand_2;
    }
    if (op == '-') {
        return operand_1 - operand_2;
    }
    if (op == '^') {
        return pow(operand_1, operand_2);
    }
    std::cout << "Error \n" << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Incorrect input \n" << std::endl;
        return 1;
    }
    long long a = std::stoll(argv[1]);
    long long b = std::stoll(argv[2]);
    char op = argv[3][0];
    long long result = calculate(a, b, op);
    std::cout << result << std::endl;
    return 0;
}