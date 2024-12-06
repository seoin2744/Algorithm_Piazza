#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 2 
#define MIN_KEYS 1

typedef struct _Node {
    int nkeys;             
    int keys[MAX_KEYS+1];   
    struct _Node *children[MAX_KEYS+2]; 
    int isLeaf;
} Node;

Node* createNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->nkeys = 0;
    for (int i = 0; i < MAX_KEYS+2; i++)
        node->children[i] = NULL;
    node->isLeaf = 1;
    return node;
}

void inorderPrint(Node *root) {
    if (root == NULL) return;
    if (root->isLeaf) {
        for (int i = 0; i < root->nkeys; i++)
            printf("%d ", root->keys[i]);
    } else {
        int i;
        for (i = 0; i < root->nkeys; i++) {
            inorderPrint(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        inorderPrint(root->children[i]);
    }
}

void splitChild(Node* parent, int idx, Node* child) {
    Node* newNode = createNode();
    newNode->isLeaf = child->isLeaf;

    int mid = child->nkeys / 2;

    int i;
    for (i = mid+1; i < child->nkeys; i++) {
        newNode->keys[i - (mid+1)] = child->keys[i];
        newNode->children[i - (mid+1)] = child->children[i];
    }
    newNode->children[i - (mid+1)] = child->children[i];

    newNode->nkeys = child->nkeys - (mid+1);
    child->nkeys = mid;

    for (i = parent->nkeys; i >= idx+1; i--) {
        parent->children[i+1] = parent->children[i];
    }
    parent->children[idx+1] = newNode;

    for (i = parent->nkeys - 1; i >= idx; i--) {
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[idx] = child->keys[mid];
    parent->nkeys += 1;
}

void insertNonFull(Node* node, int key) {
    int i = node->nkeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->nkeys += 1;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        Node *child = node->children[i];
        if (child->nkeys == MAX_KEYS+1) { 
            splitChild(node, i, child);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(Node** rootRef, int key) {
    Node* root = *rootRef;
    if (root == NULL) {
        root = createNode();
        root->keys[0] = key;
        root->nkeys = 1;
        *rootRef = root;
        return;
    }

    if (root->nkeys == MAX_KEYS+1) {
        Node* newRoot = createNode();
        newRoot->isLeaf = 0;
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        int i = 0;
        if (key > newRoot->keys[0]) i++;
        insertNonFull(newRoot->children[i], key);
        *rootRef = newRoot;
    } else {
        insertNonFull(root, key);
    }
}

int main() {
    Node *root = NULL;
    char input[100];

    while (1) {
        printf("다음 값을 입력하세요 (q: 종료): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "q") == 0) {
            printf("종료합니다.\n");
            break;
        }

        int val = atoi(input);
        insert(&root, val);

        printf("현재 트리 상태 (inorder): ");
        inorderPrint(root);
        printf("\n");
    }
    return 0;
}
