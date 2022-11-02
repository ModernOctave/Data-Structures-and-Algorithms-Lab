/*
			Data Structures and Algorithms Lab
					  Assignment 5

				By: Om Patil (200010036)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

FILE *words, *query, *output;
const int MAX_WORD_LEN = 30;

struct hashTable {
	int numSlots;
	struct node **slots;
} HashTable;

void make_hash_table(int numSlots);
int hash_value(char *word);
void hash_add(char *word);
void sort_char(char *sorted, char *word);
void print_anagrams(char *word, struct node *list);

int main(int argc, char const *argv[]) {
	// Check usage
	if (argc != 4) {
		printf("Invalid usage of command!\n");
		exit(0);
	}

	// Open the words file
	words = fopen(argv[1], "r");
	if (words == NULL) {
		printf("Could not open file '%s'!\n", argv[1]);
		exit(0);
	}

	// Make hash table
	make_hash_table(atoi(argv[2]));

	// Read words one by one and add to hash table
	char word[MAX_WORD_LEN];
	while (fgets(word, MAX_WORD_LEN, words)) {
		word[strlen(word)-1] = '\0';
		hash_add(word);
	}

	fclose(words);

	// Open the query file
	query = fopen(argv[3], "r");
	if (query == NULL) {
		printf("Could not open file '%s'!\n", argv[3]);
		exit(0);
	}

	// Open the output file
	output = fopen("anagrams.txt", "w");
	if (query == NULL) {
		printf("Could not open file 'anagrams.txt'!\n");
		exit(0);
	}

	// Find anagrams for each word in the query file
	int first = 1;
	while (fgets(word, MAX_WORD_LEN, words)) {
		if (first) {
			first = 0;
		}
		else {
			fprintf(output, "\n");
		}
		word[strlen(word)-1] = '\0';
		print_anagrams(word, HashTable.slots[hash_value(word)]);
	}

	fclose(query);
	fclose(output);

	return 0;
}

void make_hash_table(int numSlots) {
	HashTable.slots = (struct node **) malloc(sizeof(struct node *)*numSlots);
	HashTable.numSlots = numSlots;
}

int hash_value(char *word) {
	int hash = 0;
	for (int i = 0; i < strlen(word); ++i) {
		hash += word[i];
	}
	return hash % HashTable.numSlots;
}

void hash_add(char *word) {
	int hash = hash_value(word);
	HashTable.slots[hash] = insert_beginning(HashTable.slots[hash], word);
}

void sort_char(char *sorted, char *word) {
	strcpy(sorted, word);
	int word_len = strlen(sorted);
	char temp;
	for (int i = 0; i < word_len; ++i) {
		for (int j = i; j < word_len; ++j) {
			if (sorted[i] > sorted[j]) {
				temp = sorted[j];
				sorted[j] = sorted[i];
				sorted[i] = temp;
			}
		}
	}
}

void print_anagrams(char *word, struct node *list) {
	char sortedWord[MAX_WORD_LEN], sortedValue[MAX_WORD_LEN];
	sort_char(sortedWord, word);
	int list_len = length_of(list);
	int first = 1;
	for (int i = 0; i < list_len; ++i) {
		sort_char(sortedValue, value_at(list, i));
		if (!strcmp(sortedWord, sortedValue)) {
			if (first) {
				first = 0;
			}
			else {
				fprintf(output, " ");
			}
			first = 0;
			fprintf(output, "%s", value_at(list, i));
		}
	}
}