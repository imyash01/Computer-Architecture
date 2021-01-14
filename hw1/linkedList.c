#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;    
} node;

// adds a new node in a increasing order
void toAdd(int value, node **head){
    node *newNode = malloc(sizeof(node));
    newNode->val = value;
    newNode->next = NULL;
     if(head == NULL)
     {
         *head = newNode;
     }
     else{
         node *curr = *head;
         node *prev = NULL;
         while(curr != NULL){
             if(curr->val > value)
                break;
             prev = curr;
             curr = curr -> next;
         }
         if(prev == NULL){
             newNode->next = curr;
             *head = newNode;
         }
         else{
            newNode->next = prev->next;
            prev->next = newNode;
         }
     }
}
void toDelete(int value, node** head){
    if((*head) != NULL) {
        if((*head)->val == value){
            node * temp = *head; 
            *head = (*head)->next;
            free(temp);
        }
    else{
        node * curr = *head;
        node* prev = NULL;
        while(curr != NULL && curr->val != value){
            prev = curr;
            curr = curr -> next;
        }
        if(curr != NULL){
            node* temp = prev->next; 
            prev->next = curr->next;
            free(temp);
        }
    }
    }
}
void printlist(node *head){
    node *curr = head;
    node *prev = NULL;
    while (curr != NULL){
        if(prev == NULL && curr == head)
            printf("%d\t", curr->val);
        else if(prev != NULL && prev->val != curr->val)
            printf("%d\t", curr->val);
        prev = curr;
        curr = curr->next;
    }
    printf("\n");
}
int main(int argc, char* argv[])
{
    node *head = NULL;
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
        if(letter == 'i'){
            toAdd(num,&head);
        }
        if(letter == 'd'){
            toDelete(num, &head);
        }
    }while(fscanf(fp, "%c\t" "%d\n", &letter, &num) != EOF);

    
    node *ptr = head;
    int total = 0;
    while(ptr != NULL){
        total++;
        ptr = ptr->next;
    }

    printf("%d\n", total);
    printlist(head);
    fclose(fp);

    node *temp1;
    while(head!=NULL)
    {
    temp1 = head;
    head = head->next;
    free(temp1);
    }

    temp1 = NULL;
    return 0;
}
