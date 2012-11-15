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
#include <stdlib.h>
#include <string.h>
#include "fifo.c"

#define BUF_SIZE 1024

void usage();

extern int str[BUF_SIZE];
int j=0;

int main(int argc, char *argv[]) {

	//Parsing the input values
	int i;
	for (i=0; i<argc; i++) {
		if(strcmp(argv[i],"-h")==0) {
					usage();
		}
		if(strcmp(argv[i],"-f")==0) {
					//some function
				}
		if(strcmp(argv[i],"-r")==0) {
					//some function
				}
		if(strcmp(argv[i],"-i")==0) {
					//some function
				}

	}

	// file reader goes here
	printf("Filename:%s \n", argv[1]);
	FILE *fp;
	fp= fopen(argv[1], "r");

	if (fp == NULL) {
		printf("Cannot open file %s \n", argv[1]);
	}
	else {
		char s[BUF_SIZE];
		int c,k=0;
		size_t nread;
		if (fp) {
			while ((nread = fread(s, 1, sizeof s, fp)) > 0)
			        fwrite(s, 1, nread, stdout);
		}
		fclose(fp);
		//copy buffer to int array
		for(c=0;s[c]!='\0';c++) {
			k=0;
			int flag=0;
			while(!isspace(s[c])) {
				k= k*10 + s[c]-'0';
				c++;
				flag=1;
			}
			if(flag==1)
				str[j++]=k;
		}
		j--;
	}
	printf("Captured Int array\n");
	int k;
	for(k=0;k<j;k++) {
		printf("%d \n",str[k]);
	}
	return 0;
}

void usage() {
	printf("No help will be offered to you, get lost \n");
	exit(1);
}
