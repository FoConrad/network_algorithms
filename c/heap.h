#ifndef HEAP_C_H_
#define HEAP_C_H_

#define HEAP_WORD_WIDTH 3

typedef struct _heap_t {
    unsigned int size;
    unsigned int d;
    unsigned int num_items;
    int* heap_arr;
    void (*add_item)(struct _heap_t*, int);
    void (*print_heap)(struct _heap_t*);
} heap_t;

heap_t* make_heap(unsigned int, unsigned int);

#endif // HEAP_C_H_
