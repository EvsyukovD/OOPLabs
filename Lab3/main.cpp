#include <iostream>
#include "lib/PolygonWithOperators/PolygonWithOperators.hpp"
#include "lib/PolygonWithOperators/DialogLib/dialog.hpp"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    void (*fptrs[])(PolygonWithOperators::Polygon&) = {PolygonWithOperators::quit,
                                                       PolygonWithOperators::init,
                                                       PolygonWithOperators::printPolygon,
                                                       PolygonWithOperators::getGravityCenter,
                                                       PolygonWithOperators::getNodeByIndex,
                                                       PolygonWithOperators::rotate,
                                                       PolygonWithOperators::move,
                                                       PolygonWithOperators::getNodesNum,
                                                       PolygonWithOperators::set,
                                                       PolygonWithOperators::add,
                                                       PolygonWithOperators::read,
                                                       PolygonWithOperators::unaryPlus,
                                                       PolygonWithOperators::unaryMinus,
                                                       PolygonWithOperators::binaryPlus,
                                                       PolygonWithOperators::addToThisPolygon,
                                                       PolygonWithOperators::compare};
    const char* menu[] = {"0.Quit",
                          "1.Init polygon",
                          "2.Print polygon",
                          "3.Get gravity center",
                          "4.Get node by index",
                          "5.Rotate polygon",
                          "6.Move polygon",
                          "7.Get number of nodes",
                          "8.Replace node in polygon",
                          "9.Add new node",
                          "10.Read example of Polygon class from console",
                          "11.Operator unary plus",
                          "12.Operator unary minus",
                          "13.Operator binary plus",
                          "14.Operator mod equation(+=)",
                          "15.Compare this polygon with your polygon"};

    int size = sizeof(menu) / sizeof(char*);
    int rc;
    PolygonWithOperators::Polygon p;
    do {
        while ((rc = Dialog::dialog(menu, size)) != -1 && rc != 0) {
            fptrs[rc](p);
        }
    } while (rc != 0 && rc != -1);
    std::cout << "End of programm" << std::endl;
    _CrtDumpMemoryLeaks();
    return 0;
}
