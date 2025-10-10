#pragma ones

#include <string>
#include <stdexcept>

class Decimal {
private:
    unsigned char* digits;
    size_t size;
    
    // Вспомогательные методы
    void initFromString(const std::string& str);
    void removeLeadingZeros();
    int compare(const Decimal& other) const;

public:
    Decimal();
    Decimal(const size_t& n, unsigned char digit = 0);
    Decimal(const std::initializer_list<unsigned char>& digitsList);
    Decimal(const std::string& str);
    Decimal(const Decimal& other);
    Decimal(Decimal&& other) noexcept;
    virtual ~Decimal() noexcept;
    
    size_t getSize() const;
    unsigned char getDigit(size_t index) const;
    
    Decimal add(const Decimal& other) const;
    Decimal subtract(const Decimal& other) const;
    
    bool equals(const Decimal& other) const;
    bool lessThan(const Decimal& other) const;
    bool greaterThan(const Decimal& other) const;

    Decimal addAssign(const Decimal& other) const;
    Decimal subtractAssign(const Decimal& other) const;
    
    std::string toString() const;
    
    Decimal& operator=(const Decimal& other);
    Decimal& operator=(Decimal&& other) noexcept;
};