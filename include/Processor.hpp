#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

#include <Cluster.hpp>
#include <vector>

typedef unsigned long long _time;

class Scheduler;

struct TaskGraph;

class Processor {
	private:
		Scheduler* sched;
		std::vector<Cluster*> multiprocessor;

		_time curr_time;

	public:
		Processor(int clusters, int cores_per_clusters);
		void execute_tasks(TaskGraph& graph);
		Cluster* get_available_cluster() const;

		_time get_time() const;
		void seek_time(_time);

		void write_statistics();
};

#endif /* PROCESSOR_HPP_ */
