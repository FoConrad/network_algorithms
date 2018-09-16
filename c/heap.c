#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "heap.h"

void grow_heap(heap_t* heap) {
    assert(0);
}

// Parent of root is root
unsigned int parent(unsigned int d, unsigned int index) {
    return index == 0 ? 0 : (index - 1) / d;
}

void sift_up(heap_t* heap, unsigned int start_index) {
    int* ha = heap->heap_arr;
    unsigned int parent_index = parent(heap->d, start_index);
    while ((start_index) && ha[parent_index] > ha[start_index]) {
        int tmp = ha[parent_index];
        ha[parent_index] = ha[start_index];
        ha[start_index] = tmp;
        start_index = parent_index;
        parent_index = parent(heap->d, start_index);
    }
}

void add_item(heap_t* heap, int item) {
    unsigned int index = heap->num_items;
    if (index == heap->size) {
        grow_heap(heap);
    }
    heap->heap_arr[index] = item;
    sift_up(heap, index);
    heap->num_items += 1;
}

void print_heap(heap_t* heap) {
    if (heap->num_items > 100) {
        printf("Heap size exceeds printing limit\n");
        return;
    }
    int layers = ceil(log(2*heap->num_items + 1) / log(heap->d));
    int width = pow(heap->d, (layers-1)) * (HEAP_WORD_WIDTH + 1);

    char grid[layers][width];
    for (int l = 0; l < layers; l++)
        for (int w = 0; w < width; w++)
            grid[l][w] = w == width - 1 ? '\0' : ' ';

    int row_index = 0;
    int last_layer = 0;
    for (int i = 0; i < heap->num_items; i++) {
        int layer = ceil(log(2*(i + 1) + 1) / log(heap->d)) - 1;
        int items_per_layer = (int) pow(heap->d, layer);
        if (layer > last_layer) {
            last_layer = layer;
            row_index = 0;
        }
        int start = (row_index*width) / items_per_layer;
        int end = ((row_index+1) * width) / items_per_layer;

        int start_write = start + ((end-start) - HEAP_WORD_WIDTH)/2;

        char str_self[HEAP_WORD_WIDTH + 1];
        sprintf(str_self, "%d", heap->heap_arr[i]);
        str_self[HEAP_WORD_WIDTH] = '\0';
        strncpy(&grid[layer][start_write], str_self, strlen(str_self));

        row_index += 1;
    }

    for (int l = 0; l < layers; l++)
        printf("%s\n", grid[l]);
}

heap_t* make_heap(unsigned int dary, unsigned int start_size) {
    heap_t* ret = (heap_t*) calloc(1, sizeof(heap_t));
    assert(start_size > 0);
    ret->size = start_size;
    assert(dary > 1);
    ret->d = dary;
    ret->num_items = 0;
    ret->heap_arr = (int*) calloc(start_size, sizeof(int));
    ret->add_item = add_item;
    ret->print_heap = print_heap;
    return ret;
}
