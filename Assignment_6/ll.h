struct node;

struct node *delete_from(struct node *head,int pos);
struct node *delete_end(struct node *head);
struct node *delete_beginning(struct node *head);
struct node *insert_at(struct node *head,int pos,int data);
struct node *insert_end(struct node *head,int data);
struct node *insert_beginning(struct node *head,int data);
int value_at_end(struct node *head);
int value_at(struct node *head, int pos);
int length_of(struct node *head);