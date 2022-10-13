#include "math.hpp"
#include <cstring>
#include <cmath>
namespace Math {
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

    std::istream &operator>>(std::istream &in, Point &p) {
        float _x, _y;
        in >> _x >> _y;
        if (!in.good()) {
            throw std::invalid_argument("wrong coordinates");
        }
        p.x = _x;
        p.y = _y;
        return in;
    }
}