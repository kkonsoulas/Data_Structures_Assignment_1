#ifndef __FIFO_H_
#define __FIFO_H_

// fifo basics
//
// (new to que ->) - |------->|

struct fifo_node{
	struct fifo_node *nxt;
	int num;
	//data// 
};
typedef struct fifo_node fl_node;//fifo_list

struct fifo_head{
	struct fifo_node *first;
	//data//
};
typedef struct fifo_head fl_head;

//unitialised node
fl_node* _fl_node_create();
void fl_node_init(fl_node *junk_node);
fl_node* fl_node_create();


void fl_head_init(fl_head *head);

void fl_node_delete(fl_node *moribund);

void flist_delete(fl_node *first_node);

unsigned list_size(fl_node* first_node);

void fl_enqueue(fl_head *head, fl_node *new_node);

fl_node* fl_dequeue(fl_head *head);

fl_node* fl_next(fl_head *head);

#endif