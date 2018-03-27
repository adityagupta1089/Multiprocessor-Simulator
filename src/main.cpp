#include <Processor.hpp>
#include <read_write.hpp>
#include <stdio.h>
#include <TaskGraph.hpp>
#include <cstdlib>

int main(int argc, char** argv) {
	if (argc < 4) {
		fprintf(stderr,
				"Input Format: %s <clusters> <cores_per_cluster> <task_graph_file>",
				argv[0]);
		exit(1);
	}

	TaskGraph graph;
	Processor processor(atoi(argv[1]), atoi(argv[2]));

	printf("Reading graph\n");
	read_input(argv[3], graph);
	printf("Running the multiprocessor\n");
	processor.execute_tasks(graph);
	processor.print_statistics();
	_time t1 = processor.get_time();

	Processor serial_processor(1, 1);
	read_input(argv[3], graph);
	printf("Running a uniprocessor for comparison\n");
	serial_processor.execute_tasks(graph);
	_time t2 = serial_processor.get_time();

	printf("Parallelization factor is: %f\n", t2 / (double) t1);

	return 0;
}
