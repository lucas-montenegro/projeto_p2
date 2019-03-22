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
        huff *huff = create_node((char*)read_byte);
        hash -> table[*read_byte] = huff;

        return;
    }

    hash -> table[*read_byte] -> frequency++;

    return;
}

hash *read_archive(char *name_file) {
    FILE *archive = fopen(name_file, "rb");
    hash *h_byte = create_hash();

    while(1){
        unsigned char *read_byte = (unsigned char *) malloc(sizeof(unsigned char));
        if(fscanf(archive, "%c", read_byte) == EOF)
            break;
        put_hash(h_byte, read_byte);
    }
    fclose(archive);

    return h_byte;
}
