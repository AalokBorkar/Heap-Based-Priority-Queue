/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Aalok Borkar
 * Email: borkaraa@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include <assert.h>
#include "dynarray.h"
/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray *array;
};

struct node{
	void* pid; //aka actual value
	int priority;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq *p = malloc(sizeof(struct pq));
  assert(p);
  p->array = dynarray_create();
  return p;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->array);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	assert(pq->array); //Checking: is an array even allocated?
	//return (!dynarray_size(pq->array)); //if size is anything else than 0 it will return !true which is false and the other way around
	if(dynarray_size(pq->array)){
		return 0;	
	}
	return 1;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.  
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
		struct node *temp, *p, *pp;
		struct node *val = malloc(sizeof(struct node));
		val->pid = value; //set this new nodes pid to the one hess sends in
		val->priority = priority;

		dynarray_insert(pq->array, -1, val); //add 'val' to the end of the tree (next available spot)
		int index = dynarray_size(pq->array)-1; //start index at the last index
		while(((index-1)/2) > -1 && index != 0){//percolate up
			p = dynarray_get(pq->array, index);
			pp = dynarray_get(pq->array,((index-1)/2));
			temp = dynarray_get(pq->array,((index-1)/2));
			if(p->priority < pp->priority){
				dynarray_set(pq->array, ((index-1)/2), dynarray_get(pq->array, index)); //set parent = current index
				dynarray_set(pq->array, index, temp);
				index = ((index-1)/2);
			}
			else{
				break;
			}		
		}
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	assert(pq);
	assert(pq->array);
	struct node *p = dynarray_get(pq->array, 0);	
	return p->pid; //returns the address of the pid [struct] element...test.c deals with it
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	assert(pq);
	assert(pq->array);
	struct node *p = dynarray_get(pq->array, 0);	
	return p->priority; //returns the address of the pid [struct] element...test.c deals with it
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	struct node *first = dynarray_get(pq->array, 0);
	dynarray_set(pq->array, 0, dynarray_get(pq->array, -1)); //set the first element to equal the last
	dynarray_remove(pq->array, -1); //remove the last element aka decrement size and forget about it - In this case it just decrements size...
	//percolation: Left: ((i*2)+1) | Right: ((i*2)+2)
	int index = 0;
	struct node *p, *c1, *c2 = NULL;
		
	while( ((index*2)+1) < dynarray_size(pq->array) || ((index*2)+2) < dynarray_size(pq->array) ){ //while either are less; 'either' b/c you could only have one child for instance....
		p = dynarray_get(pq->array, index); //parent (starts at 0)
		if(((index*2)+1) < dynarray_size(pq->array)){
			c1 = dynarray_get(pq->array, ((index*2)+1)); //child 1
		}
		if(((index*2)+2) < dynarray_size(pq->array)){
			c2 = dynarray_get(pq->array, ((index*2)+2)); //child 2
		}
	////////////////////////////////////////////
		if((((index*2)+1) < dynarray_size(pq->array)) && (((index*2)+2) < dynarray_size(pq->array))){//if you have both children within bounds
			
			if(c2->priority > c1->priority || c2->priority == c1->priority){ //if c1 is smaller or they are the same
				if(p->priority > c1->priority ){
					dynarray_set(pq->array, index, c1);//make parent point to younger child
					dynarray_set(pq->array, ((index*2)+1), p); //fully swapped
					index = ((index*2)+1);
				}
				else{
					break;
				}
			}
			else if(c2->priority < c1->priority){ //c2 wins
				if(p->priority > c2->priority ){
					dynarray_set(pq->array, index, c2);//make parent point to younger child
					dynarray_set(pq->array, ((index*2)+2), p); //fully swapped
					index = ((index*2)+2);
				}
				else{
					break;
				}
			}
		}
		else{ //if only a left child
			if(p->priority > c1->priority ){
				dynarray_set(pq->array, index, c1);//make parent point to younger child
				dynarray_set(pq->array, ((index*2)+1), p); //fully swapped
				index = ((index*2)+1);
		    }
			else{
				break;
			}
		}
	}
	struct process *pv = first->pid;
	free(first);
	return pv;
}
