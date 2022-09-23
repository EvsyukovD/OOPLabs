#pragma once
#ifndef LIST_H
#define LIST_H
#include <iostream>
namespace List {

	// ��������� �������� ������
	struct Item {
		void* data;
		int i; // ������ ��������
		Item* next;
		Item* prev;
		Item(void* d, int idx, Item* n, Item* p) {
			data = d;
			i = idx;
			next = n;
			prev = p;
		}
	};

	// ��������� ������
	struct LinkedList {
		Item* head;
		Item* tail;
		int size; // ����� ������
		LinkedList(Item* h, Item* t, int s) {
			head = h;
			tail = t;
			size = s;
		}
	};

	/**
	 �������, ��������� ������ ������
	 @return LinkedList* ��� head � tail ����� nullptr, � size 0
	*/
	 LinkedList* create();

	/**
	   �������, ������������ ���� data �� �������� ������ list � �������� index
	  @param list - �������� ������, index - ������ �������� ��������
	  @return void* - ���� data. ���� ������ ������� ���, �� ������������ nullptr
	*/
	void* get(const LinkedList& list, int index);

	/**
	   �������, ����������� ������� data � ������ list �� ������� i.
	   ���� �� ���� ����� ��� ���� �������, �� �� ����������������
	   @param list - �������� ������, i - ������, data - �������
	   @return true ���� ������� ������ ������� � false �����
	*/
	 bool add(LinkedList& list, int i, void* data);

	 /**
	    �������, ����������� ������� data � ����� ������ list. ���� �� ���� ����� ��� ���� �������, �� �� ����������������
	   @param list - �������� ������, data - �������
	   @return true ���� ������� ������ ������� � false �����
	 */
	 bool add(LinkedList& list, void* data);

	/**
	   �������, ��������� ������� �� ������ list �� ������� i
	   @param list - �������� ������, i - ������, data - �������
	   @return ���� data ��������� ��������. ���� ������ �������� ���, �� ������������ nullptr
	*/
	 void* remove(LinkedList& list, int index);

	/**
	 ������� ������������� ������, ���������� ��� ������
	 @param  list - �������� ������
	*/
	 void erase(LinkedList* list);

};
#endif
