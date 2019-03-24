#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"
#include "descompress.h"

void create_t_reading(binary_t **bt, FILE *file, short size, short *count)
{
	if(*count == size)
		return;

	unsigned char byte;
	if(fscanf(file, "%c", &byte) == EOF)
	{		
		*count += 1;

		printf("Header -> Tree incomplete\n");

		return;
	}

	if(byte == '*') //Se for um *
	{
		

		*bt = create_binary_tree(byte, NULL, NULL);
		create_t_reading(&((*bt)->left), file, size, count);
		create_t_reading(&((*bt)->right), file, size, count);
	}
	else if(byte == '\\') //Se for uma barra
	{
		if(fscanf(file, "%c", &byte) == EOF)
		{
			printf("Header -> Tree incomplete\n");

			return;
		}

		*bt = create_binary_tree(byte, NULL, NULL);
	}
	else
		*bt = create_binary_tree(byte, NULL, NULL);	
}

unsigned char read_bit(unsigned char byte, int cont) {
	unsigned char mask = 1 << (7 - cont);

	return byte & mask;
}

void read_descompress(FILE *file, FILE *new_file, binary_t *b_tree, unsigned short trash) {
	unsigned short cont = 0, bit;
	unsigned char byte;

	binary_t *actual_node = b_tree;

	if(feof(file)) {
		printf("File incomplete.\n");

		return;
	}

	while(1) {
		fscanf(file, "%c", &byte);
		cont = 0;

		if(feof(file)) {
			while(cont < trash) {
				bit = (unsigned short) read_bit(byte, cont);

				if(actual_node -> right != NULL || actual_node -> left != NULL) {
					if(bit == 1) {
						actual_node = actual_node -> right;
					}
					else {	
						actual_node = actual_node -> left;
					}
				}
				else {
					fprintf(new_file, "%c", *((unsigned char*) actual_node -> item));
					actual_node = b_tree;
				}

				cont++;
			}

			break;
		}

		while(cont <= 7) {
			bit = (unsigned short)read_bit(byte, cont);

			if(actual_node -> right != NULL || actual_node -> left != NULL) {
				if(bit != 0) {
					actual_node = actual_node -> right;
				}
				else {	
					actual_node = actual_node -> left;
				}
			}
			else {
				fprintf(new_file, "%c", *((unsigned char*) actual_node -> item));

				actual_node = b_tree;
			}

			cont++;
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

void descompress(char *name_file) 
{
	//Leitura do cabecalho
	unsigned short trash, size_tree; //Tamanho das partes dos arquivos (2 Byte)
	unsigned char byte, byte_aux; //Bytes para leitura e operações (1 Byte)
	FILE *file = fopen(name_file, "rb"); //Ponteiro para o file referente, em forma de leitura binaria
	binary_t *b_tree = NULL; //Estrutura da arvóre

	if (fscanf(file, "%c", &byte) == EOF)
	{
		printf("Header incomplete\n");

		return;
	}

	printf("Byte %x ", byte);
	
	byte_aux = byte;
	byte_aux >> 5;
	trash = (short) byte_aux;

	byte_aux = byte;
	byte_aux << 3;
	byte_aux >> 3;
	size_tree = (short) byte_aux;
	size_tree << 8;


	if (fscanf(file, "%c", &byte) == EOF)
	{
		printf("File incomplete\n");

		return;
	}

	printf("%x\n", byte);
	size_tree = (size_tree | ((unsigned short) byte));
	
	printf("size_tree %d\n", size_tree);

	//Leitura e da montagem da arvore
	short count = 0;
	create_t_reading(&b_tree, file, size_tree, &count);

	// bt_print(b_tree);
	// printf("\n");

	//comeca a ler o arquivo byte a byte e descompacta o arquivo
	treat_string_2(&name_file);
	FILE *new_file = fopen(name_file, "wb"); //cria um novo arquivo, para descompactá-lo
	read_descompress(file, new_file, b_tree, trash);
	fclose(new_file);
}
