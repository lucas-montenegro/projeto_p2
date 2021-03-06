#include <stdio.h>
#include <stdlib.h>

#include "../../huffman_base/huffman.h"
#include "../hash/hash.h"
#include "heap.h"

heap* create_heap(int size) {
    heap *newHeap = (heap*) malloc(sizeof(heap));
    newHeap->data = (huff**) malloc(size * sizeof(huff));
    newHeap->items = 0;
    newHeap->max = size;
    return newHeap;
}

void realloc_heap(heap *heap){
    heap->data = realloc(heap->data, (++heap->max) * sizeof(huff));
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
    huff *aux = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = aux;
}

void enqueue(heap *heap, huff *node){
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

    if(heap->data[index]->frequency != heap->data[smallest]->frequency){
        swap(heap, index, smallest);

        min_heapify(heap, smallest);
    }
}

huff* dequeue(heap *heap){
    if(heap->items <= 0){
        return NULL;
    } else {
        huff *node = heap->data[1];
        swap(heap, 1, heap->items--);
        min_heapify(heap, 1);
        return node;
    }
}

huff* build_tree(heap *heap, hash *hash){
    for(int i = 0; i < 257; i++){
        if(hash->table[i] != NULL){
            enqueue(heap, hash->table[i]);
        }
    }
    if(heap->items == 1)
    {
        printf("There's only one type of byte, can't build huffman tree\n");
        return NULL;
    }
    while(heap->items > 1){
        huff *first = dequeue(heap), *second = dequeue(heap);
        huff *merged = merge_nodes(first, second);
        enqueue(heap, merged);
    }
    return heap->data[1];
}
