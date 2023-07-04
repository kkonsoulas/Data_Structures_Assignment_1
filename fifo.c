#include "fifo.h"
#include <stdlib.h>

fl_node* _fl_node_create(){
	fl_node *new = (fl_node*) malloc(sizeof(fl_node));
	if(new == NULL)
		exit(-1);
	return(new);
}

void fl_node_init(fl_node *junk_node){
	junk_node->nxt = NULL;
	//every other init//
	return;
}

void fl_head_init(fl_head *head){
	head->first = NULL;
	//every other init//
	return;
}

fl_node* fl_node_create(){
	fl_node *new = _fl_node_create();
	fl_node_init(new);
	return(new);
}

void fl_node_delete(fl_node *moribund){
	if(moribund){
		free(moribund);
	}
}

void flist_delete(fl_node *first_node){
	if(first_node){
		flist_delete(first_node->nxt);
		free(first_node);
	}
	return;
}

unsigned list_size(fl_node* first_node){
	unsigned i;
	for(i=0 ;first_node ;first_node= first_node->nxt ,i++);
	return(i);	
}

void fl_enqueue(fl_head *head,fl_node *new_node){
	
	if(head->first == NULL){
		head->first = new_node;
		return;
	}
	fl_node *ptr;
	for(ptr = head->first ;ptr->nxt ;ptr = ptr->nxt);
	ptr->nxt = new_node;
	return;
}

fl_node* fl_dequeue(fl_head *head){
	fl_node* ptr = head->first;
	head->first = ptr->nxt;
	return(ptr);
}

fl_node* fl_next(fl_head *head){
	return(head->first);
}