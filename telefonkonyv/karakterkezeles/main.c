#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void char_check(char* str)
{
    bool off = 0;
    int l = strlen(str)-1;
    for(int i = 0;i<l;i++)
    {
        printf("%c %d\n",str[i],str[i]);
        if(str[i] < 32 || str[i]>126)
        {
            off = 1;
        }
    }
    printf("%d hossz\n",l);
    if(off)
    {
        printf("[Figyelem!] A bemenet tiltott karaktert tartalmaz!\n");
    }
}

void lista()
{
    for(int i = 32;i<127;i++)
    {
        printf("%c %d\n",i,i);
    }
}

int main()
{
    char* be[51];
    while(strcmp(be,"end\n") != 0)
    {
        fflush(stdin);
        fgets(be,50,stdin);
        printf("\n");
        if(strcmp(be,"lista\n") != 0)
        {
            char_check(be);
        }
        else
        {
            lista();
        }
    }
    printf("Program vege...\n");
    return 0;
}
