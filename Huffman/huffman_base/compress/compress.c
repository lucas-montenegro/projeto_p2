#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../huffman.h"
#include "../../structures/hash/hash.h"
#include "../../structures/heap/heap.h"
#include "../../structures/binary_tree/binary_tree.h"
#include "compress.h"

void treat_string(char **name_file){
    unsigned short size_1 = strlen(*name_file), size_2 = size_1 + 4;
    char *new_string = (char*) calloc(size_2, sizeof(char));

    for(int i = 0; i < size_1; i++){
        if((*name_file)[i] == '.')
            break;
        new_string[i] = (*name_file)[i];
    }
    strcat(new_string, ".huff");
    *name_file = new_string;
}

unsigned short set_bit(unsigned short byte, unsigned short i){
    i = 15 - i;
    unsigned short mask = 1 << i;
    return (mask | byte);
}

void set_new_byte(huff *huff, unsigned short count, unsigned short byte){
    unsigned short *aux = (unsigned short*) malloc(sizeof(unsigned short));
    *aux = byte >> (16 - count);
    huff->new_byte = (void*)aux;

    if(count > 0)
        huff->byte_size = count;
}

void set_nodes(FILE *file, huff *huff, unsigned short byte, unsigned short *size_tree, unsigned short count){
    *size_tree += 1;

    if(huff->left == NULL && huff->right == NULL){
        set_new_byte(huff, count, byte);
        unsigned char aux = *((unsigned char *) huff->item);
        if(aux == '*' || aux == '\\')
        {
            fprintf(file,"\\");
            *size_tree += 1;
        }
        fprintf(file, "%c", aux);
        return;
    }

    fprintf(file, "%c", *((unsigned char *) huff->item));

    set_nodes(file, huff->left, byte, size_tree, count + 1);
    byte = set_bit(byte, count);
    set_nodes(file, huff->right, byte, size_tree, count + 1);
}

void compress(char *name_file){
    hash *h_byte = read_file(name_file);
    heap *h = create_heap(2);
    huff *huff_tree = build_tree(h, h_byte);
    if(huff_tree == NULL)
        return;


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


hash *read_file(char *name_file){
    FILE *file = fopen(name_file, "rb");
    hash *h_byte = create_hash();
    unsigned char *byte = (unsigned char*)malloc(sizeof(unsigned char));

    while(1) {
        if(fscanf(file, "%c", byte) == EOF)
            break;
        if(element_in_hash(h_byte, byte))
            put_hash(h_byte, byte);
        else{
            unsigned char *read_byte = (unsigned char*)malloc(sizeof(unsigned char));
            *read_byte = *byte;
            put_hash(h_byte, read_byte);
        }
    }
    fclose(file);

    return h_byte;
}

unsigned short read_write_compress(FILE *file_write, FILE *file_read, hash *h_byte){
    unsigned short count, current_index, mod, aux, byte_m;
    unsigned char byte, byte_t;

    while(feof(file_read) == 0) {
        byte_t = BYTE_ZERO;
        count = 0;

        while(count < 8) {
            if (fscanf(file_read, "%c", &byte) == EOF)
                break;

            aux = *((unsigned short *) h_byte -> table[(unsigned short) byte] -> new_byte);
            byte_m = aux;
            current_index = count + h_byte->table[byte] -> byte_size;
            if (current_index > 8) {
                if(current_index < 16) {
                    mod = current_index % 8;
                    count = mod;
                    byte_m >>= mod;
                    byte_t = byte_t | ((unsigned char)byte_m);

                    fprintf(file_write, "%c", byte_t);

                    byte_t = BYTE_ZERO;
                    byte_m = aux;
                    byte_m <<= (16 - mod);
                    byte_m >>= 8;
                }
                else {
                    byte_m >>= 8;
                    mod = current_index % 8;
                    byte_m >>= mod;

                    byte_t = byte_t | ((unsigned char)byte_m); // primeiro byte
                    fprintf(file_write, "%c", byte_t);

                    byte_t = BYTE_ZERO;
                    byte_m = aux;
                    byte_m <<= (16 - (h_byte->table[byte]->byte_size - (8 - count)));
                    byte_m >>= 8;

                    byte_t = byte_t | ((unsigned char)byte_m); // segundo byte
                    fprintf(file_write, "%c", byte_t);

                    byte_t = BYTE_ZERO;
                    byte_m = aux;
                    byte_m <<= (16 - mod); //criacao do terceiro byte
                    byte_m >>= 8;
                    count = mod;
                }
            }
            else {
                byte_m <<= (8 - current_index);
                count += h_byte->table[byte]->byte_size;
            }

            byte_t = byte_t | ((unsigned char)byte_m);
        }

        fprintf(file_write, "%c", byte_t);
    }

    return (8 - count);
}
