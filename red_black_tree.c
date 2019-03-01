#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct red_black_tree rbt;

struct red_black_tree { 
	bool color; // defines the color red or black, true for black and false for red
	int item;
	rbt *right_child;
	rbt *left_child;
};

rbt *create_empty_red_black_tree() {
	rbt *new_rbt = (rbt *) malloc(sizeof(rbt));
	new_rbt = NULL;

	return new_rbt; 
}

rbt *left_rotation(rbt *r_b_t) {
	if(r_b_t != NULL && r_b_t -> right_child != NULL) {
		rbt *rbt_right_child = r_b_t -> right_child;
		r_b_t -> right_child = r_b_t -> right_child -> left_child;
		rbt_right_child -> left_child = r_b_t;
	}

	// code to update the color

	return rbt_right_child;
}

rbt *right_rotation(rbt *r_b_t) {
	if(r_b_t != NULL && r_b_t -> left_child != NULL) {
		rbt *rbt_left_child = r_b_t -> left_child;
		r_b_t -> left_child = r_b_t -> left_child -> right_child;
		rbt_left_child -> right_child = r_b_t;
	}

	// code to update the color

	return rbt_left_child;
}


int main() {


	return 0;
}

/* references:
https://en.wikipedia.org/wiki/Red–black_treehttps://en.wikipedia.org/wiki/Red–black_tree




*/
