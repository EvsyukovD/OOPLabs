#pragma once
#ifndef LIST_H
#define LIST_H
#include <iostream>
namespace List {

	// Структура элемента списка
	struct Item {
		void* data;
		int i; // Индекс элемента
		Item* next;
		Item* prev;
		Item(void* d, int idx, Item* n, Item* p) {
			data = d;
			i = idx;
			next = n;
			prev = p;
		}
	};

	// Структура списка
	struct LinkedList {
		Item* head;
		Item* tail;
		int size; // Длина списка
		LinkedList(Item* h, Item* t, int s) {
			head = h;
			tail = t;
			size = s;
		}
	};

	/**
	 Функция, создающая пустой список
	 @return LinkedList* где head и tail равны nullptr, а size 0
	*/
	 LinkedList* create();

	/**
	   Функция, возвращающая поле data из элемента списка list с индексом index
	  @param list - исходный список, index - индекс искомого элемента
	  @return void* - поле data. Если такого элемета нет, то возвращается nullptr
	*/
	void* get(const LinkedList& list, int index);

	/**
	   Функция, добавляющая элемент data в список list по индексу i.
	   Если на этом месте уже есть элемент, то он перезаписывается
	   @param list - исходный список, i - индекс, data - элемент
	   @return true если вставка прошла успешно и false иначе
	*/
	 bool add(LinkedList& list, int i, void* data);

	 /**
	    Функция, добавляющая элемент data в конец списка list. Если на этом месте уже есть элемент, то он перезаписывается
	   @param list - исходный список, data - элемент
	   @return true если вставка прошла успешно и false иначе
	 */
	 bool add(LinkedList& list, void* data);

	/**
	   Функция, удаляющая элемент из списка list по индексу i
	   @param list - исходный список, i - индекс, data - элемент
	   @return Поле data удалённого элемента. Если такого элемента нет, то возвращается nullptr
	*/
	 void* remove(LinkedList& list, int index);

	/**
	 Функция высвобождения памяти, выделенной под список
	 @param  list - исходный список
	*/
	 void erase(LinkedList* list);

};
#endif
