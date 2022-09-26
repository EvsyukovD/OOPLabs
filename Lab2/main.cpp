#include <iostream>
#include "Lab2Lib/OOPLab2.hpp"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    void (*fptrs[])(Lab2::Verziera&) = {Lab2::quit,
                                        Lab2::getInflectionPoints,
                                        Lab2::getY,
                                        Lab2::getSquare,
                                        Lab2::getVolume,
                                        Lab2::getEquation,
                                        Lab2::setY};
    const char* menu[] = {"0.Quit",
                          "1.Get inflection points",
                          "2.Get Y - coordinate by X coordinate",
                          "3.Get square between verziera and its assymptote",
                          "4.Get volume of rotation figure",
                          "5.Get string with equation of verziera",
                          "6.Set Y coordinate of point A (default value: 1.0)"};
    int rc;
    Lab2::Verziera v;
    do {
        while ((rc = Lab2::dialog(menu, 7)) != -1 && rc != 0) {
            fptrs[rc](v);
        }
    } while (rc != 0 && rc != -1);
    std::cout << "End of programm" << std::endl;
    _CrtDumpMemoryLeaks();
    return 0;
}
