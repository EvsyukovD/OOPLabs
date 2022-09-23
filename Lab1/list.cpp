#include "list.h"
namespace List {
	
	 LinkedList* create() {
		return new LinkedList(nullptr, nullptr, 0);
	 }

	 /**
	  Поиск элемента списка по его индексу
	  @param list - исходный список, index - индекс искомого элемента
	  @return Item* - указатель на искомый элемент. Если такого элемента нет, то возвращает nullptr
	*/
	 Item* find(const LinkedList& list, int index) {
		if (index < 0 || index >= list.size) {
			return nullptr;
		}
		Item* ptr = list.head;
		while (ptr)
		{
			if (ptr->i == index) {
				return ptr;
			}
			ptr = ptr->next;
		}
		return nullptr;
	 }

	 void addZeroItemToTail(LinkedList& list) {
		Item* item = new Item(nullptr, list.size, nullptr, list.tail);
		if (!list.tail) {
			list.head = item;
			list.tail = item;
		}
		else {
			list.tail->next = item;
			list.tail = item;
		}
		list.size++;
	 }

	 bool add(LinkedList& list, int i, void* data) {
		if (i + 1 > list.size) {
			while (i != list.size - 1) {
				addZeroItemToTail(list);
			}
			list.tail->data = data;
			return true;
		}
		else if (i >= 0) {
			Item* ptr = find(list, i);
			ptr->data = data;
			return true;
		}
		return false;
	 }

	 bool add(LinkedList& list, void* data) {
		  return add(list,list.size, data);
	 }

	 void decreaseIndexes(Item* ptr) {
		 while (ptr) {
			 ptr->i--;
			 ptr = ptr->next;
		 }
	 }

	void* remove(LinkedList& list, int index) {
		void* res;
		Item* ptr = find(list, index);
		if (!ptr) {
			return nullptr;
		}
		if (list.head == ptr) {
			list.head = list.head->next;
			if (list.head == nullptr) {
				list.tail = nullptr;
			}
			else {
				list.head->prev = nullptr;
			}
			res = ptr->data;
			delete ptr;
			list.size--;
			decreaseIndexes(list.head);
			return res;
		}
		if (list.tail == ptr) {
			list.tail = list.tail->prev;
			list.tail->next = nullptr;
			res = ptr->data;
			delete ptr;
			list.size--;
			return res;
		}
		Item* prev = ptr->prev;
		prev->next = ptr->next;
		ptr->next->prev = prev;
		res = ptr->data;
		delete ptr;
		list.size--;
		decreaseIndexes(prev->next);
		return res;
	}

	void erase(LinkedList* list) {
		if (!list) {
			return;
		}
		while (list->size > 0) {
			remove(*list, 0);
		}
		delete list;
	}

	void* get(const LinkedList& list, int index) {
		Item* item = find(list, index);
		if (item) {
			return item->data;
		}
		return nullptr;
	}

};