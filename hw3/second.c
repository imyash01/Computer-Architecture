#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get(unsigned short num, int n){
    if((num & (1 << n)) != 0)
        return 1;
    else
        return 0;
}

int main(int argc, char* argv[])
{
    unsigned short num = atoi(argv[1]);

    int prevIsOne = 0; // If this is 0 previous wasnt 1 otherwise it was 1
    int countOfOne = 0;
    int pairs = 0;

    for(int i = 0; i < 16; i++){
        if(get(num, i) == 1){
            countOfOne++;
            if(prevIsOne == 1){
                pairs++;
                prevIsOne = 0;
            }
            else{
                prevIsOne = 1;
            }
        }
        else{
            prevIsOne = 0;
        }
    }
    if(countOfOne % 2 == 0){
        printf("Even-Parity\t%d", pairs);
    }
    else{
        printf("Odd-Parity\t%d", pairs);
    }
    return 0;
}