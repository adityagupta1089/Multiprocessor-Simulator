# Multiprocessor Simulator

This project aims to simulate the function of a multiprocessor that is modelled as clusters of cores with separate CPI (cycles per instruction) and clock period which is set to 1 each for simplicity. The simulater takes in a DAG of a task where nodes correspond to computation and edge weights correspond to communication costs. The simulator always encurs the communication cost even if the core/cluster remains the same for simplicity. Finally it gives statistics in form of total time taken for the whole computation and the utilization of each core and the parallelization factor.

## Structure

```
├── bin/ - All the binaries generated
├── include/ - All the header files
│   ├── Cluster.hpp
│   ├── Processor.hpp
│   ├── read_write.hpp
│   ├── Scheduler.hpp
│   └── TaskGraph.hpp
├── input/ - All the input files
├── makefile
├── README.md
└── src
    ├── Cluster.cpp - Represents a single cluster in the multiprocessor
    ├── main.cpp - Main driver client
    ├── Processor.cpp - Represent the aggregation of the clusters into the multiprocessor
    ├── read_write.cpp - Utility for reading the input graph from the file and parsing it
    └── Scheduler.cpp - Scheduling a graph on a given processor
```

## How to Build & Run?

- Building: `make all`
- Running: `./bin/main.o <clusters> <cores_per_cluster> <task_graph_file>`
  - e.g. `./bin/main.o 1 4 input/test.graph`
- Cleaning `make clean`

## Notes

- Assumes communication cost is always incurred.
- Assumes CPI and clock period to 1 each.
- Since no consequences entail, removal from wait list is not done. Also running list is not required per se and hasn't been created.