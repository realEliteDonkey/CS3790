#include "RingList.h"
#include <stdlib.h>
#include <stdio.h>

void init_list(RingList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

int push_back(RingList* list, pid_t data) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) return -1;

    new_node->data = data;
    new_node->index = list->len;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        new_node->next = new_node; // circular
    } else {
        new_node->next = list->head;
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->len++;
    return 0;
}

void print_list(RingList* list, const char* sep) {
    if (!list || !list->head) {
        printf("(empty list)\n");
        return;
    }

    Node* current = list->head;
    printf("List length: %u\n", list->len);
    do {
        if (current == list->head)
            printf("[H:%d]", current->data);
        else if (current == list->tail)
            printf("%s[T:%d]", sep, current->data);
        else
            printf("%s%d", sep, current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

int ring_dealloc(RingList* list) {
    if (list->head == NULL) return 0;

    Node* current = list->head;
    Node* next;
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != list->head);

    list->head = list->tail = NULL;
    list->len = 0;
    return 0;
}