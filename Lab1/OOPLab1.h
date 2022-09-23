#ifndef OOPLAB1_H
#define OOPLAB1_H
#include <iostream>
#include "list.h"
namespace Lab1 {
	struct Data {
		int data;
		int i;
		int j;
		Data(int _i, int _j, int _data) {
			data = _data;
			i = _i;
			j = _j;
		}
	};

	// Структура матрицы
	struct Matrix {
		int m; // Задаваемые размеры матрицы 
		int n; //  
		List::LinkedList* lines;
		Matrix(int linesNum, int colsNum,List::LinkedList* l) {
			m = linesNum;
			n = colsNum;
			lines = l;
		}
	};

	template<class T>
	inline bool read(T& a) {
		std::cin >> a;
		if (!std::cin.good()) {
			return false;
		}
		return true;
	}
	/**
	  Функция диалога
	  @param s - массив строк - опций для выбора, size - размер массива s
	  @return Целое значение из [0, size - 1] - номер выбранной опции и -1 в случае eof
	*/
	int dialog(const char* s[], int size);

	/**
	  Функция создающая пустую матрицу
	  @param m, n - задаваемые размеры матрицы
	  @return Matrix* - указатель на матрицу
	*/
	Matrix* createMatrix(int m, int n);

	/**
	  Функция, считывающая размеры матрицы
	  @param m, n - ссылки на размеры матрицы (m - число строк, n - число столбцов)
	  @return true если чтение прошло успешно и false иначе
	*/
	bool readSizes(int& m, int& n);

	/**
	 Диалоговая функция, печатающая матрицу matrix
	 @param matrix - исходная матрица
	*/
	void printMatrix(Matrix* matrix);

	/**
	  Функция добавляющая элемент data в матрицу matrix по координатам i, j. 
	  Если в этой точке уже есть элемент, то он перезаписывается
	  @param matrix - исходная матрица; i, j - координаты добавляемого элемента data.
	*/
	bool addElementToMatrix(Matrix& matrix, int i, int j, int data);

	/**
	   Функция высвобождения памяти, выделенной под матрицу
	   @param  matrix - исходная матрица
	*/
	void erase(Matrix* matrix);

	/**
	  Функция, задающая критерий отбора элементов матрицы
	  @param  int data - элемент матрицы
	  @return true если data удовлетворяет критерию отбора и false иначе
	*/
	bool filter(int data);

	/**
     	Диалоговая функция, добавляющая в матрицу новый элемент
		@param Matrix* matrix - исходная матрица
	*/
	void add(Matrix* matrix);

	/**
	   Диалоговая функция выхода
	   @param Matrix* matrix - исходная матрица
	*/
	void quit(Matrix* matrix);

	/**
	* Диалоговая функция, выводящая результирующий вектор
	  @param Matrix* matrix - исходная матрица
	*/
	void getVector(Matrix* matrix);

	/**
	  Функция высвобождения памяти выделенной под Data
	  @param *data - указатель на Data, который надо очистить
	*/
	void eraseData(Data* data);

	/**
	  Функция, находящая элемент Data из строки line, поле j которого равно index
	  @param line - исходная строка, index - значение поля j искомого элемента
	  @return Указатель на элемент Item содержащий искомый элемент Data. Если такого элемента нет, то возвращается nullptr
	*/
	List::Item* findItem(const List::LinkedList& line, int index);

	/**
	  Функция, находящая и возвращающая элемент Data из строки line, поле j которого равно index
	  @param line - исходная строка, index - значение поля j искомого элемента
	  @return Указатель на искомый элемент Data. Если такого элемента нет, то возвращается nullptr
	*/
	Data* findData(const List::LinkedList& line, int index);

	/**
	  Функция, применяющая к каждому элементу строки line критерий отбора, задаваемый функцией f
	  @param line - исходная строка, f - функция, реализующая критерий отбора
	  @return Сумма всех отобранных элементов
	*/
	int listFilter(const List::LinkedList& line, bool (*f)(int));

	/**
	  Функция, вычисляющая выходной вектор
	  @param matrix - исходная матрица, f - функция, реализующая критерий отбора элементов
	  @return int* указатель на выходной вектор
	*/
	int* getResultVector(const Matrix& matrix, bool (*f)(int));

	/**
	  Функция, выводящая вектор на консоль
	  @param v - указатель на вектор, size - его размер
	*/
	void printVector(const int* v, int size);

	/**
	  Функция возвращающая количество строк в матрице к старому значению
	  @param matrix - матрица с лишними строками, oldSize - размер "старой" матрицы
	*/
	void toOriginMatrix(Matrix& matrix, int oldSize);
};
#endif // !OOPLAB1_H

