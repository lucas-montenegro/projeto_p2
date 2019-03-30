#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../huffman.h"
#include "../../structures/hash/hash.h"
#include "../../structures/heap/heap.h"
#include "../../structures/binary_tree/binary_tree.h"
#include "descompress.h"

void create_pre_order(binary_t **bt, FILE *file, short size_tree, short *count, short *flag)
{
	*count += 1;
	if(*count == size_tree)
		return;
	unsigned char byte_1;
	if(fscanf(file, "%c", &byte_1) == EOF)
	{
		printf("Header incomplete\n");
		return;
	}
	if(byte_1 == '*')
	{
		*bt = create_binary_tree(byte_1, NULL, NULL);
		create_pre_order(&((*bt)->left), file, size_tree, count, flag);
		create_pre_order(&((*bt)->right), file, size_tree, count, flag);
	}
	else if(byte_1 == '\\')
	{
		if(fscanf(file, "%c", &byte_1) == EOF)
		{
			printf("Header -> Tree incomplete\n");
			return;
		}
		*count += 1;
		*bt = create_binary_tree(byte_1, NULL, NULL);
	}
	else
		*bt = create_binary_tree(byte_1, NULL, NULL);
}

unsigned char read_bit(unsigned char byte_1, int cont) {
	unsigned char mask = 1 << (7 - cont);
	return byte_1 & mask;
}

void read_descompress(FILE *file, FILE *new_file, binary_t *b_tree, unsigned short trash){ // arvore com uma letra //cont_aux *
	unsigned short cont = 0, bit;
	unsigned char byte_1, byte_2;
	binary_t *current_node = b_tree;

	if(feof(file)) {
		printf("File incomplete.\n");
		return;
	}

	while(fscanf(file, "%c", &byte_1) != EOF) {
		cont = 0;

		if(fscanf(file, "%c", &byte_2) == EOF) {
			while(cont < (8 - trash)) {
				bit = (unsigned short) read_bit(byte_1, cont);

				if(current_node -> right != NULL || current_node -> left != NULL) {
					if(bit != 0)
						current_node = current_node -> right;
					else
						current_node = current_node -> left;

					cont++;
				}
				else if(current_node -> right == NULL && current_node -> left == NULL){
					fprintf(new_file, "%c", *((unsigned char*) current_node -> item));
					current_node = b_tree;
				}
			}

			if(current_node -> right == NULL && current_node -> left == NULL){
				fprintf(new_file, "%c", *((unsigned char*) current_node -> item));
				current_node = b_tree;
			}
			return;
		}
		else {
			while(cont <= 7) {
				bit = (unsigned short) read_bit(byte_1, cont);

				if(current_node -> right != NULL || current_node -> left != NULL) {
					if(bit != 0)
						current_node = current_node -> right;
					else
						current_node = current_node -> left;

					cont++;
				}
				else if(current_node -> right == NULL && current_node -> left == NULL){
					fprintf(new_file, "%c", *((unsigned char*) current_node -> item));
					current_node = b_tree;
				}
			}
			fseek(file, -1, SEEK_CUR);
		}
	}
}

void file_extension(char **name_file){
	unsigned short size_1 = strlen(*name_file), size_2 = size_1 + 4;
	char *new_string = (char*) calloc(size_2, sizeof(char));

	for(int i = 0; i < size_1; i++){
		if((*name_file)[i] == '.')
			break;
		new_string[i] = (*name_file)[i];
	}

	*name_file = new_string;
}

void descompress(char *name_file){
	//Leitura do cabecalho
	unsigned short trash, size_tree;
	unsigned char byte_1, byte_1_aux;
	FILE *file = fopen(name_file, "rb");
	binary_t *b_tree = NULL;

	if(fscanf(file, "%c", &byte_1) == EOF)
	{
		printf("Header incomplete\n");
		return;
	}

	byte_1_aux = byte_1 >> 5;
	trash = (unsigned short) byte_1_aux;

	byte_1_aux = byte_1;
	byte_1_aux = (byte_1_aux << 3) >> 3;
	size_tree = (unsigned short) byte_1_aux;
	size_tree <<= 8;

	if(fscanf(file, "%c", &byte_1) == EOF)
	{
		printf("File incomplete\n");
		return;
	}

	size_tree = (size_tree | ((unsigned short) byte_1));

	short count = 0, flag = 0;
	create_pre_order(&b_tree, file, size_tree, &count, &flag);//Leitura e da montagem da arvore

	file_extension(&name_file);
	FILE *new_file = fopen(name_file, "wb"); //cria um novo arquivo, para descompactá-lo
	read_descompress(file, new_file, b_tree, trash); //comeca a ler o arquivo byte_1 a byte_1 e descompacta o arquivo

	fclose(new_file);
	fclose(file);
}
