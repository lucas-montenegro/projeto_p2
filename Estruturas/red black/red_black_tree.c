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
 
    new_rbt -> color = false; // we first insert new_rbt as red and then we make the necessary changes
    new_rbt -> item = item;
    new_rbt -> left_child = left_child;
    new_rbt -> right_child = right_child;
    new_rbt -> parent = parent;
 
    return new_rbt;
}
 
rbt *left_rotation(rbt **root, rbt *r_b_t) {
    rbt *rbt_right_child = NULL;
 
    if(r_b_t != NULL && r_b_t -> right_child != NULL) {
        rbt_right_child = r_b_t -> right_child;
        r_b_t -> right_child = rbt_right_child -> left_child;
        rbt_right_child -> left_child = r_b_t;
    }
 
    //change the pointer of the grandparent
    if(r_b_t->parent != NULL){
        if(r_b_t == r_b_t -> parent -> left_child) {
            r_b_t -> parent -> left_child = rbt_right_child;
        }
        else {
            r_b_t -> parent -> right_child = rbt_right_child;
        }
    }
    else
        *root = rbt_right_child;
 
    //update the parents
    rbt_right_child -> parent = r_b_t -> parent;
    r_b_t -> parent = rbt_right_child;
 
    if(r_b_t -> right_child != NULL) {
        r_b_t -> right_child -> parent = r_b_t;
    }
    return rbt_right_child;
}
 
rbt *right_rotation(rbt **root, rbt *r_b_t) {
    rbt *rbt_left_child = NULL;
 
    if(r_b_t != NULL && r_b_t -> left_child != NULL) {
        rbt_left_child = r_b_t -> left_child;
        r_b_t -> left_child = rbt_left_child -> right_child;
        rbt_left_child -> right_child = r_b_t;
    }
 
    //change the pointer of the grandparent
    if(r_b_t -> parent != NULL){
        if(r_b_t == r_b_t -> parent -> left_child) {
            r_b_t -> parent -> left_child = rbt_left_child;
        }
        else {
            r_b_t -> parent -> right_child = rbt_left_child;
        }
    }
    else
        *root = rbt_left_child;
 
    //update the parents
    rbt_left_child -> parent = r_b_t -> parent;
    r_b_t -> parent = rbt_left_child;
 
    if(r_b_t -> left_child != NULL) {
        r_b_t -> left_child -> parent = r_b_t;
    }
 
    return rbt_left_child;
}
 
rbt* add(rbt **r_b_t, rbt *parent, int item) {
    if(*r_b_t == NULL){
        *r_b_t = create_red_black_tree(item, NULL, NULL, parent);
        return *r_b_t;//keeping track of the added node
    }
    else if((*r_b_t) -> item > item) {
        add(&(*r_b_t) -> left_child, *r_b_t, item);
    }
    else {
        add(&(*r_b_t) -> right_child, *r_b_t, item);
    }
}
 
rbt* search(rbt *r_b_t, int item) {
    if(r_b_t == NULL) {
        return NULL; //the node doesnt exist
    }
    else if(r_b_t -> item == item){
        return r_b_t;
    }
    else if(r_b_t -> item > item) {
        search(r_b_t -> left_child, item);
    }
    else {
        search(r_b_t -> right_child, item);
    }
}
 
void red_uncle(rbt *parent_node, rbt *uncle) {
    parent_node -> color = true; // we set the color of the parent to black
    uncle -> color = true; // we set the color of the uncle to black
    parent_node -> parent -> color = false; // we set the color of the grandparent to red and restart all the process with the grandparent
}
 
void black_uncle(rbt **root, rbt *r_b_t, rbt *parent_node, rbt *uncle) {
    if(parent_node == parent_node -> parent -> left_child && r_b_t == parent_node -> left_child) { //left left case
        parent_node = right_rotation(root, parent_node -> parent); // first I rotate the grandparent
        parent_node -> color = true;
        parent_node -> right_child -> color = false;
    }
    else if(parent_node == parent_node -> parent -> left_child && r_b_t == parent_node -> right_child) { //left right case
        parent_node = left_rotation(root, parent_node); // first I rotate the parent
        parent_node = right_rotation(root, parent_node -> parent); // then I rotate the grandparent
        parent_node -> color = true;
        parent_node -> right_child -> color = false;
    }
    else if(parent_node == parent_node -> parent -> right_child && r_b_t == parent_node -> right_child) { //right right case
        parent_node = left_rotation(root, parent_node -> parent); // first I rotate the grandparent
        parent_node -> color = true;
        parent_node -> left_child -> color = false;
    }
    else if(parent_node == parent_node -> parent -> right_child && r_b_t == parent_node -> left_child) { //right left case
        parent_node = right_rotation(root, parent_node); // first I rotate the parent
        parent_node = left_rotation(root, parent_node -> parent); // then I rotate the grandparent
        parent_node -> color = true;
        parent_node -> left_child -> color = false;
    }
}
 
void fix(rbt **root, rbt *r_b_t) {
    rbt *parent_node = r_b_t -> parent;
 
    if(parent_node != NULL && parent_node -> color == false && parent_node -> parent != NULL) {
    //node's parent is red and there is a grandparent
        rbt *uncle;
 
        if(parent_node == parent_node -> parent -> left_child) { //parent is the left son of the grandparent
            uncle = parent_node -> parent -> right_child;
        }
        else if (parent_node == parent_node -> parent-> right_child) { //parent is the right son of the grandparent
            uncle = parent_node -> parent -> left_child;
        }
 
        if(uncle != NULL && uncle -> color == false) {
            red_uncle(parent_node, uncle);
            fix(root, parent_node -> parent);
        }
        else if(uncle == NULL || uncle -> color == true) {
            black_uncle(root, r_b_t, parent_node, uncle);
        }
    }
    
    (*root) -> color = true;//keeps the root always black
}
 
rbt *add_and_fix(rbt *root, int item) {
    rbt *added = NULL;
    added = add(&root, root, item);
 
    fix(&root, added);
 
    return root;
}
 
void print_tree_pre_order(rbt *r_b_t) {
    if(r_b_t != NULL){
        if(r_b_t -> color == true) {
            printf("black-> ");
        }
        else {
            printf("red-> ");
        }
 
        printf("%d\n", r_b_t -> item);
        print_tree_pre_order(r_b_t -> left_child);
        print_tree_pre_order(r_b_t -> right_child);
    }
}
 
int main() {
    int item;
 
    rbt *root = create_empty_red_black_tree();
 
    while(scanf("%d", &item) != EOF) {
        root = add_and_fix(root, item);
    }
 
    print_tree_pre_order(root); //tests
 
    return 0;
}
