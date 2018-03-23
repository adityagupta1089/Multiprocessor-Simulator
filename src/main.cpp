#include <Processor.hpp>
#include <read_write.hpp>
#include <stdio.h>
#include <TaskGraph.hpp>
#include <cstdlib>

int main(int argc, char** argv) {
	if (argc < 4) {
		fprintf(stderr,
				"Input Format: <clusters> <cores_per_cluster> <task_graph_file> %s",
				argv[0]);
		exit(1);
	}

	TaskGraph graph;
	Processor processor(atoi(argv[1]), atoi(argv[2]));

	read_input(argv[3], graph);
	processor.execute_tasks(graph);
	processor.write_statistics();

	return 0;
}
