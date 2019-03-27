typedef struct binary_t{
	void *item;
	struct binary_t *left;
	struct binary_t *right;
}binary_t;

extern binary_t *create_binary_tree(unsigned char byte, binary_t *left, binary_t* right);
