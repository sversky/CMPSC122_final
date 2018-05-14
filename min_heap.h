#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>
#include <cstdlib>

// Heap implementation derived from: 
// https://www.geeksforgeeks.org/binary-heap/

class MinHeap
{
private:
	// Creating internal "nested" classes is an alternative
	// to friending entire classes. This way, only MinHeap has access
	// to the a HeapNode object and its contents. 
	class HeapNode
	{
	public:
		int priority;
		int value;
		HeapNode()  { value = priority = 0; }
		HeapNode(int v, int p) { value = v; priority = p; }
		~HeapNode() { value = priority = 0; }
	};

	std::vector<HeapNode*>* heap;

	void swap_heap_node(int, int);
	void min_heapify(int);

public:
	MinHeap() { heap = new std::vector<HeapNode*>(); heap->push_back(new HeapNode(0,0)); }
	~MinHeap();

	bool is_empty() { return size() <= 0; }

	int parent(int index) { return index / 2; }
	int left(int index) { return 2 * index; }
	int right(int index) { return 2 * index + 1; }

	int min() { return (*heap)[0]->value; }
	int extract_min();

	int size() { return heap->size() - 1; }
	void insert(int, int);
	bool decrease_priority(int, int);

	void print();
};

MinHeap::~MinHeap()
{
	while (heap->size())
	{
		delete (*heap)[size()];
		heap->pop_back();
	}

	delete heap;
}

void MinHeap::swap_heap_node(int x, int y)
{
	int p = (*heap)[x]->priority;
	int v = (*heap)[x]->value;

	(*heap)[x]->priority = (*heap)[y]->priority;
	(*heap)[x]->value = (*heap)[y]->value;
	(*heap)[y]->priority = p;
	(*heap)[y]->value = v;
}

void MinHeap::min_heapify(int index)
{
	int lc = left(index);
	int rc = right(index);

	int smallest = index;

	// do comparisons with child nodes to determine small value
	// if l or r is > size, then there is no node at that index
	if (lc < size() && (*heap)[lc]->priority < (*heap)[smallest]->priority)
		smallest = lc;
	if (rc < size() && (*heap)[rc]->priority < (*heap)[smallest]->priority)
		smallest = rc;
	if (smallest != index) // if the node at index is not the smallest, perculate down the heap
	{
		swap_heap_node(index, smallest);
		min_heapify(smallest); // check again if we need to perculate down another level
	}
}

int MinHeap::extract_min()
{
	int min_value;

	if (is_empty())
		exit(1);

	if (size() == 1) 
	{
		min_value = (*heap)[size()]->value;
		delete (*heap)[size()];
		heap->pop_back();
		return min_value;
	}

	min_value = (*heap)[1]->value; // copy min value before delete the top node
	swap_heap_node(1, size()); // swap min node with last node
	delete (*heap)[size()]; // delete last node (prev min node)
	heap->pop_back();

	min_heapify(1); // reheapify starting at root node (index 1)

	return min_value;
}

void MinHeap::insert(int value, int priority)
{
	heap->push_back(new HeapNode(value, priority));

	int index = size();

	// position new node correctly in min heap
	while ( index != 1 && (*heap)[parent(index)]->priority > (*heap)[index]->priority)
	{
		// since the new node is smaller than its parent,
		// we the nodes to swap places. 
		swap_heap_node(index, parent(index));
		index = parent(index);
		// update the index to reflect our new position in the heap
	} 
}

bool MinHeap::decrease_priority(int value, int priority)
{	
	for (int i = 1; i <= size(); ++i)
	{
		if ((*heap)[i]->value == value)
		{
			(*heap)[i]->priority = priority;

			while (i != 1 && (*heap)[parent(i)]->priority > (*heap)[i]->priority)
			{
				swap_heap_node(i, parent(i));
				i = parent(i);
			}

			return true;
		}
	}
	
	return false;
}

void MinHeap::print()
{
	for (int i = 1; i <= size(); ++i)
		std::cout << (*heap)[i]->priority << " ";

	std::cout << std::endl;
}

#endif
