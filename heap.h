typedef struct heap heap;

extern heap* create_heap(int size);

extern void realloc_heap(heap *heap);

extern int get_parent_index(int index);

extern int get_left_index(int index);

extern int get_right_index(int index);

extern void swap(heap *heap, int i, int j);

extern void enqueue(heap *heap, huff *node);

extern void min_heapify(heap *heap, int index);

extern huff* dequeue(heap *heap);

extern void print_heap(huff **data, int index, int size);

extern huff* build_tree(heap *heap, hash *hash);
