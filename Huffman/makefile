COMPRESS = huffman_base/compress/compress.c
DESCOMPRESS = huffman_base/descompress/descompress.c
HUFFMAN = huffman_base/huffman.c
BINARY_TREE = structures/binary_tree/binary_tree.c
HASH = structures/hash/hash.c
HEAP = structures/heap/heap.c
TEST_C = test/test_cunit.c
TEST_H = test/test_txt_huffman.c
MAIN = huffman_base/main.c

compile_huffman:
	gcc $(COMPRESS) $(DESCOMPRESS) $(HUFFMAN) $(BINARY_TREE) $(HASH) $(HEAP) $(MAIN) -o huffman

compile_test_c:
	gcc $(TEST) $(HUFFMAN) $(BINARY_TREE) $(HASH) $(HEAP) $(TEST_C) -o test_cunit -lcunit

compile_test_h_t:
	gcc $(COMPRESS) $(DESCOMPRESS) $(HUFFMAN) $(BINARY_TREE) $(HASH) $(HEAP) $(TEST_H) -o test_huff_text
