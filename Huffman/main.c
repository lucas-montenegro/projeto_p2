#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "huffman.h"
#include "hash.h"
#include "heap.h"
#include "binary_tree.h"
#include "compress.h"
#include "descompress.h"

#define BYTE_ZERO 0

int main(int argc, char *argv[]) {
   if (argc == 3)
   {
       if(argv[1][0] == '0')
           compress(argv[2]);
       else if(argv[1][0] == '1')
           descompress(argv[2]);
   }
   else
   {
       printf("Parametros errados, por favor entre com: ./{nome do script} {operação} {nome do arquivo}\n");
       printf("Operação: 0-> Comprimir | 1-> Descomprimir\n");
   }


    return 0;
}
