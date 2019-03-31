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
	for(i = 0; i < 1000; i++)
	{
		aux = rand() % 256;
		byte_test = (unsigned char *) malloc(sizeof(unsigned char));
		*byte_test = (unsigned char) aux;
		
		//Teste do elemento colocado
		put_hash(h_test, byte_test);
		CU_ASSERT(element_in_hash(h_test, byte_test));
		
		if((p <= 5) && (i == sorted[p]))
		{
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
	heap *heap = create_heap(2);
	huff *sos;
	
	for(int i = 0; i < 10; i++){
		int *aux;
		*aux = rand() % 100;
		huff *node = create_node((void*)aux);
		enqueue(heap, node);
	}
	for(int i = 0; i < 10; i++)
		sos = dequeue(heap);

	sos = dequeue(heap);
	CU_ASSERT(sos == NULL);
}

void binary_tree_tests(){
	create_
	return;
}

int main(){
	srand(time(NULL));
	CU_pSuite pSuite = NULL;

	binary_tree_tests();

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

	if(NULL == CU_add_test(pSuite, "binary_tree_tests", binary_tree_tests)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	return CU_get_error();
}