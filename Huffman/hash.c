#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#include "hash.h"
#include "descompress.h"

#define BYTE_ZERO 0

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

hash *read_archive(char *name_file) {
    FILE *archive = fopen(name_file, "rb");
    hash *h_byte = create_hash();

    while(1) {
        unsigned char *read_byte = (unsigned char *) malloc(sizeof(unsigned char));
        if(fscanf(archive, "%c", read_byte) == EOF)
            break;
        put_hash(h_byte, read_byte);
    }
    fclose(archive);

    return h_byte;
}

unsigned short read_write_compress(FILE *file_write, FILE *file_read, hash *h_byte){
    unsigned short count, i_aux, resto, aux, byte_m;
    unsigned char byte, byte_t;

    while(feof(file_read) == 0) {
        byte_t = BYTE_ZERO;
        count = 0;

        while(count < 8) {
            if (fscanf(file_read, "%c", &byte) == EOF)
                break;

            aux = *((unsigned short *) h_byte -> table[(unsigned short) byte] -> new_byte);
            byte_m = aux;
            i_aux = count + h_byte->table[byte] -> byte_size;
            if (i_aux > 8) {
                if(i_aux < 16) {
                    count = i_aux % 8;
                    resto = i_aux % 8;
                    byte_m >>= resto;
                    byte_t = byte_t | ((unsigned char)byte_m);

                    fprintf(file_write, "%c", byte_t);

                    byte_t = BYTE_ZERO;
                    byte_m = aux;
                    byte_m <<= (16 - resto);
                    byte_m >>= 8;
                }
                else {
                    byte_m >>= 8;
                    resto = i_aux % 8;
                    byte_m >>= resto;

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
                    byte_m <<= (16 - resto); //criacao do terceiro byte
                    byte_m >>= 8;
                    count = resto;
                }
            }
            else {
                byte_m <<= (8 - i_aux);
                count += h_byte->table[byte]->byte_size;
            }

            byte_t = byte_t | ((unsigned char)byte_m);
        }

        fprintf(file_write, "%c", byte_t);
    }

    return (8 - count);
}
