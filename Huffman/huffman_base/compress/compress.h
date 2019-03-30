#define BYTE_ZERO 0

extern void treat_string(char **name_file);

extern unsigned short set_bit(unsigned short byte, unsigned short i);

extern void set_new_byte(huff *huff, unsigned short count, unsigned short byte);

extern void set_nodes(FILE *file, huff *huff, unsigned short byte, unsigned short *size_tree, unsigned short count);

extern void compress(char *name_file);

extern hash *read_file(char *name_file);

extern unsigned short read_write_compress(FILE *file_write, FILE *file_read, hash *h_byte);
