#include <iostream>
#include "include/lab2.hpp"

int main() {
    try {
        Decimal num1("12345");
        Decimal num2("6789");
        Decimal num3({5, 4, 3, 2, 1});
        
        Decimal sum = num1.add(num2);
        Decimal diff = num1.subtract(num2);
        
        bool isEqual = num1.equals(num3);
        bool isGreater = num1.greaterThan(num2);
        
        std::cout << "num1: " << num1.toString() << std::endl;
        std::cout << "num2: " << num2.toString() << std::endl;
        std::cout << "sum: " << sum.toString() << std::endl;
        std::cout << "diff: " << diff.toString() << std::endl;
        std::cout << "num1 equals num3: " << isEqual << std::endl;
        std::cout << "num1 greater than num2: " << isGreater << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}