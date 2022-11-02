/*
			Data Structures and Algorithms Lab
					  Assignment 2

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

void merge(int array[], int l, int mid, int h) {
	// Make two arrays
	int L[mid-l+1];
	int R[h-mid];
	for (int i = l; i <= mid; ++i) {
		L[i-l]=array[i];
	}
	for (int i = mid+1; i <= h; ++i) {
		R[i-mid-1]=array[i];
	}

	// Merge them in ascending order
	int j=0, k=0;
	for (int i = l; i <= h; ++i) {
		if (j<mid-l+1 && k<h-mid) {
			if (L[j]<=R[k]) {
				array[i]=L[j];
				j++;
			}
			else {
				array[i]=R[k];
				k++;
			}
		}
		else if (j<mid-l+1) {
			array[i]=L[j];
			j++;
		}
		else if (k<h-mid) {
			array[i]=R[k];
			k++;
		}
	}
}

void mergeSort(int array[], int l, int h) {
	// Merge-Sort two halves
	if (l < h) {
		int mid = l+(h-l)/2;
		mergeSort(array, l, mid);
		mergeSort(array, mid+1, h);
		merge(array, l, mid, h);
	}
}

void outputResult(int array[], int n) {
	FILE* output;

	// Open the file
	output = fopen("mergesort.txt", "w");
	if (output == NULL) {
		printf("Could not write to the file mergesort.txt!");
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
	// Check for two arguments
	if (argc != 2) {
		printf("Invalid usage of command!\n");
		return 0;
	}

	// Parse the numbers into array from file
	int n;
	int* array = parseFile(argv[1], &n);

	// Merge-Sort the array
	mergeSort(array, 0, n-1);

	// Write the output file
	outputResult(array, n);

	free(array);
	return 0;
}