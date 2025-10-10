#pragma once
#include <exception>
#include <vector>
#include <string>

using std::string;
using std::vector;

class Decimal{
public:
    // === КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ ===
    Decimal();
    Decimal(const size_t & n, unsigned char value = 0);
    Decimal(const std::initializer_list<unsigned char> &t);
    Decimal(const string &t); // создаёт объект из строки
    
    Decimal(const Decimal& other); // конструктор копирования
    Decimal(Decimal&& other) noexcept; // конструктор перемещения
    virtual ~Decimal() noexcept; // деструктор

    // === АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ===
    Decimal add(const Decimal& other) const;
    Decimal sub(const Decimal& other) const;
    Decimal copy(const Decimal& other) const;

    // === АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ С ПРИСВАИВАНИЕМ ===
    Decimal addAssign(const Decimal& other) const;
    Decimal subAssign(const Decimal& other) const;

    // === ОПЕРАЦИИ СРАВНЕНИЯ ===
    bool EQ(const Decimal& other) const;
    bool LT(const Decimal& other) const;
    bool GT(const Decimal& other) const;

    string toString() const;
    
    // === ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ ===
    size_t size() const { return digits.size(); }
    unsigned char operator[](size_t index) const { return digits[index]; }

private:
    // === ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ САМОГО КЛАССА ===
    vector<unsigned char> digits;
    void removeZeros();
    unsigned char getDigitOrZero(size_t i) const;
    unsigned char charToDigit(char c) const;
    unsigned char digitToChar(unsigned char d) const;
};