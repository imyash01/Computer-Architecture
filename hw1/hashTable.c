#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node
{
    int val;
    struct node *next;
} node;

typedef struct key
{
    struct node *head;
} key;

int hash(int num){
    int output = num % 10000;
    if(output < 0){
        return output + 10000;
    }
    return output;
}

bool insert(struct key * arr, int i, int value){
    // returns false if there in no collusion
    node *newNode = malloc(sizeof(node));
    newNode->val = value;
    newNode->next = NULL;
    if(arr[i].head == NULL){
        arr[i].head = newNode;
        return false;
    }
    else{
        node * currHead = arr[i].head;
        arr[i].head = newNode;
        newNode->next = currHead;
        return true;
    }
}

bool search(struct key *arr, int i, int value){
    if(arr[i].head == NULL){
        return false;
    }
    else{
        node *ptr = arr[i].head;
        while(ptr != NULL){
            if(ptr->val == value){
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }
}
int main(int argc, char* argv[]){
    key arr_key[10000] = {NULL};
    int numOfColl = 0;
    int numOfSuccess = 0;
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("error");
        return 0;
    }
    char letter;
    int num;
    if(argc < 2 || fscanf(fp, "%c\t" "%d\n", &letter, &num) < 2){
        printf("\n");
        return 0;
    }
    do{
        int i = hash(num);
        if(letter == 'i'){
            if(search(arr_key, i, num)){
                numOfColl++;
            }
            else if(insert(arr_key, i, num)){
                numOfColl++;
            }
        }
        if(letter == 's'){
            if(search(arr_key, i, num)){
                numOfSuccess++;
            }
        }
    }while((fscanf(fp, "%c\t" "%d\n", &letter, &num) != EOF));

    printf("%d\n%d", numOfColl, numOfSuccess);
    fclose(fp);

    for(int i = 0; i < 10000; i++){
        node *temp1 = arr_key[i].head;
        node *temp2 = NULL;
        if(temp1 != NULL){
            while(temp1!=NULL){
                temp2 = temp1;
                temp1 = temp1->next;
                free(temp2);
            }
        }
        temp1 = NULL;
        temp2 = NULL;
    }
    return 0;
}