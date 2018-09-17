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
    printf("Removing min: %d\n", heap->pop_min(heap));
    heap->print_heap(heap);
    printf("Removing min: %d\n", heap->pop_min(heap));
    heap->print_heap(heap);

    int randInts[12] = {40, 90, 34, 22, 99, 22, 39, 43, 50, 3, 7, 109};
    printf("Array to make heap: [");
    for (int i = 0; i < 11; i++)
        printf("%d, ", randInts[i]);
    printf("%d]\n", randInts[11]);

    heap_t* sec_heap = make_heap_list(3, 12, randInts);
    sec_heap->print_heap(sec_heap);
    return 0;
}
