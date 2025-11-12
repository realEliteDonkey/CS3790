#ifndef RINGLIST_H
#define RINGLIST_H

#include <sys/types.h> // for pid_t

typedef struct Node {
    pid_t data;
    unsigned int index;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    unsigned int len;
} RingList;

void init_list(RingList* list);
int push_back(RingList* list, pid_t data);
void print_list(RingList* list, const char* sep);
int ring_dealloc(RingList* list);

#endif