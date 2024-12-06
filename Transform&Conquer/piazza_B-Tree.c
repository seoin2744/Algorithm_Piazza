#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_KEYS(t) ((t) * 2 - 1)
#define MIN_KEYS(t) ((t) - 1)

typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int keyCount;
    bool isLeaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
    int t; // Minimum degree
} BTree;

BTreeNode *createNode(int t, bool isLeaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->keys = (int *)malloc(MAX_KEYS(t) * sizeof(int));
    node->children = (BTreeNode **)malloc((MAX_KEYS(t) + 1) * sizeof(BTreeNode *));
    node->keyCount = 0;
    node->isLeaf = isLeaf;
    return node;
}

BTree *createBTree(int t) {
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = createNode(t, true);
    tree->t = t;
    return tree;
}

void splitChild(BTreeNode *parent, int i, BTreeNode *child, int t) {
    BTreeNode *newChild = createNode(t, child->isLeaf);
    newChild->keyCount = MIN_KEYS(t);

    for (int j = 0; j < MIN_KEYS(t); j++)
        newChild->keys[j] = child->keys[j + t];

    if (!child->isLeaf) {
        for (int j = 0; j < t; j++)
            newChild->children[j] = child->children[j + t];
    }

    child->keyCount = MIN_KEYS(t);

    for (int j = parent->keyCount; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = newChild;

    for (int j = parent->keyCount - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = child->keys[MIN_KEYS(t)];
    parent->keyCount++;
}

void insertNonFull(BTreeNode *node, int key, int t) {
    int i = node->keyCount - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->keyCount++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;

        if (node->children[i + 1]->keyCount == MAX_KEYS(t)) {
            splitChild(node, i + 1, node->children[i + 1], t);

            if (key > node->keys[i + 1])
                i++;
        }
        insertNonFull(node->children[i + 1], key, t);
    }
}

void insert(BTree *tree, int key) {
    BTreeNode *root = tree->root;

    if (root->keyCount == MAX_KEYS(tree->t)) {
        BTreeNode *newRoot = createNode(tree->t, false);
        newRoot->children[0] = root;

        splitChild(newRoot, 0, root, tree->t);

        int i = (key > newRoot->keys[0]) ? 1 : 0;
        insertNonFull(newRoot->children[i], key, tree->t);

        tree->root = newRoot;
    } else {
        insertNonFull(root, key, tree->t);
    }
}

void traverse(BTreeNode *node) {
    if (node == NULL) return;

    for (int i = 0; i < node->keyCount; i++) {
        if (!node->isLeaf)
            traverse(node->children[i]);
        printf("%c ", node->keys[i]);
    }

    if (!node->isLeaf)
        traverse(node->children[node->keyCount]);
}

void printBTree(BTree *tree) {
    traverse(tree->root);
    printf("\n");
}

int main() {
    BTree *tree = createBTree(5);

    char keys[] = "yagfbkdhmjesrxcltuvoiznqp";
    for (int i = 0; i < sizeof(keys) - 1; i++) {
        insert(tree, keys[i]);
    }

    printf("B-Tree traversal:\n");
    printBTree(tree);

    return 0;
}
