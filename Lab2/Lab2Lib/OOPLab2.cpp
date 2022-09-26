#include "OOPLab2.hpp"
#include <cmath>
#include <cstring>

#define _CRTDBG_MAP_ALLOC
namespace Lab2 {
    Point Verziera::getA() const {
        return {0.0, yA};
    }

    void Verziera::setA(double y) {
        if (y > 0) {
            yA = y;
        } else {
            throw std::logic_error("illegal argument: y must be positive");
        }
    }

    double Verziera::getY(double x) const {
        double a3 = yA * yA * yA;
        double d = x * x + yA * yA;
        return a3 / d;
    }

    Point *Verziera::getInflectionPoints() const {
        double y = 3.0 * yA / 4.0;
        double x1 = yA / sqrt(3.0);
        return new Point[2]{Point(x1, y), Point(-x1, y)};
    }

    double Verziera::getSquare() const {
        return M_PI * yA * yA;
    }

    double Verziera::getVolume() const {
        double a3 = yA * yA * yA;
        double p = M_PI * M_PI / 2.0;
        return a3 * p;
    }

    char *Verziera::toString() const {
        double a2 = yA * yA, a3 = yA * a2;
        char num[20];
        const char *pattern = "y =  / (x ^ 2 + )";
        int length = strlen(pattern) + 1;
        sprintf_s(num, 20, "%.2f", a3);
        length += strlen(num);
        sprintf_s(num, 20, "%.2f", a2);
        length += strlen(num);
        char *res = new char[length];
        sprintf_s(res, length, "y = %.2f / (x ^ 2 + %.2f)", a3, a2);
        return res;
    }

    int dialog(const char *s[], int size) {
        int choice, i;
        bool r;
        const char *error = "Wrong choice.Try again";
        do {
            std::cout << "Menu" << std::endl;
            for (i = 0; i < size; i++) {
                std::cout << s[i] << std::endl;
            }
            puts("Choose option:");
            r = read(choice);
            if (!r) {
                return -1;
            }
            std::cout << "Your choice: " << choice << std::endl;
            if (choice < 0 || choice > (size - 1)) {
                std::cerr << error << std::endl;
            }
        } while (choice < 0 || choice > (size - 1));
        return choice;
    }

    void getY(Verziera &v) {
        std::cout << "Enter X value:" << std::endl;
        double x;
        if (!read(x)) {
            std::cerr << "Error" << std::endl;
            return;
        }
        std::cout << "Y value: " << v.getY(x) << std::endl;
    }

    void getInflectionPoints(Verziera &v) {
        std::cout << "Inflection points :" << std::endl;
        Point *p = v.getInflectionPoints();
        std::cout << "First : (" << p[0].x << "," << p[0].y << ")" << std::endl;
        std::cout << "Second : (" << p[1].x << "," << p[1].y << ")" << std::endl;
        delete[] p;
    }

    void getSquare(Verziera &v){
        std::cout << "Square: " << v.getSquare() << std::endl;
    }

    void getVolume(Verziera &v){
        std::cout << "Volume: " << v.getVolume() << std::endl;
    }

    void getEquation(Verziera &v){
        char* s = v.toString();
        std::cout << "Equation: " << s << std::endl;
        delete[] s;
    }

    void quit(Verziera &v){

    }

    void setY(Verziera &v){
        std::cout << "Enter new Y value :" << std::endl;
        double y;
        if(!read(y)){
            std::cerr << "Error" << std::endl;
            return;
        }
        try {
            v.setA(y);
        } catch(std::logic_error& e){
            std::cerr << "Error:" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }
}
