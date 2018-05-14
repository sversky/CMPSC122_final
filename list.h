#ifndef LIST_H
#define LIST_H

class ListNode
{
private: 
	int data;
	ListNode* prev;
	ListNode* next;

public:
	ListNode() { data = 0; prev = next = 0; }
	ListNode(int d, ListNode* p, ListNode* n) { data = d; prev = p; next = n; }
	~ListNode() { data = 0; prev = next = 0; }
	friend class List;
};

class List
{
private:
	ListNode* head;
	ListNode* tail;

	int removeNode(ListNode*);

public:
	List() { head = tail = 0; }
	~List();

	void clear();

	bool isEmpty() { return head == 0; }
	bool contains(int value);

	void addToHead(int value);
	void addToTail(int value);

	int removeHead();
	int removeTail();

	int removeAt(int index);
	bool remove(int value);

	int at(int index);
	int valueOf(const ListNode* elem);
	const ListNode* getNext(const ListNode* node);
	const ListNode* getPrevious(const ListNode* node);
	const ListNode* getHead() { return head; }
	const ListNode* getTail() { return tail; }
};

List::~List()
{
	clear();
}

void List::clear()
{
	while (!isEmpty())
		removeTail();
}

int List::removeNode(ListNode* node)
{
	if (node == head)
		return removeHead();

	if (node == tail)
		return removeTail();

	int value = node->data;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;

	return value;
}

bool List::contains(int value)
{
	ListNode *temp = head;
	while (temp != 0 && temp->data != value)
		temp = temp->next;

	return temp != 0;
}

void List::addToHead(int value)
{
	if (isEmpty())
	{
		head = tail = new ListNode(value, 0, 0);
	}
	else
	{
		head = new ListNode(value, 0, head);
		head->next->prev = head;	
	}
}

void List::addToTail(int value)
{
	if (isEmpty())
	{
		head = tail = new ListNode(value, 0, 0);
	}
	else
	{
		tail = new ListNode(value, tail, 0);
		tail->prev->next = tail;
	}
}

int List::removeHead()
{
	int value = head->data;
	if (head == tail)
	{
		delete tail;
		head = tail = 0;
	}
	else
	{
		head = head->next;
		delete head->prev;
		head->prev = 0;
	}

	return value;
}

int List::removeTail()
{
	int value = head->data;
	if (head == tail)
	{
		delete tail;
		head = tail = 0;
	}
	else
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = 0;
	}

	return value;
}

int List::removeAt(int index)
{
	int idx = 0;
	ListNode* temp = head;

	while (temp != 0 && idx < index)
	{
		temp = temp->next;
		++idx;
	}

	if (temp == 0)
		exit(1);

	return removeNode(temp);
}

bool List::remove(int value)
{	
	ListNode* temp = head;

	while (temp != 0 && temp->data != value)
		temp = temp->next;

	if (temp == 0)
		return false;

	removeNode(temp);

	return true;
}

int List::at(int index)
{
	int idx = 0;
	const ListNode* temp = head;

	while (temp != 0 && idx < index)
	{
		temp = getNext(temp);
		++idx;
	}

	if (temp == 0)
		exit(1);

	return temp->data;
}

int List::valueOf(const ListNode* elem)
{
	return elem->data;
}

const ListNode* List::getNext(const ListNode* node)
{
	if (node == 0)
		return 0;

	return node->next;
}

const ListNode* List::getPrevious(const ListNode* node)
{
	if (node == 0)
		return 0;

	return node->prev;
}

#endif