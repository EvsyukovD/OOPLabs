#include "DynamicPolygon.hpp"
#include "DialogLib/dialog.hpp"
#include <cmath>
#include <cstring>

namespace DynamicPolygon {
    Polygon::Polygon() {

    }

    bool Polygon::check(const Math::Point &p) {
        for (int i = 0; i < top; i++) {
            if (points[i] == p) {
                return false;
            }
        }
        return true;
    }

    bool Polygon::check(int num, const Math::Point *p) {
        for (int i = 0; i < num; i++) {
            for (int j = i + 1; j < num; j++) {
                if (p[i] == p[j]) {
                    return false;
                }
            }
        }
        return true;
    }

    Polygon::Polygon(const Math::Point &p) {
        points = new Math::Point[QUOTA];
        realSize += QUOTA;
        points[top] = p;
        top++;
    }

    Polygon::Polygon(int num, const Math::Point *p) {
        if (num <= 0) {
            throw std::logic_error("num must be positive");
        }
        if (!check(num, p)) {
            throw std::logic_error("array contains duplicates of points");
        }
        points = new Math::Point[num / QUOTA + 1];
        realSize += num / QUOTA + 1;
        for (int i = 0; i < num; i++) {
            points[i] = p[i];
            top++;
        }
    }

    Polygon::~Polygon() {
        delete[] points;
    }

    Polygon::Polygon(Polygon &&p): top(p.top), realSize(p.realSize), points(p.points) {
        p.points = nullptr;
    }

    Polygon::Polygon(const Polygon &p) : top(p.top), realSize(p.realSize) {
        if (top > 0) {
            points = new Math::Point[realSize];
            for (int i = 0; i < top; i++) {
                points[i] = p.points[i];
            }
        }
    }

    Math::Point Polygon::operator[](int index) const {
        if (index < 0 || index >= top) {
            throw std::out_of_range("index out of bounds");
        }
        return points[index];
    }

    int Polygon::operator[](const Math::Point &p) const {
        for (int i = 0; i < top; i++) {
            if (p == points[i]) {
                return i;
            }
        }
        return -1;
    }

    int Polygon::getNodesNum() const {
        return top;
    }

    void Polygon::rotate(Math::Point &p, double alpha) {
        float x = p.x, y = p.y;
        p.x = x * (float) cos(alpha) - y * (float) sin(alpha);
        p.y = y * (float) cos(alpha) + x * (float) sin(alpha);
    }

    void Polygon::operator()(int k) {
        if (k < 0) {
            throw std::invalid_argument("k can't be negative");
        }
        double alpha = M_PI_2 * (double) k;
        for (int i = 0; i < top; i++) {
            rotate(points[i], alpha);
        }
    }

    void Polygon::move(const Math::Point &end) {
        for (int i = 0; i < top; i++) {
            points[i].x += end.x;
            points[i].y += end.y;
        }
    }

    Math::Point Polygon::getGravityCenter() const {
        if (top == 0) {
            throw std::logic_error("Polygon has 0 nodes");
        }
        Math::Point res;
        for (int i = 0; i < top; i++) {
            res.x += points[i].x;
            res.y += points[i].y;
        }
        res.x = (float) res.x / (float) top;
        res.y = (float) res.y / (float) top;
        return res;
    }

    void Polygon::set(const Math::Point &p, int i) {
        if (i < 0 || i >= top) {
            throw std::out_of_range("i out of bounds");
        }
        if (!check(p)) {
            throw std::logic_error("this point already exists");
        }
        points[i].x = p.x;
        points[i].y = p.y;
    }

    void Polygon::add(const Math::Point &p) {
        if (!check(p)) {
            throw std::logic_error("this point already exists");
        }
        if (top == realSize) {
            Math::Point *ptr = points;
            points = new Math::Point[realSize + QUOTA];
            realSize += QUOTA;
            for (int i = 0; i < top; i++) {
                points[i] = ptr[i];
            }
            delete[] ptr;
        }
        points[top].x = p.x;
        points[top].y = p.y;
        top++;
    }

    std::istream &operator>>(std::istream &in, Polygon &p) {
        int num;
        Math::Point point;
        in >> num;
        if (!in.good() || num <= 0) {
            throw std::invalid_argument("wrong number of points");
        }
        p = Polygon();
        for (int i = 0; i < num; i++) {
            in >> point;
            p.add(point);
        }
        return in;
    }

