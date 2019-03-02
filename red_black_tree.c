#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct red_black_node{
    bool color;//false -> red; true -> black
    int item;
    struct red_black_node *left;
    struct red_black_node *right;
    struct red_black_node *parent;
}red_black_node;

red_black_node* create_red_black_tree(int item, red_black_node *left, red_black_node *right, red_black_node *parent){
    red_black_node *new = (red_black_node*) malloc(sizeof(red_black_node));
    if(parent == NULL)
        new->color = true;
    else
        new->color = false;
    new->item = item;
    new->left = left;
    new->right = right;
    new->parent = parent;
    return new;
}

void add(red_black_node **rbt, int item, red_black_node *parent){
    if(*rbt == NULL)
        *rbt = create_red_black_tree(item, NULL, NULL, parent);
    else if((*rbt)->item > item)
        add(&(*rbt)->left, item, *rbt);
    else
        add(&(*rbt)->right, item, *rbt);
}

void print_tree_in_order(red_black_node *rbt){
    if(rbt != NULL){
        print_tree_in_order(rbt->left);
        if(rbt->color)
            printf("black-> ");
        else
            printf("red-> ");
        printf("%d\n", rbt->item);
        print_tree_in_order(rbt->right);
    }
}

void print_tree_pre_order(red_black_node *rbt){
    if(rbt != NULL){
        if(rbt->color)
            printf("black-> ");
        else
            printf("red-> ");
        printf("%d\n", rbt->item);
        print_tree_pre_order(rbt->left);
        print_tree_pre_order(rbt->right);
    }
}

int main(){
    red_black_node *rbt = NULL;
    add(&rbt, 1, rbt);

    return 0;
}
