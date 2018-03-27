#include <Cluster.hpp>
#include <Scheduler.hpp>
#include <cstdio>
#include <iterator>

class Processor;

Scheduler::Scheduler(Processor* _processor)
		: processor(_processor), current_graph(NULL) {
}

void Scheduler::assign_graph(TaskGraph& graph) {
	current_graph = &graph;
	for (auto node : current_graph->nodes) {
		printf("Adding Task #%d to wait list\n", node->task_id);
		wait_list.push_back(node);
	}
	for (auto it = wait_list.begin(); it != wait_list.end(); it++) {
		auto node = *it;
		if (node_ready(node)) {
			printf("Adding Task #%d to ready list from wait list\n",
					node->task_id);
			ready_list.push_back(node);
			it = wait_list.erase(it) - 1;
		}
	}
}

void Scheduler::schedule() {
	for (auto it = ready_list.begin(); it != ready_list.end(); it++) {
		auto node = *it;
		Cluster* available_cluster = processor->get_available_cluster();
		int reserved_core;
		if (available_cluster
				&& (reserved_core = available_cluster->reserve_core(
						processor->get_time())) >= 0) {
			_time finish_time = processor->get_time()
					+ node->task_cost * available_cluster->cpi
							* available_cluster->clock_period;
			printf("Scheduling an event for Task #%d's completion at %llu on "
					"Cluster #%d's core #%d & adding it to running list\n",
					node->task_id, finish_time, available_cluster->id,
					reserved_core);
			event task_finish =
				{
					finish_time,
					node->task_id,
					event_type::TASK_FINISH,
					available_cluster,
					reserved_core };
			events_list.push(task_finish);
			it = ready_list.erase(it) - 1;
			// TODO running_list.push_back(node);
		}
	}
}

void Scheduler::handle_task_finish(event _event) {
	auto node = current_graph->nodes[_event.task_node_id];
	printf("Task #%d completed at %llu\n", node->task_id, _event.event_time);
	node->finished = true;
	_event.assigned_cluster->release_core(_event.core_id, _event.event_time);
	processor->seek_time(_event.event_time);
	for (auto edge : node->outgoing_edges) {
		auto child = current_graph->nodes[edge->dest_id];
		if (edge->cost > 0) {
			/* TODO simplistic communication done */
			_time communication_finish_time = processor->get_time()
					+ edge->cost;
			printf("Scheduling an event for Communication to Task #%d's "
					"completion at %llu sent from Cluster #%d's core #%d\n",
					child->task_id, communication_finish_time,
					_event.assigned_cluster->id, _event.core_id);
			event communication_finish =
				{
					communication_finish_time,
					child->task_id,
					event_type::COMMUNICATION_FINISH,
					NULL,
					0 };
			events_list.push(communication_finish);
		} else if (node_ready(child)) {
			printf("Adding Task #%d to ready list\n", child->task_id);
			ready_list.push_back(child);
			// TODO Removal from wait_list
		}
	}
}

void Scheduler::handle_comunication_finish(event _event) {
	auto node = current_graph->nodes[_event.task_node_id];
	printf("Communication to Node #%d completed at %llu\n", node->task_id,
			_event.event_time);
	processor->seek_time(_event.event_time);
	if (node_ready(node)) {
		printf("Adding Task #%d to ready list\n", node->task_id);
		ready_list.push_back(node);
		//TODO removal from wait_list
	}
}

void Scheduler::run() {
	schedule();
	while (!events_list.empty()) {
		event curr = events_list.top();
		events_list.pop();
		if (curr.type == event_type::TASK_FINISH) {
			handle_task_finish(curr);
		} else {
			handle_comunication_finish(curr);
		}
		schedule();
	}
	printf("\nAll Tasks Completed\n\n");
}

bool Scheduler::node_ready(TaskGraph::TaskNode* node) {
	for (auto edge : node->incoming_edges) {
		if (!current_graph->nodes[edge->src_id]->finished) {
			return false;
		}
	}
	return true;
}
