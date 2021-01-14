#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int val;
    struct node *left;
    struct node *right;  
} node;

node * makeNode(int value){
    node *newNode = malloc(sizeof(node));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

node* toAdd(int value, node * newNode, node* root){
    if(root ==  NULL){
        return newNode;
    }
    if(root ->val  == value){
        free(newNode);
        return root;
    }
    if(value < root->val){
        root->left = toAdd(value, newNode, root->left);
    }
    else{
        root->right = toAdd(value,newNode, root->right);
    }
    return root;
}

//Inorder traversal to print in ascending order
void toPrint(node * root){
    if(root == NULL){
        return;
    }
    toPrint(root->left);
    printf("%d\t", root->val);
    toPrint(root->right);
}

//Post order traversal to free nodes
void toFree(node *root){
    if(root == NULL){
        return;
    }
    toFree(root->left);
    toFree(root->right);
    free(root);
}
int main(int argc, char* argv[])
{
    node *root = NULL;
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("error");
        return 0;
    }
    char letter;
    int num;
    while(fscanf(fp, "%c" "%d", &letter, &num) != EOF){
        if(letter == 'i'){
            node * temp = makeNode(num);
            root = toAdd(num,temp,root);
        }
    }

    toPrint(root);
    toFree(root);
    fclose(fp);
}