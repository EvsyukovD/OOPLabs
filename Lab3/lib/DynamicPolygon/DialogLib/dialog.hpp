#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <iostream>
#include <limits>
namespace Dialog {
    /**
      Функция диалога
      @param s - массив строк - опций для выбора, size - размер массива s
      @return Целое значение из [0, size - 1] - номер выбранной опции и -1 в случае eof
    */
    int dialog(const char *s[], int size);

    template<class T>
    bool read(T &a) {
        std::cin >> a;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            return false;
        }
        return true;
    }
}
#endif