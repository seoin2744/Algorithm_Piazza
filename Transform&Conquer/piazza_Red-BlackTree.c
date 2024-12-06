#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RedBlackTree {
    Node* root;
    Node* NIL;
} RedBlackTree;

Node* createNode(int data, Node* NIL) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; 
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NULL;
    return newNode;
}

RedBlackTree* createTree() {
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->color = BLACK;
    tree->root = tree->NIL;
    return tree;
}

void leftRotate(RedBlackTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != tree->NIL) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == tree->NIL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rightRotate(RedBlackTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != tree->NIL) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == tree->NIL) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void fixInsertion(RedBlackTree* tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* uncle = z->parent->parent->right;

            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node* uncle = z->parent->parent->left;

            if (uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2: z가 왼쪽 자식
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(RedBlackTree* tree, int data) {
    Node* z = createNode(data, tree->NIL);
    Node* y = tree->NIL;
    Node* x = tree->root;

    while (x != tree->NIL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == tree->NIL) {
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    fixInsertion(tree, z);
}

void inorder(Node* root, Node* NIL) {
    if (root != NIL) {
        inorder(root->left, NIL);
        printf("%d ", root->data);
        inorder(root->right, NIL);
    }
}

int main() {
    RedBlackTree* tree = createTree();

    insert(tree, 13);
    insert(tree, 8);
    insert(tree, 17);
    insert(tree, 1);
    insert(tree, 11);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 6);
    insert(tree, 22);
    insert(tree, 27);
    insert(tree, 9);

    printf("Initial Red-Black Tree (In-order): ");
    inorder(tree->root, tree->NIL);
    printf("\n");

    insert(tree, 24);

    printf("Red-Black Tree after inserting 24 (In-order): ");
    inorder(tree->root, tree->NIL);
    printf("\n");

    return 0;
}
