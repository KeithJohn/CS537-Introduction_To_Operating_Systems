#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "AVL.h"
// Returns a node representing the root of the tree
RBT_Node *init_tree(){
    RBT_Node *root = malloc(sizeof(RBT_Node));
    root->id = NULL;
    root->data = NULL;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    root->rc = 0;
    root->lc = 0;
    return root;
}

RBT_Node *make_node(void *id, void *data, RBT_Node *parent){
    RBT_Node *newNode = init_tree();
    newNode->id = id;
    newNode->data = data;
    newNode->parent = parent;
    newNode->lc = newNode->rc = 0;
    return newNode;
}

// A root node is considered a right child
int isRight(RBT_Node *child){
    RBT_Node *parent = child->parent;
    return parent == NULL || parent->right == child;
}

RBT_Node *getBrother(RBT_Node *child){
    RBT_Node *parent = child->parent;
    if(isRight(child)){
        return parent->left;
    }
    return parent->right;
}

RBT_Node *getOnlyChild(RBT_Node *parent){
    RBT_Node *left = parent->left;
    if (left != NULL){
        return left;
    }
    return parent->right;
}

// Height includes the given node
int max_height(RBT_Node *node){
    if (node == NULL) {
        return 0;
    }
    else if (node->lc > node->rc){
        return node->lc + 1;
    }
    else{
        return node->rc + 1;
    }
}

// Height includes the given node
int max_height_rec(RBT_Node *node){
    if (node == NULL) {
        return 0;
    }
    int left = max_height_rec(node->left);
    int right = max_height_rec(node->right);
    if (left > right){
        return left+ 1;
    }
    else{
        return right+ 1;
    }
}

void updateCounts(RBT_Node *node){
    if (node == NULL) return;

    RBT_Node *right = node->right;
    node->rc = max_height(right);

    RBT_Node *left = node->left;
    node->lc = max_height(left);
}

// Returns the pointer to the data of the node on success.
// Returns NULL if the ID is not found in the tree.
RBT_Node *get_node(RBT_Node *root, void *id){
    if (root == NULL){
        return NULL;
    }
    else if (root->id == id){
        return root;
    }
    else if (root->id < id){
        return get_node(root->right, id);
    }
    else{ //(root->id > id)
        return get_node(root->left, id);
    }
}

RBT_Node *get_max_node_below(RBT_Node *root, void *id){
    if (root == NULL){
        return NULL;
    }
    else if (root->id >= id){
        return get_max_node_below(root->left, id);
    }
    else{ // (root->id < id)
        void *pos_improvement = get_max_node_below(root->right, id);
        if (pos_improvement){
            return pos_improvement;
        }
        return root;
    }
}

void rotateRight(RBT_Node *curParent){
    RBT_Node *grandParent = curParent->parent;
    RBT_Node *newParent = curParent->left;
    if (newParent == NULL) return;

    RBT_Node *right = newParent->right;

    if(grandParent != NULL){
        int curParent_was_right = isRight(curParent);
        if (curParent_was_right){
            grandParent->right = newParent;
        }
        else{
            grandParent->left = newParent;
        }
    }

    curParent->left = right;
    curParent->parent = newParent;

    newParent->right = curParent;
    newParent->parent = grandParent;

    if(right != NULL){
        right->parent = curParent;
    }
}

void rotateLeft(RBT_Node *curParent){
    RBT_Node *grandParent = curParent->parent;
    RBT_Node *newParent = curParent->right;
    if (newParent == NULL) return;

    RBT_Node *left = newParent->left;

    if(grandParent != NULL){
        int curParent_was_right = isRight(curParent);
        if (curParent_was_right){
            grandParent->right = newParent;
        }
        else{
            grandParent->left = newParent;
        }
    }

    curParent->right = left;
    curParent->parent = newParent;

    newParent->left = curParent;
    newParent->parent = grandParent;

    if(left != NULL){
        left->parent = curParent;
    }
}  

void other_fix_tree(RBT_Node *node){
    if(node == NULL) return;

    updateCounts(node);
    if(node->lc > node->rc+1){
        rotateRight(node);
    }
    else if(node->rc > node->lc + 1){
        rotateLeft(node);
    } 
    updateCounts(node);
    updateCounts(node->parent);
}

// Returns the added child
RBT_Node *add_helper(RBT_Node *root, void *id, void *data){
    RBT_Node *added_child = NULL;
    if (root == NULL || id == NULL){
        fprintf(stderr, "Cannot pass NULL into add as the root of tree or as the id\n");
        exit(1);
    }
    else if (root->id == NULL){
        root->id = id;
        root->data = data;
        return root;
    }
    else if(root->id == id){
        return NULL;
    }
    else if(id < root->id && root->left == NULL){
        RBT_Node *newNode = make_node(id, data, root);
        root->left = newNode;
        added_child = newNode;
    }
    else if(id < root->id){
        added_child = add_helper(root->left, id, data);
    }
    else if(id > root->id && root->right == NULL){
        RBT_Node *newNode = make_node(id, data, root);
        root->right = newNode;
        added_child = newNode;
    }
    else{
        added_child = add_helper(root->right, id, data);
    }
    other_fix_tree(root);
    return added_child;
}

