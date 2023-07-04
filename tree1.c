#include "tree.h"
#include <stdio.h>
#include "fifo.h"


void read_list(fl_head *listhead){
	fl_node *curr;
	int num;
	
	scanf("%d",&num);
	while(num > 0){
		curr = fl_node_create();
		curr->num = num;
		fl_enqueue(listhead,curr);
		scanf("%d",&num);
	}
	return;
}

int main(void){

	fl_head listhead;
	fl_head_init(&listhead);
	fl_node *tmp;
	read_list(&listhead);
	unsigned i,size = list_size(listhead.first);
	unsigned array[size];
	
	//construct postorder array from list (and deleting the list)
	for(i=0 ;i<size ;i++){
		tmp = fl_dequeue(&listhead);
		array[i] = tmp->num;
		fl_node_delete(tmp);
	}
	//

	tree_node *root = postorder_to_tree(array,size);
	
	//postorder_print(root);
	//putchar('\n');
	//printf("Height: %u\n",tree_height_calc(root));

	tree_to_levelorder_reversed(root,array);
	for(i=size-1 ;i!=0xFFFFFFFF ;i--){
		printf("%u ",array[i]);
	}
	putchar('\n');


	tree_delete(root);
	return(0);
}