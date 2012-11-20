#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

struct reference_string {
	int freq; //frequency
	int referred_page; //input string for the page number t be accessed
};


void lfu_eval(int orig_str[], int alloc_frames, int str_size) {
	struct reference_string page[str_size];
	struct reference_string page_table[alloc_frames];
	int i,j=0,k=0,index,flag,fault_count=0,rm_ptr=0, frame_count=0, replace_count=0;

	struct timeval start, stop;
	long elapsed_usec, elapsed_msec;
	gettimeofday(&start, NULL);

	for (i=0;i<str_size;i++) {
		page[i].referred_page= orig_str[i];
		page[i].freq=0;
	}for(i=0;i<str_size;i++) {
		printf("Page %d = %d ;freq= %d \n", i, page[i].referred_page, page[i].freq);
	} for(i=0;i<alloc_frames;i++) {
		//page_table[i].referred_page=0;
		page_table[i].freq=0;
	}

	for(i=0;i<str_size;i++) {
		flag=0;
		for(k=0;k<str_size;k++) {
					if(page[i].referred_page == page[k].referred_page)
						page[k].freq++; // because whether found or added the frequency has to be incremented
				}
		for(index=0;index < alloc_frames;index++) {
			if(page[i].referred_page == page_table[index].referred_page) {
				//printf("match found \n");
				page_table[index].freq= page[i].freq;
				flag=1;
				break;
			}
		}
		if((frame_count < alloc_frames) && (flag == 0)) {
			//fill in first three frames
			page_table[rm_ptr]= page[i];
			rm_ptr= (rm_ptr+1) % alloc_frames;
			fault_count++;
		}
		else if (flag == 0) {
			int min= page_table[0].freq;
			int eq_arr_count=0;
			for (k=0;k<alloc_frames;k++) {
				if(page_table[k].freq < min) {
					min= page_table[k].freq;
					j=k;
				}
			}
			for (k=0;k<alloc_frames;k++) {
				if (page_table[k].freq == min){
					//increment the eq_arr_count
					eq_arr_count++;
					}
			}
			if (eq_arr_count > 1) {//if eq_arr_count > 1
				int eq_arr[eq_arr_count];	//create new array int eq_arr[eq_arr_count];
				k=0;
				while(k < eq_arr_count)	{
					for(index=0; index<alloc_frames; index++) {
						if(page_table[index].freq == min){
							eq_arr[k++]=index;//initialise this new array with 'index' values that are equal to min
					}
				}
			}
			int dobreak=1,x=0,var_ptr= rm_ptr; //copy rm_ptr into new variable var_ptr adn keep incrementing until var_ptr poits to anything in the array
			for(x=0;dobreak && (x<alloc_frames);x++) { //edit line
				for(k=0; k<eq_arr_count; k++) {
					if(var_ptr == eq_arr[k]) {
						j=eq_arr[k];//j= var_ptr and break;
						dobreak=0;
						break;
					}
				}
				var_ptr= (var_ptr+1) % alloc_frames;
			}
			}
			page_table[j]= page[i];
			fault_count++;
			replace_count++;
			rm_ptr= (rm_ptr+1) % alloc_frames;
		}
		frame_count++;
		//rm_ptr= (rm_ptr+1) % alloc_frames;
	}
	printf("New page frequencies updated: \n");
	for(i=0;i<str_size;i++) {
			printf("Page %d = %d ;freq= %d \n", i, page[i].referred_page, page[i].freq);
		}
	gettimeofday(&stop, NULL);

		elapsed_msec= stop.tv_sec-start.tv_sec;
		elapsed_usec= stop.tv_usec-start.tv_usec;

		printf("Total faults: %d \n", fault_count);
		printf("Total Page replacements: %d \n", replace_count);
		printf("time taken= %ld seconds %ld microseconds \n",elapsed_msec, elapsed_usec);
}

void main() {
	int orig_str[]= {4,7,0,7,1,0,1,2,1,2,1,2,7,1,2};
	lfu_eval(orig_str,3,15);
	/*int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	lfu_eval(orig_str,4,12); faul-7 ; repl-3
	int orig_str[]= {4,7,0,7,1,0,1,2,1,2,1,2,7,1,2};
	lfu_eval(orig_str,3,15); faul-6; repl-3
	int orig_str[]= {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	lfu_eval(orig_str,3,20);
	*/
}
