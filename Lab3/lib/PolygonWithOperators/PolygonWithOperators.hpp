#ifndef POLYGON_WITH_OPERATORS_HPP
#define POLYGON_WITH_OPERATORS_HPP
#include "MathLib/math.hpp"
#include <iostream>
namespace PolygonWithOperators {
    class Polygon {
    public:
        static const int NODES_MAX_NUM = 20;
    private:
        Math::Point points[NODES_MAX_NUM];
        int top = 0;
    public:
        Polygon();

        Polygon(const Math::Point &p);

        Polygon(int num, const Math::Point *p);


        friend std::ostream &operator<<(std::ostream &output, const Polygon &p);

        Math::Point gravityCenter() const;

        Math::Point operator[](int index) const;

        void rotate(int k);

        void move(const Math::Point &end);

        int getNodesNum() const;

    private:
        bool check(int num, const Math::Point *p);

        bool check(const Math::Point &p);
    };
}
#endif