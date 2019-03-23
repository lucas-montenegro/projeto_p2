#include <stdio.h>
#include <stdlib.h>

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

void pre_order(huff *huff){
    if(huff != NULL){
        printf("%c -> %d\n", *((unsigned char*)huff->item), huff->frequency);
        pre_order(huff->left);
        pre_order(huff->right);
    }
}

unsigned char set_bit(unsigned char byte, unsigned short i){
    unsigned char mask = 1 << i;
    return mask | byte;
}

void set_nodes(huff *huff, unsigned char byte, unsigned short count){
    if(huff->left == NULL && huff->right == NULL){
        unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));
        *aux = byte;

        huff->new_byte = (void*)aux;
        if(count > 0)
            huff->byte_size = count;
        return;
    }
    set_nodes(huff->left, byte, count + 1);
    byte = set_bit(byte, count);
    set_nodes(huff->right, byte, count + 1);
}
/*
                                *                           3
                            *       3
                        1       2


count = 0; byte = 00000000 *;
count = 1; byte = 00000000 *;
count = 2; byte = 00000000 1; byte de 1 = 00000000; byte_size = 2;
count = 1; byte = 00000010 *;
count = 2; byte = 00000010 2; byte de 2 = 00000010; byte_size = 2;
count = 1; byte = 00000010 *;
count = 0; byte = 00000001 *;
count = 1; byte = 00000001 3; byte de 3 = 00000001; byte_size = 1;
*/
