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

extern unsigned char set_bit(unsigned char byte, unsigned short i);

extern void set_nodes(huff *huff, unsigned char byte, unsigned short count);
