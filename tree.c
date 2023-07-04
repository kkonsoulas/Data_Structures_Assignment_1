#include "tree.h"
#include <stdlib.h>
#include <stdio.h>


tree_node* _tree_node_create(){
	tree_node *new = (tree_node*) malloc(sizeof(tree_node));
	if(new == NULL)
		exit(-1);
	return(new);
}

void tree_node_init(tree_node *junk_node){
	short i;
	for(i=0 ;i<EDGES_NUM ;i++){
		junk_node->edges[i] = NULL;
	}
	//every other init//
	return;
}

tree_node* tree_node_create(){
	tree_node *new = _tree_node_create();
	tree_node_init(new);
	return(new);
}

void make_right_child(tree_node *parent,tree_node *child){
	if(child == NULL || parent == NULL){
		return;
	}
	parent->edges[RIGHT] = child;
	child->edges[PARENT] = parent;
}

void make_left_child(tree_node *parent,tree_node *child){
	if(child == NULL || parent == NULL){
		return;
	}
	parent->edges[LEFT] = child;
	child->edges[PARENT] = parent;
}

tree_node* postorder_to_tree(unsigned *array ,unsigned size){
	unsigned i= size-1;
	tree_node *root = _postorder_to_tree(array,&i,0,0xFFFFFFFF);
	return(root);
}

tree_node* _postorder_to_tree(unsigned *array,unsigned *i,unsigned min ,unsigned max){

	if(*i == 0xFFFFFFFF){
		return(NULL);
	}

	tree_node *root = NULL;

	if( min < array[*i] && array[*i] < max ){
		
		root =tree_node_create();
		root->key = array[(*i)--];

		make_right_child(root,_postorder_to_tree(array,i,root->key,max));
		
		make_left_child(root,_postorder_to_tree(array,i,min,root->key));

	}

	return(root);
}

void postorder_print(tree_node* root){
	if(root == NULL){
		return;
	}

	postorder_print(root->edges[LEFT]);
	postorder_print(root->edges[RIGHT]);
	printf("%u ",root->key);
}

unsigned tree_node_height_calc(tree_node *node){
	unsigned h;
	for(h=0 ;node ;h++){
		node = node->edges[PARENT];
	}
	return(h);
}

unsigned tree_height_calc(tree_node *root){
	unsigned height=0;
	height = _tree_height_calc(root,height);
	return(height);
}

unsigned _tree_height_calc(tree_node *root,unsigned height){
	if(root == NULL){
		return(height);
	}

	height++;
	unsigned new_height;
	
	new_height = _tree_height_calc(root->edges[LEFT],height);
	
	height = _tree_height_calc(root->edges[RIGHT],height);
	if(height < new_height){
		height = new_height;
	}
	return(height);

}

void tree_to_levelorder_reversed(tree_node *root ,unsigned *array){//array must be large enough
	unsigned height = tree_height_calc(root);
	for(;height ;height--){
		_tree_to_levelorder_reversed(root,&array,height);
	}

}

void _tree_to_levelorder_reversed(tree_node *root,unsigned **array,unsigned height){
	if(root == NULL){
		return;
	}
	else if(height == 1){
		**array = root->key;
		(*array)++;
		return;
	}

	height--;
	_tree_to_levelorder_reversed(root->edges[RIGHT],array,height);
	_tree_to_levelorder_reversed(root->edges[LEFT],array,height);

}


tree_node* levelorder_to_tree(unsigned *array ,unsigned height ,unsigned size){
	tree_node *root = NULL;
	unsigned h;

	if(size){
		root = tree_node_create();
		root->key = *array;
		array++;
		size--;
	}
	
	for(h=1 ; h<height ;h++){
		_levelorder_to_tree(root,&array,h,&size);
	}

	return(root);
}

void _levelorder_to_tree(tree_node *root ,unsigned **array ,unsigned height ,unsigned *size){
	if(root == NULL){
		return;
	}

	if(height == 1){
		if(*size){
			tree_node *new = tree_node_create();
			new->key = **array;
			make_left_child(root,new);
			(*array)++;
			(*size)--;
			if(*size){
				new = tree_node_create();
				new->key = **array;
				make_right_child(root,new);
				(*array)++;
				(*size)--;
			}
		}

		return;
	}

	_levelorder_to_tree(root->edges[LEFT],array,height-1,size);
	_levelorder_to_tree(root->edges[RIGHT],array,height-1,size);

	return;
}

