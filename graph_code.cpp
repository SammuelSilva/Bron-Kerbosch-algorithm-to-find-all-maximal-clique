#include "graph_structure.h"


Graph::Graph(int size) {
	qnt_vortex = size;
	adjacency_list.resize(size);
}

Graph::~Graph() {}

void Graph::insert_vortex(int v1, int v2) {
	adjacency_list[v1].push_back(v2);
	adjacency_list[v2].push_back(v1);
}

void Graph::print_graph() {
	for (int i = 0; i < qnt_vortex; i++) {

		if (i < 10)
			std::cout << "0" << i << ") -> ";
		else
			std::cout << i << ") -> ";

		for (auto iterator = adjacency_list[i].begin(); adjacency_list[i].end() != iterator; ++iterator) {
			std::cout << *iterator << " ";
		}

		std::cout << "\n";
	}

	std::cout << "\n";
}

void Graph::print_clique() {

	std::cout << "\nNumbers of cliques found: " << clique.size() << std::endl;

}


void Graph::bfs_function(int position) {
	list<int> queue;
	bool* visited = new bool[qnt_vortex];

	for (int i = 0; i < qnt_vortex; i++)
		visited[i] = false;

	visited[position] = true;
	queue.push_back(position);

	std::cout << "BFS: ";
	while (!queue.empty()) {
		position = queue.front();

		std::cout << position << "  ";
		queue.pop_front();

		for (int adj : adjacency_list[position])
			if (!visited[adj]) {
				visited[adj] = true;
				queue.push_back(adj);
			}

	};

}

void Graph::sort() {
	for (std::vector<int>::size_type vortex = 0; vortex < adjacency_list.size(); vortex++) {
		adjacency_list[vortex].sort();
	}
}

void Graph::init_bron_kerbosch() {
	vector < int > answer, adjacency, duplicate;
	std::cout << "LOOKING FOR CLIQUES" << std::endl;

	for (std::vector<int>::size_type i = 0; i < adjacency_list.size(); i++)
		adjacency.push_back(i);
	

	bron_kerbosch(answer, adjacency, duplicate);
}

void Graph::bron_kerbosch(vector < int > answer, vector < int > adjacency, vector < int > duplicate) {

	if (adjacency.empty() && duplicate.empty()) {
		clique.insert(answer);
		return;
	}
	
	for (std::vector<int>::size_type vortex = 0; vortex < adjacency.size(); vortex++) {
		vector<int> intersection_P = {}, intersection_X = {};			

		//neighbors(P)
		for (int vortex_adj : adjacency_list[adjacency[vortex]]) {
			for (std::vector<int>::size_type aux = 0; aux < adjacency.size(); aux++)
				if (vortex_adj == adjacency[aux])
					intersection_P.push_back(adjacency[aux]);


			//neighbors(X)
			for (std::vector<int>::size_type aux = 0; aux < duplicate.size(); aux++) {
				if (vortex_adj == duplicate[aux])
					intersection_X.push_back(duplicate[aux]);
			}
			
		}

		answer.push_back(adjacency[vortex]);

		bron_kerbosch(answer, intersection_P, intersection_X);

		int temp = adjacency[vortex];
		duplicate.push_back(temp);
		answer.erase(remove(answer.begin(), answer.end(), temp), answer.end());
		adjacency.erase(remove(adjacency.begin(), adjacency.end(), temp), adjacency.end());

		vortex--;
	}
}