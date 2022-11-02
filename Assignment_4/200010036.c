#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct btree {
	int data;
	struct btree *left;
	struct btree *right;
};

void runFile(char const *inputFile);
struct btree *createNode(int data);
struct btree *insert(struct btree *root, int data);
void inorder(struct btree *root);
void preorder(struct btree *root);
void postorder(struct btree *root);
void search(struct btree *root, int value);
struct btree *find(struct btree *root, int value);
struct btree *parent(struct btree *current, int value);
void minimum(struct btree *root);
void maximum(struct btree *root);
void successor(struct btree *root, int value);
void predecessor(struct btree *root, int value);

FILE *input, *output;

int main(int argc, char const *argv[]) {

	if (argc != 2) {
		printf("Invalid usage of command!\n");
		exit(0);
	}

	runFile(argv[1]);

	return 0;
}

void runFile(char const *inputFile) {
	input = fopen(inputFile, "r");
	if (input == NULL) {
		printf("Could not open the file %s!", inputFile);
		exit(0);
	}

	output = fopen("bst.txt", "w");
	if (output == NULL) {
		printf("Could not write to bst.txt!\n");
		exit(0);
	}

	struct btree *root = NULL;
	char curLine[50];
	// Run while a line is available
	while (fgets(curLine, 50, input)) {
		char com[50];
		int value;
		if (sscanf(curLine, "%s %d", com, &value) == 1) {
			// If only one inputs on the line
			if (strcmp(com,"inorder") == 0) {
				inorder(root);
				if (root != NULL) {
					fseek(output, -1, SEEK_CUR);
				}
				fprintf(output, "\n");
			}
			else if (strcmp(com,"preorder") == 0) {
				preorder(root);
				if (root != NULL) {
					fseek(output, -1, SEEK_CUR);
				}
				fprintf(output, "\n");
			}
			else if (strcmp(com,"postorder") == 0) {
				postorder(root);
				if (root != NULL) {
					fseek(output, -1, SEEK_CUR);
				}
				fprintf(output, "\n");
			}
			else if (strcmp(com,"minimum") == 0) {
				minimum(root);
			}
			else if (strcmp(com,"maximum") == 0) {
				maximum(root);
			}
			else {
				printf("Unrecognised command \"%s\"!\n", com);
			}

		}
		else if (sscanf(curLine, "%s %d", com, &value) == 2) {
			// If two input on the line
			if (strcmp(com,"insert") == 0) {
				root = insert(root, value);
			}
			else if (strcmp(com,"search") == 0) {
				search(root, value);
			}
			else if (strcmp(com,"successor") == 0) {
				successor(root, value);
			}
			else if (strcmp(com,"predecessor") == 0) {
				predecessor(root, value);
			}
			else {
				printf("Unrecognised command \"%s\"!\n", com);
			}
		}	
	}
}

struct btree *createNode(int data) {
	struct btree *newNode = (struct btree *) malloc(sizeof(struct btree));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct btree *insert(struct btree *root, int data) {
	struct btree *newNode = createNode(data);

	if (root == NULL) {	
		fprintf(output, "%d inserted\n", data);
		return newNode;
	}

	if (data < root->data) {
		root->left = insert(root->left, data);
		return root;
	}
	else {
		root->right = insert(root->right, data);
		return root;
	}
}

void inorder(struct btree *root) {
	if (root != NULL) {
		inorder(root->left);
		fprintf(output, "%d ", root->data);
		inorder(root->right);
	}
}

void preorder(struct btree *root) {
	if (root != NULL) {
		fprintf(output, "%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(struct btree *root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		fprintf(output, "%d ", root->data);
	}
}

void search(struct btree *root, int value) {
	if (root == NULL) {
		fprintf(output, "%d not found\n", value);
		return;
	}

	if (root->data == value) {
		fprintf(output, "%d found\n", value);
		return;
	}
	else if (value > root->data) {
		search(root->right, value);
	}
	else if (value < root->data) {
		search(root->left, value);
	}
}

struct btree *find(struct btree *current, int value) {
	while (current != NULL) {
		if (value == current->data) {
			return current;
		}
		else if (value > current->data) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	return current;
}

struct btree *parent(struct btree *current, int value) {
	struct btree *parent = current;
	while (current != NULL) {
		if (value == current->data) {
			return parent;
		}
		else if (value > current->data) {
			parent = current;
			current = current->right;
		}
		else {
			parent = current;
			current = current->left;
		}
	}
	return parent;
}

void minimum(struct btree *root) {
	if (root == NULL) {
		fprintf(output, "\n");
		return;
	}

	if (root->left != NULL) {
		minimum(root->left);
		return;
	}
	fprintf(output, "%d\n", root->data);
}

void maximum(struct btree *root) {
	if (root == NULL) {
		fprintf(output, "\n");
		return;
	}

	if (root->right != NULL) {
		maximum(root->right);
		return;
	}
	fprintf(output, "%d\n", root->data);
}

void successor(struct btree *root, int value) {
	struct btree *current = find(root, value);
	if (current != NULL) {
		if (current->right != NULL) {
			minimum(current->right);
		}
		else {
			struct btree *child = current;
			current = parent(root, current->data);
			while (current->left != child && current != root) {
				child = current;
				current = parent(root, current->data);
			}

			if (current->left == child) {
				fprintf(output, "%d\n", current->data);
			}
			else {
				fprintf(output, "successor of %d does not exist\n", value);
			}
		}
	}
	else {
		fprintf(output, "%d does not exist\n", value);
	}
}

void predecessor(struct btree *root, int value) {
	struct btree *current = find(root, value);
	if (current != NULL) {
		if (current->left != NULL) {
			maximum(current->left);
		}
		else {
			struct btree *child = current;
			current = parent(root, current->data);
			while (current->right != child && current != root) {
				child = current;
				current = parent(root, current->data);
			}

			if (current->right == child) {
				fprintf(output, "%d\n", current->data);
			}
			else {
				fprintf(output, "predecessor of %d does not exist\n", value);
			}
		}
	}
	else {
		fprintf(output, "%d does not exist\n", value);
	}
}