#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int i;
    i=0;
    printf("#");
    while(i<argc)
    {
        printf("%s#",argv[i]);
        i++;
    }
    printf("\n");
    return 0;
}