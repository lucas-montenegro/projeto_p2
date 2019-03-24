typedef struct hash{
    huff *table[256];
}hash;

extern hash *create_hash();

extern void put_hash(hash *hash, unsigned char *read_byte);

extern hash *read_archive(char *name_file);

extern unsigned short read_write_compress(FILE *file_write, FILE *file_read, hash *h_byte);