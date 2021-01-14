#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long time = 0;//keeps time of the whole program

typedef struct block
{
    long time;
    unsigned long tag;
    int valid;
} block;


void replace(block** cache, int setIndex, unsigned long tag, int amountOfBlocks){
    int leastTime = time;
    int indexOfSmallestTime = 0;
    for(int i = 0; i < amountOfBlocks; i++){
        if(cache[setIndex][i].valid == 0){
            indexOfSmallestTime = i;
            break;
        }
        else{
            if(cache[setIndex][i].time < leastTime){
                indexOfSmallestTime = i;
                leastTime = cache[setIndex][i].time;
            }
        }
    }
    cache[setIndex][indexOfSmallestTime].valid = 1;
    cache[setIndex][indexOfSmallestTime].time = time++;
    cache[setIndex][indexOfSmallestTime].tag = tag;
}

int main(int argc, char* argv[])
{
    if(argc != 6){
        printf("error\n");
        return 1;
    }
    long cacheMiss = 0;
    long cacheHit = 0;
    long memRead = 0;
    long memWrite = 0;
    int cacheSize = atoi(argv[1]);
    int blockSize = atoi(argv[4]);

    //checks all the command prompt input if they are power of 2
    if((floor(log2(cacheSize))!= ceil(log2(cacheSize))) || (floor(log2(blockSize))!= ceil(log2(blockSize)))){
        printf("error\n");
        return 1;
    }

    FILE *fp = fopen(argv[5], "r");
    if(fp == NULL){
        printf("error\n");
        return 1;
    }
    int amountOfSet = 0;
    int amountOfBlocks = 0; //amount of Lines/blocks in a set

    //make a 2d array to store all the memory then use the set as x and go through each block in the set
    if(strcmp(argv[2], "direct") == 0){
        amountOfSet = cacheSize/blockSize/1; //cacheSize/blockSize/set assoc
        amountOfBlocks = 1; 
    }
    else if(strcmp(argv[2], "assoc") == 0){
        amountOfSet = 1; //0 index in set has 0 bits
        amountOfBlocks = cacheSize/blockSize;
    }
    else if(argv[2][5] == ':'){
        char *str = argv[2];
        char s[2] = ":";
        char *token;

        token = strtok(str,s);
        token = strtok(NULL,s);
        char num = atoi(token);

        
        if(floor(log2(num)) != ceil(log2(num))){
            printf("error\n");
            return 1;
        }
        amountOfSet = cacheSize/blockSize/num;
        amountOfBlocks = num;
    }
    else{
        printf("error\n");
        return 1;
    }

    block **cache = calloc(amountOfSet, sizeof(block*));

    for(int i = 0; i < amountOfSet; i++){
        cache[i] = calloc(amountOfBlocks, sizeof(block));
    }

    int b = log(blockSize)/log(2); // block bits
    int s = log(amountOfSet)/log(2); // set bits

    int mask = (1 << s) - 1;

    char instruct; //holds the instruction
    long long address; //holds the address long long because the address will be <= 48 and ll is larger and wont cause problems
    int setIndex;
    unsigned long tag;

    while(fscanf(fp,"%*s %c %llx\n", &instruct, &address) != EOF){
        setIndex = (((address >> b) & mask));
        tag = address >> (b + s);

        int didItHit = 0; //bool 0 = true and 1 = false
        if(instruct == 'R'){
            for(int i = 0; i < amountOfBlocks; i++){
                if(cache[setIndex][i].valid == 0 || cache[setIndex][i].tag != tag){
                    continue;
                }
                else if(cache[setIndex][i].tag == tag){
                    if(strcmp(argv[3], "lru") == 0){
                        cache[setIndex][i].time = time++;
                    }
                    cacheHit++;
                    didItHit = 1;
                }
            }
            if(!didItHit){
                cacheMiss++;
                memRead++;
                replace(cache, setIndex, tag, amountOfBlocks);
            }
            didItHit = 0;
        }
        else if(instruct == 'W'){
            for(int i = 0; i < amountOfBlocks; i++){
                if(cache[setIndex][i].valid == 0 || cache[setIndex][i].tag != tag){
                    continue;
                }
                else if(cache[setIndex][i].tag == tag){
                    if(strcmp(argv[3], "lru") == 0){
                        cache[setIndex][i].time = time++;
                    }
                    cacheHit++;
                    didItHit = 1;
                    memWrite++;
                }
            }
            if(!didItHit){
                memRead++;
                memWrite++;
                cacheMiss++;
                replace(cache, setIndex, tag, amountOfBlocks);
            }
            didItHit = 0;
        }
    }
    printf("Memory reads: %ld\n", memRead);
    printf("Memory writes: %ld\n", memWrite);
    printf("Cache hits: %ld\n", cacheHit);
    printf("Cache misses: %ld\n", cacheMiss);

    for(int i = 0; i < amountOfSet; i++){
        free(cache[i]);
    }
    free(cache);
    fclose(fp);
}