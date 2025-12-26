# Operating Systems Lab

This repository contains implementations of various Operating System algorithms in C, structured by category.

## Directory Structure

```
Operating-Systems-
├── CPU_Scheduling
│   ├── FCFS.c          # First Come First Serve
│   ├── SJF.c           # Shortest Job First (Non-Preemptive)
│   ├── SJFpre.c        # Shortest Job First (Preemptive)
│   ├── RR.c            # Round Robin
│   ├── Priority.c      # Priority Scheduling (Non-Preemptive)
│   └── PriorityPre.c   # Priority Scheduling (Preemptive)
├── Memory_Management
│   ├── FirstFit.c      # First Fit Allocation
│   ├── BestFit.c       # Best Fit Allocation
│   └── WorstFit.c      # Worst Fit Allocation
├── Page_Replacement
│   ├── FIFO.c          # First In First Out
│   ├── LRU.c           # Least Recently Used
│   └── LFU.c           # Least Frequently Used
├── Disk_Scheduling
│   ├── DiskFCFS.c      # FCFS Disk Scheduling
│   ├── DiskSCAN.c      # SCAN Disk Scheduling
│   └── DiskCSCAN.c     # C-SCAN Disk Scheduling
├── Synchronization
│   └── ProducerConsumer.c # Producer Consumer Problem (Semaphores)
└── Deadlock
    └── bankers.c       # Banker's Algorithm
```

## How to Compile and Run

All programs are written in C and can be compiled using `gcc`.

### Example

To run the Priority Scheduling program:

1. Navigate to the directory:
   ```bash
   cd CPU_Scheduling
   ```
2. Compile the program:
   ```bash
   gcc Priority.c -o Priority
   ```
3. Run the executable:
   ```bash
   ./Priority
   ```

## Input Format

Most programs follow a consistent input format:
1. **Number of Processes/Requests**: Enter the total count.
2. **Details**: Enter Arrival Time, Burst Time, Priority, etc., as prompted.
3. **Output**: The program will display the results (Gantt chart, Table, Seek Time, etc.).

## Author

- **RoYaL-_**
