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
	return;
	//CU_ASSERT(); //{sentença que vai conter uma expressão (Verdadeira ou falsa)}
	//Para testar cada aspecto da estrutura
	//Vc cria entrada necessária e testa...
}



void hash_tests(){
	hash* h_test = NULL;
	h_test = create_hash();

	CU_ASSERT(h_test != NULL); //Verificando se a hash foi criada.

	srand(time(NULL));
	unsigned char aux, *byte_test = (unsigned char *) malloc(sizeof(unsigned char));
	unsigned short i, p = 0, sorted[5];

	for (i = 0; i < 4; i++)
		sorted[i] = (rand() % 1000);

	//Adicionando 1000 bytes na hash e sorteando 5 aos quais serao posteriormente verificados.
	//Casos como estes devem ser feitos para varias estruturas.
	for(i = 0; i < 1000; i++)
	{
		aux = rand() % 256;
		*byte_test = (unsigned char) aux;
		put_hash(h_test, byte_test);

		if((p <= 5) && (i == sorted[p]))
		{
			sorted[p] = aux;
			p++;
		}
	}

	free(byte_test);
}

void heap_tests(){
	return;
}

void binary_tree_tests(){
	return;
}

int run_tests() {
	huff_tests();
	hash_tests();
	heap_tests();
	binary_tree_tests();
}

int main(){
	//Base do CUNIT
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clear_suite);
	if(pSuite == NULL){
		return CU_get_error();
	}
	
	if(NULL == CU_add_test(pSuite, "hash_tests", hash_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "huff_tests", huff_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}


	if(NULL == CU_add_test(pSuite, "heap_tests", heap_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "binary_tree_tests", binary_tree_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_cleanup_registry();
	
	return CU_get_error();
}