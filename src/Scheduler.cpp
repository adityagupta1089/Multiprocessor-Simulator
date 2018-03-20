#include <Cluster.hpp>
#include <Processor.hpp>
#include <Scheduler.hpp>
#include <iterator>

class Processor;

Scheduler::Scheduler(Processor* _processor, TaskGraph& graph)
		: processor(_processor), current_graph(&graph), curr_time(0) {
	for (TaskGraph::TaskNode* node : current_graph->nodes) {
		wait_list.push_back(node);
	}
	schedule_ready_list();
	schedule_next_event();
}

void Scheduler::schedule_ready_list() {
	for (auto it = wait_list.begin(); it != wait_list.end(); it++) {
		TaskGraph::TaskNode* node = *it;
		bool ready = true;
		for (TaskGraph::TaskEdge* edge : node->incoming_edges) {
			if (!current_graph->nodes[edge->src_id]->finished) {
				ready = false;
				break;
			}
		}
		if (ready) {
			ready_list.push_back(node);
			it = wait_list.erase(it);
		}
	}
}

void Scheduler::schedule_next_event() {
	TaskGraph::TaskNode* node = ready_list.back();
	Cluster* available_cluster = processor->get_available_cluster();
	if (available_cluster && available_cluster->reserve_core()) {
		unsigned long long finish_time = curr_time
				+ node->task_cost * available_cluster->cpi
						* available_cluster->clock_period;
		event task_finish =
			{ finish_time, node->task_id, event_type::TASK_FINISH };
		events_list.push(task_finish);
		ready_list.pop_back();
		running_list.push_back(node);
	}
}

void Scheduler::handle_task_finish(event _event) {

}

void Scheduler::handle_comunication_finish(event _event) {

}

void Scheduler::run() {
	while (!events_list.empty()) {
		event curr = events_list.top();
		events_list.pop();
		if (curr.type == event_type::TASK_FINISH) {
			handle_task_finish(curr);
		} else {
			handle_comunication_finish(curr);
		}
		schedule_next_event();
	}
}
