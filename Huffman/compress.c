#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "hash.h"
#include "heap.h"
#include "compress.h"


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

    // printf("Hash:\n");
    // for(int i = 0; i < 257; i++){
    //     if(h_byte -> table[i] != NULL) {
    //         printf("%d -> %x -> %d\n", *(unsigned char *)h_byte->table[i]->item, *(unsigned char *)h_byte->table[i]->item, h_byte->table[i]->frequency);
    //     }
    // }
    
    // printf("Árvore:\n");
    // pre_order(huff_tree);
    
    FILE *file_read = fopen(name_file, "rb");
    
    treat_string(&name_file);
    FILE *file_write = fopen(name_file, "wb");
    
    fprintf(file_write, "%c%c", BYTE_ZERO, BYTE_ZERO);
    
    unsigned short size_tree = 0, trash;
    set_nodes(file_write, huff_tree, BYTE_ZERO, &size_tree, 0);
    trash = read_write_compress(file_write, file_read, h_byte);

    if(size_tree >= 8192)
    {
        printf("Arvore maior que o cabeçalho comporta!!\n");

        return;
    }

    unsigned char byte_1 = (((unsigned char) trash) << 5);
    unsigned char byte_2 = ((((unsigned char) (size_tree >> 8)) << 3) >> 3);

    byte_1 = byte_1 | byte_2;    
    byte_2 = ((unsigned char)((size_tree << 8) >> 8));

    rewind(file_write);
    fprintf(file_write, "%c%c", byte_1, byte_2);
}