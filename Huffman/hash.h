typedef struct hash{
    huff *table[256];
}hash;

extern hash *create_hash();

extern void put_hash(hash *hash, unsigned char *read_byte);
