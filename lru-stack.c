
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


struct node {
    int data;
    struct node *next;
};

int traverse(struct node *);


int lru_stack_eval(int orig_str[BUFSIZ],int alloc_frames,int str_size) {
int flag=0,pos=0,pos1=0,pos2=0,replace_count=0,i=0;
struct node *node1,*node2,*root=NULL;
for(i=0;i<str_size;i++) {
    flag=0;
    pos=0;
    pos1=0;
    pos2=0;
    node1=root;
    node2=root;
    while(node1!=NULL) {
	if(node1->data==orig_str[i]) {
		flag=1;
                break;
        }
        pos=pos+1;
        node1=node1->next;
    }
    node1=root;
    if(root==NULL) {     // if root is null
       struct node *newnode;
       newnode= malloc(sizeof(struct node));//new node;
       newnode->data=orig_str[i];
       root=newnode;
       newnode->next=NULL;
    }
    else if(flag!=1 && traverse(node1)<alloc_frames) {  // if element is not present and l<fr
       struct node *newnode;
       newnode=malloc(sizeof(struct node));//new node;
       newnode->data=orig_str[i];
       newnode->next=root;
       root=newnode;
    }
    //node1=root;
    else if(flag==1) {         // if element is present
       while(pos1<pos-1) {
              node1=node1->next;
	      pos1=pos1+1;
       }
       while(pos2<pos) {
	      node2=node2->next;
              pos2=pos2+1;
       }
       node1->next=node2->next;
       node2->next=root;
       root=node2;
    }
    //node1=root;
    else {        // element is not in list and str_size>alloc_frames
      while(pos<alloc_frames-2) {
	    pos=pos+1;
	    node1=node1->next;
      }
      node1->next=NULL;
      struct node *newnode;
      newnode=malloc(sizeof(struct node));//new node;
      newnode->data=orig_str[i];
      newnode->next=root;
      root=newnode;
      replace_count=replace_count+1;
    }
}
return replace_count;
}

int traverse(struct node *l) {
int lil=0;
while(l!=NULL) {
    lil=lil+1;
    l=l->next;
}
return lil;
}
