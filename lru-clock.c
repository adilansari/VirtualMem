#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

struct referenced_string {
	int bit; //referenced bit
	int referred_page; //input string for the page number t be accessed
};


int lru_clock_eval(int orig_str[], int alloc_frames, int str_size) {
	struct referenced_string page[str_size];
	struct referenced_string page_table[alloc_frames];
	int i,j=0,k=0,index,flag,fault_count=0, replace_count=0, frame_count=0, rm_ptr=0;

		for (i=0;i<str_size;i++) {
		page[i].referred_page= orig_str[i];
		page[i].bit=0;  //ref_bit
	}for(i=0;i<alloc_frames;i++) {
		page_table[i].referred_page = -969;
		page_table[i].bit=0;
	}
	for(i=0;i<str_size;i++) {
		flag=0;
		j=0; //fault_count_flag
		for(index=0;index < alloc_frames;index++) {
			if(page[i].referred_page == page_table[index].referred_page) {
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
		//---------------
		if (frame_count > str_size+1) {
			index=0;
		}
		//---------------
		replace_count= fault_count -alloc_frames;
	}
		return replace_count;
}


