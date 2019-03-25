#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"
#include "descompress.h"

void create_t_reading(binary_t **bt, FILE *file, short size, short *count)
{
	if(*count == size)
		return;

	unsigned char byte_1;
	if(fscanf(file, "%c", &byte_1) == EOF)
	{		
		*count += 1;

		printf("Header -> Tree incomplete\n");

		return;
	}

	if(byte_1 == '*') //Se for um *
	{
		

		*bt = create_binary_tree(byte_1, NULL, NULL);
		create_t_reading(&((*bt)->left), file, size, count);
		create_t_reading(&((*bt)->right), file, size, count);
	}
	else if(byte_1 == '\\') //Se for uma barra
	{
		if(fscanf(file, "%c", &byte_1) == EOF)
		{
			printf("Header -> Tree incomplete\n");

			return;
		}

		*bt = create_binary_tree(byte_1, NULL, NULL);
	}
	else
		*bt = create_binary_tree(byte_1, NULL, NULL);	
}

unsigned char read_bit(unsigned char byte_1, int cont) {
	unsigned char mask = 1 << (7 - cont);

	return byte_1 & mask;
}

void read_descompress(FILE *file, FILE *new_file, binary_t *b_tree, unsigned short trash) { // arvore com uma letra
	unsigned short cont = 0, cont_aux = 0, bit;
	unsigned char byte_1, byte_2;

	binary_t *current_node = b_tree;

	if(feof(file)) {
		printf("File incomplete.\n");

		return;
	}

	while(fscanf(file, "%c", &byte_1) != EOF) {
		//printf("%x\n", byte_1);
		cont = 0;
		cont_aux++;
		//printf("%d\n", cont_aux);

		if(fscanf(file, "%c", &byte_2) == EOF) {
			while(cont < (8 - trash)) {
				//printf("%d < %d\n", cont, 8 - trash);
				bit = (unsigned short) read_bit(byte_1, cont);

				if(current_node -> right != NULL || current_node -> left != NULL) {
					//printf("oi\n");
					if(bit != 0) {
						current_node = current_node -> right;
					}
					else {	
						current_node = current_node -> left;
					}

					cont++;
					//printf("%c\n", *((unsigned char*)current_node -> item));
				}	
				else if(current_node -> right == NULL && current_node -> left == NULL){
					fprintf(new_file, "%c", *((unsigned char*) current_node -> item));
					//printf("%c\n", *((unsigned char*)current_node -> item));

					current_node = b_tree;
				}
			}
			
			if(current_node -> right == NULL && current_node -> left == NULL){
				fprintf(new_file, "%c", *((unsigned char*) current_node -> item));
				//printf("%c\n", *((unsigned char*)current_node -> item));

				current_node = b_tree;
			}

			return;
		}
		else {
			while(cont <= 7) {
				bit = (unsigned short) read_bit(byte_1, cont);

				if(current_node -> right != NULL || current_node -> left != NULL) {
					if(bit != 0) {
						current_node = current_node -> right;
					}
					else {	
						current_node = current_node -> left;
					}

					//printf("%c\n", *((unsigned char*)current_node -> item));

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

void treat_string_2(char **name_file)
{
	unsigned short s1_string = strlen(*name_file), s2_string = s1_string + 4, i, ver = 0; 
	char *new_string = (char *)malloc(sizeof(char) * s2_string); 
	for (i = 0; i < s2_string; i++)
		new_string[i] = '\0';

	for(i = 0; i < s1_string; i++){
		if((*name_file)[i] == '.')
			break;

		new_string[i] = (*name_file)[i];
	}

	*name_file = new_string;
}   

void descompress(char *name_file)  {
	//Leitura do cabecalho
	unsigned short trash, size_tree; //Tamanho das partes dos arquivos (2 byte_1)
	unsigned char byte_1, byte_1_aux; //byte_1s para leitura e operações (1 byte_1)
	FILE *file = fopen(name_file, "rb"); //Ponteiro para o file referente, em forma de leitura binaria
	binary_t *b_tree = NULL; //Estrutura da arvóre

	if (fscanf(file, "%c", &byte_1) == EOF)
	{
		printf("Header incomplete\n");

		return;
	}

	//printf("byte_1 %x ", byte_1);
	
	byte_1_aux = byte_1;
	byte_1_aux >>= 5;
	trash = (short) byte_1_aux;

	byte_1_aux = byte_1;
	byte_1_aux <<= 3;
	byte_1_aux >>= 3;
	size_tree = (short) byte_1_aux;
	size_tree >>= 8;


	if (fscanf(file, "%c", &byte_1) == EOF)
	{
		printf("File incomplete\n");

		return;
	}

	//printf("%x\n", byte_1);
	size_tree = (size_tree | ((unsigned short) byte_1));
	
	//printf("trash: %d | size_tree %d\n", trash, size_tree);

	//Leitura e da montagem da arvore
	short count = 0;
	create_t_reading(&b_tree, file, size_tree, &count);

	// bt_print(b_tree);
	// printf("\n");

	//comeca a ler o arquivo byte_1 a byte_1 e descompacta o arquivo
	treat_string_2(&name_file);
	FILE *new_file = fopen(name_file, "wb"); //cria um novo arquivo, para descompactá-lo
	read_descompress(file, new_file, b_tree, trash); // tratar de arvore com uma letra
	
	//printf("10101100 01001101 11000000\n");
	fclose(new_file);
	fclose(file);
}