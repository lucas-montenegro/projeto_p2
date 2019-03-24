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

	printf("%c ", *((unsigned char *)bt->item));
	bt_print(bt->left);
	bt_print(bt->right);
}