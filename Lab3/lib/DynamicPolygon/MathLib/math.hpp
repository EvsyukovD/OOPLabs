#ifndef POINT_HPP
#define POINT_HPP
namespace Math{
    struct Point {
        float x;
        float y;

        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }

        Point() {
            x = 0.0;
            y = 0.0;
        }

        /**
          * Строковое представление точки
          * @return Строка с точкой
          * */
        char *toString() const;

        bool operator==(const Point &p) const;
    };
}
#endif