#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

int fifo_eval(int orig_str[], int alloc_frames, int str_size) {


	int page_table[alloc_frames];
	int index,flag,i, j=0,fault_count=0;
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

	int replace_count= fault_count- alloc_frames;
	return replace_count;
}
