#include <iostream>
#include "lib/SimplePolygon/Polygon.hpp"
#include "lib/SimplePolygon/DialogLib/dialog.hpp"
#define SIMPLE_POLYGON Lab3::SimplePolygon
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    void (*simplePolygonFuncs[])(SIMPLE_POLYGON::Polygon&) = {SIMPLE_POLYGON::quit,
                                                                   SIMPLE_POLYGON::initPolygonByEmptyConstructor,
                                                                    SIMPLE_POLYGON::initPolygonByPoint,
                                                                    SIMPLE_POLYGON::initPolygonByArray,
                                                                    SIMPLE_POLYGON::printPolygon,
                                                                    SIMPLE_POLYGON::getGravityCenter,
                                                                    SIMPLE_POLYGON::getNodeByIndex,
                                                                    SIMPLE_POLYGON::rotate,
                                                                    SIMPLE_POLYGON::move,
                                                                    SIMPLE_POLYGON::getNodesNum,
                                                                    SIMPLE_POLYGON::set};
    const char* menu[] = {"0.Quit",
                          "1.Init polygon by empty constructor",
                          "2.Init polygon by point",
                          "3.Init polygon by array",
                          "4.Print polygon",
                          "5.Get gravity center",
                          "6.Get node by index",
                          "7.Rotate polygon",
                          "8.Move polygon",
                          "9.Get number of nodes",
                          "10.Replace node in polygon"};
    int size = sizeof(menu) / sizeof(char*);
    int rc;
    SIMPLE_POLYGON::Polygon p;
    do {
        while ((rc = Dialog::dialog(menu, size)) != -1 && rc != 0) {
            simplePolygonFuncs[rc](p);
        }
    } while (rc != 0 && rc != -1);
    std::cout << "End of programm" << std::endl;
    _CrtDumpMemoryLeaks();
    return 0;
}
