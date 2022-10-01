#include "dialog.hpp"

namespace Dialog {
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

}
