#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

#include <utility>
#include <vector>

typedef unsigned long long _time;

class Cluster {
	private:
		std::vector<_time> last_access_time, utilization_time;
		std::vector<bool> core_busy;

		float cpi = 1;
		int clock_period = 1;
		unsigned id;

		friend class Scheduler;
		friend class Processor;

	public:
		Cluster(int id, unsigned cores);

		int reserve_core(_time time);
		void release_core(int core_id, _time time);

		bool is_free();

		void resize(unsigned size);

};

#endif /* CLUSTER_HPP_ */
