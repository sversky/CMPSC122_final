#include <iostream>
#include <string>
#include "graph.h"
#include "min_heap.h"
#include "set.h"
#include "stack.h"
#include <limits>

using namespace std;

void dijkstra(Graph graph, int start, int end);
int main()
{
	Graph *graph = new Graph();
	string path;
        int startIndex, targetIndex;        

	cout << "Please enter location of graph file to load: ";
	cin >> path;
        
        cout << "Please enter the index of the starting vertex: ";
        cin >> startIndex;
        
        cout << "Please enter the index of the target vertex: ";
        cin >> targetIndex;
        
	(*graph).create_graph(path);

	cout << (*graph).dimension() << endl;
        
        dijkstra(*graph, startIndex, targetIndex);

	return 0;
}

void dijkstra(Graph graph, int start, int end) {
    int *distance = new int[graph.dimension()];
    int *previous = new int[graph.dimension()];
    
    MinHeap heap = MinHeap();
    
    distance[start] = 0;

    for( int i = 0; i < graph.dimension(); i++ ) {
        if(i != start)
        {
            distance[i] = std::numeric_limits<int>::max();
        }
        
        previous[i] = -1;
        heap.insert(i, distance[i]);
    }
    
    int nearestNeighbor = -1;
    
    while( !heap.is_empty() ) {
        nearestNeighbor = heap.extract_min();
        
        if( nearestNeighbor == end ) {
            break;
        }
        
        for(int i = 0; i < graph.dimension(); i++) {
            int u = nearestNeighbor;
            int v = i;
            
            if(v == nearestNeighbor || graph.get_weight(u, v) == 0)
            {
                // Skip current node
                continue;
            }
                        
            int alt = distance[u] + graph.get_weight( u, v );
            
            if( alt < distance[v] )
            {
                distance[v] = alt;
                previous[v] = u;
                heap.decrease_priority(v, alt);
            }
        }
        
    }
    
    Stack stack = Stack();
    int u = end;
    
    while( u != -1 ) {
        stack.push(u);
        u = previous[u];
    }
    int totalPathLength = 0;
    
    cout << "The shortest path from vertex " << start <<" to vertex "<< end << " is: " << endl << endl;
    
    while( !stack.isEmpty() ) {
        int current = stack.pop();
        
        if( current == end )
        {
            break;
        }
        int next = stack.top();
        int weight = graph.get_weight(current, next);
        cout << current << " to " << next << ": " << weight << endl;
        
        totalPathLength += weight;
    }
    
    cout << endl;
    cout << "Total path length is " << totalPathLength << endl;
    
    delete distance;
    delete previous;
}