    char *Polygon::toString() const {
        char *res = new char[1]{'\0'}, *strPoint = nullptr;
        size_t strPointSize = 0, resOldLen = 1;
        for (int i = 0; i < top; i++) {
            strPoint = points[i].toString();
            strPointSize = strlen(strPoint);
            resOldLen = strlen(res) + 1;
            res = (char *) realloc(res, strPointSize + resOldLen);
            strcpy(&res[resOldLen - 1], strPoint);
            delete[] strPoint;
            strPoint = nullptr;
        }
        res[strPointSize + resOldLen - 1] = '\0';
        return res;
    }

    std::ostream &operator<<(std::ostream &output, const Polygon &p) {
        char *s = p.toString();
        output << s;
        delete[] s;
        return output;
    }

    Polygon::operator const Math::Point *() {
        const Math::Point *p;
        if (top) {
            p = points;
        } else {
            p = nullptr;
        }
        return p;
    }

    const Polygon Polygon::operator++(int) {
        Polygon x(*this);
        for (int i = 0; i < top; i++) {
            points[i].x += 1.0;
            points[i].y += 1.0;
        }
        return x;
    }

    Polygon &Polygon::operator++() {
        for (int i = 0; i < top; i++) {
            points[i].x += 1.0;
            points[i].y += 1.0;
        }
        return *this;
    }

    const Polygon Polygon::operator--(int) {
        Polygon x(*this);
        for (int i = 0; i < top; i++) {
            points[i].x -= 1.0;
            points[i].y -= 1.0;
        }
        return x;
    }

    Polygon &Polygon::operator--() {
        for (int i = 0; i < top; i++) {
            points[i].x -= 1.0;
            points[i].y -= 1.0;
        }
        return *this;
    }

    Polygon &Polygon::operator=(const Polygon &p) {
        if (this == &p) {
            return *this;
        }
        top = p.top;
        delete[] points;
        points = new Math::Point[p.realSize];
        realSize = p.realSize;
        for (int i = 0; i < top; i++) {
            points[i] = p.points[i];
        }
        return *this;
    }

    Polygon &Polygon::operator=(Polygon &&p) {
        int tmpTop = top,tmpRealSize = realSize;
        Math::Point* tmpPtr = points;
        top = p.top;
        realSize = p.realSize;
        points = p.points;
        p.top = tmpTop;
        p.realSize = tmpRealSize;
        p.points = tmpPtr;
        return *this;
    }

    Polygon Polygon::operator+(const Polygon &p) const {
        Polygon x(*this);
        for (int i = 0; i < p.top; i++) {
            try {
                x.add(p.points[i]);
            } catch (std::exception &e) {

            }
        }
        return x;
    }

    Polygon &Polygon::operator+=(const Polygon &p) {
        //Добавляются вершины из того же \n
        // самого многоугольника -> ни одна вершина\n
        // не будет добавлена
        if (this == &p) {
            return *this;
        }
        *this = *this + p;
        return *this;
    }

    bool Polygon::operator==(const Polygon &p) const {
        if (top == 0 && p.top == 0) {
            return true;
        }
        if (top * p.top == 0) {
            return false;
        }
        Math::Point g1 = getGravityCenter(), g2 = p.getGravityCenter();
        const float e = 1E-32;
        float d1 = g1.x * g1.x + g1.y * g1.y;
        float d2 = g2.x * g2.x + g2.y * g2.y;
        if (std::fabs(d1 - d2) < e) {
            return true;
        }
        return false;
    }

    bool Polygon::operator<(const Polygon &p) const {
        if (top == 0 && p.top == 0) {
            return false;
        }
        if (top == 0 && p.top > 0) {
            return true;
        }
        if (top > 0 && p.top == 0) {
            return false;
        }
        Math::Point g1 = getGravityCenter(), g2 = p.getGravityCenter();
        const float e = 1E-32;
        float d1 = g1.x * g1.x + g1.y * g1.y;
        float d2 = g2.x * g2.x + g2.y * g2.y;
        if (d1 - d2 < -e) {
            return true;
        }
        return false;
    }

    bool Polygon::operator>(const Polygon &p) const {
        if (top == 0 && p.top == 0) {
            return false;
        }
        if (top == 0 && p.top > 0) {
            return false;
        }
        if (top > 0 && p.top == 0) {
            return true;
        }
        Math::Point g1 = getGravityCenter(), g2 = p.getGravityCenter();
        const float e = 1E-32;
        float d1 = g1.x * g1.x + g1.y * g1.y;
        float d2 = g2.x * g2.x + g2.y * g2.y;
        if (d1 - d2 > e) {
            return true;
        }
        return false;
    }
}
