COMPRESS = huffman_base/compress/compress.c
DESCOMPRESS = huffman_base/descompress/descompress.c
HUFFMAN = huffman_base/huffman.c
BINARY_TREE = structures/binary_tree/binary_tree.c
HASH = structures/hash/hash.c
HEAP = structures/heap/heap.c
TEST = test/test_cunit.c
MAIN = huffman_base/main.c

compile_huffman:
	gcc $(COMPRESS) $(DESCOMPRESS) $(HUFFMAN) $(BINARY_TREE) $(HASH) $(HEAP) $(MAIN) -o huffman

compile_test:
	gcc $(TEST) $(HUFFMAN) $(BINARY_TREE) $(HASH) $(HEAP) $(TEST) -o test_cunit -lcunit
