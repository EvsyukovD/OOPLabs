#include "Polygon.hpp"
#include <cmath>
#include <cstring>
#include "../DialogLib/dialog.hpp"

namespace Lab3 {
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

    namespace SimplePolygon {

        Polygon::Polygon() {

        }

        bool Polygon::check(const Point &p) {
            for (int i = 0; i < top; i++) {
                if (points[i] == p) {
                    return false;
                }
            }
            return true;
        }

        bool Polygon::check(int num, const Point *p) {
            for (int i = 0; i < num; i++) {
                for (int j = i + 1; j < num; j++) {
                    if (p[i] == p[j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        Polygon::Polygon(const Point &p) {
            points[top] = p;
            top++;
        }

        Polygon::Polygon(int num, const Point *p) {
            if (num > NODES_MAX_NUM) {
                throw std::length_error("too many points");
            }
            if (num <= 0) {
                throw std::logic_error("num must be positive");
            }
            if (!check(num, p)) {
                throw std::logic_error("array contains duplicates of points");
            }
            for (int i = 0; i < num; i++) {
                points[i] = p[i];
                top++;
            }
        }

        Point Polygon::get(int index) const {
            if (index < 0 || index >= top) {
                throw std::out_of_range("index out of bounds");
            }
            return points[index];
        }

        int Polygon::getNodesNum() const {
            return top;
        }

        void Polygon::rotate(Point &p, double alpha) {
            float x = p.x, y = p.y;
            p.x = x * (float) cos(alpha) - y * (float) sin(alpha);
            p.y = y * (float) cos(alpha) + x * (float) sin(alpha);
        }

        void Polygon::rotate(int k) {
            if (k < 0) {
                throw std::invalid_argument("k can't be negative");
            }
            double alpha = M_PI_2 * (double) k;
            for (int i = 0; i < top; i++) {
                rotate(points[i], alpha);
            }
        }

        void Polygon::move(const Point &end) {
            for (int i = 0; i < top; i++) {
                points[i].x += end.x;
                points[i].y += end.y;
            }
        }

        Point Polygon::getGravityCenter() const {
            if (top == 0) {
                throw std::logic_error("Polygon has 0 nodes");
            }
            Point res;
            for (int i = 0; i < top; i++) {
                res.x += points[i].x;
                res.y += points[i].y;
            }
            res.x = (float) res.x / (float) top;
            res.y = (float) res.y / (float) top;
            return res;
        }

        void Polygon::set(const Point &p, int i) {
            if (i < 0 || i >= top) {
                throw std::out_of_range("i out of bounds");
            }
            if (!check(p)) {
                throw std::logic_error("this point already exists");
            }
            points[i].x = p.x;
            points[i].y = p.y;
        }

        char *Polygon::toString() const {
            char *res = new char[1]{'\0'}, *strPoint = nullptr;
            int strPointSize = 0, resOldLen = 1;
            for (int i = 0; i < top; i++) {
                strPoint = points[i].toString();
                strPointSize = strlen(strPoint);
                resOldLen = strlen(res) + 1;
                res = (char *) realloc(res, strPointSize + resOldLen);
                memcpy((res + resOldLen - 1), strPoint, strPointSize);
                delete[] strPoint;
                strPoint = nullptr;
            }
            res[strPointSize + resOldLen - 1] = '\0';
            return res;
        }

        void Polygon::print(std::ostream &output) const {
            char *s = toString();
            output << s;
            delete[] s;
        }

        void initPolygonByEmptyConstructor(Polygon &p) {
            p = Polygon();
        }

        void initPolygonByPoint(Polygon &p) {
            Point point;
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
            if (!Dialog::read(num) || num <= 0 || num > Polygon::NODES_MAX_NUM) {
                std::cerr << "Error" << std::endl;
                return;
            }
            Point *points = new Point[num];
            for (int i = 0; i < num; i++) {
                std::cout << "Enter new x value of point:" << std::endl;
                if (!Dialog::read(points[i].x)) {
                    delete[] points;
                    std::cerr << "Error" << std::endl;
                    return;
                }
                std::cout << "Enter new y value of point:" << std::endl;
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

        void printPolygon(Polygon &p) {
            std::cout << "Your polygon:" << std::endl;
            p.print(std::cout);
            std::cout << std::endl;
        }

        void getGravityCenter(Polygon &p) {

            try {
                Point point = p.getGravityCenter();
                char *s = point.toString();
                std::cout << "Gravity center: " << s << std::endl;
                delete[] s;

            } catch (std::logic_error &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        void getNodeByIndex(Polygon &p) {
            int i;
            std::cout << "Enter index of point:" << std::endl;
            if (!Dialog::read(i)) {
                std::cerr << "Error" << std::endl;
                return;
            }
            try {
                Point point = p.get(i);
                char *s = point.toString();
                std::cout << "Your node: " << s << std::endl;
                delete[] s;
            } catch (std::out_of_range &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        void rotate(Polygon &p) {
            int k;
            std::cout << "Enter number of rotations on 90 degrees:" << std::endl;
            if (!Dialog::read(k)) {
                std::cerr << "Error" << std::endl;
                return;
            }
            try {
                p.rotate(k);
                std::cout << "Rotated polygon:" << std::endl;
                p.print(std::cout);
                std::cout << std::endl;
            } catch (std::invalid_argument &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        void move(Polygon &p) {
            Point point;
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
            p.print(std::cout);
            std::cout << std::endl;
        }

        void getNodesNum(Polygon &p) {
            std::cout << "Nodes number: " << p.getNodesNum() << std::endl;
        }

        void set(Polygon &p) {
            int i;
            std::cout << "Enter index of old node:" << std::endl;
            if (!Dialog::read(i)) {
                std::cerr << "Error" << std::endl;
                return;
            }
            Point point;
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
                p.print(std::cout);
                std::cout << std::endl;
            } catch (std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}
