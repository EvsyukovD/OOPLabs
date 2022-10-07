#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

namespace Math {
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

        /**
        * Чтение точки из входного потока
        * @param in - входной поток
        * @param p - переменная, куда считывается точка
        * @throws std::invlaid_argument - если не удалось считать входные координаты
        * @return Изменённый входной поток
        * */
        friend std::istream &operator>>(std::istream &in, Point &p);
    };
}
#endif