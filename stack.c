#include "stack.h"
#include <stdlib.h>

node* _node_create(){
	node *new = (node*) malloc(sizeof(node));
	if(new == NULL)
		exit(-1);
	return(new);
}

void node_init(node *junk_node){
	junk_node->nxt = NULL;
	//every other init//
	return;
}

node* node_create(){
	node *new = _node_create();
	node_init(new);
	return(new);
}

void node_delete(node *moribund){
	if(moribund){
		free(moribund);
	}
}

void list_delete(node *first_node){
	if(first_node){
		list_delete(first_node->nxt);
		free(first_node);
	}
	return;
}

short is_empty(head *head){
	if(head->top){
		return(0);
	}
	return(1);
}

void push(head *head,node *element){
	element->nxt = head->top;
	head->top = element;
	return;
}

node* pop(head *head){
	node *top_node = head->top;
	if(top_node){
		head->top = top_node->nxt;	
	}
	return(top_node);
}

node* top(head *head){
	return(head->top);
}