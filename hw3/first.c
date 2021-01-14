#include <stdio.h>
#include <string.h>

int get(unsigned short num, int n){
        if((num & (1 << n)) != 0)
            return 1;
        else
            return 0;
    }
    
unsigned short set(unsigned short num, unsigned short n, unsigned short bit){
    if(bit == 0){
        return num & (~(1 << n));
    }
    else{
        return num | (1 << n);
    }
}

unsigned short comp(unsigned short num, unsigned short n){
    return num ^ (1 << n);
}

int main(int argc, char* argv[])
{
    FILE *fp = fopen(argv[1], "r");

    unsigned short x;

    fscanf(fp, "%hu\n", &x);

    char c[5];

    while(fscanf(fp, "%s\t", &c[0]) != EOF){
        unsigned short n;
        unsigned short bit;
        if(strcmp("set", c) == 0){
            fscanf(fp, "%hu\t", &n);
            fscanf(fp, "%hu\n", &bit);
            x = set(x,n,bit);
            printf("%hu\n",x);
        }
        else if(strcmp("get", c) == 0){
            fscanf(fp, "%hu\t", &n);
            fscanf(fp, "%hu\n", &bit); // added to go to the new line
            if(get(x,n) != 0)
                printf("1\n");
            else
                printf("0\n");
            
        }
        else{
            fscanf(fp, "%hu\t", &n);
            fscanf(fp, "%hu\n", &bit); // added to go to the new line   
            x = comp(x,n);
            printf("%hu\n", x);
        }
    }
    fclose(fp);
    return 0;
}
