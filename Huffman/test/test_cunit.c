#include <stdio.h>
#include <stdlib.h>
#include "../huffman_base/huffman.h"
#include "../structures/hash/hash.h"
#include "../structures/heap/heap.h"
#include "../structures/binary_tree/binary_tree.h"
#include <time.h>
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

int init_suite(void) {
	return 0;
}

int clear_suite(void) {
	return 0;
}

int pre_order_tree(binary_t *bt, char *str, unsigned short size, unsigned short *count) {
	if (bt == NULL)
		return 0;
	else if((*count > size) || (*((char *)bt->item) != str[*count]))
		return 1;

	*count += 1;
	pre_order_tree (bt->left, str, size, count);
	pre_order_tree (bt->right, str, size, count);
}

//Testar criação das estruturas e funções principais (Chamar CU_ASSERT para cada aspecto testado)
//Para cada estrutura

void huff_tests(){
	huff *node_1 = create_node(NULL);
	huff *node_2 = create_node(NULL);
	huff *sum_nodes = merge_nodes(node_1, node_2);
	CU_ASSERT(sum_nodes->frequency == 2);
}



void hash_tests(){
	hash* h_test = NULL;
	h_test = create_hash();

	CU_ASSERT(h_test != NULL); //Verificando se a hash foi criada.

	srand(time(NULL));
	unsigned char aux, *byte_test;
	unsigned short i, p = 0, sorted[5];

	for (i = 0; i < 4; i++)
		sorted[i] = (rand() % 1000);

	//Adicionando 1000 bytes na hash e sorteando 5 aos quais serao posteriormente verificados.
	//Casos como estes devem ser feitos para varias estruturas.
	for(i = 0; i < 1000; i++){
		aux = rand() % 256;
		byte_test = (unsigned char *) malloc(sizeof(unsigned char));
		*byte_test = (unsigned char) aux;

		//Teste do elemento colocado
		put_hash(h_test, byte_test);
		CU_ASSERT(element_in_hash(h_test, byte_test));

		if((p <= 5) && (i == sorted[p])){
			sorted[p] = aux;
			p++;
		}
	}

	//Testes de elementos sorteados
	byte_test = (unsigned char *) malloc(sizeof(unsigned char));
	for(i = 0; i < 5; i++){
		*byte_test = (unsigned char) sorted[p];

		CU_ASSERT(element_in_hash(h_test, byte_test));
	}

	free(byte_test);
}
void heap_tests(){
	heap *h = create_heap(2);
	huff *sos, *idk, *merged, *root;

	for(int i = 0; i < 10; i++){
		int *aux = (int*) malloc(sizeof(int));
		*aux = rand() % 100;
		huff *node = create_node((void*)aux);
		enqueue(h, node);
	}
	huff* test = h->data[1];
	CU_ASSERT(test != NULL);
	while(h->items > 1)
	{
		sos = dequeue(h), idk = dequeue(h);
		merged = merge_nodes(sos, idk);
		enqueue(h, merged);
	}
	root = dequeue(h);
	sos = dequeue(h);
	CU_ASSERT(sos == NULL);	
	CU_ASSERT(root != NULL);
	CU_ASSERT(root->frequency > root->left->frequency);
	CU_ASSERT(root->frequency > root->right->frequency);
	
}

void b_tests(){
	unsigned short count = 0;
	binary_t * binary_tree;
	char *str = malloc(sizeof(char) * 13);
	str = "***AB*TR**nlp";

	binary_tree = create_binary_tree(
		str[0],

		create_binary_tree(
			str[1],

			create_binary_tree(
				str[2],

				create_binary_tree(
					str[3],
					NULL,
					NULL
				) ,

				create_binary_tree(
					str[4],
					NULL,
					NULL
				)
			),

			create_binary_tree(
				str[5],

				create_binary_tree(
					str[6],
					NULL,
					NULL
				) ,

				create_binary_tree(
					str[7],
					NULL,
					NULL
				)
			)
		) ,

		create_binary_tree(
			str[8],

			create_binary_tree(
				str[9],

				create_binary_tree (
					str[10],
					NULL,
					NULL
				) ,

				create_binary_tree (
					str[11],
					NULL,
					NULL
				)
			),

			create_binary_tree (
				str[12],
				NULL,
				NULL
			)
		)
	) ;

	CU_ASSERT(binary_tree != NULL);
	CU_ASSERT(pre_order_tree(binary_tree, str, 12, &count) == 0);
}

int main(){
	srand(time(NULL));
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_basic_set_mode(CU_BRM_VERBOSE);

	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clear_suite);
	if(pSuite == NULL){
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "hash_tests", hash_tests)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "huff_tests", huff_tests)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "heap_tests", heap_tests)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "b_tests", b_tests)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	return CU_get_error();
}
