/*
			Linked List Implementation
				  (String Data)

			 By: Om Patil (200010036)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const int MAX_WORD_LEN;

struct node {
	char *data;
	struct node *next;
};

struct node *create_node(void) {
	struct node *newnode = (struct node*) malloc(sizeof(struct node));
	newnode->data = (char *) malloc(sizeof(char)*MAX_WORD_LEN);
	strcpy(newnode->data, "");
	newnode->next=NULL;
	return newnode;
}

void display(struct node *head) {
	if (head == NULL) {
		printf("List is empty!\n");
	}
	else {
		struct node *currentnode;
		currentnode = head;
		do {
		 	printf("%s ", currentnode->data);
			currentnode = currentnode->next;
		} while (currentnode != head);
		printf("\n");
	}
}

int length_of(struct node *head) {
	if (head == NULL) {
		return 0;
	}
	else {
		int i = 1;
		struct node *currentnode = head;
		while (currentnode->next != head) {
			currentnode = currentnode->next;
			i++;
		}
		return i;
	}
}

char *value_at(struct node *head, int pos) {
	if (head == NULL) {
		char *empty = (char *) malloc(sizeof(char)*MAX_WORD_LEN);
		strcpy(empty, "");
		return empty;
	}
	else {
		struct node *currentnode = head;
		for (int i = 0; i < pos; ++i) {
			if (currentnode->next == head) {
				char *empty = (char *) malloc(sizeof(char)*MAX_WORD_LEN);
				strcpy(empty, "");
				return empty;
			}
			else {
				currentnode = currentnode->next;
			}
		}
		return currentnode->data;
	}
}

struct node *add_to_empty_list(struct node *head, char *data) {
	struct node *newnode;
	newnode = create_node();
	strcpy(newnode->data, data);
	head = newnode;
	newnode->next = head;
	return head;
}

struct node *insert_beginning(struct node *head, char *data) {
	if (head == NULL) {
		head = add_to_empty_list(head, data);
	}
	else {
		struct node *last = head;
		while (last->next != head) {
			last = last->next;
		}
		struct node *newnode = create_node();
		strcpy(newnode->data, data);
		newnode->next = head;
		head = newnode;
		last->next = newnode;
	}
	return head;
}

struct node *insert_end(struct node *head, char *data) {
	if (head == NULL) {
		head = add_to_empty_list(head, data);
	}
	else {
		struct node *last;
		last = head;
		while (last->next != head) {
			last = last->next;
		}
		struct node *newnode;
		newnode = create_node();
		strcpy(newnode->data, data);
		newnode->next = head;
		last->next = newnode;
	}
	return head;
}

struct node *insert_at(struct node *head, int pos, char *data) {
	if (head == NULL) {
		if (pos == 0) {
			head = add_to_empty_list(head, data);
		}
		else {
			printf("Invalid position!\n\n");
		}
	}
	else {
		if (pos == 0) {
			head = insert_beginning(head, data);
		}
		else if (pos > 0) {
			struct node *prevnode;
			prevnode = head;
			for (int i = 0; i < pos-1; ++i) {
				prevnode = prevnode->next;
				if (prevnode == head) {
					printf("Invalid position!\n\n");
					return head;
				}
			}
			struct node *newnode = create_node();
			strcpy(newnode->data, data);
			newnode->next = prevnode->next;
			prevnode->next = newnode;
		}
		else {
			printf("Invalid position!\n\n");
		}
	}
	return head;
}

struct node *delete_beginning(struct node *head) {
	if (head == NULL) {
		printf("Cannot delete, list is empty!\n\n");
	}
	else {
		struct node *delete;
		delete = head;
		if (delete->next == head) {
			head = NULL;
		}
		else {
			struct node *last;
			last = head;
			while (last->next != head) {
				last = last->next;
			}
			head = delete->next;
			last->next = delete->next;
		}
		free(delete);
	}
	return head;
}

struct node *delete_end(struct node *head) {
	if (head == NULL) {
		printf("Cannot delete, list is empty!\n\n");
	}
	else {
		struct node *delete;
		delete = head;
		if (delete->next == head) {
			head = NULL;
		}
		else {
			struct node *prev;
			while (delete->next != head) {
				prev = delete;
				delete = delete->next;
			}
			prev->next = head;
		}
		free(delete);
	}
	return head;
}

struct node *delete_from(struct node *head, int pos) {
	if (head == NULL) {
		printf("Cannot delete, list is empty!\n\n");
	}
	else {
		struct node *delete;
		delete = head;
		if (delete->next == head) {
			if (pos == 0) {
				head = NULL;
				free(delete);
			}
			else {
				printf("Invalid position!\n\n");
			}
		}
		else {
			if (pos < 0) {
				printf("Invalid position!\n\n");
			}
			else if (pos == 0) {
				head = delete_beginning(head);
			}
			else {
				struct node *prev;
				for (int i = 0; i < pos; ++i) {
					prev = delete;
					delete = delete->next;
					if (delete == head) {
						printf("Invalid position!\n\n");
						return head;
					}
				}
				prev->next = delete->next;
				free(delete);
			}
		}
	}
	return head;
}
