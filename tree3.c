#include "tree.h"
#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>

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
    unsigned size = list_size(listhead.first);
	unsigned preorder_array[size];
	unsigned i ,num1 ,num2;
	unsigned *commonpath_array;

	//construct preorder array from list (and deleting the list)
    for(i=0 ;i<size ;i++){
        tmp = fl_dequeue(&listhead);
        preorder_array[i] = tmp->num;
        fl_node_delete(tmp);
    }
    //
	tree_node *root = preorder_to_tree(preorder_array,size);

	printf("Enter 2 integers: ");
	scanf("%u %u",&num1,&num2);
	putchar('\n');

	//search for nodes
	tree_node *node1 = search_bst(root,num1);
	tree_node *node2 = search_bst(root,num2);
	//

	//if both are found print shortest common path, else print message
	if(node1 && node2){//
		commonpath_array = tree_node_commonpath(node1,node2);
		printf("Path is: ");
		for(i=0 ;commonpath_array[i] ;i++){
			printf("%u ",commonpath_array[i]);
		}
		fseek(stdout,(long)-1,SEEK_CUR);
		printf("\n");
		free(commonpath_array);
	}
	else{
		printf("%u not found!\n",node1==NULL?num1:num2);
	}
	//

	tree_delete(root);

    return(0);
}