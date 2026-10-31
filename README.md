# OS Lab Programs (C++)

Simple, commented C++ programs for the 11 Operating Systems lab experiments.

| # | Experiment | File |
|---|-----------|------|
| 1 | FCFS scheduling | 01_cpu_scheduling/01_fcfs.cpp |
| 2 | SJF scheduling | 01_cpu_scheduling/02_sjf.cpp |
| 3 | Priority scheduling | 01_cpu_scheduling/03_priority.cpp |
| 4 | Round Robin scheduling | 01_cpu_scheduling/04_round_robin.cpp |
| 5 | Producer-Consumer | 02_ipc_problems/05_producer_consumer.cpp |
| 6 | Readers-Writers | 02_ipc_problems/06_readers_writers.cpp |
| 7 | Dining Philosophers | 02_ipc_problems/07_dining_philosophers.cpp |
| 8 | FIFO page replacement | 03_page_replacement/08_fifo.cpp |
| 9 | LRU page replacement | 03_page_replacement/09_lru.cpp |
| 10 | LFU page replacement | 03_page_replacement/10_lfu.cpp |
| 11 | Optimal page replacement | 03_page_replacement/11_optimal.cpp |

## Run
```bash
g++ 01_cpu_scheduling/01_fcfs.cpp -o fcfs && ./fcfs
g++ -pthread 02_ipc_problems/05_producer_consumer.cpp -o pc && ./pc   # IPC programs need -pthread
```

## Inputs
- FCFS / SJF / Round Robin: number of processes, then `arrival burst` for each (Round Robin also asks for the time quantum).
- Priority: `arrival burst priority` (smaller number = higher priority).
- Page replacement: number of pages, the reference string, then the number of frames.
  Example: `12`, `7 0 1 2 0 3 0 4 2 3 0 3`, `3`
- IPC programs need no input.
