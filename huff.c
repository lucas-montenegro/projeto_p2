#include <stdio.h>
#include <stdlib.h>

typedef struct huffman{
    void *item;
    int frequency;
    struct huffman *left;
    struct huffman *right;
}huffman;

typedef struct heap{
    int items, max;
    huffman **data;
}heap;

huffman* create_node(void *item, int frequency){
    huffman *newNode = (huffman*) malloc(sizeof(huffman));
    newNode->item = item;
    newNode->frequency = frequency;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

huffman* merge_nodes(huffman *left, huffman *right){
    huffman *new = (huffman*) malloc(sizeof(huffman));
    new->item = (char*) '*';
    new->frequency = (left->frequency)+(right->frequency);
    new->left = left;
    new->right = right;
    return new;
}

heap* create_heap(int n){
    heap *newHeap = (heap*) malloc(sizeof(heap));
    newHeap->data = (huffman**) malloc(n * sizeof(huffman));
    newHeap->items = 0;
    newHeap->max = n;
    return newHeap;
}

void realloc_heap(heap *heap){
    heap->data = realloc(heap->data, (++heap->max) * sizeof(huffman));
    return;
}

int get_parent_index(int index){
    return index >> 1;
}

int get_left_index(int index){
    return index << 1;
}

int get_right_index(int index){
    return (index << 1) + 1;
}

void swap(heap *heap, int i, int j){
    huffman *aux = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = aux;
}

void enqueue(heap *heap, huffman *node){
    if(heap->items == heap->max - 1)
        realloc_heap(heap);
    heap->data[++heap->items] = node;
    int key_index = heap->items;
    int parent_index = get_parent_index(heap->items);
    while(parent_index >= 1 && heap->data[key_index]->frequency <= heap->data[parent_index]->frequency){
        swap(heap, key_index, parent_index);

        key_index = parent_index;
        parent_index = get_parent_index(key_index);
    }
}

void add(void *item, int frequency, heap *heap){
    huffman *node = create_node(item, frequency);
    enqueue(heap, node);
}

void min_heapify(heap *heap, int index){
    int smallest;
    int left = get_left_index(index);
    int right = get_right_index(index);

    if(left <= heap->items && heap->data[left]->frequency <= heap->data[index]->frequency)
        smallest = left;
    else
        smallest = index;
    if(right <= heap->items && heap->data[right]->frequency <= heap->data[smallest]->frequency)
        smallest = right;

    if(heap->data[index] != heap->data[smallest]){
        swap(heap, index, smallest);

        min_heapify(heap, smallest);
    }
}

huffman* dequeue(heap *heap){
    if(heap->items <= 0){
        printf("Heap Underflow\n");
        return NULL;
    } else {
        huffman *node = heap->data[1];
        swap(heap, 1, heap->items--);
        min_heapify(heap, 1);
        return node;
    }
}

void pre_order(huffman *huffman){
    if(huffman != NULL){
        printf("frequency = %d\n", huffman->frequency);
        pre_order(huffman->left);
        pre_order(huffman->right);
    }
}

void print_heap(huffman **data, int index, int size){
    if(index < size && data[index] != NULL){
        printf("i = %d, f = %d", *((int*)data[index]->item), data[index]->frequency);
        if(index < size - 1)
            printf(" | ");
        else
            printf("\n");
        print_heap(data, index + 1, size);
    }
}

void read(heap *heap){
    int value, frequency;
    printf("Informe o valor e frequencia:\n");
    if(scanf("%d %d", &value, &frequency) == EOF){
        printf("Heap:\n");
        print_heap(heap->data, 1, heap->max);
        while(heap->items > 1){//precisa ter ao menos dois nos para dar merge
            huffman *aux = dequeue(heap), *sos = dequeue(heap);
            huffman *help = merge_nodes(aux, sos);
            enqueue(heap, help);
        }
        printf("Arvore:\n");
        pre_order(heap->data[1]);

        return;
    }
    void *ptr = &value;
    add(ptr, frequency, heap);
    read(heap);
}

int main(){
    int sz;
    printf("Heap size:\n");
    scanf("%d", &sz);
    heap *h = create_heap(sz + 1);//pedindo tamanho para questoes de teste, mas create_heap pode receber 1 e realocar a partir dai
    read(h);
    //FIX ---> fora de read a heap ainda recebe lixo de memoria do ponteiro void

    return 0;
}
