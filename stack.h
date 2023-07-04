#ifndef __STACK_H_
#define __STACK_H_

//Stack Basics (by kkonsoulas)
//  |
//  |
//  |
//__|___

struct stack_node{
	struct stack_node *nxt;
	//data// 
};
typedef struct stack_node node;

struct stack_head{
	struct stack_node *top;
	//data//
};
typedef struct stack_head head;

//unitialised node
node* _node_create();

void node_init(node *junk_node);

//initialised node
node* node_create();

void node_delete(node *moribund);

short is_empty(head *head);

void push(head *head,node *element);

node* pop(head *head);

node* top(head *head); 

#endif