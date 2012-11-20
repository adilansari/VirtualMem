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
#include<sys/types.h>
#include<sys/time.h>
//#include "fifo.c"

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
	int replace_count1;
	struct timeval start1, stop1, start2, stop2;
		long elapsed_msec1, elapsed_msec2;
		gettimeofday(&start1, NULL);
	if (algo_flag == 2) {
		//replace_count1 lfu_eval();
		printf("\n gamma 5 \n");
	}else if(algo_flag == 3) {
		//replace_count1 lru-stack_eval();
		printf("\n gamma 6 \n");
	}else if(algo_flag == 4) {
		//replace_count1 lru-clock_eval();
	} else if(algo_flag == 5) {
		//replace_count1= lru-ref8_eval();
	} else {
		printf("\n gamma 2 \n");
		printf("%d %d \n", frames,j);
		printf("\n Captured Int array \n");
			int k;
			for(k=0;k<j;k++) {
				printf("%d ",str[k]);
			}
		//replace_count1= fifo_eval(str,frames,j);
	}
	gettimeofday(&stop1, NULL);
	elapsed_msec1= stop1.tv_usec-start1.tv_usec;
	gettimeofday(&start2, NULL);
	//int replace_count2 = optimal_eval();
	gettimeofday(&stop2, NULL);
		elapsed_msec2= stop2.tv_usec-start2.tv_usec;
	//print_results(elapsed_msec1, elapsed_msec2, replace_count1, replace_count2)
}

void print_results(long time_alg, long time_opt, int replace_alg, int replace_opt) {

}

void usage() {
	printf("No help will be offered to you, get lost \n");
	exit(1);
}
