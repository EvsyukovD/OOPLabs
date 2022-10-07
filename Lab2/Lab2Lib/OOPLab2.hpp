#ifndef OOPLAB2_HPP
#define OOPLAB2_HPP

#include <iostream>

namespace Lab2 {
    struct Point {
        double x;
        double y;

        Point() {
            x = 0.0;
            y = 0.0;
        }

        Point(double x0, double y0) {
            x = x0;
            y = y0;
        }
    };

    class Verziera {
    private:
        double yA;
    public:
        Verziera() {
            yA = 1.0;
        }
        /**
         * Конструктор класса Verzieera
         * @param y - Y координата точки A
         * @throws std::logic_error - исключение в случае если y <= 0
         * */
        Verziera(double y) {
            if (y > 0.0) {
                yA = y;
            } else {
                throw std::logic_error("illegal coordinate: y must be positive");
            }
        }

        /**
         * Функция, возвращающая точку A
         * @return Point структура точки A
         * */
        Point getA() const;

        /**
         * Функция, изменяющая координату Y точки A
         * @param y - новая координата y точки A
         * @throws std::logic_error - исключение в случае если  y меньше или равно 0
         * */
        void setA(double y);

        /**
         * Функция, возвращающая координату y точки (x,y) принадлежащей верьезе по координате x
         * @return координату y
         * */
        double getY(double x) const;

        /**
         * Функция, возвращающая точки перегиба
         * @return Point* - массив точек перегиба
         * */
        Point *getInflectionPoints() const;

        /**
         * Функция, возвращающая площадь между верзьерой и её ассимптотой
         * @return Значение площади
         * */
        double getSquare() const;

        /**
         * Функция, возвращающая объём фигуры вращения полочы вокруг ассимптоты
         * @return Значение объёма
         * */
        double getVolume() const;

        /**
         * Функция, возвращающая строковое представление верзьеры
         * @return Строка с уравнением верзьеры
         * */
        char *toString() const;
    };

    /**
	  Функция диалога
	  @param s - массив строк - опций для выбора, size - размер массива s
	  @return Целое значение из [0, size - 1] - номер выбранной опции и -1 в случае eof
	*/
    int dialog(const char *s[], int size);

    template<class T>
    inline bool read(T &a) {
        std::cin >> a;
        if (!std::cin.good()) {
            return false;
        }
        return true;
    }

    /**
     * Диалоговая функция, вычисляющая и выводящая значение координаты Y по значению X
     * @param v - исходная верзьера
     * */
    void getY(Verziera &v);

    /**
     * Диалоговая функция, выводящая координаты точек перегиба верзьеры
     * @param v - исходная верзьера
     * */
    void getInflectionPoints(Verziera &v);

    /**
     * Диалоговая функция, выводящая значение площади под верзьерой
     * @param v - исходная верзьера
     * */
    void getSquare(Verziera &v);

    /**
     * Диалоговая функция, выводящая объём тела вращения верзьера вокруг ассимптоты
     * @param v - исходная верзьера
     * */
    void getVolume(Verziera &v);

    /**
     * Диалоговая функция, выводящая уравнение на экран
     * @param v - исходная верзьера
     * */
    void getEquation(Verziera &v);

    /**
     * Диалоговая функция выхода из программы
     * @param v - исходная верзьера
     * */
    void quit(Verziera &v);

    /**
     * Диалоговая, функция изменяющая координату Y точки A
     * @param v - исходная верзьера
     * */
    void setY(Verziera &v);
}
#endif