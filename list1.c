#include <stdio.h>
#include "fifo.h"

//Read list (stop at 0)
void read_list(fl_head *listhead){
	fl_node *curr;
	int num;
	
	scanf("%d",&num);
	while(num){
		curr = fl_node_create();
		curr->num = num;
		fl_enqueue(listhead,curr);
		scanf("%d",&num);
	}
	return;
}

void largest_zero_queue(fl_head *listhead,unsigned res[3]){
	fl_node *start_ptr ,*curr;
	int start=0 ,end ,i ,min=0 ,max=0;
	unsigned listsize = list_size(listhead->first);
	int sum;

	start_ptr = listhead->first;

	for(;start_ptr ;start_ptr = start_ptr->nxt ,start++){
		
		sum = (end = 0);
		for(curr =start_ptr, i=start ;curr ;curr = curr->nxt,i++){
			sum += curr->num;
			if(sum == 0){
				end = i;
			}

		}

		//if new set bigger replace the current set
		if(end-start > max-min){
			min = start;
			max = end;
		}
		//
		
		//if biggest set bigger than the remaining list break
		if( (max-min)+1 >= listsize-(start+1)){
			break;
		}
		//
	}
	res[0] = min;
	res[1] = max;
	res[2] = (max - min) +1;
	return;
}

void sublist_print(fl_head *headlist ,unsigned start ,unsigned end){
	fl_node *curr;
	unsigned i;
	for(i=0,curr=headlist->first ;i<start ;curr = curr->nxt ,i++);
	while(i<=end && curr){
		printf("%d ",curr->num);
		i++;
		curr = curr->nxt;
	}
	putchar('\n');
	return;
}	

int main(int argc ,char *argv[]){
	fl_head listhead;
	unsigned res[3]={'\0'};

	fl_head_init(&listhead);
	read_list(&listhead);

	largest_zero_queue(&listhead,res);

	printf("start: %d, stop: %d, size: %d\n",res[0],res[1],res[2]);

	sublist_print(&listhead,res[0],res[1]);

	flist_delete(listhead.first);

	return(0);
}