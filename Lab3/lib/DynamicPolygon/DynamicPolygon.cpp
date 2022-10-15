#include "DynamicPolygon.hpp"
#include "DialogLib/dialog.hpp"
#include <cmath>
#include <cstring>
#define _CRTDBG_MAP_ALLOC
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
        double alpha = 3.141592654 * (double) k;
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

    void quit(Polygon &p) {

    }

    void initPolygonByEmptyConstructor(Polygon &p) {
        p = Polygon();
    }

    void initPolygonByPoint(Polygon &p) {
        Math::Point point;
        std::cout << "Enter new x value of point:" << std::endl;
        if (!Dialog::read(point.x)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        std::cout << "Enter new y value of point:" << std::endl;
        if (!Dialog::read(point.y)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        p = Polygon(point);
    }

    void initPolygonByArray(Polygon &p) {
        int num = -1;
        std::cout << "Enter number of points:" << std::endl;
        if (!Dialog::read(num) || num <= 0) {
            std::cerr << "Error: wrong number" << std::endl;
            return;
        }
        Math::Point *points = new Math::Point[num];
        for (int i = 0; i < num; i++) {
            std::cout << "Enter x value of point " << i << " :" << std::endl;
            if (!Dialog::read(points[i].x)) {
                delete[] points;
                std::cerr << "Error" << std::endl;
                return;
            }
            std::cout << "Enter y value of point " << i << " :" << std::endl;
            if (!Dialog::read(points[i].y)) {
                delete[] points;
                std::cerr << "Error" << std::endl;
                return;
            }
        }
        try {
            p = Polygon(num, points);
        } catch (std::logic_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        delete[] points;
    }

    void init(Polygon &p) {
        void (*fptrs[])(Polygon &) = {initPolygonByEmptyConstructor,
                                      initPolygonByPoint,
                                      initPolygonByArray};
        const char *menu[] = {"0.Init polygon by empty constructor",
                              "1.Init polygon by point",
                              "2.Init polygon by array"};
        int size = sizeof(menu) / sizeof(char *), rc;
        if ((rc = Dialog::dialog(menu, size)) != -1 && rc != 0) {
            fptrs[rc](p);
        }
    }

    void printPolygon(Polygon &p) {
        if (p.getNodesNum() == 0) {
            std::cout << "Polygon doesn't have nodes" << std::endl;
        } else {
            std::cout << "Your polygon:" << std::endl;
            std::cout << p << std::endl;
        }
    }

    void getGravityCenter(Polygon &p) {

        try {
            Math::Point point = p.getGravityCenter();
            char *s = point.toString();
            std::cout << "Gravity center: " << s << std::endl;
            delete[] s;

        } catch (std::logic_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void getNodeByIndex(Polygon &p) {
        if (p.getNodesNum() == 0) {
            std::cout << "Polygon doesn't have nodes" << std::endl;
            return;
        }
        int i;
        std::cout << "Enter index of point:" << std::endl;
        if (!Dialog::read(i)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        try {
            Math::Point point = p[i];
            char *s = point.toString();
            std::cout << "Your node: " << s << std::endl;
            delete[] s;
        } catch (std::out_of_range &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void rotate(Polygon &p) {
        if (p.getNodesNum() == 0) {
            std::cout << "Polygon doesn't have nodes" << std::endl;
            return;
        }
        int k;
        std::cout << "Enter number of rotations on 90 degrees:" << std::endl;
        if (!Dialog::read(k)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        try {
            p(k);
            std::cout << "Rotated polygon:" << std::endl;
            std::cout << p << std::endl;
        } catch (std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void move(Polygon &p) {
        if (p.getNodesNum() == 0) {
            std::cout << "Polygon doesn't have nodes" << std::endl;
            return;
        }
        Math::Point point;
        std::cout << "Enter x value of ending point:" << std::endl;
        if (!Dialog::read(point.x)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        std::cout << "Enter y value of ending point:" << std::endl;
        if (!Dialog::read(point.y)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        p.move(point);
        std::cout << "Moved polygon:" << std::endl;
        std::cout << p << std::endl;
    }

    void getNodesNum(Polygon &p) {
        std::cout << "Nodes number: " << p.getNodesNum() << std::endl;
    }

    void set(Polygon &p) {
        if (p.getNodesNum() == 0) {
            std::cout << "Polygon doesn't have nodes" << std::endl;
            return;
        }
        int i;
        std::cout << "Enter index of old node:" << std::endl;
        if (!Dialog::read(i)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        Math::Point point;
        std::cout << "Enter x value of new point:" << std::endl;
        if (!Dialog::read(point.x)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        std::cout << "Enter y value of new point:" << std::endl;
        if (!Dialog::read(point.y)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        try {
            p.set(point, i);
            std::cout << "New polygon:" << std::endl;
            std::cout << p << std::endl;
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void read(Polygon &p) {
        std::cout << "Enter the number of elements and coordinates of the points, separated by a space" << std::endl;
        Polygon polygon;
        try {
            std::cin >> polygon;
            std::cout << "Your polygon:" << std::endl;
            std::cout << polygon << std::endl;
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void add(Polygon &p) {
        Math::Point point;
        std::cout << "Enter x value of point:" << std::endl;
        if (!Dialog::read(point.x)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        std::cout << "Enter y value of point:" << std::endl;
        if (!Dialog::read(point.y)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        try {
            p.add(point);
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void unaryPlus(Polygon &p) {
        ++p;
    }


    void unaryMinus(Polygon &p) {
        --p;
    }

    void binaryPlus(Polygon &p) {
        std::cout << "Enter the number of elements and coordinates of the points, separated by a space" << std::endl;
        Polygon polygon1, polygon2, polygon3;
        try {
            std::cout << "First polygon:" << std::endl;
            std::cin >> polygon1;
            std::cout << "Your polygon1:" << std::endl;
            std::cout << polygon1 << std::endl;

            std::cout << "Second polygon:" << std::endl;
            std::cin >> polygon2;
            std::cout << "Your polygon2:" << std::endl;
            std::cout << polygon2 << std::endl;
            polygon3 = polygon1 + polygon2;
            std::cout << "Result:" << std::endl;
            std::cout << polygon3 << std::endl;
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void addToThisPolygon(Polygon &p) {
        std::cout << "Enter the number of elements and coordinates of the points, separated by a space" << std::endl;
        Polygon polygon;
        try {
            std::cin >> polygon;
            std::cout << "Your polygon:" << std::endl;
            std::cout << polygon << std::endl;
            p += polygon;
            std::cout << "Result:" << std::endl;
            std::cout << p << std::endl;
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void compare(Polygon &p) {
        std::cout << "Enter the number of elements and coordinates of the points, separated by a space" << std::endl;
        Polygon polygon;
        try {
            std::cin >> polygon;
            std::cout << "Your polygon:" << std::endl;
            std::cout << polygon << std::endl;
            if (p > polygon) {
                std::cout << "This polygon 'bigger' than your:" << p << " > " << polygon << std::endl;
            }
            if (p < polygon) {
                std::cout << "This polygon 'less' than your:" << p << " < " << polygon << std::endl;
            }
            if (p == polygon) {
                std::cout << "This polygon equals to your:" << p << " = " << polygon << std::endl;
            }
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
