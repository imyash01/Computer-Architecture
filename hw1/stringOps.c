#include <stdio.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("\n");
    }
    for(int i = 1; i < argc; i++){
        for(int j = 0; j < strlen(argv[i]); j++){
            char c = argv[i][j];
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c =='u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c =='U'){
                printf("%c", c);
            }
        }
    }
    return 0;
}