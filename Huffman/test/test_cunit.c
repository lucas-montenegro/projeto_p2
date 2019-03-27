#include "../huffman_base/huffman.h"
#include "../structures/hash/hash.h"
#include "../structures/heap/heap.h"
#include "../structures/binary_tree/binary_tree.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

int init_suite(void) {
	return 0;
}

int clear_suite(void) {
	return 0;
}

int equals(DATATYPE d1, DATATYPE d2) {
	UCH x, y;
	x = ((UCH)d1);
	y = ((UCH)d2);
	return x == y;
}

void print(DATATYPE d) {
	UCH x = d;
	printf("%c", x);
}

//Testar criação das estruturas e funções principais (Chamar CU_ASSERT para cada aspecto testado)
//Para cada estrutura

void huff_tests(){
	CU_ASSERT(); //{sentença que vai conter uma expressão (Verdadeira ou falsa)}
	//Para testar cada aspecto da estrutura
	//Vc cria entrada necessária e testa...
}

void hash_tests(){

}

void heap_tests(){

}

void binary_tree_tests(){

}

int run_tests() {
	huff_tests()
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

	if(NULL == CU_add_test(pSuite, "huff_tests", huff_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "hash_tests", hash_tests)) {
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