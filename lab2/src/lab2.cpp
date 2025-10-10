#include "../include/lab2.hpp"
#include <algorithm>
#include <cstring>

Decimal::Decimal() : digits(new unsigned char[1]{0}), size(1) {}

Decimal::Decimal(const size_t& n, unsigned char digit) : size(n) {
    if (digit > 9) {
        throw std::invalid_argument("Digit must be between 0 and 9");
    }
    digits = new unsigned char[n];
    std::fill(digits, digits + n, digit);
}

Decimal::Decimal(const std::initializer_list<unsigned char>& digitsList) : size(digitsList.size()) {
    digits = new unsigned char[size];
    size_t i = 0;
    for (auto digit : digitsList) {
        if (digit > 9) {
            delete[] digits;
            throw std::invalid_argument("Digit must be between 0 and 9");
        }
        digits[i++] = digit;
    }
}

void Decimal::initFromString(const std::string& str) {
    if (str.empty()) {
        size = 1;
        digits = new unsigned char[1]{0};
        return;
    }
    
    size = str.length();
    digits = new unsigned char[size];
    
    for (size_t i = 0; i < size; ++i) {
        char c = str[size - 1 - i];
        if (c < '0' || c > '9') {
            delete[] digits;
            throw std::invalid_argument("String must contain only digits");
        }
        digits[i] = c - '0';
    }
    
    removeLeadingZeros();
}

Decimal::Decimal(const std::string& str) {
    initFromString(str);
}

Decimal::Decimal(const Decimal& other) : size(other.size) {
    digits = new unsigned char[size];
    std::copy(other.digits, other.digits + size, digits);
}

Decimal::Decimal(Decimal&& other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

Decimal::~Decimal() noexcept {
    delete[] digits;
}

void Decimal::removeLeadingZeros() {
    if (size == 1) return;
    
    size_t newSize = size;
    while (newSize > 1 && digits[newSize - 1] == 0) {
        --newSize;
    }
    
    if (newSize != size) {
        unsigned char* newDigits = new unsigned char[newSize];
        std::copy(digits, digits + newSize, newDigits);
        delete[] digits;
        digits = newDigits;
        size = newSize;
    }
}

int Decimal::compare(const Decimal& other) const {
    if (size != other.size) {
        return size > other.size ? 1 : -1;
    }
    
    for (size_t i = size; i > 0; --i) {
        size_t idx = i - 1;
        if (digits[idx] != other.digits[idx]) {
            return digits[idx] > other.digits[idx] ? 1 : -1;
        }
    }
    
    return 0;
}

size_t Decimal::getSize() const {
    return size;
}

unsigned char Decimal::getDigit(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return digits[index];
}

Decimal Decimal::add(const Decimal& other) const {
    size_t maxSize = std::max(size, other.size);
    size_t resultSize = maxSize + 1;
    unsigned char* resultDigits = new unsigned char[resultSize]{0};
    
    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char sum = carry;
        if (i < size) sum += digits[i];
        if (i < other.size) sum += other.digits[i];
        
        resultDigits[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0) {
        resultDigits[maxSize] = carry;
    } else {
        resultSize = maxSize;
    }
    
    Decimal result;
    delete[] result.digits;
    result.digits = resultDigits;
    result.size = resultSize;
    result.removeLeadingZeros();
    
    return result;
}

Decimal Decimal::subtract(const Decimal& other) const {
    if (lessThan(other)) {
        throw std::invalid_argument("Result would be negative");
    }
    
    size_t resultSize = size;
    unsigned char* resultDigits = new unsigned char[resultSize]{0};
    
    unsigned char borrow = 0;
    for (size_t i = 0; i < size; ++i) {
        int diff = digits[i] - borrow;
        if (i < other.size) {
            diff -= other.digits[i];
        }
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        resultDigits[i] = diff;
    }
    
    Decimal result;
    delete[] result.digits;
    result.digits = resultDigits;
    result.size = resultSize;
    result.removeLeadingZeros();
    
    return result;
}

bool Decimal::equals(const Decimal& other) const {
    return compare(other) == 0;
}

bool Decimal::lessThan(const Decimal& other) const {
    return compare(other) < 0;
}

bool Decimal::greaterThan(const Decimal& other) const {
    return compare(other) > 0;
}

Decimal Decimal::addAssign(const Decimal& other) const {
    return add(other);
}

Decimal Decimal::subtractAssign(const Decimal& other) const {
    return subtract(other);
}

std::string Decimal::toString() const {
    if (size == 0) return "0";
    
    std::string result;
    result.reserve(size);
    
    for (size_t i = size; i > 0; --i) {
        result += '0' + digits[i - 1];
    }
    
    return result;
}

Decimal& Decimal::operator=(const Decimal& other) {
    if (this != &other) {
        delete[] digits;
        size = other.size;
        digits = new unsigned char[size];
        std::copy(other.digits, other.digits + size, digits);
    }
    return *this;
}

Decimal& Decimal::operator=(Decimal&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;
        size = other.size;
        other.digits = nullptr;
        other.size = 0;
    }
    return *this;
}