#include "gtest/gtest.h"
#include "..\Lab2Lib\OOPLab2.hpp"

/**
 * Функция, передающая инициализирующему конструктору Verziera
 *  некорректные параметры.
 * */
void illegalArgumentInitialization() {
    double illegalArg = -1.45;
    Lab2::Verziera v(illegalArg);
}

TEST(VerzieraConstructors, EmptyConstructor) {
    Lab2::Verziera v;
    const double error = 0.1;
    ASSERT_NEAR(1.0, v.getA().y, error);
}

TEST(VerzieraConstructors, InitConstructor) {
    Lab2::Verziera v(2.0);
    const double error = 0.1;
    ASSERT_NEAR(2.0, v.getA().y, error);
    ASSERT_THROW(illegalArgumentInitialization(), std::logic_error);
}

TEST(VerzieraMethods, Setters) {
    Lab2::Verziera v;
    v.setA(2.0);
    const double error = 0.1;
    ASSERT_NEAR(2.0, v.getA().y, error);
    ASSERT_THROW(v.setA(-1.2), std::logic_error);
}

TEST(VerzieraMethods, Parameters) {
    Lab2::Verziera v;
    const double error = 0.001;
    ASSERT_NEAR(3.142, v.getSquare(), error);
    ASSERT_NEAR(4.935, v.getVolume(), error);
    Lab2::Point *p = v.getInflectionPoints();
    ASSERT_NEAR(0.75, p[0].y, error);
    ASSERT_NEAR(0.577, p[0].x, error);
    ASSERT_NEAR(-0.577, p[1].x, error);
    delete[] p;
    char *s = v.toString();
    ASSERT_STREQ("y = 1.00 / (x ^ 2 + 1.00)", s);
    delete[] s;
    v.setA(2);
    s = v.toString();
    ASSERT_STREQ("y = 8.00 / (x ^ 2 + 4.00)",s);
    delete[] s;
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest();
    return ::RUN_ALL_TESTS();
}
