#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"

//não defini o strut aqui pois ele precisava ser definido na header, ja que funçoes de heap usam o sizeof de huff
//e o compilador de c interpreta estruturas definidas na header como incompletas

huff* create_node(void *item){
    huff *newNode = (huff*) malloc(sizeof(huff));
    newNode->item = item;
    newNode->frequency = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

huff* merge_nodes(huff *left, huff *right){
    huff *new = (huff*) malloc(sizeof(huff));
    new->item = (char*) '*';
    new->frequency = (left->frequency)+(right->frequency);
    new->left = left;
    new->right = right;
    return new;
}

void pre_order(huff *huff){
    if(huff != NULL){
        printf("frequency = %d\n", huff->frequency);
        pre_order(huff->left);
        pre_order(huff->right);
    }
}
