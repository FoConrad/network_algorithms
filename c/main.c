#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

// Args: n_elements_to_add
int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: ./a.out <d-children_size> <items-to-add>\n");
        return -1;
    }

    unsigned int d = strtoul(argv[1], NULL, 10);
    unsigned int size = strtoul(argv[2], NULL, 10);
    heap_t* heap = make_heap(d, size);

    clock_t start = clock();

    for (unsigned int i = 0; i < size; i++) {
        heap->add_item(heap, rand() % 1000);
    }

    double time_taken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
    printf("Time taken to add %u items is %.3f seconds.\n",
            size, time_taken);

    heap->print_heap(heap);
    return 0;
}
