/*
			Data Structures and Algorithms Lab
					  Assignment 7

				By: Om Patil (200010036)
*/

#include <stdio.h>
#include <stdlib.h>
// Depends on ll.c
#include "ll.h"

// Structure definitions
struct nodeInfo {
	int isNotVisited;
};


// Variable declarations
FILE *input, *output;
int numVertex, numEdge, curNode;
struct node **adjList, *TS = NULL;
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
	}

	// Read edges and add to adjacency list
	int a, b;
	for (int i = 0; i < numEdge; ++i) {
	 	fscanf(input, "%d %d\n", &a, &b);
		adjList[a] = insert_end(adjList[a], b);
	}

	// Close the input file
	fclose(input);

	// Run DFS for all nodes 
    for (int i = 0; i < numVertex; i++) {
        if (NodeInfo[i].isNotVisited) {
			NodeInfo[i].isNotVisited = 0;
            explore_node(i);
        }
    }

	// Open the output file
	output = fopen("ts.txt", "w");
	if (output == NULL) {
		printf("Could not open file 'sd.txt'!\n");
		exit(0);
	}

	// Print the TS to the output file
	for (int i = 0; i < numVertex; i++) {
		fprintf(output, "%d\n", value_at(TS, i));
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
			// If not visited mark as visited and explore
			NodeInfo[newNode].isNotVisited = 0;
            explore_node(newNode);
		}
	}
	TS = insert_beginning(TS, curNode);
}