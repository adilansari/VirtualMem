#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
//#include <iostream.>

void lru_ref8_eval(int orig_str[],int alloc_frames,int str_size) {
	printf("hello");
int bit_arr[alloc_frames][2],pos=0,flag=0,rem_ptr=0,replace_count=0,min=0,i=0,j=0,k=0;
for(i=0;i<alloc_frames;i++) {
	//printf("\n alpha 1");
    bit_arr[i][0]=-1;
    bit_arr[i][1]=0x00;
}
for(i=0;i<str_size;i++) {
    pos=0;
    flag=0;
    min=bit_arr[0][1];
    //printf("\n alpha 2");
    for(j=0;j<alloc_frames;j++) {
        bit_arr[j][1]=bit_arr[j][1]>>1;
        //printf("\n alpha 3");
    }
    for(j=0;j<alloc_frames;j++) {
        if(orig_str[i]==bit_arr[j][0]) {
                flag=1;
                pos=j;
                //printf("\n alpha 4");
                break;
        }
    }
    if(flag==1) {
    	//printf("\n alpha 5");
      	bit_arr[pos][1]=bit_arr[pos][1]|0x80;
    }
    else if((flag!=1) && (bit_arr[alloc_frames-1][0]==-1)) {
    	bit_arr[rem_ptr][0]=orig_str[i];
        bit_arr[rem_ptr][1]=bit_arr[rem_ptr][1]|0x80;
        rem_ptr=(rem_ptr+1)%alloc_frames;
        //printf("\n alpha 6");
    }
    else {
        for(j=0;j<alloc_frames;j++) {
            if(min>bit_arr[j][1]) {
                 min=bit_arr[j][1];
                 //printf("\n alpha 7");
            }
        }
        for(j=0;j<alloc_frames;j++) {
            if(bit_arr[j][1]==min) {
                 pos=j;
                 //printf("\n alpha 8");
                 break;
            }
        }
        bit_arr[pos][0]=orig_str[i];
        bit_arr[pos][1]=0x80;
        //printf("\n alpha 9");
        replace_count=replace_count+1;
    }
}
printf("\n Page replacements: %d\n",replace_count);
}

void main() {
	int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	lru_ref8_eval(orig_str,4,12);
	/*int orig_str[]= {1,2,3,4,1,2,5,1,2,3,4,5};
	lru_ref8_eval(orig_str,4,12); f-6; r-2
	int orig_str[]= {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	lru_ref8_eval(orig_str,3,20);
	int orig_str[]= {4,7,0,7,1,0,1,2,1,2,1,2,7,1,2};
	lru_ref8_eval(orig_str,3,15); f-6, r-3
	int orig_str[]= {0,4,3,2,1,4,6,3,0};
	lru_ref8_eval(orig_str,3,9); f-,r-
	*/
		//return 0;
}
