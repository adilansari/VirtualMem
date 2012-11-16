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
		//int x,y,z=0;
		flag=0;
		/*printf("\n alpha 1");
		printf(" page table now: ");
						while(x<alloc_frames){
							printf("%d ",page_table[x++]);
						}*/
		for(index=0;index<alloc_frames;index++) {
			if(orig_str[i] == page_table[index]) {
				flag=1;
				/*j=index+1;
				printf("\n alpha 3");
				printf(" page table now: ");
				while(y<alloc_frames) {
					printf("%d ", page_table[y]);
					y++;
				}
				break;*/
			}
		}
		if(flag==0) {
						page_table[j%alloc_frames]= orig_str[i];
						fault_count++;
						j++;
						/*printf("\n alpha 2");
						printf(" page table now: ");
								while(z<alloc_frames){
										printf("%d ",page_table[z]);
										z++;
								}*/
							}
	}
	printf("Total faults: %d \n", fault_count);
}

void main() {
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	fifo_eval(orig_str,4,12);
}
