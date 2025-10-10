#include <iostream>
#include "include/lab2.hpp"

int main() {
    
    // === ДЕМОНСТРАЦИЯ РАЗЛИЧНЫХ КОНСТРУКТОРОВ ===
    
    Decimal firstNum("123");
    std::cout << "Первое число: " << firstNum.toString() << std::endl;

    Decimal secondNum("45");
    std::cout << "Второе число: " << secondNum.toString() << std::endl;

    Decimal defaultNum;
    std::cout << "Число по умолчанию: " << defaultNum.toString() << std::endl;

    Decimal initListNum({3, 2, 1}); // создаст число 123
    std::cout << "Число из списка инициализации: " << initListNum.toString() << std::endl;

    Decimal sizeValueNum(4, 7); // создаст число 7777
    std::cout << "Число из размера и значения: " << sizeValueNum.toString() << std::endl;

    Decimal copyNum(firstNum.copy(firstNum));
    std::cout << "Копия первого числа: " << copyNum.toString() << std::endl;

    // === ДЕМОНСТРАЦИЯ АРИФМЕТИЧЕСКИХ ОПЕРАЦИЙ ===

    Decimal sumNum = firstNum.add(secondNum);
    std::cout << "Сумма 123 + 45 = " << sumNum.toString() << std::endl;

    Decimal diffNum = firstNum.sub(secondNum);
    std::cout << "Разность 123 - 45 = " << diffNum.toString() << std::endl;

    Decimal sumAssignNum = firstNum.addAssign(secondNum);
    std::cout << "Сумма с присваиванием: " << sumAssignNum.toString() << std::endl;

    Decimal subAssignNum = firstNum.subAssign(secondNum);
    std::cout << "Разность с присваиванием: " << subAssignNum.toString() << std::endl;

    // === ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ СРАВНЕНИЯ ===
    
    std::cout << "firstNum == secondNum? " << (firstNum.EQ(secondNum) ? "true" : "false") << std::endl;
    std::cout << "firstNum < secondNum? " << (firstNum.LT(secondNum) ? "true" : "false") << std::endl;
    std::cout << "firstNum > secondNum? " << (firstNum.GT(secondNum) ? "true" : "false") << std::endl;

    // === ДЕМОНСТРАЦИЯ ОБРАБОТКИ ИСКЛЮЧЕНИЙ ===
    
    try {
        Decimal invalidNum("12A");  // некорректный символ
    } catch (std::exception& exception) {
        std::cerr << "Перехвачено исключение: " << exception.what() << std::endl;
    }

    try {
        Decimal invalidDigit(3, 15);  // некорректная цифра
    } catch (std::exception& exception) {
        std::cerr << "Перехвачено исключение: " << exception.what() << std::endl;
    }

    try {
        Decimal smallNum("25");
        Decimal largeNum("100");
        smallNum.sub(largeNum);  // отрицательный результат
    } catch (std::exception& exception) {
        std::cerr << "Перехвачено исключение: " << exception.what() << std::endl;
    }

    return 0;
}