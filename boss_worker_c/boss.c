#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

/**
 * @brief Structure to hold dynamic array along with a 
 * counter of prime numbers added to array
 * 
 * @param max_primes 
 * @return PrimeList* 
 */
typedef struct PrimeList {
    unsigned num_primes;
    int primes[];
} PrimeList;

int sort_lt(const void* p1, const void* p2);
PrimeList* new_prime_list(size_t max_primes);
int arg_cnt_check(int argc, char* argv[]);
int clear_txt(const char* dir_name);
int get_primes(PrimeList* pl, const char* dir_name);


/**
 * @brief Allocates and initializes a new PrimeList structure to hold up to max_primes integers.
 *
 * This function dynamically allocates memory for a PrimeList structure, including space for
 * an array of integers to store prime numbers. The number of primes currently stored is
 * initialized to zero.
 *
 * @param max_primes The maximum number of prime numbers the list can hold.
 * @return Pointer to the newly allocated PrimeList structure, or NULL if allocation fails.
 */
PrimeList* new_prime_list(size_t max_primes) {
    PrimeList* pl = malloc(sizeof(PrimeList) + (max_primes * sizeof(int)));
    if (!pl) return NULL;
    pl->num_primes = 0;

    return pl;
}

/**
 * @brief Custom omparator function passed to stdlib.h qsort()
 * 
 * @param p1 
 * @param p2 
 * @return int 
 */
int sort_lt(const void* p1, const void* p2) {
    if (p1 == NULL || p2 == NULL) return 0;
    if (*(int*)p1 < *(int*)p2) return -1;
    if (*(int*)p1 > *(int*)p2) return 1;
}

/**
 * @brief Reads prime numbers from files in the specified directory and stores them in a PrimeList.
 *
 * This function opens the given directory, iterates through all files excluding "." and "..",
 * and reads each line from the files in the "prime_files/" subdirectory. Each line is expected
 * to contain a prime number, which is converted to an integer and added to the PrimeList.
 *
 * @param pl Pointer to a PrimeList structure where the primes will be stored.
 * @param dir_name Name of the directory containing the prime files.
 * @return 0 on success, -1 on failure (if the directory or a file cannot be opened).
 */
int get_primes(PrimeList* pl, const char* dir_name) {
    system("cd prime_files/");

    DIR* dir;
    struct dirent* dp;

    if ((dir = opendir(dir_name)) == NULL) {
        printf("Could not open file %s.\n", dir_name);
        return -1;
    }

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        char path[256] = "prime_files/";
        strcat(path, dp->d_name);
        FILE* file = fopen(path, "r");
        if (file == NULL) {printf("Error opening file: %s\n", path); return -1;}
        
        char* line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, file)) != -1) {
            pl->primes[pl->num_primes++] = atoi(line);
        }

        free(line);
        fclose(file);
    }

    return 0;
}


/**
 * @brief Step through every file inside a specified directory
 * and delete all files inside directory.
 * 
 * @param dir: Directory to remove files from.
 * 
 * @return int 
 * 0  : Success
 * -1 : Failure
 */
int clear_txt(const char* dir_name) {
    system("cd prime_files/");

    DIR* dir;
    struct dirent* dp;

    if ((dir = opendir(dir_name)) == NULL) {
        printf("Could not open file %s.\n", dir_name);
        return -1;
    }
    
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        char path[256] = "prime_files/";
        strcat(path, dp->d_name);
        int result = remove(path);
        if (result != 0) {
            printf("Error removing file: %s\n", dp->d_name);
        } else {
            printf("Removed file: %s\n", dp->d_name);
        }
    }

    return 0;
}


/**
 * @brief Validates the CL-arguments according to program needs.
 * 
 * @param argc Must equal 3
 * @param argv Must be in order of:
 * [prog_name] [#processes] [upper_bound]
 * 
 * prog_name   = ./boss
 * #processes  = Custom number of processes to spawn
 * upper_bound = largest number to check for primality 
 * @return int 
 * 0  : Success
 * -1 : Fail
 */
