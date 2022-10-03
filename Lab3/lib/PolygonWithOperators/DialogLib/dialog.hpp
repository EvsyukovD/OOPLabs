#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <iostream>

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
            return false;
        }
        return true;
    }
}
#endif