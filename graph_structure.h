#ifndef GRAPHSTRUCTURE_HPP
#define GRAPHSTRUCTURE_HPP

#include <iostream>
#include <list>
#include <set>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using std::list;
using std::vector;
using std::pair;
using std::map;
using std::set;

class Graph {
private:

	vector < list < int > > adjacency_list;
	set < vector < int > > clique;
	int qnt_vortex = 0;
	map < int, int > degree;

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
	int insert_degree(vector<int>);
	//vector<int> choose_pivot(vector<int>, vector <int>);
	void remove_small_clq(int);
};

#endif