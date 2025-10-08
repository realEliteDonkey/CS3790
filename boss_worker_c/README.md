# Parallel Prime Number Generator

This project is a multi-process prime number generator in C. It is composed of two programs:

1. **`boss`**: The main program that spawns multiple worker processes to check for prime numbers in parallel.
2. **`worker`**: Both an independent and helper program executed by `boss` to check a specific range of numbers for primality.

All discovered prime numbers are written to unique text files in the `prime_files/` directory and then aggregated and sorted by `boss`.
Each generted text file has its name equaling the PID of the process.

---

## Features

- Parallel computation of prime numbers using multiple processes.
- Dynamically allocates memory for storing primes.
- Reads primes from multiple files and sorts them with quicksort.
- Removes duplicate primes before storing in the final sorted output file (prime_files/sorted_primes.txt).
- Clean management of temporary files. Upon running program, all files inside prime_files are deleted prior to new files being added.

---

## Compilation

Compile both programs separately:

```bash
gcc -o boss boss.c -lm
gcc -o worker worker.c -lm
```
---
## Usage
```bash
./boss <num_processes> <upper_bound>
```
Ex. Spawn 4 processes. Compute prime numbers up to 50 (inclusive).
```bash
./boss 4 50
```

## Program Description
### Boss Program

#### The boss program is responsible for:
  
  - Validating command-line arguments.
  - Clearing any existing files in prime_files/.
  - Dividing the number range among multiple worker processes.
  - Spawning worker processes using fork() and executing worker via execl().
  - Waiting for all worker processes to finish.
  - Aggregating all primes from temporary files into a dynamically allocated PrimeList.
  - Sorting the primes using qsort().
  - Writing the sorted, unique primes to prime_files/sorted_primes.txt.

### Worker Program

#### The worker program:

  - Receives a number range from boss via command-line arguments.
  - Checks each number in the range for primality using trial division up to the square root of the number.
  - Writes prime numbers to a text file named after its PID (e.g., prime_files/12345.txt).
  - Each worker operates independently, allowing for parallel computation.
