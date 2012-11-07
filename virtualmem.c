/*
Class 1: read input file
Class 2: FIFO and call to PRINT class
Class 3: LFU
Class 4: LRU_STACK
Class 5: LRU_Clock
Class 6: LRU_REF8
Class 8: Optimal
Class 9: Print results
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("Filename:%s \n", argv[1]);
	FILE *fp;
	fp= fopen(argv[1], "r");

	if (fp == NULL) {
		printf("Cannot open file %s \n", argv[1]);
	}
	else {
		int c;
		while ((c = fgetc(fp)) != EOF) {
			printf("%c\n", c);
		}
		fclose(fp);
	}

	return 0;
}
