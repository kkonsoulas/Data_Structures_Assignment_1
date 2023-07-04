#ifndef __TREE_H_
#define __TREE_H_

/*	Binary Tree Basics (by kkonsoulas)
	
   2
 /  \
1     3
*/

#define EDGES_NUM 3

#define PARENT 0
#define LEFT 1
#define RIGHT 2 

struct tree_node{
	struct tree_node *edges[EDGES_NUM];// 0=PARENT ,1=LEFT ,2=RIGHT
	int key;
};
typedef struct tree_node tree_node; 

//unitialised node
tree_node* _tree_node_create();

void tree_node_init(tree_node *junk_node);

//initialised node
tree_node* tree_node_create();

void make_right_child(tree_node *parent,tree_node *child);

void make_left_child(tree_node *parent,tree_node *child);

unsigned tree_node_height_calc(tree_node *node);

unsigned tree_height_calc(tree_node *root);
unsigned _tree_height_calc(tree_node *root,unsigned height);

void postorder_print(tree_node* root);

tree_node* postorder_to_tree(unsigned *array ,unsigned size);
tree_node* _postorder_to_tree(unsigned *array ,unsigned *i,unsigned min ,unsigned max);

void tree_to_levelorder_reversed(tree_node *root ,unsigned *array);//array must be large enough
void _tree_to_levelorder_reversed(tree_node *root,unsigned **array,unsigned height);

tree_node* levelorder_to_tree(unsigned *array ,unsigned height ,unsigned size);
void _levelorder_to_tree(tree_node *root ,unsigned **array ,unsigned height ,unsigned *size);

/*
tree_node* preorder_to_tree(unsigned *array,unsigned size);
void _preorder_to_tree(tree_node *root,unsigned **array,unsigned size);
*/
short is_binary_search_tree(tree_node *root);
short _is_binary_search_tree(tree_node *root ,unsigned min ,unsigned max);

tree_node* preorder_to_tree(unsigned *array ,unsigned size);
tree_node* _preorder_to_tree(unsigned **array,unsigned *end,unsigned min ,unsigned max);

tree_node* search_bst(tree_node *root ,unsigned key);

//returns array that must be freed
unsigned* tree_node_commonpath(tree_node *node1,tree_node *node2);

void tree_delete(tree_node *root);

#endif