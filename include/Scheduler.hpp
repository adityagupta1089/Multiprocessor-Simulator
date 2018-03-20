#ifndef SCHEDULER_H_
#define SCHEDULER_H_

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
				unsigned long long event_time;
				unsigned task_node_id;
				event_type type;
				bool operator<(const event& that) const {
					return event_time < that.event_time;
				}
		};

		std::priority_queue<event> events_list;

		std::vector<TaskGraph::TaskNode*> ready_list, wait_list, running_list;

		Processor* processor;
		TaskGraph* current_graph;

		unsigned long long curr_time;

		void handle_task_finish(event _event);
		void handle_comunication_finish(event _event);
		void schedule_ready_list();
		void schedule_next_event();

	public:
		Scheduler(Processor* _processor, TaskGraph& graph);
		void run();

};
#endif /* SCHEDULER_H_ */
