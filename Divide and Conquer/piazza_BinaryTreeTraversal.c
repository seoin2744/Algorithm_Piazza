#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int key;
    struct _Node *left;
    struct _Node *right;
} Node;

typedef struct {
    Node* root;
} BST;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void create_tree(BST* my_BST) {
    my_BST->root = create_node(60);

    my_BST->root->left = create_node(41);
    my_BST->root->left->left = create_node(16);
    my_BST->root->left->left->right = create_node(25);
    my_BST->root->left->right = create_node(53);
    my_BST->root->left->right->left = create_node(46);
    my_BST->root->left->right->left->left = create_node(42);
    my_BST->root->left->right->right = create_node(55);
    
    my_BST->root->right = create_node(74);
    my_BST->root->right->left = create_node(65);
    my_BST->root->right->left->right = create_node(70);
    my_BST->root->right->left->left = create_node(63);
    my_BST->root->right->left->left->left = create_node(62);
    my_BST->root->right->left->left->right = create_node(64);
}

void preorder_traversal(Node* node) {
    if (node == NULL) return;
    printf("%d ", node->key);         
    preorder_traversal(node->left); 
    preorder_traversal(node->right); 
}

void inorder_traversal(Node* node) {
    if (node == NULL) return;
    inorder_traversal(node->left);   
    printf("%d ", node->key);       
    inorder_traversal(node->right); 
}

void postorder_traversal(Node* node) {
    if (node == NULL) return;
    postorder_traversal(node->left);  
    postorder_traversal(node->right); 
    printf("%d ", node->key);  
}


int main() {
    BST my_BST = {NULL}; 

    create_tree(&my_BST);

    printf("Pre-order Traversal: ");
    preorder_traversal(my_BST.root);
    printf("\n");


    printf("In-order Traversal: ");
    inorder_traversal(my_BST.root);
    printf("\n");

    printf("Post-order Traversal: ");
    postorder_traversal(my_BST.root);
    printf("\n");

    
    return 0;
}
