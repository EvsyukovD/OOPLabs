// OOPLab1.cpp: определяет точку входа для приложения.
//
#include "OOPLab1.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{  
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	void (*fptrs[])(Lab1::Matrix*) = {Lab1::quit,Lab1::printMatrix,Lab1::add,Lab1::getVector};
	const char* options[] = { "0.Quit","1.Print matrix","2.Add element","3.Get result vector" };
	int rc, m, n;
	if (!Lab1::readSizes(m, n)) {
		std::cout << "End of programm" << std::endl;
		return 1;
	}
	Lab1::Matrix* matrix;
	matrix = Lab1::createMatrix(m, n);
	do {
		while ((rc = Lab1::dialog(options, 4)) != -1 && rc != 0) {
			fptrs[rc](matrix);
		}
	} while (rc != 0 && rc != -1);
	std::cout << "End of programm" << std::endl;
	Lab1::erase(matrix);
	_CrtDumpMemoryLeaks();
	return 0;
}