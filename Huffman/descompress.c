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
	if(fscanf(file, "%hhu", &byte) == EOF)
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
		if(fscanf(file, "%hhu", &byte) == EOF)
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
	byte = 0 << cont;
	byte = 0 >> 7 - (cont + 1);

	return byte;
}

void read_descompress(FILE *file, FILE *new_file, binary_t *b_tree, unsigned short trash) {
	unsigned short cont = 0, aux = 0;
	unsigned char byte, bit;
	binary_t *actual_node = b_tree;

	if(feof(file)) {
		printf("File incomplete.\n");

		return;
	}

	while(1) {
		fscanf(file, "%hhu", &byte);
		aux = 0;

		if(feof(file)) {
			while(aux < trash) {
				bit = read_bit(byte, cont);

				if(actual_node -> right != NULL || actual_node -> left != NULL) {
					if(bit == 1) {
						actual_node = actual_node -> right;
					}
					else {	
						actual_node = actual_node -> left;
					}

					cont++;
				}
				else {
					fprintf(new_file, "%hhu", *((unsigned char*) actual_node -> item));

					cont = 0;
					actual_node = b_tree;
				}

				aux++;
			}

			break;
		}

		while(aux <= 7) {
			bit = read_bit(byte, cont);

			if(actual_node -> right != NULL || actual_node -> left != NULL) {
				if(bit == 1) {
					actual_node = actual_node -> right;
				}
				else {	
					actual_node = actual_node -> left;
				}

				cont++;
			}
			else {
				fprintf(new_file, "%hhu", *((unsigned char*) actual_node -> item));

				cont = 0;
				actual_node = b_tree;
			}

			aux++;
		}
	}


	return;
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

	if (fscanf(file, "%hhu", &byte) == EOF)
	{
		printf("Header incomplete\n");

		return;
	}

	byte_aux = byte;
	byte_aux >> 5;
	trash = (short) byte_aux;

	byte_aux = byte;
	byte_aux << 3;
	byte_aux >> 3;
	size_tree = (short) byte_aux;
	size_tree << 8;

	if (fscanf(file, "%hhu", &byte) == EOF)
	{
		printf("File incomplete\n");

		return;
	}

	size_tree = (size_tree | ((unsigned short) byte));

	//Leitura e da montagem da arvore
	short count = 0;
	create_t_reading(&b_tree, file, size_tree, &count);

	//bt_print(b_tree);
	//printf("\n");

	//comeca a ler o arquivo byte a byte e descompacta o arquivo
	treat_string_2(&name_file);
	FILE *new_file = fopen(name_file, "wb"); //cria um novo arquivo, para descompactá-lo
	read_descompress(file, new_file, b_tree, trash);
}
