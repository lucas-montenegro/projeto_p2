#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#include "hash.h"

hash *create_hash(){
    hash *new_hash = (hash *) malloc(sizeof(hash));
    int i;

    for(i = 0; i < 256; i++) {
        new_hash -> table[i] = NULL;
    }

    return new_hash;
}

void put_hash(hash *hash, unsigned char *read_byte) {
    if(hash -> table[*read_byte] == NULL) {
        huff *huff = create_node((void*)read_byte);
        hash -> table[*read_byte] = huff;

        return;
    }

    hash -> table[*read_byte] -> frequency++;

    return;
}

short element_in_hash(hash *hash, unsigned char *element) {
    if(hash -> table[*element] == NULL)
        return 0;
    else
        return 1;
}
