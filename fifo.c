#include <stdio.h>
#include <string.h>

void fifo_eval(int orig_str[], int alloc_frames, int str_size) {

	printf("New file");

	int page_table[alloc_frames];
	int index,flag,i;
	int j,fault_count=0;
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
	printf("Total faults: %d \n", fault_count);
}

void main() {
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	fifo_eval(orig_str,4,12);
}
