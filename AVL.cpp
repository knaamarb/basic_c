#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Node
{
    int key;
    int height;
    struct Node *left, *right;
};

struct Node *createNode(int key){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->height = 1;
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int max(int a, int b){
    return a > b ? a : b;
}

int height(struct Node *tmp){
    if(tmp == NULL)return 0;
    return tmp->height;
}

int balanceFac(struct Node *tmp){
    if (tmp == NULL) return 0;
    return height(tmp->left)-height(tmp->right);
}

// left rotate
struct Node *leftRotate(struct Node *x){
    struct Node *y = x->right;
    struct Node *yl = y->left;

    y->left = x;
    x->right = yl;

    x->height = max(height(x->right), height(x->left))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    return y;
}

// right rotate
struct Node *rightRotate(struct Node *y){
    struct Node *x = y->left;
    struct Node *xr = x->right;

    x->right = y;
    y->left = xr;
    
    x->height = max(height(x->right), height(x->left))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return x;
}


// balance node
struct Node *balanceNode(struct Node *node){
    if(node == NULL)return 0;
    node->height = max(height(node->left), height(node->right))+1;
    int balance = balanceFac(node);

    if(balance > 1 && balanceFac(node->left)>=0){
        return rightRotate(node);
    }

    if(balance > 1 && balanceFac(node->left)< 0){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if(balance < -1 && balanceFac(node->right)<= 0){
        return leftRotate(node);
    }
    if(balance <-1 && balanceFac(node->right)> 0){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


struct Node *insertNode(struct Node *node, int key){
    if(node == NULL) return createNode(key);
    if(key < node->key)node->left = insertNode(node->left, key);
    else if (key > node->key)node->right = insertNode(node->right, key);
    else return node;
    
    return balanceNode(node);
}

struct Node *minVal(struct Node *curr){
    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
    
}

struct Node *deleteNode(struct Node *node, int key){
    if(node == NULL) return 0;
    if(key < node->key)node->left = deleteNode(node->left, key);
    else if(key > node->key)node->right = deleteNode(node->right, key);
    else{
        if(node->left == NULL || node->right == NULL){
            struct Node *tmp = node->left ? node->left:node->right;
            if(tmp == NULL){
                tmp = node;
                node = NULL;
                free(tmp);
                return NULL;
            }else{
                *node = *tmp;
                free(tmp);
            }
        }else{
            struct Node *tmp = minVal(node->right);
            node->key = tmp->key;
            node->right = deleteNode(node->right, tmp->key);
        }
    }
    if(node == NULL) return 0;
    return balanceNode(node);

}

void print(struct Node *curr){
    if (curr != NULL)
    {
        printf("%d ", curr->key);
        print(curr->left);
        print(curr->right);
    }

}


int main(){
    struct Node *root = NULL;

    root = insertNode(root, 8);
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    print(root); puts("");
    root = deleteNode(root, 8);
    root = insertNode(root, 3);
    root = insertNode(root, 30);

    print(root);

    return 0;
}