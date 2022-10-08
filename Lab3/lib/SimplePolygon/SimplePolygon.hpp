#ifndef LAB3_HPP
#define LAB3_HPP

#include <iostream>
#include "MathLib/math.hpp"
/**
 * "Статическая" реализация класса многоугольника (Polygon), не использующая операторы.
 *
 * <p>Вершины многоугольника хранятся в массиве points, при этом подразумевается,
 * что вершина points[0] соединена с points[1], points[1] соединена с
 * points[2] ... Также подразумевается, что соединенны первая и последние
 * вершины.
 * @author <a href=https://github.com/EvsyukovD>EvsyukovD </a>
 * */
namespace SimplePolygon {
    class Polygon {
    public:
        static const int NODES_MAX_NUM = 20;
    private:
        Math::Point points[NODES_MAX_NUM];
        //свободная позиция в массиве
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
        explicit Polygon(const Math::Point &p);

        /**
         * Инициализация с помощью массива точек - вершин многоугольника
         * @param num, p - количество вершин и массив вершин
         * @throws std::logic_error - если в массиве есть совпадающие точки или если num меньше или равен 0
         * @throws std::length_error - если num > NODES_MAX_NUM
         * */
        Polygon(int num, const Math::Point *p);

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
        Math::Point getGravityCenter() const;

        /**
         * Получение вершины многоугольника с индексом index
         * @param index - индекс вершины в массиве
         * @throws std::out_of_range - если index меньше 0 или
         * index больше либо равен числу вершин в многоугольнике
         * */
        Math::Point get(int index) const;

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
        void move(const Math::Point &end);

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
        void set(const Math::Point &p, int i);

        /**
         * Строковое представление многоугольника
         * @return Строка с точками многоугольника
         * */
        char *toString() const;

        /**
         * Добавление новой вершины в конец массива
         * @throws std::logic_error - если есть повторяющиеся вершины
         * @throws std::length_error - если массив точек полностью заполнен
         * @param p - новая точка
         * */
        void add(const Math::Point &p);

        /**
         * Чтение экземпляра класса из входного потока
         * @param in - ссылка на входной поток
         * @throws std::invalid_argument - если чтение прошло неудачно или \n
         * если задано некорректное количество точек
         * @throws std::logic_error - если есть повторяющиеся вершины
         * @throws std::length_error - если массив точек полностью заполнен
         * @return Изменённый входной поток
         * */
        std::istream &read(std::istream &in, Polygon &p);

    private:
        /**
         * Проверка наличия повторяющихся вершин в массиве p
         * @param num ,p - количество вершин и массив точек
         * @return true если проверка прошла успешно и false иначе
         * */
        bool check(int num, const Math::Point *p);

        /**
         * Проверка отсутствия вершины p в массиве points
         * @param p - добавляемая точка
         * @return true если проверка прошла успешно и false иначе
         * */
        bool check(const Math::Point &p);

        /**
         * Функция поворачивающая вектор {O,p} на угол alpha, где O - начало координат
         * @param p - исходная точка
         * @param alpha - угол поворота
         * */
        void rotate(Math::Point &p, double alpha);

    };

    /**
     * Диалоговая функция выхода
     * @param p - исходный многоугольник
     * */
    void quit(Polygon &p);

    /**
     * Диалоговая функция инициализации многоугольника с помощью пустого конструктора
     * @param p - исходный многоугольник
     * */
    void initPolygonByEmptyConstructor(Polygon &p);

    /**
     * Диалоговая функция инициализации многоугольника с помощью точки
     * @param p - исходный многоугольник
     * */
    void initPolygonByPoint(Polygon &p);

    /**
     * Диалоговая функция инициализации многоугольника с помощью массива точек
     * @param p - исходный многоугольник
     * */
    void initPolygonByArray(Polygon &p);

    /**
     * Диалоговая функция инициализации многоугольника
     * @param p - исходный многоугольник
     * */
    void init(Polygon &p);

    /**
     * Диалоговая функция вывода многоугольника в консоль
     * @param p - исходный многоугольник
     * */
    void printPolygon(Polygon &p);

    /**
     * Диалоговая функция вывода в консоль центра тяжести многоугольника
     * @param p - исходный многоугольник
     * */
    void getGravityCenter(Polygon &p);

    /**
     * Диалоговая функция получения вершины многоугольника по её номеру
     * @param p - исходный многоугольник
     * */
    void getNodeByIndex(Polygon &p);

    /**
     * Диалоговая функция поворота многоугольника
     * @param p - исходный многоугольник
     * */
    void rotate(Polygon &p);

    /**
     * Диалоговая функция перемещения многоугольника
     * @param p - исходный многоугольник
     * */
    void move(Polygon &p);

    /**
     * Диалоговая функция получения количества вершин многоугольника
     * @param p - исходный многоугольник
     * */
    void getNodesNum(Polygon &p);

    /**
     * Диалоговая функция замены одной вершины многоугольника на другую
     * @param p - исходный многоугольник
     * */
    void set(Polygon &p);

    /**
     * Диалоговая функция добавления новой вершины в конец массива
     * @param p - исходный многоугольник
     * */
    void add(Polygon &p);

    /**
     * Диалоговая функция чтения экземпляра класса из консоли
     * @param p - исходный многоугольник
     * */
    void read(Polygon &p);

}
#endif