#include <stdio.h>
#include <stdlib.h>

typedef struct t_b binary_t;

struct t_b 
{
	unsigned char item;
	binary_t *left;
	binary_t *right;
};

binary_t *create_binary_tree(unsigned char byte, binary_t *left, binary_t* right)
{
	binary_t *new_node = (binary_t *) malloc(sizeof(binary_t));
	new_node->item = byte;
	new_node->left = left;
	new_node->right = right;

	return new_node;
}

void bt_print (binary_t *bt)
{
	if(bt == NULL)
		return;

	printf("%x ", bt->item);
	bt_print(bt->left);
	bt_print(bt->right);
}

void create_t_reading(binary_t **bt, FILE *file, short size, short *count)
{
	if (*count == size)
		return;

	unsigned char byte;
	*count += 1;

	if (fscanf(file, "%c", &byte) == EOF)
	{
		printf("file incomplete\n");

		return;
	}

	if (byte == '*')
	{
		*bt = create_binary_tree(byte, NULL, NULL);
		create_t_reading(&((*bt)->left), file, size, count);
		create_t_reading(&((*bt)->right), file, size, count);
	}
	else if (byte == '\\')
	{
		*count += 1;

		if (fscanf(file, "%c", &byte) == EOF)
		{
			printf("file incomplete\n");

			return;
		}

		*bt = create_binary_tree(byte, NULL, NULL);
	}
	else
	{
		*bt = create_binary_tree(byte, NULL, NULL);	
	}
}


void descompress(char *name_file) 
{
	unsigned short trash, size_tree; //Tamanho das partes dos arquivos
	unsigned char byte, byte_aux;
	FILE *file = fopen(name_file, "rb");
	binary_t *b_tree = NULL;

	if (fscanf(file, "%c", &byte) == EOF)
	{
		printf("file incomplete\n");

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
		printf("file incomplete\n");

		return;
	}

	size_tree = size_tree | ((unsigned short) byte);
	short count = 0;

	create_t_reading(&b_tree, file, size_tree, &count);

	bt_print(b_tree);
	printf("\n");
}