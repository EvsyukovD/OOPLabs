#ifndef DYNAMIC_POLYGON_HPP
#define DYNAMIC_POLYGON_HPP
#include <iostream>
#include "MathLib/math.hpp"
namespace DynamicPolygon {
    class Polygon {
    private:
        Math::Point *points;
        int top = 0;
    public:
        Polygon();

        Polygon(const Math::Point &p);

        Polygon(int num, const Math::Point *p);

        Polygon(const Polygon &p);

        Polygon(const Polygon &&p);

        ~Polygon();

        void print(std::ostream &output) const;

        Math::Point gravityCenter() const;

        Math::Point get(int index) const;

        void rotate(int k);

        void move(const Math::Point &end);

        int getNodesNum() const;

    private:
        bool check(int num, const Math::Point *p);

        bool check(const Math::Point &p);
    };
}
#endif