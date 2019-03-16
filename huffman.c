#include <stdio.h>
#include <stdlib.h>

typedef struct huff huff;
typedef struct hash hash;

struct huff {
    void *item;
    int frequency;
    huff* left;
    huff* right;
};

struct hash {
    huff * table[256];
};

huff *create_huff(unsigned char *read_byte) {
    huff *new_huff = (huff *) malloc(sizeof(huff));
    new_huff -> item = (unsigned char *) read_byte;
    new_huff -> frequency = 1;
    new_huff -> left = NULL;
    new_huff -> right = NULL;

    return new_huff;
}

hash *create_hash() {
    hash *new_hash = (hash *) malloc(sizeof(hash));
    int i;

    for(i = 0; i < 256; i++) {
        new_hash -> table[i] = NULL;
    }

    return new_hash;
}

void put_hash(hash *hash, unsigned char *read_byte) {
    if(hash -> table[*read_byte] == NULL) {
        huff *huff = create_huff(read_byte);
        hash -> table[*read_byte] = huff;

        return;
    }

    hash -> table[*read_byte] -> frequency++;

    return;
}

hash *read_archive(char *name_file) {
    FILE *archive = fopen(name_file, "rb");
    //unsigned char *read_byte = (unsigned char *) malloc(sizeof(unsigned char));

    hash *h_byte = create_hash();

    while(1){
        unsigned char *read_byte = (unsigned char *) malloc(sizeof(unsigned char));
        if(fscanf(archive, "%c", read_byte) == EOF)
            break;
        put_hash(h_byte, read_byte);
    }

    int i = 0;
    while(i < 256) {
        if(h_byte -> table[i] != NULL) {
            printf("%s -> %x -> %d\n", (unsigned char *)h_byte->table[i]->item, *(unsigned char *)h_byte->table[i]->item, h_byte->table[i]->frequency);
        }
        i++;
    }

    fclose(archive);

    return h_byte;
}

int main(int argc, char *argv[]) {
    hash *h_byte = read_archive(argv[1]);

    return 0;
}
