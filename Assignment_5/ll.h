/*
			Linked List Implementation
				  (String Data)

			 By: Om Patil (200010036)
*/

struct node;

struct node *delete_from(struct node *head,int pos);
struct node *delete_end(struct node *head);
struct node *delete_beginning(struct node *head);
struct node *insert_at(struct node *head,int pos,char *data);
struct node *insert_end(struct node *head,char *data);
struct node *insert_beginning(struct node *head,char *data);
void display(struct node *head);
int length_of(struct node *head);
char *value_at(struct node *head, int pos);