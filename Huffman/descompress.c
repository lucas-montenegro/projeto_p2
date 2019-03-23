#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

binary_t *create_binary_tree(unsigned char byte, binary_t *left, binary_t* right)
{
	unsigned char *aux = (unsigned char *) malloc(sizeof(unsigned char));
	*aux = byte;

	binary_t *new_node = (binary_t *) malloc(sizeof(binary_t));
	new_node->item = (void *) aux;
	new_node->left = left;
	new_node->right = right;

	return new_node;
}

void bt_print (binary_t *bt)
{
	if(bt == NULL)
		return;

	printf("%x ", *((unsigned char *)bt->item));
	bt_print(bt->left);
	bt_print(bt->right);
}

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

	size_tree = (size_tree | ((unsigned short) byte));

	//Leitura e da montagem da arvore
	short count = 0;
	create_t_reading(&b_tree, file, size_tree, &count);

	bt_print(b_tree);
	printf("\n");
}