RBT_Node *getRoot(RBT_Node *someNode){
    while(someNode->parent != NULL){
        someNode = someNode->parent;
    }
    return someNode;
}

// Returns the new root node on success, and NULL on failure. If the given
// ID is already in the tree this will fail.
RBT_Node *add(RBT_Node *root, void *id, void *data){
    RBT_Node *just_added_node = add_helper(root, id, data);
    if (just_added_node == NULL){
        return NULL;
    }
    return getRoot(root);
}

// Deletes the id and data for node with given id.
// Returns NULL if id is not in tree.
// Returns the node that needs to be removed from tree.
RBT_Node *delete(RBT_Node *root, void *id){
    RBT_Node *toDelete = get_node(root, id);
    if (toDelete == NULL){
        return NULL;
    }
    RBT_Node *toRemove = get_max_node_below(toDelete, id);
    if (toRemove == NULL){
        return toDelete;
    }
    else{
        toDelete->id = toRemove->id;
        toDelete->data = toRemove->data;
        return toRemove;
    }
}

RBT_Node *splice(RBT_Node *toRemove){
    RBT_Node *parent = toRemove->parent;
    RBT_Node *child = getOnlyChild(toRemove);

    if(parent == NULL && child == NULL){
        toRemove->id = NULL;
        toRemove->data = NULL;
        return toRemove;
    }
    if (child != NULL){
        child->parent = parent;
    }

    if(parent != NULL){
        if(isRight(toRemove)){
            parent->right = child;
        }
        else{
            parent->left = child;
        }
        free(toRemove);
        return parent;
    }
    free(toRemove);
    return child;
}
// Returns the pointer to the data of the node on success.
// Returns NULL if the ID is not found in the tree.
RBT_Node *remove_fix_node(RBT_Node *root, void *id){
    if (root == NULL){
        return NULL;
    }
    else if (root->id < id){
        RBT_Node *tmp = remove_fix_node(root->right, id);
        other_fix_tree(root);
        return tmp;
    }
    else if(root->id > id){
        RBT_Node *tmp = remove_fix_node(root->left, id);
        other_fix_tree(root);
        return tmp;
    }
    else{
        return root;
    }
}

// Returns 1 on success, 0 on failure. If the given
// ID is not in the tree to begin with this will fail.
RBT_Node *removeNode(RBT_Node *root, void *id){
    RBT_Node *toRemove = delete(root, id);
    if (toRemove == NULL) return NULL;
    else {
        RBT_Node *someNode = splice(toRemove);
        root = getRoot(someNode);
        remove_fix_node(root, id);
        return root;
    }
}

void *get(RBT_Node *root, void *id){
    RBT_Node *targetNode = get_node(root, id);
    if (targetNode == NULL) return NULL;
    else return targetNode->data;
}

// Returns the pointer to the data of the node with the
// largest ID that is less than the given ID.
// Returns NULL if there is no ID in the tree < the given ID.
void *get_max_below(RBT_Node *root, void *id){
    RBT_Node *max_below = get_max_node_below(root, id);
    if (max_below == NULL) return NULL;
    else return max_below->data;
}

void print_indent(int size){
    for (int i=0; i<size; i++){
        printf("\t");
    }
}

void print_tree(RBT_Node *root, int indent_size){
    if(root == NULL){
        print_indent(indent_size);
        printf("NULL\n");
    }
    else{
        print_indent(indent_size);
        printf("%p\n", root->id);
        //        print_indent(indent_size);
        //        if(root->isRed) printf("red%i\n", indent_size);
        //        else printf("black%i\n", indent_size);
        indent_size++;
        print_tree(root->right, indent_size);
        print_tree(root->left, indent_size);
    }
}

int is_BST(RBT_Node *root){
    if (root == NULL) return 1;

    RBT_Node *left = root->left;
    RBT_Node *right = root->right;

    if((left == NULL || left->id < root->id) &&
            (right == NULL || right->id > root->id)){
        return is_BST(left) && is_BST(right);
    }
    return 0;
}
int size(RBT_Node *root){
    if(root == NULL){
        return 0;
    }
    return size(root->left) + size(root->right) + 1;
}

//int main(){
//    srand(time(0));
//    RBT_Node *root = init_tree();
//    int LOOPS = 10000000;
//    int start_size = 1;
//    float start = clock();
//    for (int i=0; i<LOOPS; i++){
//        char *val = 1;
//        val = val+i;
//
//        char *num = rand();
//        RBT_Node *tmp = removeNode(root, num);
//        if (tmp != NULL) root = tmp;
//        num = rand();
//        tmp = add(root, num, num);
//        if (tmp != NULL) root = tmp;
//        int curSize = 1;//size(root);
//        if (curSize != start_size && curSize != start_size+1 && curSize != start_size-1){
//            printf("error\n");
//            exit(1);
//        }
//        start_size = curSize;
//    } 
//    float end = clock();
//    //    print_tree(root, 0);
//    printf("size: %d\n", size(root));
//    printf("max height: %d\n", max_height_rec(root));
//    printf("time: %f\n", (end-start)/CLOCKS_PER_SEC);
//    if(!is_BST(root)){
//        printf("\nNOT BST!!!!\n\n");
//    }
//    printf("%p\n", get_max_below(root, (char*) 334));
//} 
