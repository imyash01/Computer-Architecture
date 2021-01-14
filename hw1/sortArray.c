#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("error");
        return 0;
    }
    int arrSize = 0;
    int numOfEvens = 0;
    int numOfOdds = 0;

    fscanf(fp, "%d\n", &arrSize);
    int arr[arrSize];
    //stores all the numbers in the file into an array
    for(int i = 0; i < arrSize; i++){
        int num = 0;
        fscanf(fp, "%d\t", &num);
        if((num %2) == 0){
            numOfEvens++;
        }
        else{
            numOfOdds++;
        }
        arr[i] = num;
    }
    fclose(fp);

    int even[numOfEvens];
    int odd[numOfOdds];
    int indexevn = 0;
    int indexodd = 0;
    for(int j = 0; j < arrSize; j++){
        if((arr[j]%2) == 0){
            even[indexevn] = arr[j];
            indexevn++;
        }
        else{
            odd[indexodd] = arr[j];
            indexodd++;
        }
    }

    int i, num, j;
    for(i = 1; i < indexevn; i++){
        num = even[i];
        j = i - 1;
        while(j >= 0 && even[j] > num){
            even[j + 1] = even[j];
            j = j - 1;
        }
        even[j + 1] = num;
    }

    int k, curr, l;
    for(k = 1; k < indexodd; k++){
        curr = odd[k];
        l = k - 1;
        while(l >= 0 && odd[l] < curr){
            odd[l + 1] = odd[l];
            l = l - 1;
        }
        odd[l + 1] = curr;
    }
    
    for(int i = 0; i < indexevn; i++){
        printf("%d\t" , even[i]);
    }
    for(int j = 0; j < indexodd; j++){
        printf("%d\t", odd[j]);
    }
    return 0;
}
