#include "graph_structure.h"

using namespace std::chrono;

int main(int argc, char const* argv[]) {
	FILE* file;
	char trash[10];
	char c_trash;
	int quantityOfVortex;
	int quantityOfEdges;
	int vortex_one, vortex_two;
	duration<double> time_span2;
	std::vector < int > all_vortex;


	if ((file = fopen(argv[1], "r")) == NULL) { //Abertura do arquivo.txt
		std::cout << "Error " << argv[1] << std::endl;
		exit(1);
	}
	if (fscanf(file, "%c %[A-Z a-z] %d %d '\n'", &c_trash, trash, &quantityOfVortex, &quantityOfEdges))
		std::cout << quantityOfVortex << " " << quantityOfEdges << std::endl;
	else
		return 1;

	Graph graph (quantityOfVortex);

	for (int i = 0; i < quantityOfVortex; i++)
		all_vortex.push_back(0);
	

	while (fscanf(file, "%c %d %d '\n'", &c_trash, &vortex_one, &vortex_two) != EOF) {
		graph.insert_vortex(vortex_one - 1, vortex_two - 1);
		all_vortex[vortex_one - 1]++;
		all_vortex[vortex_two - 1]++;
	}
	//graph.print_graph();

	int qnt_k2 = graph.insert_degree(all_vortex);


	fclose(file);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	if (qnt_k2 != 0)
		graph.remove_small_clq(qnt_k2);

	graph.init_bron_kerbosch();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double, std::milli>>(t2 - t1);

	std::cout << "\nExecution Time " << time_span.count() << " ms " << std::endl;

	graph.print_clique();
	return 0;
}
