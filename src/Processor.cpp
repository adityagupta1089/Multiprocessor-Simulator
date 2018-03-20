#include <Processor.hpp>
#include <Scheduler.hpp>

Processor::Processor(int clusters, int cores_per_clusters) {
	multiprocessor.resize(clusters);
	for (Cluster* cluster : multiprocessor) {
		cluster->core_busy.resize(cores_per_clusters);
	}
}

void Processor::execute_tasks(TaskGraph& graph) {
	Scheduler sched(this, graph);
	sched.run();
}

Cluster* Processor::get_available_cluster() {
	for (Cluster* cluster : multiprocessor) {
		for (bool core_busy : cluster->core_busy) {
			if (!core_busy) {
				return cluster;
			}
		}
	}
	return NULL;
}
