#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "heap.h"

#define DEBUG 0
#define debug_print(fmt, ...) \
    do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)


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

unsigned int min_child(heap_t* heap, unsigned int start_index) {
    if (start_index * heap->d + 1 >= heap->num_items) {
        return -1;
    }

    int* arr = heap->heap_arr;
    int min = start_index*heap->d + 1;

    // Range is [i*d + 1, i*d + 1 + d), where second term is rewritten as
    // d(i + 1) + 1
    unsigned int end = heap->num_items < heap->d*(start_index + 1) + 1 ? 
        heap->num_items : heap->d*(start_index + 1) + 1;

    for (unsigned int c = start_index*heap->d + 1; c < end; c++)
        if (arr[c] < arr[min])
            min = c;
    return min;
}

void sift_down(heap_t* heap, unsigned int start_index) {
    int* ha = heap->heap_arr;
    int min_child_index = min_child(heap, start_index);
    while (min_child_index > 0 && ha[min_child_index] < ha[start_index]) {
        int tmp = ha[start_index];
        ha[start_index] = ha[min_child_index];
        ha[min_child_index] = tmp;
        start_index = min_child_index;
        min_child_index = min_child(heap, start_index);
    }
}

int peak_min(heap_t* heap) {
    assert(heap->num_items > 0);
    return heap->heap_arr[0];
}

int pop_min(heap_t* heap) {
    assert(heap->num_items > 0);
    int* ha = heap->heap_arr;
    int ret = ha[0];

    // We need the last item, and then to decrement the number of items. Why not
    // decrement first
    ha[0] = ha[--heap->num_items];
    sift_down(heap, 0);
    return ret;
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
    int layers = ceil(log((heap->d - 1)*heap->num_items + 1) / log(heap->d));
    int width = pow(heap->d, (layers-1)) * (HEAP_WORD_WIDTH + 1);

    char grid[layers][width];
    for (int l = 0; l < layers; l++)
        for (int w = 0; w < width; w++)
            grid[l][w] = w == width - 1 ? '\0' : ' ';

    int row_index = 0;
    int last_layer = 0;
    for (unsigned int i = 0; i < heap->num_items; i++) {
        int layer = ceil(log((heap->d - 1)*(i + 1) + 1) / log(heap->d)) - 1;
        int items_per_layer = (int) pow(heap->d, layer);
        if (layer > last_layer) {
            last_layer = layer;
            row_index = 0;
        }
        int start = (row_index*width) / items_per_layer;
        int end = ((row_index+1) * width) / items_per_layer;

        int start_write = start + ((end-start) - HEAP_WORD_WIDTH)/2;
/*#if DEBUG*/
        debug_print("Printing %d in level %d at start %d, in range [%d, %d)\n",
                heap->heap_arr[i], layer, start_write, start, end);
/*#endif*/

        char str_self[HEAP_WORD_WIDTH + 1];
        sprintf(str_self, "%d", heap->heap_arr[i]);
        strncpy(&grid[layer][start_write], str_self, strlen(str_self));

        row_index += 1;
    }

    for (int l = 0; l < layers; l++)
        printf("%s\n", grid[l]);
}

void _set_methods(heap_t* heap) {
    heap->add_item = add_item;
    heap->print_heap = print_heap;
    heap->peak_min = peak_min;
    heap->pop_min = pop_min;
}

heap_t* make_heap(unsigned int dary, unsigned int start_size) {
    heap_t* ret = (heap_t*) calloc(1, sizeof(heap_t));

    assert(start_size > 0);
    ret->size = start_size;

    assert(dary > 1);
    ret->d = dary;

    ret->num_items = 0;
    ret->heap_arr = (int*) calloc(start_size, sizeof(int));

    _set_methods(ret);
    return ret;
}

heap_t* make_heap_list(unsigned int d, unsigned int n, int* items) {
    heap_t* ret = (heap_t*) calloc(1, sizeof(heap_t));

    assert(n > 0);
    ret->size = n;

    assert(d > 1);
    ret->d = d;

    ret->num_items = n;
    ret->heap_arr = (int*) calloc(n, sizeof(int));

    _set_methods(ret);
    for (unsigned int i = 0; i < n; i++)
        ret->heap_arr[i] = items[i];

    int last_layer = ceil(log((d - 1)*n + 1)/log(d)) - 1;
    last_layer = last_layer < 1 ? 1 : last_layer;
    int last_item = ((int) pow(d, last_layer)) / (d - 1);
    for (int i = last_item - 1; i >= 0; i--) {
        sift_down(ret, i);
    }
    return ret;
}
