#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

FILE* output;

/*********************************************
Implementing queue data structure
*********************************************/
struct Node {
	int data;
	struct Node* next;
} *Head = NULL;

int isQueueEmpty() {
	if(Head == NULL)
		return 1;
	else
		return 0;
}

void Enqueue(int value) {
	struct Node* t = (struct Node*)malloc(sizeof(struct Node));
	if(t == NULL)
		printf("Queue is full!");
	else
	{
		t->data = value;
		t->next = NULL;

		struct Node* p = Head;

		if(!isQueueEmpty())
		{
			while(p->next != NULL)
				p = p->next;
			p->next = t;
		}
		else
		{
			Head = t;
		}
	}
}

void addb(struct Node** Front, int x) {
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    if(t == NULL)
        printf("Queue is Full!");
    else {
        struct Node *p;
        p = *Front;
        t->data = x;
        t->next = NULL;
        if(p != NULL) {
            while(p->next != NULL)
                p = p->next;
            p->next = t;
        } else {
            *Front = t;
        }
    }
}

int Dequeue() {
	int x = -1;

	if(isQueueEmpty())
		printf("Queue is empty!");
	else {
		struct Node* p = Head;
		Head = Head->next;
		x = p->data;
		free(p);
	}
	return x;
}


/*********************************************
Adjecency list creation
*********************************************/
void addEdge(struct Node** adj, int x, int y) {
	addb(&adj[x], y);
	addb(&adj[y], x);
}

/*********************************************
Implementing BFS
*********************************************/
void BFS(struct Node** adj, int n, int start) {
	int* visited = (int*)malloc(n * sizeof(int));
	int* distance = (int*)malloc(n * sizeof(int));
	printf("6\n");
	for(int i=0; i<n; i++) {
		visited[i] = 0;
		distance[i] = -1;
	}
	printf("7\n");
	Enqueue(start);
	visited[start] = 1;
	distance[start] = 0;
	printf("8\n");
	while(!isQueueEmpty()) {
		int u = Dequeue();
		struct Node* p = adj[u];
		//printf("9\n");
		while(p!=NULL) {
			if(visited[p->data] == 0) {
				distance[p->data] = distance[u] + 1;
				Enqueue(p->data);
				visited[p->data] = 1;
			//	printf("10\n");
			}
			p = p->next;
		}
		//printf("***{%d}***\n",u);
	}
//	printf("11\n");
	for(int i=0; i<n; i++) {
		fprintf(output, "%d\n", distance[i]);
		printf("%d    ", distance[i]);
	}
	printf("12\n");
}

/*********************************************
main function
*********************************************/
int main(int argc, char const* argv[]) {
	//checking number of arguments inputted
	if(argc != 2) {
		printf("INVALID! Enter a single input file!");
		exit(0);
	}

	//opening the file
	FILE* input = fopen(argv[1], "r");
	if(input == NULL) {
		printf("FILE DOESN'T EXIST");
		exit(0);
	}
	int vertices, edges;
	fscanf(input, "%d %d\n", &vertices, &edges);

	//array of pointers to form adjacency list
	struct Node* adj_list[vertices];
	for(int i=0;i<vertices;i++){
		adj_list[i]=NULL;
	}
	int x, y;
	while(fscanf(input, "%d %d\n", &x, &y) != EOF) {
		addEdge(adj_list, x, y);
	}

	//creating output file
	output = fopen("sd.txt", "w");
    printf("4\n");
	BFS(adj_list, vertices, 0);
    printf("5\n");
	fclose(input);
	fclose(output);

	input = NULL;
	output = NULL;

	return 0;
}
