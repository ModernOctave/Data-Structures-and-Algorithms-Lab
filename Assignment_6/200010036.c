/*
			Data Structures and Algorithms Lab
					  Assignment 6

				By: Om Patil (200010036)
*/

#include <stdio.h>
#include <stdlib.h>
// Depends on ll.c and queue.c
#include "ll.h"
#include "queue.h"

// Structure definitions
struct nodeInfo {
	int isNotVisited;
	int distance;
};

// Variable declarations
FILE *input, *output;
int numVertex, numEdge, curNode;
struct node *queue, **adjList;
struct nodeInfo *NodeInfo;


// Function declarations
void explore_node(int curNode);


// Main loop
int main(int argc, char const *argv[]) {
	// Check usage
	if (argc != 2) {
		printf("Invalid usage of command!\n");
		exit(0);
	}

	// Open the input file
	input = fopen(argv[1], "r");
	if (input == NULL) {
		printf("Could not open file '%s'!\n", argv[1]);
		exit(0);
	}

	// Read first line
	fscanf(input, "%d %d\n", &numVertex, &numEdge);

	// Prepare adjacency list and nodeInfo array
	adjList = (struct node **) malloc(sizeof(struct node *)*numVertex);
	NodeInfo = (struct nodeInfo *) malloc(sizeof(struct nodeInfo)*numVertex);
	for (int i = 0; i < numVertex; ++i) {
		NodeInfo[i].isNotVisited=1;
		NodeInfo[i].distance=-1;
	}

	// Read edges and add to adjacency list
	int a, b;
	for (int i = 0; i < numEdge; ++i) {
	 	fscanf(input, "%d %d\n", &a, &b);
		adjList[a] = insert_beginning(adjList[a], b);
		adjList[b] = insert_beginning(adjList[b], a);
	}

	// Close the input file
	fclose(input);

	// Manually enqueue zeroth node
	queue = enqueue(queue, 0);
	NodeInfo[0].distance = 0;
	NodeInfo[0].isNotVisited = 0;

	// While queue is not empty keep exploring nodes
	while (!is_queue_empty(queue)) {
		queue = dequeue(queue, &curNode);
		explore_node(curNode);
	}

	// Open the output file
	output = fopen("sd.txt", "w");
	if (output == NULL) {
		printf("Could not open file 'sd.txt'!\n");
		exit(0);
	}

	// Print distances to output file
	for (int i = 0; i < numVertex; ++i) {
		fprintf(output, "%d\n", NodeInfo[i].distance);
	}

	// Close the output file
	fclose(output);

	// Free allocated space
	free(adjList);
	free(NodeInfo);

	return 0;
}


// Function definitions
void explore_node(int curNode) {
	// Check for unvisited adjacent node
	for (int i = 0; i < length_of(adjList[curNode]); ++i) {
		int newNode = value_at(adjList[curNode],i);
		if (NodeInfo[newNode].isNotVisited) {
			// If not visited enqueue and mark as visited
			queue = enqueue(queue, newNode);
			NodeInfo[newNode].distance = NodeInfo[curNode].distance + 1;
			NodeInfo[newNode].isNotVisited = 0;
		}
	}
}