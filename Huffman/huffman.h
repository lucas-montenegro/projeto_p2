typedef struct huff{
    void *item;
    void *new_byte;//new encoded byte
    unsigned short byte_size;
    int frequency;
    struct huff *left;
    struct huff *right;
}huff;

extern huff* create_node(void *item);

extern huff* merge_nodes(huff *left, huff *right);

extern void pre_order(huff *huffman);

extern unsigned short set_bit(unsigned short byte, unsigned short i);

extern void set_nodes(FILE *file, huff *huff, unsigned short byte, unsigned short *size_tree, unsigned short count);

extern void treat_string(char **name_file);

extern void compress(char *name_file);