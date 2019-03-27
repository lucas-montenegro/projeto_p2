extern void create_t_reading(binary_t **bt, FILE *file, short size, short *count);

extern void descompress(char *name_file);

extern void file_extension(char **name_file);

extern void read_descompress(FILE *file, FILE *new_file, binary_t *b_tree, unsigned short trash);

extern unsigned char read_bit(unsigned char byte, int cont);
