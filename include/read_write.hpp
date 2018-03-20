#ifndef INCLUDE_READ_WRITE_HPP_
#define INCLUDE_READ_WRITE_HPP_

struct TaskGraph;

class Processor;

void read_input(char* file_name, TaskGraph& graph);
void write_statistics(Processor& processor);

#endif /* INCLUDE_READ_WRITE_HPP_ */
