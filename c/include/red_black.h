#ifndef RED_BLACK_C_H_
#define RED_BLACK_C_H_

enum color {red, black};

typedef struct _node_t {
    struct _node_t left;
    struct _node_t right;
    struct _node_t parent;
    enum color color;
    void* item;
} node_t;

typedef struct _tree_t {
    struct _node_t root;
    struct _node_t nil;
    int (*compare)(const void*, const void*);
} tree_t;

tree_t* make_tree(int (*compare)(const void*, const void*));
tree_t* make_tree_list(int (*compare)(const void*, const void*), void**);

int insert(tree_t*, void*);
int remove(tree_t*, void*);



#endif // RED_BLACK_C_H_

