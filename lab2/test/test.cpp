#include <gtest/gtest.h>
#include "../include/lab2.hpp"

// === Конструкторы ===
TEST(DecimalConstructors, DefaultConstructor) {
    Decimal n;
    EXPECT_EQ(n.toString(), "0");
}

TEST(DecimalConstructors, SizeValueConstructor) {
    Decimal n(3, 5);
    EXPECT_EQ(n.toString(), "555");
}

TEST(DecimalConstructors, InitializerListConstructor) {
    Decimal n({1, 2, 3});
    EXPECT_EQ(n.toString(), "321");
}

TEST(DecimalConstructors, InitializerListConstructor2) {
    Decimal n({5, 0, 1});
    EXPECT_EQ(n.toString(), "105");
}

TEST(DecimalConstructors, StringConstructor) {
    Decimal n("12345");
    EXPECT_EQ(n.toString(), "12345");
}

TEST(DecimalConstructors, CopyConstructor) {
    Decimal n1("123");
    Decimal n2(n1);
    EXPECT_EQ(n2.toString(), "123");
}

TEST(DecimalConstructors, MoveConstructor) {
    Decimal n1(Decimal("123"));
    EXPECT_EQ(n1.toString(), "123");
}

TEST(DecimalConstructors, InvalidCharacterThrows) {
    EXPECT_THROW(Decimal("12A"), std::invalid_argument);
}

TEST(DecimalConstructors, InvalidDigitThrows) {
    EXPECT_THROW(Decimal(2, 15), std::invalid_argument);
}

// === Арифметические операции ===
TEST(DecimalArithmetic, Add) {
    Decimal n1("123");
    Decimal n2("45");
    Decimal sum = n1.add(n2);
    EXPECT_EQ(sum.toString(), "168");
}

TEST(DecimalArithmetic, AddWithCarry) {
    Decimal n1("999");
    Decimal n2("1");
    Decimal sum = n1.add(n2);
    EXPECT_EQ(sum.toString(), "1000");
}

TEST(DecimalArithmetic, Sub) {
    Decimal n1("123");
    Decimal n2("45");
    Decimal diff = n1.sub(n2);
    EXPECT_EQ(diff.toString(), "78");
}

TEST(DecimalArithmetic, SubNegativeThrows) {
    Decimal n1("45");
    Decimal n2("123");
    EXPECT_THROW(n1.sub(n2), std::invalid_argument);
}

TEST(DecimalArithmetic, AddAssign) {
    Decimal n1("100");
    Decimal n2("50");
    Decimal result = n1.addAssign(n2);
    EXPECT_EQ(result.toString(), "150");
}

TEST(DecimalArithmetic, SubAssign) {
    Decimal n1("100");
    Decimal n2("50");
    Decimal result = n1.subAssign(n2);
    EXPECT_EQ(result.toString(), "50");
}

TEST(DecimalArithmetic, CopyMethod) {
    Decimal n1("123");
    Decimal copy = n1.copy(n1);
    EXPECT_EQ(copy.toString(), "123");
}

// === Операции сравнения ===
TEST(DecimalComparison, EQ) {
    Decimal n1("123");
    Decimal n2("123");
    Decimal n3("124");
    EXPECT_TRUE(n1.EQ(n2));
    EXPECT_FALSE(n1.EQ(n3));
}

TEST(DecimalComparison, LT) {
    Decimal n1("123");
    Decimal n2("124");
    EXPECT_TRUE(n1.LT(n2));
    EXPECT_FALSE(n2.LT(n1));
}

TEST(DecimalComparison, GT) {
    Decimal n1("124");
    Decimal n2("123");
    EXPECT_TRUE(n1.GT(n2));
    EXPECT_FALSE(n2.GT(n1));
}

TEST(DecimalComparison, DifferentLengths) {
    Decimal n1("1000");
    Decimal n2("999");
    EXPECT_TRUE(n2.LT(n1));
    EXPECT_TRUE(n1.GT(n2));
}

// === toString ===
TEST(DecimalToString, CorrectString) {
    Decimal n("12345");
    EXPECT_EQ(n.toString(), "12345");
}

TEST(DecimalToString, RemoveLeadingZeros) {
    Decimal n("000123");
    EXPECT_EQ(n.toString(), "123");
}

TEST(DecimalToString, SingleZero) {
    Decimal n("0");
    EXPECT_EQ(n.toString(), "0");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}