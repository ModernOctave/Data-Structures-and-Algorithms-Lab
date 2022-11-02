#include <stdio.h>

int main(int argc, char const *argv[]) {
	// Check for two arguments
	if (argc != 2) {
		printf("Invalid usage of command!\n");
		return 0;
	}

	int num, total=0, sum=0, min, max=0;
	float average;

	// Open file
	FILE *input, *output;
	input = fopen(argv[1], "r");

	// Check if open
	if (input == NULL) {
		printf("Could not open the file %s!", argv[1]);
		return 0;
	}
	
	// Read numbers
	while (fscanf(input,"%d\n", &num)==1) {
		total++;
		if (total==1) {
			min=num;
		}
		if (num<min) {
			min=num;
		}
		if (num>max) {
			max=num;
		}
		sum += num;
	}
	average=((float)sum/total);
	fclose(input);

	// Write output file
	output = fopen("output.txt", "w");
	fprintf(output, "%d\n%d\n%d\n%d\n%.2f\n", total, min, max, sum, average);
	fclose(output);

	return 0;
}