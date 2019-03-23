#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "hash.h"
#include "heap.h"

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

unsigned char set_bit(unsigned char byte, unsigned short i){
    unsigned char mask = 1 << i;
    return mask | byte;
}

void set_nodes(FILE *file, huff *huff, unsigned char byte, unsigned short *size_tree, unsigned short count){
    *size_tree += 1;

    if(huff->left == NULL && huff->right == NULL){
        unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));
        *aux = byte;

        huff->new_byte = (void*)aux;
        if(count > 0)
            huff->byte_size = count;

        unsigned char aux_2 = *((unsigned char *) huff->item);
        
        if(aux_2 == '*' || aux_2 == '\\')
            fprintf(file,"%c", '\\');

        fprintf(file, "%c", aux_2);

        return;
    }

    fprintf(file, "%c", *((unsigned char *) huff->item));

    set_nodes(file, huff->left, byte, size_tree, count + 1);
    byte = set_bit(byte, count);
    set_nodes(file, huff->right, byte, size_tree, count + 1);
}

void treat_string(char **name_file)
{
    unsigned short s1_string = strlen(*name_file), s2_string = s1_string + 4, i, ver = 0; 
    char *new_string = (char *)malloc(sizeof(char) * s2_string); 
    for (i = 0; i < s2_string; i++)
        new_string[i] = '\0';

    for(i = 0; i < s1_string; i++){
        if((*name_file)[i] == '.')
            break;
        
        new_string[i] = (*name_file)[i];
    }

    strcat(new_string, ".huff");

    *name_file = new_string;
}   

void compress(char *name_file){
    hash *h_byte = read_archive(name_file);
    heap *h = create_heap(257);
    huff *huff_tree = build_tree(h, h_byte);

    printf("Hash:\n");
    for(int i = 0; i < 257; i++){
        if(h_byte -> table[i] != NULL) {
            printf("%s -> %x -> %d\n", (unsigned char *)h_byte->table[i]->item, *(unsigned char *)h_byte->table[i]->item, h_byte->table[i]->frequency);
        }
    }
    
    printf("Árvore:\n");
    pre_order(huff_tree);

    treat_string(&name_file);
    FILE *file = fopen(name_file, "wb");
    unsigned short size_tree = 0;
    set_nodes(file, huff_tree, BYTE_ZERO, &size_tree, 0);

    if(size_tree >= 8192)
    {
        printf("Arvore maior que o cabeçalho!!\n");

        return;
    }

    //rewind(file);
    //fprintf(file, "%c", BYTE_ZERO);
}
