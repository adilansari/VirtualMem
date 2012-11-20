#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

struct reference_string {
	int pos; //position
	int referred_page; //input string for the page number t be accessed
};


void optimal_eval(int orig_str[], int alloc_frames, int str_size) {
	struct reference_string page[str_size];
	struct reference_string page_table[alloc_frames];
	int i,j=0,k=0,index,flag,fault_count=0, replace_count=0, frame_count=0, rm_ptr=0;

	struct timeval start, stop;
	long elapsed_usec, elapsed_msec;
	gettimeofday(&start, NULL);

	for (i=0;i<str_size;i++) {
		page[i].referred_page= orig_str[i];
		page[i].pos=i;
		for (j=0;j<i;j++) {
			if(page[j].referred_page == page[i].referred_page) {
				page[j].pos = page[i].pos;
			}
		}
	}for(i=0;i<str_size;i++) {
		printf("Page %d = %d ;pos_max= %d \n", i, page[i].referred_page, page[i].pos);
	}for(i=0;i<alloc_frames;i++) {
		page_table[i].pos=0;
	}

	for(i=0;i<str_size;i++) {
		flag=0;

		for(index=0;index < alloc_frames;index++) {
			if(page[i].referred_page == page_table[index].referred_page) {
				printf("match found \n");
				flag=1;
				if(i == page[i].pos) {
						page_table[index].pos =0;
						}
			}
		}
			if(i == page[i].pos) {
						page[i].pos= 0;
					}
			if((frame_count < alloc_frames) && (flag == 0)) {
						//fill in first three frames
						page_table[rm_ptr]= page[i];
						rm_ptr= (rm_ptr+1) % alloc_frames;
						fault_count++;
						frame_count++;
					}
					else if (flag == 0) {
						int max= page_table[0].pos;
						int eq_arr_count=0;
						for (k=0;k<alloc_frames;k++) {
							if(page_table[k].pos > max) {
								max= page_table[k].pos;
								j=k;
							}
						}
						for (k=0;k<alloc_frames;k++) {
							if (page_table[k].pos == 0){
								//increment the eq_arr_count
								eq_arr_count++;
								}
						}
						if (eq_arr_count >= 1) {//if eq_arr_count > 1
							int eq_arr[eq_arr_count];	//create new array int eq_arr[eq_arr_count];
							k=0;
							while(k < eq_arr_count)	{
								for(index=0; index<alloc_frames; index++) {
									if(page_table[index].pos == 0){
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
		}
	printf("New page pos updated: \n");
	for(i=0;i<str_size;i++) {
			printf("Page %d = %d ;pos= %d \n", i, page[i].referred_page, page[i].pos);
		}
	gettimeofday(&stop, NULL);

		elapsed_msec= stop.tv_sec-start.tv_sec;
		elapsed_usec= stop.tv_usec-start.tv_usec;

		printf("Total faults: %d \n", fault_count);
		printf("Page replacements: %d \n", replace_count);
		printf("time taken= %ld seconds %ld microseconds \n",elapsed_msec, elapsed_usec);
}

void main() {
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	optimal_eval(orig_str,4,12);
	/*int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	optimal_eval(orig_str,4,12); f-6; r-2
	int orig_str[]= {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	optimal_eval(orig_str,3,20);
	int orig_str[]= {4,7,0,7,1,0,1,2,1,2,1,2,7,1,2};
	optimal_eval(orig_str,3,15); f-5, r-2
	int orig_str[]= {0,4,3,2,1,4,6,3,0};
	optimal_eval(orig_str,3,9); f-7,r-4
	*/
}
