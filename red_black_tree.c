#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct red_black_tree rbt;

struct red_black_tree { 
	bool color; // defines the color red or black 
	int item;
	rbt *right_child;
	rbt *left_child;
};


int main() {


	return 0;
}

/* references:
https://en.wikipedia.org/wiki/Red–black_treehttps://en.wikipedia.org/wiki/Red–black_tree




*/
