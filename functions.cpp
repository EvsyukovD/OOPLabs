#include "OOPLab1.h"
#define _CRTDBG_MAP_ALLOC
namespace Lab1 {

	int dialog(const char* s[], int size) {
		int choice, i;
		bool r;
		char* error = "Wrong choice.Try again";
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
			if (choice < 0 || choice >(size - 1)) {
				std::cerr << error << std::endl;
			}
		} while (choice < 0 || choice >(size - 1));
		return choice;
	}

	Matrix* createMatrix(int m, int n) {
		return new Matrix(m, n, List::create());
	}

	void eraseData(Data* data) {
		delete data;
	}

	List::Item* findItem(const List::LinkedList& line, int index) {
		List::Item* ptr = line.head;
		Data* d;
		while (ptr) {
			if (ptr->data) {
				d = (Data*)ptr->data;
				if (d->j == index) {
					return ptr;
				}
			}
			ptr = ptr->next;
		}
		return nullptr;
	}

	Data* findData(const List::LinkedList& line, int index) {
		List::Item* res = findItem(line, index);
		return res != nullptr ? (Data*)res->data : nullptr;
	}

	void printMatrix(Matrix* matrix) {
		if (!matrix) {
			return;
		}
		List::LinkedList* lines = matrix->lines,*line;
		Data* d;
		std::cout << "Your matrix:" << std::endl;
		for (int i = 0; i < matrix->m; i++) {
			line = (List::LinkedList*)List::get(*lines, i);
			for (int j = 0; j < matrix->n; j++) {
				 d = line != nullptr ? findData(*line, j) : nullptr;
				 int data = d != nullptr ? d->data : 0;
				 std::cout << data << " ";

			}
			std::cout << std::endl;
		}
	}


	bool addElementToMatrix(Matrix& matrix, int i, int j, int data) {
		if (i < 0 || j < 0 || i >= matrix.m || j >= matrix.n) {
			return false;
		}
		Data* d = new Data(i, j, data);
		if (i < matrix.lines->size) {
			List::LinkedList* line = (List::LinkedList*)List::get(*(matrix.lines), i);
			List::Item* item = findItem(*line, j);
			if (!item) {
				List::add(*line, d);
			}
			else {
				eraseData((Data*)item->data);
				item->data = d;
			}
		} else {
			while (i != matrix.lines->size - 1) {
				   List::add(*(matrix.lines),List::create());
			}
			List::LinkedList* line = (List::LinkedList*)List::get(*(matrix.lines), i);
			List::Item* item = findItem(*line, j);
			if (!item) {
				List::add(*line, d);
			}
			else {
				eraseData((Data*)item->data);
				item->data = d;
			}
		}
		return true;
	}
	
	void erase(Matrix* matrix) {
		if (!matrix) {
			return;
		}
		List::LinkedList* lines = matrix->lines;
		while (lines->size) {
			   List::LinkedList* line = (List::LinkedList*)remove(*lines, 0);
			   while (line->size > 0) {
				   eraseData((Data*)remove(*line, 0));
			   }
			   delete line;
		}
		delete lines;
		delete matrix;
	}


	bool filter(int data) {
		if (data == 0) {
			return false;
		}
		while (data != 0) {
			if (data % 10 == 0) {
				return false;
			}
			data = data / 10;
		}
		return true;
	}
	
	int listFilter(const List::LinkedList& line, bool (*f)(int)) {
		int s = 0;
		List::Item* ptr = line.head;
		Data* d;
		while (ptr) {
			d = (Data*)ptr->data;
			s = s + ((f(d->data)) ? d->data : 0);
			ptr = ptr->next;
		}
		return s;
	}

	int* getResultVector(const Matrix& matrix, bool (*f)(int)) {
		int size = matrix.m;
		int* res = new int[size];
		List::Item* item = matrix.lines->head;
		for (int i = 0; i < size; i++) {
			if (item) {
				res[i] = item->data != nullptr ? listFilter(*((List::LinkedList*)item->data), f) : 0;
				item = item->next;
			}
			else {
				res[i] = 0;
			}
		}
		return res;
	}
	
	void printVector(const int* v,int size) {
		if (!v) {
			return;
		}
		for (int i = 0; i < size; i++) {
			 std::cout << v[i] << std::endl;
		}
	}

	bool readSizes(int& m, int& n) {
		const char* error = "Wrong sizes. Try again";
		int _m = 0, _n = 0;
		do {
			std::cout << "Enter m" << std::endl;
			if (!read(_m)) {
				return false;
			}
			std::cout << "Enter n" << std::endl;
			if (!read(_n)) {
				return false;
			}
			if (_m <= 0 || _n <= 0) {
				std::cerr << error << std::endl;
			}
		} while (_m <= 0 || _n <= 0);
		m = _m;
		n = _n;
		return true;
	}

	void quit(Matrix* matrix) {
	}

	void toOriginMatrix(Matrix& matrix, int oldSize) {
		List::LinkedList* lines = matrix.lines;
		while (lines->size > oldSize) {
			List::LinkedList* line = (List::LinkedList*)remove(*lines, lines->size - 1);
			while (line->size > 0) {
				eraseData((Data*)remove(*line, 0));
			}
			delete line;
		}
	}

	void add(Matrix* matrix) {
		if (!matrix) {
			return;
		}
		int data,i,j;
		const char* error = "Wrong parametrs. Try again";
		bool flag = true;
		do
		{
			if (!flag) {
				std::cerr << error << std::endl;
				flag = true;
			}
			std::cout << "Enter i" << std::endl;
			flag = read(i);
			flag = flag && i >= 0 && i <= matrix->m - 1;
			std::cout << "Enter j" << std::endl;
			flag = flag && read(j);
			flag = flag && j >= 0 && j <= matrix->n - 1;
			std::cout << "Enter data" << std::endl;
			flag = flag && read(data);
		} while (!flag);
		int oldSize = matrix->lines->size;
		try {
			addElementToMatrix(*matrix, i, j, data);
			std::cout << "Element has been added!" << std::endl;
		}
		catch (std::bad_alloc& e) {
			toOriginMatrix(*matrix, oldSize);
			std::cout << "Can't allocate enough memory" << std::endl;
			std::cout << e.what() << std::endl;
		}
	}

	void getVector(Matrix* matrix) {
		if (!matrix) {
			return;
		}
		try {
			int* res = getResultVector(*matrix, filter);
			std::cout << "Result vector:" << std::endl;
			printVector(res, matrix->m);
			delete[] res;
		}
		catch (std::bad_alloc& e) {
			std::cout << "Can't allocate enough memory" << std::endl;
			std::cout << e.what() << std::endl;
		}
	}
};