typedef struct huff{
    void *item;
    void *new_byte;//new encoded byte
    unsigned short byte_size;
    long long int frequency;
    struct huff *left;
    struct huff *right;
}huff;

extern huff* create_node(void *item);

extern huff* merge_nodes(huff *left, huff *right);
