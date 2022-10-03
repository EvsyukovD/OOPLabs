#include <iostream>
#include "lib/SimplePolygon/SimplePolygon.hpp"
#include "lib/SimplePolygon/DialogLib/dialog.hpp"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    void (*simplePolygonFuncs[])(SimplePolygon::Polygon&) = {SimplePolygon::quit,
                                                             SimplePolygon::initPolygonByEmptyConstructor,
                                                             SimplePolygon::initPolygonByPoint,
                                                             SimplePolygon::initPolygonByArray,
                                                             SimplePolygon::printPolygon,
                                                             SimplePolygon::getGravityCenter,
                                                             SimplePolygon::getNodeByIndex,
                                                             SimplePolygon::rotate,
                                                             SimplePolygon::move,
                                                             SimplePolygon::getNodesNum,
                                                             SimplePolygon::set,
                                                             SimplePolygon::add,
                                                             SimplePolygon::read};
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
                          "10.Replace node in polygon",
                          "11.Add new node",
                          "12.Read example of Polygon class from console"};
    int size = sizeof(menu) / sizeof(char*);
    int rc;
    SimplePolygon::Polygon p;
    do {
        while ((rc = Dialog::dialog(menu, size)) != -1 && rc != 0) {
            simplePolygonFuncs[rc](p);
        }
    } while (rc != 0 && rc != -1);
    std::cout << "End of programm" << std::endl;
    _CrtDumpMemoryLeaks();
    return 0;
}
