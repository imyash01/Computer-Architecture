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

    for(int i = 0; i < 8; i++){
        if(get(num,i) != get(num, 15 - i)){
            printf("Not-Palindrome");
            return 0;
        }
    }
    printf("Is-Palindrome");
    return 0;
}