short is_binary_search_tree(tree_node *root){
	return(_is_binary_search_tree(root,0,0xFFFFFFFF));
}

short _is_binary_search_tree(tree_node *root ,unsigned min ,unsigned max){
	if(root == NULL){
		return(1);
	}

	if(min <root->key && root->key <max){
		char trigger;
		trigger = _is_binary_search_tree(root->edges[LEFT],min,root->key);
		if(trigger == 0){
			return(0);
		}
		trigger = _is_binary_search_tree(root->edges[RIGHT],root->key,max);
		return(trigger);
	}

	return(0);
}


tree_node* preorder_to_tree(unsigned *array ,unsigned size){
	unsigned *endof_array = array + size;
	tree_node *root = _preorder_to_tree(&array,endof_array,0,0xFFFFFFFF);
	return(root);
}

tree_node* _preorder_to_tree(unsigned **array,unsigned *end,unsigned min ,unsigned max){

	if(*array == end){
		return(NULL);
	}

	tree_node *root = NULL;

	if( min < **array && **array < max ){
		
		root =tree_node_create();
		root->key = **array;
		(*array)++;

		make_left_child(root,_preorder_to_tree(array,end,min,root->key));
		
		make_right_child(root,_preorder_to_tree(array,end,root->key,max));

	}

	return(root);
}



tree_node* search_bst(tree_node *root ,unsigned key){
	
	while(root && root->key != key){
		if(root->key < key){
			root = root->edges[RIGHT];
		}
		else{
			root = root->edges[LEFT];
		}
	}

	return(root);
}

unsigned* tree_node_commonpath(tree_node *node1,tree_node *node2){
	unsigned size1 = tree_node_height_calc(node1);
	unsigned size2 = tree_node_height_calc(node2);
	unsigned array1[size1],array2[size2];
	unsigned i,j,commonpath_size;

	//Construct path from node->root
	for(i=0 ;i<size1 ;i++,node1 = node1->edges[PARENT]){
		array1[i] = node1->key;
	}
	for(j=0 ;j<size2 ;j++,node2 = node2->edges[PARENT]){
		array2[j] = node2->key;
	}
	//

	//Find common node_key to calculate commonpath_size
	for(i=size1-1,j=size2-1 ;array1[i] == array2[j] ;i--,j--);
	size1 = i+2;//+2 to include the common node 
	size2 = j+1;
	commonpath_size = size1 + size2 +1;//+1 to include terminating 0
	//

	//Create and fill array with the keys of the path
	unsigned *commonpath_array = (unsigned*) malloc(commonpath_size * sizeof(unsigned));
	for(i=0 ;i<size1 ;i++){
		commonpath_array[i] = array1[i];		
	}
	for(j=size2-1 ;j<0xFFFFFFFF ;j--,i++){
		commonpath_array[i] = array2[j];
	}
	commonpath_array[i] = 0;//adding the terminating 0
	//

	return(commonpath_array);
}


void tree_delete(tree_node *root){
	char trigger;
	short i; // MUST i >= EDGES_NUM
	tree_node *leaf; 
	do{	
		if(root == NULL){
			return;
		}
		//Child searcher
		trigger=0;
		for(i=1 ;i<EDGES_NUM ;i++){
			if(root->edges[i]){
				trigger = 1;
				break;
			}
		}
		//

		//if there are childs go into them
		if(trigger){
			root = root->edges[i];
		}
		else{//delete the current node
			leaf = root;
			root = root->edges[0];

			if(root == NULL){
				//printf("FREED %d\n",leaf->key);
				free(leaf);
				return;
			}

			for(i=1 ;i<EDGES_NUM ;i++){
				if(root->edges[i] == leaf){
					root->edges[i]=NULL;
				}
			}
			
			//printf("FREED %d\n",leaf->key);
			free(leaf);
			
		}

	}while(1);

}
