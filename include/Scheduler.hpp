#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <Processor.hpp>
#include <TaskGraph.hpp>
#include <queue>
#include <vector>

class Processor;

class Scheduler {
	private:
		enum event_type {
			TASK_FINISH,
			COMMUNICATION_FINISH
		};

		struct event {
				_time event_time;
				unsigned task_node_id;
				event_type type;
				Cluster* assigned_cluster;
				int core_id;
				bool operator<(const event& that) const {
					return event_time > that.event_time;
				}
		};

		std::priority_queue<event> events_list;

		std::vector<TaskGraph::TaskNode*> ready_list, wait_list;

		Processor* processor;
		TaskGraph* current_graph;

		void handle_task_finish(event _event);
		void handle_comunication_finish(event _event);
		void schedule();

		bool node_ready(TaskGraph::TaskNode*);

	public:
		Scheduler(Processor* _processor);
		void assign_graph(TaskGraph& graph);
		void run();

};
#endif /* SCHEDULER_H_ */
