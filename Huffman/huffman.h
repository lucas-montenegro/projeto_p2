typedef struct huff{
    void *item;
    int frequency;
    struct huff *left;
    struct huff *right;
}huff;

extern huff* create_node(void *item);

extern huff* merge_nodes(huff *left, huff *right);

extern void pre_order(huff *huffman);
