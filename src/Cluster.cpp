#include <Cluster.hpp>
#include <Processor.hpp>

int Cluster::reserve_core(_time time) {
	for (unsigned i = 0; i < core_busy.size(); i++) {
		if (!core_busy[i]) {
			core_busy[i] = true;
			last_access_time[i] = time;
			return i;
		}
	}
	return -1;
}

void Cluster::release_core(int core_id, _time time) {
	if (core_busy[core_id]) {
		core_busy[core_id] = false;
		_time utilization = time - last_access_time[core_id];
		utilization_time[core_id] += utilization;
		last_access_time[core_id] = time;
	}
}

Cluster::Cluster(int _id, unsigned cores)
		: id(_id) {
	core_busy.resize(cores);
	last_access_time.resize(cores);
	utilization_time.resize(cores);
	for (unsigned i = 0; i < cores; i++) {
		core_busy[i] = false;
		last_access_time[i] = 0;
		utilization_time[i] = 0;
	}
}

bool Cluster::is_free() {
	for (bool busy : core_busy) {
		if (!busy) {
			return true;
		}
	}
	return false;
}
