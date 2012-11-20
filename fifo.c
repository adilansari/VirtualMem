#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

int fifo_eval(int orig_str[], int alloc_frames, int str_size) {

	printf("New file");

	int page_table[alloc_frames];
	int index,flag,i, j=0,fault_count=0;

	struct timeval start, stop;
	long elapsed_usec, elapsed_msec;
	gettimeofday(&start, NULL);


	printf("incoming values %d %d \n", alloc_frames, str_size);
	for(i=0;i<str_size;i++) {
		printf("%d,", orig_str[i]);
	}
	for (i=0;i<str_size;i++) {
		flag=0;
		for(index=0;index<alloc_frames;index++) {
			if(orig_str[i] == page_table[index]) {
				flag=1;
			}
		}
		if(flag==0) {
						page_table[j%alloc_frames]= orig_str[i];
						fault_count++;
						j++;
							}
	}
	gettimeofday(&stop, NULL);

	elapsed_msec= stop.tv_sec-start.tv_sec;
	elapsed_usec= stop.tv_usec-start.tv_usec;

	printf("Total faults: %d \n", fault_count);
	int replace_count= fault_count- alloc_frames;
	printf("Total Page replacements: %d \n", replace_count);
	printf("time taken= %ld seconds %ld microseconds \n",elapsed_msec, elapsed_usec);
	return replace_count;
}

/*void main() {
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	fifo_eval(orig_str,3,12);
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	fifo_eval(orig_str,4,12); faul-10 ; repl-6
	int orig_str[]= {4,7,0,7,1,0,1,2,1,2,1,2,7,1,2};
	fifo_eval(orig_str,3,15); faul-6 ; repl-3
	int orig_str[]= {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	fifo_eval(orig_str,3,20); faul-9 ; repl- 6
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	fifo_eval(orig_str,3,12); faul-9 ; repl-6

}*/
