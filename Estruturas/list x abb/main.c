#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> 

//Tree part
typedef struct t_n t_node;

struct t_n
{
	int item;
	t_node *left;
	t_node *right;
};

void create_tree(t_node **bt, int item, t_node *left, t_node *right)
{
	*bt = malloc(sizeof(t_node));
	(*bt)->item = item;
	(*bt)->left = left, (*bt)->right = right;
}

t_node *add_node_bt(t_node *bt, int item)
{
	if (bt == NULL)
		create_tree(&bt, item, NULL, NULL);
	else if(bt->item > item)
		bt->left = add_node_bt(bt->left, item);
	else
		bt->right = add_node_bt(bt->right, item);

	return bt;
}

void search_bt(int *count, t_node *bt, int item)
{
	if (bt != NULL)
	{
		*count += 1;

		if(bt->item == item)
			return;
		else if(bt->item > item)
			search_bt(count, bt->left, item);
		else if(bt->item < item)
			search_bt(count, bt->right, item);
	}
	
}	

t_node *clear_bt(t_node *bt)
{
	if (bt != NULL)
	{
		clear_bt(bt->right);
		clear_bt(bt->left);

		free(bt);
	}

	return NULL;
}

//List part

typedef struct l_n l_node;

struct l_n
{
	int item;
	l_node* next;
};

typedef struct 
{
	l_node *head;
	l_node *tail;
} list;

void create_list(list **l)
{
	if (*l != NULL)
	{
		printf("Lista já criada!\n");
	}
	else
	{
		*l = malloc(sizeof(list));
		(*l)->head = NULL, (*l)->tail = NULL;
	}

}

void add_list(char type, list *l, int item)
{
	if(type == 'h')
	{
		l_node *new_node = (l_node *) malloc(sizeof(l_node));
		new_node->item = item;
		new_node->next = l->head;

		if(l->tail == NULL)
			l->tail = new_node;

		l->head = new_node;
	}
	else if(type == 't')
	{
		l_node *new_node = (l_node *) malloc(sizeof(l_node));
		new_node->item = item;
		new_node->next = NULL;

		if(l->head == NULL)
			l->head = new_node;			
		
		l->tail->next = new_node;
		l->tail = new_node;
	}
	else
	{
		printf("Tipo errado!\n");
		
		return;
	}
}

void search_list(int *count, list *l, int item)
{
	l_node *aux = l->head;

	while(aux != NULL)
	{
		*count += 1;

		if(aux->item == item)
			return;
	
		aux = aux->next;
	}

	*count = -1;
}

void clear_list (list *l)
{
	l_node *aux;

	while(l->head != NULL)
	{
		aux = l->head->next;

		free(l->head);

		l->head = aux;
	}

	l->head = NULL, l->tail = NULL;
}

void function_print(t_node *bt)
{
	if(bt != NULL)
	{
		printf("%d\n", bt->item);

		function_print(bt->left);
		function_print(bt->right);
	}
}

int main()
{
	//Criando os ponteiros para as estruturas
	t_node *bt = NULL;
	list *l = NULL;
	
	create_list(&l);

	//Variaveis utilizadas
	int i, aux, size, sorted, count[2];
	char buffer[1000], s_aux[100];
	//i: vai ser a quantidade de numeros adicionados naquela instancia
	//aux: será o numero sorteado na interação de i
	//size: será a váriavel que guardara a variação do tamanho
	//count: guardara a quantidade de verificações na lista e na arvóre

	//Criando e solicitando os recursos do SO
	FILE *data_bt = fopen("saida_bt.csv", "w");
	FILE *data_list = fopen("saida_list.csv", "w");
	
	//Escrevendo base dos arquivos csv
	fprintf(data_bt, "size, comparison\n");
	fprintf(data_list, "size, comparison\n");

	printf("Testando dados...\n	|| ");

	for (size = 1; size <= 10000; size ++)
	{
		if(size % 1000 == 0 || size == 1)
			printf(". ");

		//Definindo uma semente para rand()
		srand(time(NULL));

		//Sorteado um numero
		sorted = rand() % size;


		for(i = 0; i < size; i ++)
		{
			aux = rand();

			//Verificando e pegando numero sorteado
			if (i == sorted)
				sorted = aux;

			//Adicionando numeros na estrutura
			bt = add_node_bt(bt, aux);
			add_list('h', l, aux);

		}

		count[0] = 0, count[1] = 0;

		//Fazendo a busca do numero, anteriormente adicionado e sorteado
		search_bt(&count[0], bt, sorted);
		search_list(&count[1], l, sorted);

		//Limpando a lista
		clear_bt(bt);
		clear_list(l);

		bt = NULL;


		//Setando string da ABB, da ultima verificação
		sprintf(s_aux, "%d", size);
		strcpy(buffer, s_aux);
		memset(s_aux, 0, sizeof(s_aux));

		strcat(buffer, ",");
		
		sprintf(s_aux, "%d", count[0]);
		strcat(buffer, s_aux);
		memset(s_aux, 0, sizeof(s_aux));
		
		strcat(buffer, "\n");

		//Escrevendo no arquivo de saida para a ABB
		fprintf(data_bt, "%s", buffer);
		memset(buffer, 0, sizeof(buffer));

		//Setando string da lista, da ultima verificação		
		sprintf(s_aux, "%d", size);
		strcpy(buffer, s_aux);
		memset(s_aux, 0, sizeof(s_aux));

		strcat(buffer, ",");
		
		sprintf(s_aux, "%d", count[1]);
		strcat(buffer, s_aux);
		memset(s_aux, 0, sizeof(s_aux));

		strcat(buffer, "\n");

		//Escrevendo no arquivo de saida para a lista
		fprintf(data_list, "%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}

	printf(" ||\nTerminado!\n");
	
	//Fechando os recursos do SO
	fclose(data_bt);
	fclose(data_list);

	printf("Gerando gráfico ...\n");

	system("Rscript script.r");
	
	printf("Exibindo ...\n");

	system("firefox Rplots.pdf");

	sleep(2);

	system("rm saida_bt.csv");
	system("rm saida_list.csv");
	system("rm Rplots.pdf");
	

	printf("Programa Terminado\n");

	return 0;
}