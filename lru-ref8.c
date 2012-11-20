#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
//#include <iostream.>

int lru_ref8_eval(int orig_str[],int alloc_frames,int str_size) {
int bit_arr[alloc_frames][2],pos=0,flag=0,rem_ptr=0,replace_count=0,min=0,i=0,j=0,k=0;
for(i=0;i<alloc_frames;i++) {
    bit_arr[i][0]=-1;
    bit_arr[i][1]=0x00;
}
for(i=0;i<str_size;i++) {
    pos=0;
    flag=0;
    min=bit_arr[0][1];
    for(j=0;j<alloc_frames;j++) {
        bit_arr[j][1]=bit_arr[j][1]>>1;
    }
    for(j=0;j<alloc_frames;j++) {
        if(orig_str[i]==bit_arr[j][0]) {
                flag=1;
                pos=j;
                break;
        }
    }
    if(flag==1) {
      	bit_arr[pos][1]=bit_arr[pos][1]|0x80;
    }
    else if((flag!=1) && (bit_arr[alloc_frames-1][0]==-1)) {
    	bit_arr[rem_ptr][0]=orig_str[i];
        bit_arr[rem_ptr][1]=bit_arr[rem_ptr][1]|0x80;
        rem_ptr=(rem_ptr+1)%alloc_frames;
    }
    else {
        for(j=0;j<alloc_frames;j++) {
            if(min>bit_arr[j][1]) {
                 min=bit_arr[j][1];
            }
        }
        for(j=0;j<alloc_frames;j++) {
            if(bit_arr[j][1]==min) {
                 pos=j;
                 break;
            }
        }
        bit_arr[pos][0]=orig_str[i];
        bit_arr[pos][1]=0x80;
        replace_count=replace_count+1;
    }
}
return replace_count;
}
