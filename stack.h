#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack
{
private:
	List* list;
public:
	Stack() { list = new List(); }
	~Stack() { delete list;	}

	bool isEmpty() { return list->isEmpty(); }
	void clear() { list->clear(); }
	void push(int data) { list->addToHead(data); }
	int pop() { return list->removeHead(); }
	int top() { return list->valueOf(list->getHead()); }
};

#endif
