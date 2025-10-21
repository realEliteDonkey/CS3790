#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define TRUE 1
#define FALSE 0

#define FILE_PATH_SIZE 512
#define PID_DIGITS 10

/**
 * @brief Worker program called by execl from boss.exe.
 * Receives a range of numbers to process for primality.
 * Will print numbers within lower and upper bounds that
 * is prime.
 * 
 * Algorithm functions by testing target, represented as
 * target >= lower_bound && target <= upper_bound.
 * 
 * Checks if target is divisble by any number >= 2 &&
 * any number <= the square root ceiling of the target.
 * 
 * If the target is divisble by anything within these
 * parameters, the is_prime is assigned false, and the
 * for loop breaks.
 * 
 * Text file is opened and named after PID.
 * 
 * After the foor loop, if is_prime is true AND the 
 * target is within the restrictions (>= 1, >= lower_bound)
 * then the number is printed to the text file to show
 * that it is a prime number.
 * 
 * @param argc Must equal 3
 * @param argv Must be in order of:
 * argv[] = [ [#processes], [upper_bound] ]
 * 
 * #processes  = Custom number of processes to spawn
 * upper_bound = largest number to check for primality
 * @return int 
 * 0  : Success
 * -1 : Failure
 */
int main(int argc, char* argv[]) {

    printf("Enter worker.\n");
    char file_name[FILE_PATH_SIZE] = "prime_files/";
    char pid_str[PID_DIGITS];

    mkdir("prime_files", 0700);

    /*
        Convert int: PID to string, and store in pid_str.
        Concatenate the PID to the directory name (file_name).
        Then we append.txt to the end to create the text file.
    */
    sprintf(pid_str, "%d", (int)getpid());
    strcat(file_name, pid_str);
    strcat(file_name, ".txt");

    FILE* file = fopen(file_name, "w");
    if (!file) {
        perror("fopen");
        exit(1);
    }  

    // receives [range] [upper_bnd]
    int range       = atoi(argv[1]);
    int upper_bound = atoi(argv[2]);

    fflush(stdout);

    /*
        Algorithm for finding primes:
        1. Given an upperbound and a range, we can compute the lower bound
           as upper_bound - range.
        2. Target is computed as upper_bound - range.
        3. We square root the target and name it target_bound. This bound is
           used to be multiplies by 2 and up to the target bound itself.
           IF the result of a multiplication equals the target, is_prime is set to
           false, the loop breaks, and the system is not added to the list of primes.
           IF the loop of multiplications finishes the loop without triggering the 
           is_prime = FALSE, then the number is added to primes list.
    */
    for (int target = upper_bound - range; target <= upper_bound; target++) {
        int is_prime = TRUE;
        int target_bound = (int)sqrt(target);

        // Testing for primality
        for (int test = 2; test <= target_bound; test++) {
            if ((target % test) == 0) {
                is_prime = FALSE;
                break;
            }
        }

        // Add primes to the unique PID file located in prime_files/
        if (is_prime && (target > 1)) {
            char target_str[64];
            if (target >= upper_bound - range) {
                fprintf(file, "%d\n", target);
                printf("%d <-\n", target);
                fflush(stdout);
            }
        }
    }

    fclose(file);

    return 0;
}

