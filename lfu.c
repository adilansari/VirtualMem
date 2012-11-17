#include <stdio.h>
#include <string.h>

struct reference_string {
	int freq; //frequency
	int referred_page; //input string for the page number t be accessed
};


void lfu_eval(int orig_str[], int alloc_frames, int str_size) {
	struct reference_string page[str_size];
	struct reference_string page_table[alloc_frames];
	int i,j=0,k=0,index,flag,fault_count=0;

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
		if (flag == 0) {
			j= get_min(page_table, alloc_frames);
			page_table[j]= page[i];
			fault_count++;
		}
	}
	printf("New page frequencies updated: \n");
	for(i=0;i<str_size;i++) {
			printf("Page %d = %d ;freq= %d \n", i, page[i].referred_page, page[i].freq);
		}
	printf("\ntotal faults= %d \n",fault_count);
}

int get_min(struct reference_string ptr[],int alloc_frames) {
	int min=ptr[0].freq,i,pos=0;

	for(i=0;i < alloc_frames;i++) {
		printf("%d ", ptr[i].referred_page);

		if((ptr[i].freq < min)) {
			min= ptr[i].freq;
		}
	}
	while(ptr[pos].freq != min) {
		pos++;
	}

	printf("min= %d \n",pos);
	return pos;
}

void main() {
	int orig_str[]= {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	lfu_eval(orig_str,4,20);
	/*int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
		lfu_eval(orig_str,4,12);*/
}
