#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool wkeres(char* a, char* b)
{

    printf(".\n");
    int al = strlen(a) -1;
    int bl = strlen (b) -1;
    if(bl < 1 || al == 0 || bl > al+1)
    {
        return false;
    }
    int ch = -1;
    for(int i = 0;i<bl;i++)
    {
        if(b[i] == '*')
        {
            ch = i;
        }
    }
    if(ch == 0)
    {
        int s = al;
        for(int i = bl-1;i >= 1;i--)
        {
            if(a[s--] != b[i])
            {
                return false;
            }
        }
        return 1;
    }
    else if(ch == bl-1)
    {
        for(int i = 0;i<bl-1;i++)
        {
            if(a[i] != b[i])
            {
                return false;
            }
        }
        return 1;
    }
    else if(ch != -1)
    {
        for(int i = 0;i<ch;i++)
        {
            if(a[i] != b[i])
            {
                return false;
            }
        }
        int s = bl-1;
        for(int i = al;i > al-(bl-ch-1);i--)
        {
            if(a[i] != b[s--])
            {
                return false;
            }
        }
        return 1;
    }
    else
        {
            b[bl] = '\0';
            if(strcmp(a,b) == 0)
            {
                return 1;
            }
        }
    return false;

}

int main()
{
    typedef struct Nevek
    {
        char* nev;
    }Nevek;
    Nevek n[10];
    n[0].nev = "Toth Bernadett";
    n[1].nev = "Szabo Jozsef";
    n[2].nev = "Bogdan Roland";
    n[3].nev = "Virag Mihaly";
    n[4].nev = "Szalai Csaba";
    n[5].nev = "Drozda Gabor";
    n[6].nev = "Szladek Mate";
    n[7].nev = "Banki Andras";
    n[8].nev = "Toth Adam Laszlo";
    n[9].nev = "Baksa-Toth Balazs";

    printf("Mekafull kereso algoritmus v1.0 by TA1120\n");
    char* hk[51];
    while(strcmp(hk,"end\n") != 0)
    {
        printf("\n\n");
    fgets(hk,50,stdin);
    if(strcmp(hk,"end\n") == 0)
    {
        break;
    }
    for(int i = 0;i<10;i++)
    {
        if(wkeres(n[i].nev,hk))
        {
            printf("%s\n",n[i].nev);
        }

    }
    }
    return 0;
}
