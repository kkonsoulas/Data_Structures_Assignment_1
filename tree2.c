#include "tree.h"
#include "fifo.h"
#include <stdio.h>
//#include <math.h>

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
    
	unsigned i,height,size = list_size(listhead.first);
    unsigned levelorder_array[size];
    
	//construct levelorder array from list (and deleting the list)
    for(i=0 ;i<size ;i++){
        tmp = fl_dequeue(&listhead);
        levelorder_array[i] = tmp->num;
        fl_node_delete(tmp);
    }
    //

    // height of the perfect tree calc
    for(height=0 ;size>>height ;height++){
		//empty
	}
    //printf("Height: %u\n",height);

	tree_node *root = levelorder_to_tree(levelorder_array ,height ,size);
	//postorder_print(root);
	//putchar('\n');
	printf("%s\n",is_binary_search_tree(root)? "Binary Search Tree":"Binary Tree");
	
	tree_delete(root);
	return(0);
}