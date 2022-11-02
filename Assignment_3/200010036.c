/*
			Data Structures and Algorithms Lab
					  Assignment 3

				By: Om Patil (200010036)
*/

#include <stdio.h>
#include <stdlib.h>

int* parseFile(char const* filename, int* n) {
	// Open file
	FILE *input, *output;
	input = fopen(filename, "r");

	// Check if open
	if (input == NULL) {
		printf("Could not open the file %s!", filename);
		return 0;
	}
	
	// Find count of numbers
	int count=0, num;
	while (fscanf(input,"%d\n", &num)==1) {
		count++;
	}

	// Reopen file
	fclose(input);
	input = fopen(filename, "r");
	if (input == NULL) {
		printf("Could not open the file %s!", filename);
		return 0;
	}

	// Load numbers into array
	int* arr = (int*)malloc(count*sizeof(int));
	int i=0;
	while (fscanf(input,"%d\n", &num)==1) {
		arr[i]=num;
		i++;
	}

	fclose(input);
	*n = count;
	return arr;
}

int power(int a, int b) {
	// Basic power function
	int ans = 1;
	for (int i = 0; i < b; ++i) {
		ans *= a;
	}
	return ans;
}

void countingSort(int array[], int index, int size) {
	// Prepare digits array
	int digit_array[size];
	for (int i = 0; i < size; ++i) {
		digit_array[i]=(array[i]/power(10,index))%10;
	}

	// Prepare digit count array
	int digit_count[size];
	for (int i = 0; i < size; ++i) {
		digit_count[i]=0;
	}
	for (int i = 0; i < size; ++i) {
		digit_count[digit_array[i]]++;
	}
	for (int i = 1; i < size; ++i) {
		digit_count[i]+=digit_count[i-1];
	}

	// Count-Sort into temp array
	int temp[size];
	for (int i = size-1; i >= 0; --i) {
		temp[digit_count[digit_array[i]]-1]=array[i];
		digit_count[digit_array[i]]--;
	}

	// Copy temp array into given array
	for (int i = 0; i < size; ++i) {
		array[i]=temp[i];
	}
}

void radixSort(int array[], int digits, int size) {
	// Count-Sort for each digit
	for (int i = 0; i < digits; ++i) {
		countingSort(array, i, size);
	}
}

void outputResult(int array[], int n) {
	FILE* output;

	// Open the file
	output = fopen("radix.txt", "w");
	if (output == NULL) {
		printf("Could not write to the file radix.txt!");
		return;
	}

	// Print results
	for (int i = 0; i < n-1; ++i) {
		fprintf(output, "%d\n", array[i]);
	}
	fprintf(output, "%d", array[n-1]);

	// Close file
	fclose(output);
}

int main(int argc, char const *argv[]) {
	// Check for three arguments
	if (argc != 3) {
		printf("Invalid usage of command!\n");
		return 0;
	}

	// Parse the numbers into array from file
	int digits = atoi(argv[2]);
	int size;
	int* array = parseFile(argv[1], &size);

	// Radix-Sort the array
	radixSort(array, digits, size);

	// Output the result
	outputResult(array, size);

	free(array);
	return 0;
}