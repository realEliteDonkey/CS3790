#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <err.h>
#include <fcntl.h> // O_RDONLY, O_WRONLY
/**
 * 	gcc -c -lcrypt server.c
 * 	gcc -lcrypt server.c -o server
 */

/**
 *	Server should access a file that contains 
 *	valid usernames and passwords in /users/information.txt
 *	take username and decrypt hashed password with input password.
 *	IF accepted, 
*/

static int auth_pass(const char* user_enter_pass, const char* stored_hash);
static int digits(int num);
static int cycle = 0;
static int found = 0;
static int validated = 0;

static int auth_pass(const char* user_enter_pass, const char* stored_hash) {
    if (!user_enter_pass || !stored_hash) return 0;
    char* result = crypt(user_enter_pass, stored_hash);
    if (!result) return 0;
    return strcmp(result, stored_hash) == 0 ? 1 : 0;
}

static int digits(int num) {
    int n = 0;
    while (num != 0) {
        num /= 10;
        n++;
    }
    return n;
}


int main() {
	
    printf("Server running...\n");

    char buffer[1024] = "Connected to server -> PID: ";
    char* valid_message = "+ACCOUNT VALID";
    char* nonvalid_message = "-INVALID ACCOUNT\n+GOODBYE";
    char* salt = "#$EL1t3$)(d0n[K3Y$]#";
	char* pipe_sc    = "pipe/SERVER_TO_CLIENT";
	char* pipe_cs    = "pipe/CLIENT_TO_SERVER";
    char* auth_instr = "Enter: [username] [password]";



    // create named pipe
    mkdir("pipe", 0700);
    mkfifo(pipe_sc, 0600);
    mkfifo(pipe_cs, 0600);
    
    // eliminates blocking
	int fd_read  = open(pipe_cs, O_RDONLY);
	int fd_write = open(pipe_sc, O_WRONLY);

    // write first (Connected to server, PID: getpid())
    sprintf(buffer, "%d\n%s", getpid(), auth_instr);
    buffer[digits(getpid()) + strlen(auth_instr) + 1] = '\0';
    write(fd_write, buffer, strlen(buffer));
    memset(buffer, '\0', sizeof(buffer));

    FILE* users_file = fopen("user_files.txt", "r");
    if (!users_file) {
        perror("Couldnt open file");
        return -1;
    }

    while(1) {

        // -------------------------------------------------------------------------
        // START USER AUTH
        

        int n = read(fd_read, buffer, sizeof(buffer));
        if (n > 0 && cycle == 0) {
            // seperate username and password into separate args
            char arg_username[256];
            char arg_password[256];
            sscanf(buffer, "%255s %255s", arg_username, arg_password);
            memset(buffer, '\0', sizeof(buffer));
            while (fgets(buffer, sizeof(buffer), users_file) != NULL) {
                char line_usr[256];
                char line_pass[256];
                sscanf(buffer, "%255s %255s", line_usr, line_pass);
                if (strcmp(line_usr, arg_username) == 0) {
                    /*
                        Use auth_pass to compare user entered plain-text password
                        with hashed password stored inside user_files.txt
                    */
                    if (auth_pass(arg_password, line_pass)) {
                        memset(buffer, '\0', sizeof(buffer));
                        snprintf(buffer, sizeof(buffer), "%s", valid_message);
                        write(fd_write, buffer, strlen(buffer));
                        memset(buffer, '\0', sizeof(buffer));
                        validated = 1;
                    } else {
                        memset(buffer, '\0', sizeof(buffer));
                        snprintf(buffer, sizeof(buffer), "%s", nonvalid_message);
                        write(fd_write, buffer, strlen(buffer));
                        memset(buffer, '\0', sizeof(buffer));
                    }
                    break;
                } else {
                    memset(buffer, '\0', sizeof(buffer));
                    snprintf(buffer, sizeof(buffer), "%s", nonvalid_message);
                    write(fd_write, buffer, strlen(buffer));
                    memset(buffer, '\0', sizeof(buffer));
                }
            }
            fclose(users_file);
            cycle = 1;
            continue;
        }


        // END USER AUTH
        // -----------------------------------------------------------------------

        if (n > 0 && cycle > 0) {

            // argv[0]: path
            // argv[1]: prog_name
            // argv[2]: range
            // argv[3]: upper_bound
            
            // fork here and do exec for worker located
            // in /home/elitedonkey/CS3790/boss_worker_c/worker
            // /home/elitedonkey/CS3790/boss_worker_c/worker ./worker 50 20
            
            int status;
            pid_t pid = fork();
            
            if (pid == 0) {
                char argv[4][128];
                // keep as 31 to allow for null terminator
                sscanf(buffer, "%127s %127s %127s %127s",
                        argv[0], argv[1], argv[2], argv[3]);
                
                execl(argv[0], argv[1], argv[2], argv[3], (char *)NULL);

                memset(buffer, '\0', sizeof(buffer)); 
                snprintf(buffer, sizeof(buffer), "-EXEC FAILED");
                write(fd_write, buffer, strlen(buffer) + 1);
            }
            else {
                // wait for child process to complete
                wait(NULL);
                
                // return pid to client
                memset(buffer, '\0', sizeof(buffer));
                snprintf(buffer, sizeof(buffer), "+EXEC SUCCESS");
                write(fd_write, buffer, strlen(buffer) + 1);

            }
        }
    }

    close(fd_read);
    close(fd_write);
    unlink(pipe_sc);
    unlink(pipe_cs);

    return 0;
}





