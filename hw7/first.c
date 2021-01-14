#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//holds the index of where it is in the first line
// inputvar 2 A B. A will hold 1 and B 0
typedef struct node{
    char *name;
    int value;
    struct node  *next;
}node;


//Adds to the end of the Linked List
node* addVariable(node *head, char *str){
    node *temp = calloc(1,sizeof(node));
    temp->name = malloc(100);
    strcpy(temp->name, str);
    temp->value = 0;
    temp->next = NULL;

    node *curr = head;
    node *prev = head;

    if(head == NULL){
        return temp;
    }
    else{
        while(curr != NULL){
            prev = curr;
            curr = curr->next;
        }
        prev->next = temp;
    }
    return head;
}

node * toFind(node *head, char *str){
    node *curr = head;
    while(curr != NULL){
        if(strcmp(curr->name,str) == 0){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("error\n");
        return 0;
    }
    
    char linesInArray[1000][1000]  = {0};
    int totalLines = 0;
    while(fgets(linesInArray[totalLines], 1000, fp) != NULL){
        totalLines++;
    }
    
    int numInput;
    int numOutput;

    node *head = NULL;

    char *tempStr = malloc(1000);

    strtok(linesInArray[0], " \n");
    numInput = atoi(strtok(NULL," \n"));
    for(int i = 0; i < numInput; i++){
        strcpy(tempStr,strtok(NULL, " \n"));
        head = addVariable(head, tempStr);
    }

    strtok(linesInArray[1], " \n");
    numOutput = atoi(strtok(NULL," \n"));
    for(int i = 0; i < numOutput; i++){
        strcpy(tempStr,strtok(NULL, " \n"));
        head = addVariable(head, tempStr);
    }

    char *opr = malloc(10);
    char *var1 = malloc(1000);
    char *var2 = malloc(1000); // this can be used for store if we use not where there is only one variable
    char *store = malloc(1000); // stores the output of var1 oprand var2

    for(int i = 0; i < pow(2, numInput); i++){
        node *ptr = head;
        for(int j = numInput - 1; j >= 0; j--){
            if(i & (1 << j)){
                printf("1 ");
                ptr->value = 1;
            }
            else{
                printf("0 ");
                ptr->value = 0;
            }
            ptr = ptr->next;
        }
        for(int i = 2; i < totalLines; i++){

            sscanf(linesInArray[i], "%s %s %s %s", opr, var1, var2, store);
            if(strcmp(opr, "NOT") == 0){
                if(toFind(head, var2) == NULL){
                    head = addVariable(head, var2);
                }
                toFind(head, var2)->value = !(toFind(head,var1)->value);
            }
            else if(strcmp(opr, "AND") == 0){
                if(toFind(head, store) == NULL){
                    head = addVariable(head, store);
                }
                toFind(head, store)->value = (toFind(head,var1)->value & toFind(head,var2)->value);
            }
            else if(strcmp(opr, "OR") == 0){
                if(toFind(head, store) == NULL){
                    head = addVariable(head, store);
                }
                toFind(head, store)->value = (toFind(head,var1)->value | toFind(head,var2)->value);
            }
            else if(strcmp(opr, "NAND") == 0){
                if(toFind(head, store) == NULL){
                    head = addVariable(head, store);
                }
                toFind(head, store)->value = !(toFind(head,var1)->value & toFind(head,var2)->value);
            }
            else if(strcmp(opr, "NOR") == 0){
                if(toFind(head, store) == NULL){
                    head = addVariable(head, store);
                }
                toFind(head, store)->value = !(toFind(head,var1)->value | toFind(head,var2)->value);
            }
            else if(strcmp(opr, "XOR") == 0){
                if(toFind(head, store) == NULL){
                    head = addVariable(head, store);
                }
                toFind(head, store)->value = (toFind(head,var1)->value ^ toFind(head,var2)->value);
            }
        }
        for(int i = 0; i < numOutput; i++){
            printf("%d ", ptr->value);
            ptr = ptr->next;
        }
        printf("\n");
    }

    node *temp1;
    while(head!=NULL)
    {
        temp1 = head;
        head = head->next;
        free(temp1->name);
        free(temp1);
    }
    free(tempStr);
    free(opr);
    free(var1);
    free(var2);
    free(store);
    fclose(fp);
}