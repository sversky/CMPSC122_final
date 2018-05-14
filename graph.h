#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
// NOTE: Changed so header would compile...
#include <cstdlib>

class Graph
{
private:
	int adj_matrix_size;
	int* adj_matrix;
	bool filled;

public:
	Graph() { adj_matrix_size = 0; adj_matrix = 0; filled = false; };
	~Graph();

	bool create_graph(std::string);
	int get_weight(int, int);
	void print_adj_matrix();

	int dimension() { return adj_matrix_size; }
};

Graph::~Graph()
{
	filled = false;

	for (int r = 0; r < adj_matrix_size; ++r)
		for (int c = 0; c < adj_matrix_size; ++c)
			adj_matrix[r * adj_matrix_size + c] = 0;

	if (adj_matrix)
		delete adj_matrix;
}

bool Graph::create_graph(std::string path)
{
	// open file with input file stream on given path
    // NOTE: Changed so header would compile...
	std::ifstream fs(path.c_str());
	std::string line;

	// check for errors openign file
	if (!fs.is_open())
		return false;

	// clear any existing graph data
	adj_matrix_size = 0;
	filled = false;
	if (adj_matrix)
	{
		delete adj_matrix;
		adj_matrix = 0;
	}

	// get matrix size from first line
	std::getline(fs, line);
	std::istringstream ss(line);

	ss >> adj_matrix_size;

	// create square matrix to store graph information
	adj_matrix = new int[adj_matrix_size * adj_matrix_size];

	for (int r = 0; r < adj_matrix_size; ++r)
	{
		// get next line of adj matrix
		if (!std::getline(fs, line))
			return false;

		// clear previous flag, set iss to read over new string
		ss.clear();
		ss.str(line);

		for (int c = 0; c < adj_matrix_size; ++c)
		{
			// fill matrix token by token
			if (!(ss >> adj_matrix[r * adj_matrix_size + c]))
				return false; // exit if reading token failed
		}
	}

	if (fs.bad())
		return false;

	fs.close();
	filled = true;
	return true;
}

int Graph::get_weight(int row, int column)
{
	if (row < 0 || adj_matrix_size <= row || column < 0 || adj_matrix_size <= column)
	{
		std::cout << "Invalid indexing, no weight exists at " << row << "," << column << std::endl;
		exit(1);
	}

	return adj_matrix[row * adj_matrix_size + column];
}

void Graph::print_adj_matrix()
{
	for (int r = 0; r < adj_matrix_size; ++r)
	{
		for (int c = 0; c < adj_matrix_size; ++c)
			std::cout << adj_matrix[r * adj_matrix_size + c] << " ";

		std::cout << std::endl;
	}
}

#endif
