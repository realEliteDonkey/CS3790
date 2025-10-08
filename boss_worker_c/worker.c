#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0


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

    char file_name[128] = "prime_files/";
    char pid_str[10];
    sprintf(pid_str, "%d", (int)getpid());
    strcat(file_name, pid_str);
    strcat(file_name, ".txt");

    FILE* file = fopen(file_name, "w");

    // receives [worker] [range] [lower_bnd] [upper_bnd]
    int range       = atoi(argv[0]);
    int upper_bound = atoi(argv[1]);

    for (int target = upper_bound - range; target <= upper_bound; target++) {
        int is_prime = TRUE;
        int target_bound = (int)sqrt(target);
        for (int test = 2; test <= target_bound; test++) {
            if ((target % test) == 0) {
                is_prime = FALSE;
                break;
            }
        }
        if (is_prime && (target > 1)) {
            char target_str[64];
            if (target >= upper_bound - range) {
                sprintf(target_str, "%d\n", target);
                fputs(target_str, file);
            }
        }
    }

    return 0;
}

