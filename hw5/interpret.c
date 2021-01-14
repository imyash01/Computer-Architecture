#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short add(short x, short y){
    return x + y;
}

short sub(short x, short y){
    return y - x;
}

short mul(short x, short y){
    return x * y;
}

short division(short x, short y){
    return x/y;
}

int regIndex(char regString[]){
    if(strcmp(regString,"ax") == 0){
        return 0;
    }
    else if(strcmp(regString,"bx") == 0){
        return 1;
    }
    else if(strcmp(regString,"cx") == 0){
        return 2;
    }
    else if(strcmp(regString,"dx") == 0){
        return 3;
    }
    else{
        return -1;
    }
}

int main(int argc, char* argv[])
{
    //index for each register ax is 0, bx is 1,cx is 2, dx is 3
    short regs[4] = {0};

    //a 2d array with row greater than 100 and columns greater than 18
    // the file is going to have 100 lines and the largest number is going to be 6 digits with command length
    char fileInArray[101][101] = {0};

    FILE *fp = fopen(argv[1], "r");

    if(fp == NULL){
        printf("Error");
        return -1;
    }

    int totalLines = 0; //In the end will give total file lines starts from 0 to total
    while(fgets(fileInArray[totalLines], 101, fp) != NULL){
        totalLines++;
    }

    //for loop loops through the whole array with lines
    for(int i = 0; i < totalLines; i++){
        char command[101];
        //Checks if there is a command if line is empty it goes to the next
        if(sscanf(fileInArray[i], "%s", command) != 1){
            continue; //skips the line if there is a no-op
        }

        //Checking with all the commands
        //FirstArg is the command of the line
        if(strcmp("mov",command) == 0){
            char secondArg[7];
            char thirdArg[7];
            sscanf(fileInArray[i], "%s %s %s", command, secondArg, thirdArg);
            int returnValue = regIndex(secondArg);//store the value returned by the regIndex to use later

            if(returnValue != - 1){
                regs[regIndex(thirdArg)] = regs[returnValue];
            }
            else{
                regs[regIndex(thirdArg)] = atoi(secondArg);
            }
        }
        else if(strcmp("add",command) == 0){
            char secondArg[7];
            char thirdArg[7];
            sscanf(fileInArray[i], "%s %s %s", command, secondArg, thirdArg);
            int returnValue = regIndex(secondArg);//store the value returned by the regIndex to use later
            if(returnValue != - 1){
                short x = regs[regIndex(secondArg)];
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = add(x,y);
            }
            else{
                short x = atoi(secondArg);
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = add(x,y);
            }
        }
        else if(strcmp("sub",command) == 0){
            char secondArg[7];
            char thirdArg[7];
            sscanf(fileInArray[i], "%s %s %s", command, secondArg, thirdArg);
            int returnValue = regIndex(secondArg);//store the value returned by the regIndex to use later
            if(returnValue != - 1){
                short x = regs[regIndex(secondArg)];
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = sub(x,y);
            }
            else{
                short x = atoi(secondArg);
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = sub(x,y);
            }
        }
        else if(strcmp("mul",command) == 0){
            char secondArg[7];
            char thirdArg[7];
            sscanf(fileInArray[i], "%s %s %s", command, secondArg, thirdArg);
            int returnValue = regIndex(secondArg);//store the value returned by the regIndex to use later
            if(returnValue != - 1){
                short x = regs[regIndex(secondArg)];
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = mul(x,y);
            }
            else{
                short x = atoi(secondArg);
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = mul(x,y);
            }
        }
        else if(strcmp("div",command) == 0){
            char secondArg[7];
            char thirdArg[7];
            sscanf(fileInArray[i], "%s %s %s", command, secondArg, thirdArg);
            int returnValue = regIndex(secondArg);//store the value returned by the regIndex to use later
            if(returnValue != - 1){
                short x = regs[regIndex(secondArg)];
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = division(x,y);
            }
            else{
                short x = atoi(secondArg);
                short y = regs[regIndex(thirdArg)];
                regs[regIndex(thirdArg)] = division(x,y);
            }
        }
        else if(strcmp("jmp",command) == 0){
            int index;
            sscanf(fileInArray[i], "%s %d", command, &index);
            i = index - 1;
        }
        else if(strcmp("je",command) == 0){
            int index;//is the L
            char secondArg[7];
            char thirdArg[7];
            short x = 0;
            short y = 0;
            sscanf(fileInArray[i], "%s %d %s %s", command, &index, secondArg, thirdArg);
            if(regIndex(secondArg) != -1){
                x = regs[regIndex(secondArg)];
            }
            else{
                x = atoi(secondArg);
            }
            if(regIndex(thirdArg) != -1){
                y = regs[regIndex(thirdArg)];
            }
            else{
                y = atoi(thirdArg);
            }
            if(x == y){
                i = index - 1;
            }
        }
        else if(strcmp("jne",command) == 0){
            int index;//is the L
            char secondArg[7];
            char thirdArg[7];
            short x = 0;
            short y = 0;
            sscanf(fileInArray[i], "%s %d %s %s", command, &index, secondArg, thirdArg);
            if(regIndex(secondArg) != -1){
                x = regs[regIndex(secondArg)];
            }
            else{
                x = atoi(secondArg);
            }
            if(regIndex(thirdArg) != -1){
                y = regs[regIndex(thirdArg)];
            }
            else{
                y = atoi(thirdArg);
            }
            if(x != y){
                i = index - 1;
            }
        }
        else if(strcmp("jg",command) == 0){
            int index;//is the L
            char secondArg[7];
            char thirdArg[7];
            short x = 0;
            short y = 0;
            sscanf(fileInArray[i], "%s %d %s %s", command, &index, secondArg, thirdArg);
            if(regIndex(secondArg) != -1){
                x = regs[regIndex(secondArg)];
            }
            else{
                x = atoi(secondArg);
            }
            if(regIndex(thirdArg) != -1){
                y = regs[regIndex(thirdArg)];
            }
            else{
                y = atoi(thirdArg);
            }
            if(x > y){
                i = index - 1;
            }
        }
        else if(strcmp("jge",command) == 0){
            int index;//is the L
            char secondArg[7];
            char thirdArg[7];
            short x = 0;
            short y = 0;
            sscanf(fileInArray[i], "%s %d %s %s", command, &index, secondArg, thirdArg);
            if(regIndex(secondArg) != -1){
                x = regs[regIndex(secondArg)];
            }
            else{
                x = atoi(secondArg);
            }
            if(regIndex(thirdArg) != -1){
                y = regs[regIndex(thirdArg)];
            }
            else{
                y = atoi(thirdArg);
            }
            if(x >= y){
                i = index - 1;
            }
        }
        else if(strcmp("jl",command) == 0){
            int index;//is the L
            char secondArg[7];
            char thirdArg[7];
            short x = 0;
            short y = 0;
            sscanf(fileInArray[i], "%s %d %s %s", command, &index, secondArg, thirdArg);
            if(regIndex(secondArg) != -1){
                x = regs[regIndex(secondArg)];
            }
            else{
                x = atoi(secondArg);
            }
            if(regIndex(thirdArg) != -1){
                y = regs[regIndex(thirdArg)];
            }
            else{
                y = atoi(thirdArg);
            }
            if(x < y){
                i = index - 1;
            }
        }
        else if(strcmp("jle",command) == 0){
            int index;//is the L
            char secondArg[7];
            char thirdArg[7];
            short x = 0;
            short y = 0;
            sscanf(fileInArray[i], "%s %d %s %s", command, &index, secondArg, thirdArg);
            if(regIndex(secondArg) != -1){
                x = regs[regIndex(secondArg)];
            }
            else{
                x = atoi(secondArg);
            }
            if(regIndex(thirdArg) != -1){
                y = regs[regIndex(thirdArg)];
            }
            else{
                y = atoi(thirdArg);
            }
            if(x <= y){
                i = index - 1;
            }
        }
        else if(strcmp("read",command) == 0){
            char secondArg[5];
            sscanf(fileInArray[i], "%s %s", command, secondArg);
            short input;
            scanf("%hd",&input);
            regs[regIndex(secondArg)] = input;
        }
        else if(strcmp("print",command) == 0){
            char secondArg[5];
            sscanf(fileInArray[i], "%s %s", command, secondArg);
            int returnValue = regIndex(secondArg);//stores the return value in the array
            if(returnValue != -1){
                printf("%d", regs[returnValue]);
            }
            else{
                printf("%d", atoi(secondArg));
            }
        }
        else{
            printf("wrong command");
            return -1;
        }
    }

    fclose(fp);
    return 0;
}
