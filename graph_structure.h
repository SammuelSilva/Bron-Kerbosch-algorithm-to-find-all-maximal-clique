#ifndef GRAPHSTRUCTURE_HPP
#define GRAPHSTRUCTURE_HPP

#include <iostream>
#include <list>
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

using std::list;
using std::vector;
using std::set;


class Graph {
private:

	vector < list < int > > adjacency_list;
	set < vector < int > > clique;
	int qnt_vortex = 0;

public:

	Graph(int);
	~Graph();
	void insert_vortex(int, int);
	void print_graph();
	void print_clique();
	void bfs_function(int);
	void init_bron_kerbosch();
	void bron_kerbosch(vector <int>, vector <int>, vector <int>);
	void sort();
};

#endif