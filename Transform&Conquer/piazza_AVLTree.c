#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int height(Node* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    node->height = 1; 
    return node;
}

void updateHeight(Node* node) {
    node->height = max(height(node->left), height(node->right)) + 1;
}

int balanceFactor(Node* node) {
    return height(node->left) - height(node->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}


Node* balance(Node* node) {
    updateHeight(node);

    if (balanceFactor(node) > 1 && balanceFactor(node->left) >= 0)
        return rightRotate(node);

    if (balanceFactor(node) > 1 && balanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balanceFactor(node) < -1 && balanceFactor(node->right) <= 0)
        return leftRotate(node);

    if (balanceFactor(node) < -1 && balanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int value) {
    if (!root) return root;

    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }

    return balance(root);
}

void inorderTraversal(Node* node) {
    if (!node) return;
    inorderTraversal(node->left);
    printf("%d ", node->value);
    inorderTraversal(node->right);
}

void printTree(Node* root) {
    inorderTraversal(root);
    printf("\n");
}

int main() {
    Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(10);
    root->left->left = createNode(2);
    root->left->right = createNode(4);
    root->right->left = createNode(7);
    root->right->right = createNode(11);
    root->left->left->left = createNode(1);
    root->right->left->left = createNode(6);
    root->right->left->right = createNode(9);
    root->right->right->right = createNode(12);
    root->right->left->right->left = createNode(8);

    printf("Original Tree (in-order): ");
    printTree(root);

    root = deleteNode(root, 10);
    printf("Tree after deleting 10 (in-order): ");
    printTree(root);

    return 0;
}
