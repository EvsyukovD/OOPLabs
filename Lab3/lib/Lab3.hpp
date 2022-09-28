#ifndef LAB3_HPP
#define LAB3_HPP

#include <iostream>

namespace Lab3 {
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

        bool operator==(const Point &p) const;
    };

    class Polygon;
    namespace SimplePolygon {
        class Polygon {
        public:
            static const int NODES_MAX_NUM = 20;
        private:
            Point points[NODES_MAX_NUM];
            int top = 0;
        public:
            /**
             * Пустой конструктор
             * */
            Polygon();

            /**
             * Инициализация с помощью одной точки,
             * при этом многоугольник будет представлять из себя одну точку
             * @param p - исходная точка
             * */
            explicit Polygon(const Point &p);

            /**
             * Инициализация с помощью массива точек - вершин многоугольника
             * @param num, p - количество вершин и массив вершин
             * @throws std::logic_error - если в массиве есть совпадающие точки или если num <= 0
             * @throws std::length_error - если num > NODES_MAX_NUM
             * */
            Polygon(int num, const Point *p);

            /**
             * Вывод многоугольника в выходой поток
             * @param output - выходной поток
             * */
            void print(std::ostream &output) const;

            /**
             * Поучение центра тяжести многоугольника
             * @return Point - точка центра тяжести
             * @throws std::logic_error - если у многоугольника нет вершин
             * */
            Point gravityCenter() const;

            /**
             * Получение вершины многоугольника с индексом index
             * @param index - индекс вершины в массиве
             * @throws std::out_of_range - если index < 0 или
             * index больше либо равен числу вершин в многоугольнике
             * */
            Point get(int index) const;

            /**
             * Поворот многоугольника относительно (0,0) на угол,
             * кратный 90 градусам против часовой стрелки
             * @param k - множитель 90 градусов
             * @throws std::invalid_argument - если k меньше 0
             * */
            void rotate(int k);

            /**
             * Перемещение многоугольника в направлении и
             * на величину вектора {O,end}, где O - начало координат
             * @param end - конечная точка
             * */
            void move(const Point &end);

            /**
             * Получение количества вершин в многоугольнике
             * @return int - количество вершин
             * */
            int getNodesNum() const;

            /**
             * Поместить на место i - ой вершины новую вершину p
             * @param p - новая вершина
             * @param i - индекс замещаемой вершины
             * @throws std::logic_error - если такая вершина уже есть
             * @throws std::out_of_range - если i меньше 0 или
             * i больше либо равен числу вершин в многоугольнике
             * */
            void set(const Point &p, int i);

        private:
            /**
             * Проверка наличия повторяющихся вершин в массиве p
             * @param num ,p - количество вершин и массив точек
             * @return true если проверка прошла успешно и false иначе
             * */
            bool check(int num, const Point *p);

            /**
             * Проверка отсутствия вершины p в массиве points
             * @param p - добавляемая точка
             * @return true если проверка прошла успешно и false иначе
             * */
            bool check(const Point &p);

            /**
             * Функция поворачивающая вектор {O,p} на угол alpha, где O - начало координат
             * @param p - исходная точка
             * @param alpha - угол поворота
             * */
            void rotate(Point &p, double alpha);
        };
    }
    namespace PolygonWithOperators {
        class Polygon {
        public:
            static const int NODES_MAX_NUM = 20;
        private:
            Point points[NODES_MAX_NUM];
            int top = 0;
        public:
            Polygon();

            Polygon(const Point &p);

            Polygon(int num, const Point *p);


            friend std::ostream &operator<<(std::ostream &output, const Polygon &p);

            Point gravityCenter() const;

            Point operator[](int index) const;

            void rotate(int k);

            void move(const Point &end);

            int getNodesNum() const;

        private:
            bool check(int num, const Point *p);

            bool check(const Point &p);
        };
    }
    namespace DynamicPolygon {
        class Polygon {
        private:
            Point *points;
            int top = 0;
        public:
            Polygon();

            Polygon(const Point &p);

            Polygon(int num, const Point *p);

            Polygon(const Polygon &p);

            Polygon(const Polygon &&p);

            ~Polygon();

            void print(std::ostream &output) const;

            Point gravityCenter() const;

            Point get(int index) const;

            void rotate(int k);

            void move(const Point &end);

            int getNodesNum() const;

        private:
            bool check(int num, const Point *p);

            bool check(const Point &p);
        };
    }
}
#endif