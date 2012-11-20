#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

struct reference_string {
	int bit; //reference bit
	int referred_page; //input string for the page number t be accessed
};


void lru_clock_eval(int orig_str[], int alloc_frames, int str_size) {
	struct reference_string page[str_size];
	struct reference_string page_table[alloc_frames];
	int i,j=0,k=0,index,flag,fault_count=0, replace_count=0, frame_count=0, rm_ptr=0;

	struct timeval start, stop;
	long elapsed_usec, elapsed_msec;
	gettimeofday(&start, NULL);

	for (i=0;i<str_size;i++) {
		page[i].referred_page= orig_str[i];
		page[i].bit=0;  //ref_bit
	}for(i=0;i<str_size;i++) {
		printf("Page %d = %d ;bit= %d \n", i, page[i].referred_page, page[i].bit);
	}for(i=0;i<alloc_frames;i++) {
		page_table[i].referred_page = -969;
		page_table[i].bit=0;
	}for(i=0;i<alloc_frames;i++) {
		printf("Page %d = %d ;bit= %d \n", i, page_table[i].referred_page, page_table[i].bit);
	}

	for(i=0;i<str_size;i++) {
		flag=0;
		j=0; //fault_count_flag
		for(index=0;index < alloc_frames;index++) {
			if(page[i].referred_page == page_table[index].referred_page) {
				printf("\n match found");
				flag=1;
				page_table[index].bit = 1; //set page_table[ref_bit] =1 ;
			}
		}
		while (flag == 0) {
			if(page_table[rm_ptr].bit == 0) {
				flag=1;
				page_table[rm_ptr] = page[i];
				fault_count++;
				rm_ptr= (rm_ptr+1) % alloc_frames;	//replace this page and set flag=1;
			}
			else if(page_table[rm_ptr].bit ==1) {
				page_table[rm_ptr].bit = 0;
				rm_ptr= (rm_ptr+1) % alloc_frames;
			}
		}
		printf("\n ref_page= %d Page table :", page[i].referred_page);
		for (k=0;k<alloc_frames;k++){
			printf(" %d", page_table[k].referred_page);
		}
		}
	gettimeofday(&stop, NULL);

		elapsed_msec= stop.tv_sec-start.tv_sec;
		elapsed_usec= stop.tv_usec-start.tv_usec;

		replace_count= fault_count -alloc_frames;

		printf("Total faults: %d \n", fault_count);
		printf("Page replacements: %d \n", replace_count);
		printf("time taken= %ld seconds %ld microseconds \n",elapsed_msec, elapsed_usec);
}

void main() {
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	lru_clock_eval(orig_str,4,12);
	/*int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	lru_clock_eval(orig_str,4,12); f-6; r-2
	int orig_str[]= {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	lru_clock_eval(orig_str,3,20);
	int orig_str[]= {4,7,0,7,1,0,1,2,1,2,1,2,7,1,2};
	lru_clock_eval(orig_str,3,15); f-6, r-3
	int orig_str[]= {0,4,3,2,1,4,6,3,0};
	lru_clock_eval(orig_str,3,9); f-,r-
	*/
}
