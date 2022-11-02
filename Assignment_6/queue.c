/*
			Queue Implementation
			   (Integer Data)

		   By: Om Patil (200010036)
*/

#include <stdlib.h>
// Depends on ll.c
#include "ll.h"

int is_queue_empty(struct node *head) {
	if (head == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

struct node *enqueue(struct node *head, int data) {
	return insert_beginning(head, data);
}

struct node *dequeue(struct node *head, int *data) {
	*data = value_at_end(head);
	return delete_end(head);
}