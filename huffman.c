#include <stdio.h>
#include <stdlib.h>

typedef struct huff huff;
typedef struct hash hash;

struct huff
{
    void *item;
    int frequency;
    huff* left;
    huff* right;
};

struct hash
{
    huff * table[256];
};

huff *create_huff(unsigned char *read_byte) {
    huff *new_huff = (huff *) malloc(sizeof(huff));
    new_huff -> item = read_byte;
    new_huff -> frequency = 1;

    return new_huff;
}

hash *create_hash()
{
    hash *new_hash = (hash *) malloc(sizeof(hash));

    int i;

    for(i = 0; i < 256; i++)
    {
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

/*int get(hash_table *ht, int key) {
	int h = key % 7;

	element *head = ht -> table[h];

	while(head != NULL) {
		if(head -> key == key) {
			return head -> value;
		}

		head = head -> next;  
	}

	return -1; // error code
}*/

hash *read_archive(char *name_file)
{
    FILE *archive = fopen(name_file, "rb");
    unsigned char *read_byte = (unsigned char *) malloc(sizeof(unsigned char));

    hash *h_byte = create_hash();

    while(fscanf(archive, "%c", read_byte) != EOF)
    {
        put_hash(h_byte, read_byte);
    }

    fclose(archive);

    return h_byte;
}

int main(int argc, char *argv[]) {

    hash *h_byte = read_archive(argv[1]);

    return 0;
}
