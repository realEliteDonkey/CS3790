#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include "RingList.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

Node* current_process = NULL;
const char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
unsigned int alpha_index = 0;

void next(int sigcode);



void next(int sigcode) {
    // stop current process
    kill(current_process->data, SIGSTOP);

    // iterate to next process in list -> make current
    current_process = current_process->next;

    // continue current process
    kill(current_process->data, SIGCONT);

    alarm(3);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Must have 2 args total.\n");
        return -1;
    }

    unsigned int num_processes = atoi(argv[1]);
    unsigned int alpha_size = strlen(alpha);
    //printf("Number of processes to spawn: %u\nSize of printable chars: %u\n", num_processes, alpha_size);
    if (num_processes > alpha_size) {
        perror("# of processes input must be less than 26.\n");
        return -1;
    }

    struct sigaction sa;
    sa.sa_handler = next;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    RingList list;
    init_list(&list);

    for (unsigned int i = 0; i < num_processes; i++) {
        pid_t pid = fork();
        // error check
        if (pid == -1) {
            perror("Failed to create new process.\n");
            return -1;
        }
        // child process
        // call execl on period.c
        if (pid == 0) {
            char letter[2] = { alpha[i], '\0' };
            execl("./period", "period", letter, (char*)NULL);
            perror("execl failed.\n");
            return -1;
        }
        // parent process
        // add childs pid to RingList containing all pids
        else if (pid > 0) {
            printf("Pushing back PID: %d\n", pid);
            push_back(&list, pid);
            print_list(&list, " -> ");
        }
    }

    current_process = list.head;

    // stop all processes starting from head, ending at tail
    Node* current_it = list.head;
    do {
        kill(current_it->data, SIGSTOP);
        current_it = current_it->next;
    } while (current_it != list.head);

    // restart head process
    kill(current_process->data, SIGCONT);

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction failed");
        return -1;
    }

    alarm(3);
    while (1) { 
        pause(); 
    }

    ring_dealloc(&list);
    return 0;
}