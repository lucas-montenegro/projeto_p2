#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct red_black_tree rbt;

struct red_black_tree { 
	bool color; // defines the color red or black, true for black and false for red
	int item;
	rbt *parent;
	rbt *right_child;
	rbt *left_child;
};

rbt *create_empty_red_black_tree() {
	rbt *new_rbt = (rbt *) malloc(sizeof(rbt));
	new_rbt = NULL;

	return new_rbt; 
}

rbt* create_red_black_tree(int item, rbt *left_child, rbt *right_child, rbt *parent) {
    rbt *new_rbt = (rbt *) malloc(sizeof(rbt));

    if(parent == NULL) {  // new_rbt is the root
        new_rbt -> color = true;
    }
    else {
        new_rbt -> color = false; // we first insert new_rbt as red and then we make the necessary changes
    }

    new_rbt -> item = item;
    new_rbt -> left_child = left_child;
    new_rbt -> right_child = right_child;
    new_rbt -> parent = parent;

    return new_rbt;
}

bool update_color(rbt *r_b_t) {
	if(r_b_t -> color == false) { // change from red to black
		return true;
	}

	return false; // change from black to red
}

rbt *left_rotation(rbt *r_b_t) {
	rbt *rbt_right_child = NULL;

	if(r_b_t != NULL && r_b_t -> right_child != NULL) {
		rbt_right_child = r_b_t -> right_child;
		r_b_t -> right_child = rbt_right_child -> left_child;
		rbt_right_child -> left_child = r_b_t;
	}

	return rbt_right_child;
}

rbt *right_rotation(rbt *r_b_t) {
	rbt *rbt_left_child = NULL;

	if(r_b_t != NULL && r_b_t -> left_child != NULL) {
		rbt_left_child = r_b_t -> left_child;
		r_b_t -> left_child = rbt_left_child -> right_child;
		rbt_left_child -> right_child = r_b_t;
	}

	return rbt_left_child;
}

rbt* add(rbt *r_b_t, int item) {
    if(r_b_t == NULL){
        rbt *new_rbt = create_red_black_tree(item, NULL, NULL, r_b_t);
        return new_rbt;
    }
    else if(r_b_t -> item < item) {
        r_b_t -> left_child = add(r_b_t -> left_child, item);
    }
    else {
        r_b_t -> right_child = add(r_b_t -> right_child, item);
    }
}

void red_uncle(rbt *parent_node, rbt *uncle) {
	parent_node -> color = true; // we set the color of the parent to black 
	uncle -> color = true; // we set the color of the uncle to black
	parent_node -> parent -> color = false; // we set the color of the grandparent to red and restart all the process with the grandparent
}

void black_uncle(rbt *r_b_t, rbt *parent_node, rbt *uncle) {
	//rbt *grandparent;
	//Left Left Case (p is left child of g and x is left child of p)
	//Left Right Case (p is left child of g and x is right child of p)
	/*if(parent_node == parent_node -> parent -> left_child && r_b_t == parent_node -> left_child) { //left left case

	}
	else if(parent_node == parent_node -> parent -> left_child && r_b_t == parent_node -> right_child) { //left right case

	}
	else if() {

	}
	else if() {

	}*/
}

void fix(rbt *r_b_t) {
    rbt *parent_node = r_b_t -> parent;

    if(parent_node == NULL && r_b_t -> color == false) { //root and its color is red
        r_b_t -> color = true;
    }
    else if(parent_node != NULL && parent_node -> color == false) { //node's parent is red and node isn't root
    	if(parent_node -> parent != NULL) { // there is a grandparent
            rbt *uncle;

            if(parent_node == parent_node -> parent -> left_child) { //parent is the left son of the grandparent
                uncle = parent_node -> parent -> right_child;
            }
            else if (parent_node == parent_node -> parent-> right_child) { //parent is the right son of the grandparent
                uncle = parent_node -> parent-> left_child;
            }

            if(uncle != NULL && uncle -> color == false) {
            	red_uncle(parent_node, uncle);
            	fix(parent_node -> parent);
            }
            else {
            	black_uncle(r_b_t, parent_node, uncle);
            }
        }
    }
}

void add_and_fix(rbt *r_b_t, int item) {
    rbt *added = NULL;

    added = add(r_b_t, item);
    fix(added);
}

void print_tree_pre_order(rbt *r_b_t) {
    if(r_b_t != NULL){
        if(r_b_t -> color)
            printf("black-> ");
        else
            printf("red-> ");

        printf("%d\n", r_b_t -> item);
        print_tree_pre_order(r_b_t -> left_child);
        print_tree_pre_order(r_b_t -> right_child);

    }
}

int main() {
	int item;

	rbt *r_b_t = create_empty_red_black_tree();

	while(scanf("%d", &item) != EOF) {
		add_and_fix(r_b_t, item);
	}


	return 0;
}

/* references:
https://en.wikipedia.org/wiki/Red–black_treehttps://en.wikipedia.org/wiki/Red–black_tree
https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
*/
