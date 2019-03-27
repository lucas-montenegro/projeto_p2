#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

//não defini o strut aqui pois ele precisava ser definido na header, ja que funçoes de heap usam o sizeof de huff
//e o compilador de c interpreta estruturas definidas na header como incompletas

huff* create_node(void *item){
    huff *new_node = (huff*) malloc(sizeof(huff));
    new_node->item = item;
    new_node->new_byte = NULL;
    new_node->byte_size = 1;
    new_node->frequency = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

huff* merge_nodes(huff *left, huff *right){
    huff *new = (huff*) malloc(sizeof(huff));
    unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));
    *aux = '*';
    new->item = (void*)aux;
    new->frequency = (left->frequency)+(right->frequency);
    new->left = left;
    new->right = right;
    return new;
}
