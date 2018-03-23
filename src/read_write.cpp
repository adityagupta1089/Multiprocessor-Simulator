#include <Processor.hpp>
#include <read_write.hpp>
#include <TaskGraph.hpp>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

class Processor;

void read_input(char* file_name, TaskGraph& graph) {
	std::ifstream in;
	char c;

	in.open(file_name);

	if (!in) {
		printf("Couldn't open file!\n");
		exit(1);
	}

	int n;
	in >> n;
	graph.resize(n);

	for (int i = 0; i < n; i++) {
		int id;
		in >> id;
		std::string name = "";
		if (in >> c && c == ',' && in >> c && c == '\"') {
			in >> std::noskipws;
			while (in >> c && c != '\"') {
				name += c;
			}
			in >> std::skipws;
			while (in >> c && c != ',')
				;
		}
		int cost;
		in >> cost;
		TaskGraph::TaskNode* node = new TaskGraph::TaskNode(id, name, cost);
		graph.add_node(node);
	}

	for (int i = 0; i < n; i++) {
		int src, dest;
		unsigned cost = 0;
		in >> src;
		while (in >> c && c != ',')
			;
		in >> dest;
		while (in >> c && c != ',')
			;
		if (in.get(c) && c != '\n') in >> cost;
		TaskGraph::TaskEdge* edge = new TaskGraph::TaskEdge(src, dest, cost);
		graph.add_edge(edge);
	}

	in.close();
}
