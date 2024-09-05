#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

AVLNode* newNode(int key);
int getHeight(AVLNode* node);
void updateHeight(AVLNode* node);
AVLNode* leftRotate(AVLNode* x);
AVLNode* rightRotate(AVLNode* y);
int getBalance(AVLNode* node);
AVLNode* insert(AVLNode* root, int key);
void inOrder(AVLNode* root);

AVLNode* newNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    if (node) {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
    }
    return node;
}

int getHeight(AVLNode* node) {
    return (node == NULL) ? 0 : node->height;
}

void updateHeight(AVLNode* node) {
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

int getBalance(AVLNode* node) {
    return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);
}

AVLNode* insert(AVLNode* root, int key) {
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // Duplicate keys not allowed
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    switch (balance) {
        case 2:
            if (key < root->left->key)
                return rightRotate(root);
            else {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
            break;
        case -2:
            if (key > root->right->key)
                return leftRotate(root);
            else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
            break;
        default:
            return root;
            break;
    }
}


void inOrder(AVLNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void preOrder(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->key);  
        preOrder(root->left);      
        preOrder(root->right);     
    }
}

void postOrder(AVLNode* root) {
    if (root != NULL) {
        postOrder(root->left);     
        postOrder(root->right);    
        printf("%d ", root->key);  
    }
}

void freeTree(AVLNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    AVLNode* root = NULL;

    root = insert(root, 60);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    printf("AVL TREE: ");
    inOrder(root);
    printf("\n");
    freeTree(root);
    return 0;
}
