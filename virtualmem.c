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
void algo();

int str[BUF_SIZE];
int j=0;
int frames = 5;
char *filename;
int algo_flag=1;

int main(int argc, char *argv[]) {

	//Parsing the input values
	int i;
	for (i=0; i<argc; i++) {
		if(strcmp(argv[i],"-h")==0) {
					usage();
		}
		if(strcmp(argv[i],"-f")==0) {
			frames= atoi(argv[i+1]);
			printf("\n gamma 0");
				}
		if(strcmp(argv[i],"-r")==0) {
					if(strcmp(argv[i+1],"LFU")==0) {
						algo_flag=2;
					}
					else if(strcmp(argv[i+1],"LRU-STACK")==0) {
						algo_flag=3;
					}
					else if(strcmp(argv[i+1],"LRU-CLOCK")==0) {
						algo_flag=4;
					}
					else if(strcmp(argv[i+1],"LRU-REF8")==0) {
						algo_flag=5;
					}
					else {
						//FIFO
						printf("\n gamma 1");
					}
				}
		if(strcmp(argv[i],"-i")==0) {
			filename= argv[i+1];
				}

	}

	/*code to verify parameters have been updated
	printf("Frames= %d\n", frames);
	printf("Filename:%s \n", filename);*/

	// file reader goes here
	FILE *fp;
	fp= fopen(filename, "r");

	if (fp == NULL) {
		printf("Cannot open file %s \n", argv[1]);
	}
	else {
		char s[BUF_SIZE];
		int c,flag;
		int k=0;
		size_t nread;
		if (fp) {
			/*while ((nread = fread(s, 1, sizeof s, fp)) > 0)
			        fwrite(s, 1, nread, stdout);*/
			while ((s[k] = fgetc(fp)) != EOF) {
					//printf("%c\n", c);
						k++;
					}
		}
		fclose(fp);
		//copy buffer to int array
		for(c=0;s[c]!='\0';c++) {
			k=0;
			flag=0;
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
	printf("\n Captured Int array \n");
	int p;
	for(p=0;p<j;p++) {
		printf("%d ",str[p]);
	}
	printf("\n gamma 3");
	algo();
	return 0;
}

void algo() {
	printf("\n gamma 4 \n");
	if (algo_flag == 2) {
		//lfu
		printf("\n gamma 5 \n");
	}else if(algo_flag == 3) {
		//lru-stack
		printf("\n gamma 6 \n");
	}else if(algo_flag == 4) {
		//lru-clock
	} else if(algo_flag == 5) {
		//lru-ref8
	} else {
		printf("\n gamma 2 \n");
		printf("%d %d \n", frames,j);
		printf("\n Captured Int array \n");
			int k;
			for(k=0;k<j;k++) {
				printf("%d ",str[k]);
			}
		//fifo_eval(str,frames,j);
	}
}

void usage() {
	printf("No help will be offered to you, get lost \n");
	exit(1);
}