int arg_cnt_check(int argc, char* argv[]) {
    if (argc != 3) {
        printf(
            "Must supply 3 args:\n"
            "    argv[1]: # of processes to spawn\n"
            "    argv[2]: upper bound (inclusive)\n"
        );
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        printf("# of processes can't be negative.\n");
        return -1;
    }

    // set lower bound min >= 0
    // set upper bound limit > lower bound
    if (atoi(argv[2]) <= 0) {
        printf("Upper bound must be > 0.\n");
        return -1;
    }

    if (atoi(argv[1]) > atoi(argv[2])) {
        printf("Why would you want more processes than numbers to compute?\n");
        printf("Processes must not exceed upper bound.\n");
        return -1;
    }

    return 0;
}




/**
 * @brief spawns processes specified by user with fork()
 * and feeds command line arguments to new program "./worker"
 * which takes in lower bound, upper bound, range, and 
 * checks for primality. If any given number within range 
 * fed to program is prime, "./worker" will print the prime
 * number to the console.
 * 
 * @param argc Must equal 3
 * @param argv Must be in order of:
 * [prog_name] [#processes] [upper_bound]
 * 
 * prog_name   = ./boss
 * #processes  = Custom number of processes to spawn
 * upper_bound = largest number to check for primality 
 * @return int 
 * 0  : Success
 * -1 : Fail
 */
int main(int argc, char* argv[]) {

    if (arg_cnt_check(argc, argv) != 0) {
        printf("Exiting program...\n");
        exit(-1);
    }

    if (clear_txt("prime_files/") != 0) {
        printf("Failed to clear files in prime_files/\n");
        return -1;
    }

    int num_workers = atoi(argv[1]);
    int upper_bound = atoi(argv[2]);
    for (int i = 0; i < num_workers; i++) {
        // set ranges for each i worker
        // spawn worker
        // exec worker program containing problem logic
        int range_size = upper_bound / num_workers;
        int remaining  = upper_bound % num_workers;

        int low  = i * range_size;
        int high = low + range_size;

        printf("PID: %d | RANGE: %d | HIGH: %d\n", (int)getpid(), range_size, high);

        pid_t pid = fork();
        if (pid == -1) return -1;

        char upp_buff[128];
        char range[128];
        sprintf(upp_buff, "%d", high);
        if (i == 0)
            sprintf(range, "%d", (range_size + remaining));
        else
            sprintf(range, "%d", range_size);

        // child process
        if (pid == 0) {
            if (execl("./worker", range, upp_buff, (char*)NULL) == -1) {
                printf("Failed to execute execl().\n");
                return -1;
            }
            exit(0);
        }

    }

    int status;
    for (int i = 0; i < num_workers; i++)
        wait(&status);


    // Only original parent process remains
    // Add all numbers from all files into buffer of size upper_bound
    // quick sort buffer
    // add sorted buffer into sorted.txt
    /* sorted.txt example:
        
        This file contains a sorted list of prime numbers from 2 -> (upper_bound):
        ...
        ...
        ...
    */


    PrimeList* pl = new_prime_list(upper_bound);
    if (get_primes(pl, "prime_files/") != 0) {
        printf("Failed to add primes to prime.txt.\n");
        return -1;
    }


    // Quick sort primes
    //void qsort (void* base, size_t num, size_t size,            int (*compar)(const void*,const void*));
    qsort(pl->primes, (size_t)pl->num_primes, sizeof(int), sort_lt);

    // Add quick sorted primes[] to primes.txt
    FILE* file = fopen("prime_files/sorted_primes.txt", "w");
    if (file == NULL) { printf("Error creating file.\n"); return -1; }


    for (int i = 0; i < pl->num_primes; i++) {
        char num_str[64];
        if (i > 0) {
            if (pl->primes[i] == pl->primes[i-1])
            continue;
        }
        sprintf(num_str, "%d\n", pl->primes[i]);
        fputs(num_str, file);
    }
    fclose(file);


    return 0;
}
