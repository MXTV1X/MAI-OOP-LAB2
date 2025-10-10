#include <gtest/gtest.h>
#include "../include/lab2.hpp"


TEST(Decimal, defaultConstructor) {
    Decimal num;
    EXPECT_EQ(num.toString(), "0");
}

TEST(Decimal, constructorFromString) {
    Decimal num("12345");
    EXPECT_EQ(num.toString(), "12345");
}

TEST(Decimal, constructorWithSizeAndDigit) {
    Decimal num(4, 5);
    EXPECT_EQ(num.toString(), "5555");
}

TEST(Decimal, constructorFromInitializerList) {
    Decimal num({1, 2, 3, 4, 5});
    EXPECT_EQ(num.toString(), "54321");
}

TEST(Decimal, copyConstructor) {
    Decimal original("123");
    Decimal copy(original);
    EXPECT_EQ(copy.toString(), "123");
}

TEST(Decimal, addSimpleNumbers) {
    Decimal a("123");
    Decimal b("456");
    Decimal result = a.add(b);
    EXPECT_EQ(result.toString(), "579");
}

TEST(Decimal, addWithCarry) {
    Decimal a("999");
    Decimal b("1");
    Decimal result = a.add(b);
    EXPECT_EQ(result.toString(), "1000");
}

TEST(Decimal, addDifferentSizes) {
    Decimal a("1000");
    Decimal b("99");
    Decimal result = a.add(b);
    EXPECT_EQ(result.toString(), "1099");
}

TEST(Decimal, addWithZero) {
    Decimal a("12345");
    Decimal zero;
    Decimal result = a.add(zero);
    EXPECT_EQ(result.toString(), "12345");
}

TEST(Decimal, subtractSimpleNumbers) {
    Decimal a("579");
    Decimal b("456");
    Decimal result = a.subtract(b);
    EXPECT_EQ(result.toString(), "123");
}

TEST(Decimal, subtractWithBorrow) {
    Decimal a("1000");
    Decimal b("1");
    Decimal result = a.subtract(b);
    EXPECT_EQ(result.toString(), "999");
}

TEST(Decimal, subtractEqualNumbers) {
    Decimal a("555");
    Decimal b("555");
    Decimal result = a.subtract(b);
    EXPECT_EQ(result.toString(), "0");
}

TEST(Decimal, subtractThrowsWhenNegativeResult) {
    Decimal a("100");
    Decimal b("200");
    EXPECT_THROW(a.subtract(b), std::invalid_argument);
}

TEST(Decimal, equalsSameNumbers) {
    Decimal a("123");
    Decimal b("123");
    EXPECT_TRUE(a.equals(b));
}

TEST(Decimal, equalsDifferentNumbers) {
    Decimal a("123");
    Decimal b("456");
    EXPECT_FALSE(a.equals(b));
}

TEST(Decimal, lessThanSmallerNumber) {
    Decimal a("123");
    Decimal b("456");
    EXPECT_TRUE(a.lessThan(b));
}

TEST(Decimal, lessThanLargerNumber) {
    Decimal a("456");
    Decimal b("123");
    EXPECT_FALSE(a.lessThan(b));
}

TEST(Decimal, greaterThanLargerNumber) {
    Decimal a("456");
    Decimal b("123");
    EXPECT_TRUE(a.greaterThan(b));
}

TEST(Decimal, greaterThanSmallerNumber) {
    Decimal a("123");
    Decimal b("456");
    EXPECT_FALSE(a.greaterThan(b));
}

TEST(Decimal, addAssignSimple) {
    Decimal a("100");
    Decimal b("50");
    Decimal result = a.addAssign(b);
    EXPECT_EQ(result.toString(), "150");
    EXPECT_EQ(a.toString(), "100"); // Original unchanged
}

TEST(Decimal, subtractAssignSimple) {
    Decimal a("100");
    Decimal b("25");
    Decimal result = a.subtractAssign(b);
    EXPECT_EQ(result.toString(), "75");
    EXPECT_EQ(a.toString(), "100"); // Original unchanged
}

TEST(Decimal, removeLeadingZeros) {
    Decimal num("000123");
    EXPECT_EQ(num.toString(), "123");
}

TEST(Decimal, allZerosBecomesSingleZero) {
    Decimal num("0000");
    EXPECT_EQ(num.toString(), "0");
}

TEST(Decimal, largeNumber) {
    Decimal num("12345678901234567890");
    EXPECT_EQ(num.toString(), "12345678901234567890");
}

TEST(Decimal, veryLargeAddition) {
    Decimal a("99999999999999999999");
    Decimal b("1");
    Decimal result = a.add(b);
    EXPECT_EQ(result.toString(), "100000000000000000000");
}

TEST(Decimal, getDigitValidIndex) {
    Decimal num("123");
    EXPECT_EQ(num.getDigit(0), 3); // units
    EXPECT_EQ(num.getDigit(1), 2); // tens
    EXPECT_EQ(num.getDigit(2), 1); // hundreds
}

TEST(Decimal, getDigitThrowsWhenInvalidIndex) {
    Decimal num("123");
    EXPECT_THROW(num.getDigit(5), std::out_of_range);
}

TEST(Decimal, getSize) {
    Decimal num1("123");
    Decimal num2("12345");
    EXPECT_EQ(num1.getSize(), 3);
    EXPECT_EQ(num2.getSize(), 5);
}

TEST(Decimal, assignmentOperator) {
    Decimal a("123");
    Decimal b("456");
    a = b;
    EXPECT_EQ(a.toString(), "456");
}

TEST(Decimal, immutabilityAfterOperations) {
    Decimal original("100");
    Decimal result1 = original.add(Decimal("50"));
    Decimal result2 = original.subtract(Decimal("25"));
    
    EXPECT_EQ(original.toString(), "100");
    EXPECT_EQ(result1.toString(), "150");
    EXPECT_EQ(result2.toString(), "75");
}

TEST(Decimal, constructorThrowsForInvalidDigit) {
    EXPECT_THROW(Decimal num(3, 10), std::invalid_argument);
}

TEST(Decimal, constructorThrowsForInvalidString) {
    EXPECT_THROW(Decimal num("12a34"), std::invalid_argument);
}