#include <Processor.hpp>
#include <stddef.h>
#include <Scheduler.hpp>

Processor::Processor(int clusters, int cores_per_clusters)
		: curr_time(0) {
	sched = new Scheduler(this);
	multiprocessor.resize(clusters);
	for (int i = 0; i < clusters; i++) {
		multiprocessor[i] = new Cluster(i, cores_per_clusters);
	}
}

void Processor::execute_tasks(TaskGraph& graph) {
	sched->assign_graph(graph);
	sched->run();
}

Cluster* Processor::get_available_cluster() const {
	for (Cluster* cluster : multiprocessor) {
		if (cluster->is_free()) {
			return cluster;
		}
	}
	return NULL;
}

_time Processor::get_time() const {
	return curr_time;
}

void Processor::seek_time(_time time) {
	curr_time = time;
}

void Processor::write_statistics() {
	printf("Total time taken: %llu\n", curr_time);
	int i = 0;
	for (Cluster* cluster : multiprocessor) {
		printf("\nCluster #%d:\n\n", i);
		int j = 0;
		for (_time utilization_time : cluster->utilization_time) {
			printf("Core #%d: %lf%%\n", j,
					100.0 * utilization_time / (double) curr_time);
			j++;

		}
		i++;
	}
}

