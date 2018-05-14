#ifndef SET_H
#define SET_H

#include "list.h"

class Set
{
private: 
	List* list;
	int set_size;
public:
	Set() { list = new List(); set_size = 0; }
	~Set() { delete list; }

	bool contains(int value) { return list->contains(value); }
	bool add(int);
	bool remove(int);
	void clear();

	void print();
	int size() { return set_size; }
};

bool Set::add(int value)
{
	if (list->contains(value))
		return false;

	list->addToTail(value);
	++set_size;

	return true;
}

bool Set::remove(int value)
{
	if (list->contains(value))
		return list->remove(value);

	return false;
}

void Set::print()
{
	const ListNode* temp = list->getHead();

	while (temp != 0)
	{
		std::cout << list->valueOf(temp) << " ";
		temp = list->getNext(temp);
	}
	std::cout << std::endl;
}

#endif