#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

#define BYTE_ZERO 0

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

unsigned short set_bit(unsigned short byte, unsigned short i){
    i = 15 - i;
    unsigned short mask = 1 << i;
    return (mask | byte);
}

void set_nodes(FILE *file, huff *huff, unsigned short byte, unsigned short *size_tree, unsigned short count){
    *size_tree += 1;

    if(huff->left == NULL && huff->right == NULL) {
        unsigned short *aux = (unsigned short*) malloc(sizeof(unsigned short));
        byte = byte >> (16 - count);
        *aux = byte;
        huff->new_byte = (void*)aux;

        if(count > 0)
            huff->byte_size = count;

        unsigned char aux_2 = *((unsigned char *) huff->item);

        if(aux_2 == '*' || aux_2 == '\\')
            fprintf(file,"\\");

        fprintf(file, "%c", aux_2);

        return;
    }

    fprintf(file, "%c", *((unsigned char *) huff->item));

    set_nodes(file, huff->left, byte, size_tree, count + 1);
    byte = set_bit(byte, count);
    set_nodes(file, huff->right, byte, size_tree, count + 1);
}
