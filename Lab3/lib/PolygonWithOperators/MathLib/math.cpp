//
// Created by devsy on 02.10.2022.
//
#include "math.hpp"
#include <cstring>
#include <cmath>
#include <iostream>
namespace Math{
    bool Point::operator==(const Point &p) const {
        const float e = 1E-32;
        return std::fabs(x - p.x) < e && std::fabs(y - p.y) < e;
    }

    char *Point::toString() const {
        const Point &p = *this;
        const char *pattern = "(, )";
        int len = strlen(pattern) + 1;
        char num[20];
        sprintf_s(num, 20, "%.2f", p.x);
        len += strlen(num);
        sprintf_s(num, 20, "%.2f", p.y);
        len += strlen(num);
        char *res = new char[len];
        sprintf_s(res, len, "(%.2f, %.2f)", p.x, p.y);
        return res;
    }
}