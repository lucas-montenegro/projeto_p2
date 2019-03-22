#include <stdio.h>
#include <stdlib.h>


typedef struct t_b binary_t;

struct t_b 
{
	unsigned char *item;
	binary_t *left;
	binary_t *right;
}

void create_binary_tree(binary_t **b_t)
{
	*bt = malloc(sizeof(binary_t));
	(*bt)->item = NULL;
	(*bt)->left = NULL;
	(*bt)->right = NULL;
}

create_t_reading (binary_bt *bt, FILE *archive, int size, int count) 
{
	if (count == size)
		return bt;

	if (fscanf(archive,	"%c", byte) == EOF)
	{
		printf("Archive incomplete\n");

		return NULL;
	}

	if(*bt == '*')
		bt->left = create_t_reading(bt)
}

void decompactar(char *name_file) 
{
	unsigned short trash, size_tree;
	unsigned char *byte = (unsigned char*) (malloc(sizeof(unsigned char)));
	unsigned char *byte_aux = (unsigned char*) (malloc(sizeof(unsigned char)));
	FILE *archive = fread(name_file, "wb");

	if (fscanf(archive,	"%c", byte) == EOF)
	{
		printf("Archive incomplete\n");

		return;
	}

	*byte_aux = *byte;
	(*byte_aux) >> 5;
	trash = (short) *byte_aux;


	*byte_aux = *byte;
	(*byte_aux) << 3;
	(*byte_aux) >> 3;
	size_tree = *byte_aux;
	size_tree << 8;

	if (fscanf(archive,	"%c", byte) == EOF)
	{
		printf("Archive incomplete\n");

		return;
	}

	size_tree = size_tree | ((unsigned short) (*byte));


	binary_t *b_tree;
	create_binary_tree(&b_tree);
	free(byte_aux);


	create_t_reading (archive, size_tree, 0);
}