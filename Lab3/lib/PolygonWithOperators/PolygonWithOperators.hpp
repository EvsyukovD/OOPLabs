#ifndef POLYGON_WITH_OPERATORS_HPP
#define POLYGON_WITH_OPERATORS_HPP

#include "MathLib/math.hpp"
#include <iostream>

/**
 * Реализация класса многоугольника (Polygon), использующая операторы.
 *
 * <p>Вершины многоугольника хранятся в массиве points, при этом подразумевается,
 * что вершина points[0] соединена с points[1], points[1] соединена с
 * points[2] ... Также подразумевается, что соединенны первая и последние
 * вершины.
 * @author <a href=https://github.com/EvsyukovD>EvsyukovD</a>
 * */
namespace PolygonWithOperators {
    class Polygon {
    public:
        const static int NODES_MAX_NUM = 20;
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


        Polygon(const Polygon &p);

        /**
         * Поучение центра тяжести многоугольника
         * @return Point - точка центра тяжести
         * @throws std::logic_error - если у многоугольника нет вершин
         * */
        Math::Point getGravityCenter() const;


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
         * Добавление новых вершин в многоугольник:
         *
         * <p> Берётся множество точек 1-го многоугольника V1\n
         * и дополняется подмножеством множеством точек 2-го многоугольника V2',\n
         * причём V2' не является подмножеством V1 и |V1 u V2'| не больше NODES_MAX_NUM.\n
         *
         * <p>Результирующее множество записывается в массив нового
         * многоугольника
         *
         * @param p -  2-ой многоугольник
         * @return Экземпляр класса Polygon c результирующим
         * множеством точек
         * */
        Polygon operator+(const Polygon &p) const;


        /**
         * Постфиксный инкремент
         *
         * <p>В многоугольнике координаты каждой точки увеличиваются на 1,\n
         * если точек в многоугольнике нет, то ничего не происходит
         * @return исходный многоугольник
         * */
        const Polygon operator++(int);

        /**
         * Префиксный инкремент
         *
         * <p>В многоугольнике координаты каждой точки увеличиваются на 1,\n
         * если точек в многоугольнике нет, то ничего не происходит
         *
         * @return многоугольник, в котором координаты каждой точки
         * увеличиваются на 1
         * */
        Polygon &operator++();

        /**
         * Постфиксный декремент
         *
         * <p>В многоугольнике координаты каждой точки уменьшается на 1,\n
         * если точек в многоугольнике нет, то ничего не происходит
         * @return исходный многоугольник
         * */
        const Polygon operator--(int);

        /**
         * Префиксный декремент
         *
         * <p>В многоугольнике координаты каждой точки уменьшается на 1,\n
         * если точек в многоугольнике нет, то ничего не происходит
         *
         * @return многоугольник, в котором координаты каждой точки
         * уменьшается на 1
         * */
        Polygon &operator--();

        /**
         * Оператор пррисваивания
         * */
        Polygon &operator=(const Polygon &p);

        Polygon &operator+=(const Polygon &p);

        /**
         * Оператор "меньше"
         * @param p - многоугольник, сравниваемый с данным
         * @return true, если количество вершин данного многоугольника равно 0, а количества вершин у p больше 0,\n
         * или, если расстояние от начала коодинат до центра тяжести данного многоугольника меньше\n
         * соответствующего растояния у многоугольника p
         * */
        bool operator<(const Polygon &p) const;

        /**
         * Оператор "больше"
         * @param p - многоугольник, сравниваемый с данным
         * @return true, если количество вершин данного многоугольника больше 0, а количества вершин у p равно 0,\n
         * или, если расстояние от начала коодинат до центра тяжести данного многоугольника больше\n
         * соответствующего растояния у многоугольника p
         * */
        bool operator>(const Polygon &p) const;

        /**
         * Оператор эквивалентности многоугольников
         * @param p - многоугольник, сравниваемый с данным
         * @return true, если они имеют одинаковое количество вершин равное 0 или\n
         * расстояние от начала координат до их цетров тяжести совпадают, и false иначе
         * */
        bool operator==(const Polygon &p) const;


        /**
         * Получение вершины многоугольника с индексом index
         * @param index - индекс вершины в массиве
         * @throws std::out_of_range - если index меньше 0 или
         * index больше либо равен числу вершин в многоугольнике
         * */
        Math::Point operator[](int index) const;

        /**
         * Получение индекса вершины p многоугольника
         * @param p - вершина в массиве
         * @throws std::out_of_range - если такой вершине многоугольнике нет
         * */
        int operator[](const Math::Point &p) const;

        /**
         * Поворот многоугольника относительно (0,0) на угол,
         * кратный 90 градусам против часовой стрелки
         * @param k - множитель 90 градусов
         * @throws std::invalid_argument - если k меньше 0
         * */
        void operator()(int k);

        /**
        * Чтение экземпляра класса из входного потока
        * @param in - ссылка на входной поток
        * @throws std::invalid_argument - если чтение прошло неудачно или \n
        * если задано некорректное количество точек
        * @throws std::logic_error - если есть повторяющиеся вершины
        * @throws std::length_error - если массив точек полностью заполнен
        * @return Изменённый входной поток
        * */
        friend std::istream &operator>>(std::istream &in, Polygon &p);

        /**
         * Вывод многоугольника в выходой поток
         * @param output - выходной поток
         * */
        friend std::ostream &operator<<(std::ostream &output, const Polygon &p);

        /**
         * Преобразование типа Polygon к типу Point*
         * @return Указатель на массив точек многоугольника.\n
         * Если количество вершин многоугольника ровно 0, то\n
         * возращается nullptr
         * */
        explicit operator const Math::Point *();

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

    /**
     * Диалоговая функция, совершающая преобразование ++p
     * @param p - исходный многоугольник
     * */
    void unaryPlus(Polygon &p);

    /**
     * Диалоговая функция, совершающая преобразование --p
     * @param p - исходный многоугольник
     * */
    void unaryMinus(Polygon &p);

    /**
     * Диалоговая функция сложения двух многоугольников
     * @param p - исходный многоугольник
     * */
    void binaryPlus(Polygon &p);


    /**
     * Диалоговая функция прибавляющая к данному многоугольнику\n
     * многоугольник
     * @param p - исходный многоугольник
     * */
    void addToThisPolygon(Polygon &p);

    /**
     * Диалоговая функция сравнения данного многоугольника с\n
     * введённым
     * @param p - исходный многоугольник
     * */
    void compare(Polygon &p);
}
#endif