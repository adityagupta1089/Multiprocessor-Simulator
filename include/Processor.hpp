#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

#include <Cluster.hpp>
#include <vector>

struct TaskGraph;

class Processor {
	private:
		std::vector<Cluster*> multiprocessor;

	public:
		Processor(int clusters, int cores_per_clusters);
		void execute_tasks(TaskGraph& graph);
		Cluster* get_available_cluster();
};

#endif /* PROCESSOR_HPP_ */
