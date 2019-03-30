#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../huffman_base/huffman.h"
#include "../structures/hash/hash.h"
#include "../structures/heap/heap.h"
#include "../structures/binary_tree/binary_tree.h"
#include "../huffman_base/compress/compress.h"
#include "../huffman_base/descompress/descompress.h"

int main () {
	unsigned short i, size, count = 0;
	long long int t;
	char aux;
	char *str_0 = (char *) malloc(sizeof(char) * 15000);
	char *str_1 = (char *) malloc(sizeof(char) * 15000);
	char entrie_0[20] = "archive_test.txt";
	char entrie_1[20] = "archive_test.huff"; 
	char entrie_2[20] = "archive_test";

	FILE *archive, *test_log = fopen("test.log", "w");  

	while (1) {
		count ++;
		printf("Count: %d\n", count);

		archive = fopen(entrie_0, "w");
		t = time(NULL) * rand();
		srand(t);
		printf("Semente time: %lld\n\n", t);
		size = rand() % 10000;

		for(i = 0; i < size; i++) {
			aux = ((char) ((rand() % 94) + 32));

			fprintf(archive, "%c", ((char) aux));
		}
		
		fclose(archive);
		archive = fopen(entrie_0, "r");
		fscanf(archive, "%[^\n]s", str_0);
		fclose(archive);

		printf("dsada\n");
		compress(entrie_0);
		printf("dsada\n");
		descompress(entrie_1);
		
		archive =  fopen(entrie_2, "r");
		fscanf(archive, "%[^\n]s", str_1);
		fclose(archive);

		if (strcmp(str_0, str_1) != 0) {
			fprintf(test_log, "%s\n\n", "Original file");
			fprintf(test_log, "%s\n\n", str_0);

			fprintf(test_log, "%s\n\n", "Descompressed file");
			fprintf(test_log, "%s\n\n", str_1);	

			fprintf(test_log, "\n%s\n", "-----------------------------------------------------------------------");		
		}

		memset(str_0, 0, sizeof(str_0));
		memset(str_0, 0, sizeof(str_1));
	}

	return 0;
}
