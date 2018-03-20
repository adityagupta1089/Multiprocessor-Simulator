#ifndef TASKGRAPH_HPP_
#define TASKGRAPH_HPP_

#include <string>
#include <vector>

struct TaskGraph {

		struct TaskEdge {
				int src_id;
				int dest_id;
				unsigned cost;
				TaskEdge(int s, int d, int c)
						: src_id(s), dest_id(d), cost(c) {
				}
		};

		struct TaskNode {
				unsigned task_id;
				std::string task_name;
				unsigned task_cost;
				bool finished = false;
				std::vector<TaskEdge*> incoming_edges;
				std::vector<TaskEdge*> outgoing_edges;
				TaskNode(unsigned id, std::string name, unsigned cost)
						: task_id(id), task_name(name), task_cost(cost) {
				}
		};

		std::vector<TaskNode*> nodes;

		void resize(int n) {
			nodes.resize(n);
		}

		void add_node(TaskNode* node) {
			nodes[node->task_id] = node;
		}

		void add_edge(TaskEdge* edge) {
			nodes[edge->src_id]->outgoing_edges.push_back(edge);
			nodes[edge->dest_id]->incoming_edges.push_back(edge);
		}
};

#endif /* TASKGRAPH_HPP_ */

