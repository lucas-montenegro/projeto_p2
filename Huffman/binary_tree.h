typedef struct b_t{
    void *item;
    struct b_t* left;
    struct b_t* right;
} binary_t;

extern binary_t *create_binary_tree(unsigned char byte, binary_t *left, binary_t* right);

extern void bt_print (binary_t *bt);