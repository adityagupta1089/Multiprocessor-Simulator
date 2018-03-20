#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

#include <vector>

struct Cluster {
		float cpi;
		int clock_period;
		int cores;
		int cores_busy = 0;

		bool reserve_core() {
			if (cores_busy < cores) {
				cores_busy++;
				return true;
			} else return false;
		}

		bool release_core() {
			if (cores_busy > 0) {
				cores_busy--;
			} else return false;
		}
};

#endif /* CLUSTER_HPP_ */
