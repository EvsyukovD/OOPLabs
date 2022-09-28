#include "Lab3.hpp"
#include <cmath>

namespace Lab3 {
    bool Point::operator==(const Point &p) const {
        const float e = 1E-32;
        return std::fabs(x - p.x) < e && std::fabs(y - p.y) < e;
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
            p.x = p.x * cos(alpha) - p.y * sin(alpha);
            p.y = p.y * cos(alpha) + p.x * sin(alpha);
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

        Point Polygon::gravityCenter() const {
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
    }
}
