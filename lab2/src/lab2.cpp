#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "../include/lab2.hpp"

Decimal::Decimal() {
    digits.push_back(0);
}

Decimal::Decimal(const size_t & n, unsigned char value) : digits(n, value) {
    if (value > 9){
        throw std::invalid_argument("Цифра не может быть больше 9");
    }
    removeZeros();
}

Decimal::Decimal(const std::initializer_list<unsigned char> &t) {
    for (auto it = t.begin(); it != t.end(); ++it){
        if (*it > 9){
            throw std::invalid_argument("Некорректная цифра (должна быть от 0 до 9)");
        }
        digits.push_back(*it);
    }
    removeZeros();
}

Decimal::Decimal(const string& t){
    if (t.empty()){
        throw std::invalid_argument("Пустая строка");
    }
    
    for (auto it = t.rbegin(); it != t.rend(); ++it){ // начинаем с младших разрядов
        digits.push_back(charToDigit(*it));
    }
    removeZeros();
}

Decimal::Decimal(const Decimal &other) = default;
Decimal::Decimal(Decimal&& other) noexcept = default;
Decimal::~Decimal() noexcept = default;

void Decimal::removeZeros(){
    while(digits.size() > 1 && digits.back() == 0){
        digits.pop_back();
    }
}

unsigned char Decimal::charToDigit(char c) const{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    throw std::invalid_argument("Недопустимый символ для десятичного числа");
}

unsigned char Decimal::digitToChar(unsigned char d) const{
    if (d > 9){
        throw std::invalid_argument("Цифра больше 9");
    }
    return '0' + d;
}

unsigned char Decimal::getDigitOrZero(size_t i) const{
    return i < digits.size() ? digits[i] : 0;
}

string Decimal::toString() const{
    if (digits.empty()){
        return "0";
    }
    string res;
    res.reserve(digits.size());
    
    // начинаем с последнего элемента (старшей цифры)
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i){
        res += digitToChar(digits[i]);
    }
    return res;
}

Decimal Decimal::copy(const Decimal& other) const{
    return other;
}

Decimal Decimal::add(const Decimal& other) const{
    Decimal res;
    res.digits.clear(); // очищаем цифру по умолчанию
    
    unsigned char carry = 0;
    size_t i = 0;
    size_t maxSize = std::max(digits.size(), other.digits.size());
    
    while (i < maxSize || carry){
        unsigned char sum = getDigitOrZero(i) + other.getDigitOrZero(i) + carry;
        res.digits.push_back(sum % 10);
        carry = sum / 10;
        i++;
    }
    res.removeZeros();
    return res;
}

Decimal Decimal::sub(const Decimal& other) const{
    if (this->LT(other)){
        throw std::invalid_argument("Результат вычитания отрицателен");
    }

    Decimal res;
    res.digits.clear(); // очищаем цифру по умолчанию
    
    unsigned char borrow = 0;
    size_t i = 0;
    size_t maxSize = std::max(digits.size(), other.digits.size());
    
    while(i < maxSize){
        int diff = int(getDigitOrZero(i)) - int(other.getDigitOrZero(i)) - borrow;
        if (diff < 0){
            diff += 10;
            borrow = 1;
        }
        else{
            borrow = 0;
        }
        res.digits.push_back(static_cast<unsigned char>(diff));
        i++;
    }
    res.removeZeros();
    return res;
}

// Сложение с присваиванием
Decimal Decimal::addAssign(const Decimal& other) const{
    return this->add(other);
}

// Вычитание с присваиванием
Decimal Decimal::subAssign(const Decimal& other) const{
    return this->sub(other);
}

bool Decimal::EQ(const Decimal& other) const{
    if (digits.size() != other.digits.size()){
        return false;
    }
    
    for (size_t i = 0; i < digits.size(); i++){
        if (digits[i] != other.digits[i]){
            return false;
        }
    }
    return true;
}

bool Decimal::LT(const Decimal& other) const{
    if (digits.size() != other.digits.size()){
        return digits.size() < other.digits.size();
    }

    // сравниваем с старших разрядов
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--){
        if (digits[i] != other.digits[i]){
            return digits[i] < other.digits[i];
        }
    }
    return false; // числа равны
}

bool Decimal::GT(const Decimal& other) const{
    return !EQ(other) && !LT(other);
}