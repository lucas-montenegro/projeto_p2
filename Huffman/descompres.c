#include <stdio.h>
#include <stdlib.h>


typedef struct t_b binary_t;

struct t_b 
{
	unsigned char item;
	binary_t *left;
	binary_t *right;
}

binary_t *create_binary_tree(unsigned char byte, binary_t *left, binary_t*right)
{
	binary_t *new_node = (binary_t *) malloc(sizeof(binary_t));
	new_node->item = byte;
	new_node->left = left;
	new_node->right = right;

	return new_node;
}


binary_t *create_binary_tree(binary_t* bt, FILE *archive, short size, short count)
{
	
}

void decompactar(char *name_file) 
{
	short *count;
	unsigned short trash, size_tree;
	unsigned char *byte = (unsigned char*) malloc(sizeof(unsigned char)); 
	unsigned char *byte_aux = (unsigned char*) malloc(sizeof(unsigned char)); 
	FILE *archive = fread(name_file, "wb");
	binary_t *b_tree;

	if (fscanf(archive,	"%c", byte) == EOF)
	{
		printf("Archive incomplete\n");

		return;
	}

	*byte_aux = *byte;
	*byte_aux >> 5;
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


	create_binary_tree(NULLNULL, NULL);

	*count = 0;
	create_t_reading (archive, size_tree, count);
}