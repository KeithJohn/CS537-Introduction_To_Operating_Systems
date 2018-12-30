#ifndef TREE
#define TREE

typedef struct RBT_Node {
    void *id;
    void *data;
    struct RBT_Node *left;
    struct RBT_Node *right;
    struct RBT_Node *parent;
    int rc;
    int lc;
} RBT_Node;

// Returns a node representing the root of the tree
RBT_Node *init_tree();

// Returns new root on sucess, NULL on failure. If the given
// ID is already in the tree this will fail.
RBT_Node *add(RBT_Node *root, void *id, void *data);

// Returns 1 on success, 0 on failure. If the given
// ID is not in the tree to vegin with this will fail.
RBT_Node *removeNode(RBT_Node *root, void *id);

// Returns the pointer to the data of the node on success.
// Returns NULL if the ID is not found in the tree.
void *get(RBT_Node *root, void *id);

// Returns the pointer to the data of the node with the
// largest ID that is less than the given ID.
// Returns NULL if there is no ID in the tree < the given ID.
void *get_max_below(RBT_Node *root, void *id);


void print_tree(RBT_Node *root, int indent_size);
#endif
