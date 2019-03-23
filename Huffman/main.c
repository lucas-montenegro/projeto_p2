#include <stdlib.h>
#include <stdio.h>

#include "huffman.h"
#include "hash.h"
#include "heap.h"

int main(int argc, char *argv[]) {
    hash *h_byte = read_archive(argv[1]);
    heap *h = create_heap(257);
    huff *huff_tree = build_tree(h, h_byte);
    printf("Hash:\n");
    for(int i = 0; i < 257; i++){
        if(h_byte -> table[i] != NULL) {
            printf("%s -> %x -> %d\n", (unsigned char *)h_byte->table[i]->item, *(unsigned char *)h_byte->table[i]->item, h_byte->table[i]->frequency);
        }
    }

    compress(argv[1], huff_tree);
    
    printf("Árvore:\n");
    pre_order(huff_tree);

    return 0;
}
