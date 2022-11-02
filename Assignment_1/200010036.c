/*
	 Data Structures and Algorithms Lab
			   Assignment 1

		 By: Om Patil (200010036)


References:
Tower of Hanoi - Wikipedia [https://en.wikipedia.org/wiki/Tower_of_Hanoi#Recursive_solution]
Stack Data Structure (Introduction and Program) - GeeksforGeeks [https://www.geeksforgeeks.org/stack-data-structure-introduction-program/]
*/

#include <stdio.h>
#include <stdlib.h>

FILE* output;

struct Stack {
	char name;
	int size;
	int* array;
	int top;
};

struct Stack* makeStack(int size, char name) {
	// Make stack
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	// Set name
	stack->name = name;
	// Set size
	stack->size = size;
	// Make array inside stack
	stack->array = (int*)malloc(size*sizeof(int));
	// Initialize top
	stack->top = -1;
	// Return pointer to made stack
	return stack;
}

int isStackFull(struct Stack* stack) {
	// If top of stack is equal to size of stack then it is full
	if (stack->top == stack->size-1) {
		return 1;
	}
	else {
		return 0;
	}
}

int isStackEmpty(struct Stack* stack) {
	// If top of stack is -1 then it is empty
	if (stack->top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

void push(int e, struct Stack* stack) {
	// Make sure stack isn't full
	if (!isStackFull(stack)) {
		// Incriment top and push new element
		stack->top++;
		stack->array[stack->top]=e;
		fprintf(output, "Push disk %d to Stack %c\n", e, stack->name);
	}
	else {
		printf("Cannot push, stack is full!\n");
		exit(1);
	}
}

int pop(struct Stack* stack) {
	// Make sure stack ins't empty
	if (!isStackEmpty(stack)) {
		// pop value and decriment top
		int value = stack->array[stack->top];
		stack->top--;
		fprintf(output, "Pop disk %d from Stack %c\n", value, stack->name);
		return value;
	}
	else {
		printf("Cannot pop, stack is empty!\n");
		exit(1);
	}
}

void initialize(int num, struct Stack* stack) {
	// Place the initial discs in the first stack
	for (int i = 0; i < num; ++i) {
		push(num-i,stack);
	}
}

// Move top n discs from start stack to end stack using middle stack
void toh(int n, struct Stack* start, struct Stack* middle, struct Stack* end) {
	// If only one element left
	if (n == 1) {
		// Pop this element from start
		int element = pop(start);
		// Push it to the end
		push(element, end);
		// Done
		return;
	}
	// If more than one elements
	// Move first n-1 elements from start to end using toh() function
	toh(n-1, start, end, middle);
	// Pop last remaining element in start
	int element = pop(start);
	// Push it to end
	push(element, end);
	// Use toh() function to move n-1 elements from middle to end
	toh(n-1, middle, start, end);
}

int main(int argc, char const *argv[]) {
	// Check usage
	if (argc != 2) {
		printf("Incorrect usage!\n");
		return 1;
	}
	// Load parameter
	int stackSize = atoi(argv[1]);

	// Initialize stacks
	struct Stack* A = makeStack(stackSize, 'A');
	struct Stack* B = makeStack(stackSize, 'B');
	struct Stack* C = makeStack(stackSize, 'C');

	// Open file
	output = fopen("toh.txt", "w");
	if (output == NULL) {
		printf("Could not open output file!\n");
		return 1;
	}

	// Initialize problem
	initialize(stackSize, A);

	// Move all discs from A to C using B
	toh(stackSize, A, B, C);

	// Close file
	fclose(output);

	// Successfully exit
	return 0;
}