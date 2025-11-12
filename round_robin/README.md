# 🧭 Round Robin Process Scheduler (C)

This project implements a simple **Round Robin scheduler** in C using **UNIX signals** and **process control**.  
It spawns multiple child processes (each running a separate `period` program) and schedules them in a circular fashion —  
allowing each process to run for a fixed time slice (3 seconds) before pausing it and switching to the next one.

---

## ⚙️ Features

- Implements **Round Robin scheduling** using:
  - `fork()` to create child processes
  - `execl()` to launch the `period` program
  - `SIGSTOP` and `SIGCONT` for pausing and resuming processes
  - `alarm()` and `pause()` for timing and signal handling
- Uses a **circular linked list** (`RingList`) to store and rotate through process PIDs
- Supports up to **26 processes** (A–Z)
- Simple and modular design — separate logic for process management and list structure

---


---

## 🚀 How It Works

1. The **scheduler** reads an integer `N` from command-line arguments (number of processes to create).
2. It spawns `N` child processes using `fork()` and `execl("./period", "period", letter, NULL)`  
   Each child prints its assigned letter (`A`, `B`, `C`, …).
3. After creating all processes, the scheduler:
   - Pauses all children with `SIGSTOP`
   - Starts the first one with `SIGCONT`
4. Every **3 seconds**, the signal handler:
   - Stops the current process (`SIGSTOP`)
   - Moves to the next process in the ring
   - Resumes it (`SIGCONT`)

This creates a **cyclic time-sharing effect** — like a simple operating system scheduler.

---

## 🧠 Example Output

```bash
$ ./scheduler 3
Number of processes to spawn: 3
Pushing back PID...
(Len: 1) [Head: 1234]
Pushing back PID...
(Len: 2) [Head: 1234] -> [Tail: 1235]
Pushing back PID...
(Len: 3) [Head: 1234] -> 1235 -> [Tail: 1236]

Sig handler triggered.
Sig handler triggered.
...
```

## Building and Running
#Build
```bash
gcc main.c RingList.c -o main
gcc period.c -o period
```
#Run
```bash
./main <num_processes>
```
#Example
```bash
./main 5
```
