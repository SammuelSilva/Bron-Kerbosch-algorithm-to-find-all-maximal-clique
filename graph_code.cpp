#include "graph_structure.h"

static int counter = 0;

//insere os dados de um vector que contem os graus para um map;
int Graph::insert_degree(vector <int> aux_dg) {
	bool ini = 0;
	for (int i = 0; i < qnt_vortex; i++) {
		degree.insert(pair<int, int>(i, aux_dg[i])); // i = vertice, aux_dg[i] == grau
		if (aux_dg[i] == 1) 
			ini+=1;
		
	}

	for (auto itr = degree.begin(); itr != degree.end(); ++itr)
		std::cout << "Vortex: " << itr->first << ", Degree: " << itr->second << std::endl;

	std::cout << std::endl;

	std::cout << "K2 Quantity: " << ini << std::endl << std::endl;
	return ini;
}

//Adiciona os K2 em clique e remove eles do grafo 
void Graph::remove_small_clq(int qnt) {
	for (auto it = degree.begin(); it != degree.end(); ++it) {

		if (qnt == 0)
			break;

		if (it->second > 1 || it->second < 0)
			continue;

		int aux  = it->first;
		int aux2 = *adjacency_list[aux].begin();
		clique.insert(vector<int> { aux, aux2 });
		adjacency_list[aux2].remove(aux);
		adjacency_list.erase(adjacency_list.begin() + aux);

		degree.erase(it);

		for (auto tmp = degree.begin(); tmp != degree.end(); ++tmp)
			if (tmp->first == aux2) {
				tmp->second = -1;
				qnt_vortex--;
				qnt--;
				break;
			}
					
		
	}

	//print_graph();
}

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

	FILE* result;
	if ((result = fopen("exit.txt", "w")) == NULL) { //Criação do arquivo de saida.txt
		std::cout << "ERRO" << std::endl;
		exit(1);
	}
	char trash = '|';
	for (auto it = clique.begin(); it != clique.end(); ++it) {
		for (int i = 0; i < (*it).size(); i++)
			fprintf(result, "%d " " ", (*it)[i]);
		fprintf(result, "%c " " \n", trash);
	}

	fclose(result);

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
/*
vector<int> Graph::choose_pivot(vector <int> v1, vector <int> v2) {
	vector <int> aux = {};
	vector <int> aux_2 = {};

	for (int i = 0; i < v1.size(); i++) {
		aux.push_back(v1[i]);
		aux_2.push_back(v1[i]);
		for (int j = 0; j < v2.size(); j++)
			if (v1[i] != v2[i])
				aux.push_back(v2[i]);
	}

	int ammount = 0;
	int position = 0;

	for(int i = 0; i < aux.size(); i++)
		if (dg[aux[i]]->degree > ammount) {
			ammount = dg[aux[i]]->degree;
			position = i;
		}
	
	for (int vortex_adj : adjacency_list[position])
		aux_2.erase(remove(aux_2.begin(), aux_2.end(), vortex_adj), aux_2.end());

	return aux_2;
}
*/

void Graph::init_bron_kerbosch() {
	vector < int > answer, adjacency, duplicate;

	for (std::vector<int>::size_type i = 0; i < adjacency_list.size(); i++)
		adjacency.push_back(i);

	std::cout << "LOOKING FOR CLIQUES" << std::endl;
	bron_kerbosch(answer, adjacency, duplicate);


	std::cout << "Calls: " << counter << std::endl;
}
static long long int x = 100000;

void Graph::bron_kerbosch(vector < int > answer, vector < int > adjacency, vector < int > duplicate) {
	counter++;
	if (adjacency.empty() && duplicate.empty()) {
		clique.insert(answer);
		return;
	}
	if (counter == x) {
		std::cout << ">= " << counter << std::endl;
		x += 1000000;
	}
	//std::cout << &answer << " " << &adjacency << " " << &duplicate << std::endl;
	//vector<int> adjacency_temp = choose_pivot(adjacency, duplicate);

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

		duplicate.push_back(adjacency[vortex]);
		answer.erase(remove(answer.begin(), answer.end(), adjacency[vortex]), answer.end());
		adjacency.erase(remove(adjacency.begin(), adjacency.end(), adjacency[vortex]), adjacency.end());
		answer.erase(remove(answer.begin(), answer.end(), adjacency[vortex]), answer.end()); // Remove o vertice da resposta
		adjacency.erase(remove(adjacency.begin(), adjacency.end(), adjacency[vortex]), adjacency.end()); //Remove o vertice do conjunto de adjacency
>>>>>>> 8e81d6e607c29d4651762bed55eabe735f236c4c

		vortex--; //Atrasa a posicao em 1
	}
}
