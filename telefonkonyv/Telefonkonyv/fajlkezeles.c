#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include "adatkezeles.h"
#include "fajlkezeles.h"
#include "felulet.h"

void sorbol_feltolt(Rekord* uj, char* sor)
{
    sscanf(sor,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",uj->name.lname,uj->name.fname,uj->ctel,uj->htel,uj->wtel,uj->address.addr,uj->address.city,uj->address.zip,uj->waddr.addr,uj->waddr.city,uj->waddr.zip,uj->ceg,uj->osztaly,uj->beosztas,uj->email,uj->bday);
}

Rekord* betoltes(Rekord* ab)
{
    printf("Kerem adja meg a beolvasni kivant CSV fajl nevet!(kiterjesztes jeloles nelkul)\n");
    char* fajlnev[20];
    scanf("%s",&fajlnev);
    strcat(fajlnev,".csv");
    FILE* be;
    be = fopen(fajlnev,"r");
    if(be != NULL)
    {
        printf("\nSikeres fajlnyitas!\n\n");
        char sor[501];
        fgets(sor,500,be);
        Rekord* elozo = ab;
        Rekord* uj;
        while(fgets(sor,500,be) != NULL)
        {
            uj = (Rekord*) malloc(sizeof(Rekord));
            sorbol_feltolt(uj,sor);
            uj->kov = elozo;
            elozo = uj;
        }
        fclose(be);
        pre();
        return uj;
    }
    else
    {
        sikertelen("fajlletrehozas");
        aktiv_ab = false;
        return NULL;
    }
}

void fajlba_kiir(Rekord* ab)
{
    if(dbcheck(ab))
    {
        return;
    }
    printf("Adjon meg egy fajlnevet!(kiterjesztes jeloles nelkul)\n");
    char fajlnev[20];
    scanf("%s",&fajlnev);
    strcat(&fajlnev,".csv");
    FILE* ki;
    ki = fopen(fajlnev,"w");
    if(ki != NULL)
    {
        fprintf(ki,"Vezeteknev,Keresztnev,Mobil szam,Otthoni szam,Munkahelyi szam,Lakcim_cim,Lakcim_varos,Lakcim_irsz,");
        fprintf(ki,"Mhely_cim,Mhely_varos,Mhely_irsz,Ceg,Osztaly,Beosztas,Email,Szuletesnap");
        fprintf(ki,"\n");
        Rekord* mozgo = ab;
        while(mozgo->kov != NULL)
        {
            fprintf(ki,"%s,%s,",mozgo->name.lname,mozgo->name.fname);
            fprintf(ki,"%s,%s,%s,",mozgo->ctel,mozgo->htel,mozgo->wtel);
            fprintf(ki,"%s,%s,%s,",mozgo->address.addr,mozgo->address.city,mozgo->address.zip);
            fprintf(ki,"%s,%s,%s,",mozgo->waddr.addr,mozgo->waddr.city,mozgo->waddr.zip);
            fprintf(ki,"%s,%s,%s,%s,%s",mozgo->ceg,mozgo->osztaly,mozgo->beosztas,mozgo->email,mozgo->bday);
            fprintf(ki,"\n");
            mozgo = mozgo->kov;
        }
        fclose(ki);
        printf("Sikeres mentes!\n");
    }
    else
    {
        sikertelen("fajlletrehozas");
        return;
    }

}

void exportal(Rekord* ab)
{
   if(dbcheck(ab))
    {
        return;
    }
    printf("Adjon meg egy fajlnevet!(kiterjesztes jeloles nelkul)\n");
    char fajlnev[20];
    scanf("%s",&fajlnev);
    strcat(&fajlnev,".vcf");
    FILE* ki;
    ki = fopen(fajlnev,"w");
    if(ki != NULL)
    {
        Rekord* mozgo = ab;
        while(mozgo->kov != NULL)
        {
            fprintf(ki,"BEGIN:VCARD\n");
            fprintf(ki,"VERSION:2.1\n");
            fprintf(ki,"N:%s;%s\n",mozgo->name.fname,mozgo->name.lname);
            if(strcmp(mozgo->ctel,"nincs") != 0)
            {
                fprintf(ki,"TEL;CELL;VOICE:%s\n",mozgo->ctel);
            }
            if(strcmp(mozgo->htel,"nincs") != 0)
            {
                fprintf(ki,"TEL;HOME;VOICE:%s\n",mozgo->htel);
            }
            if(strcmp(mozgo->wtel,"nincs") != 0)
            {
                fprintf(ki,"TEL;WORK;VOICE:%s\n",mozgo->wtel);
            }
            if(strcmp(mozgo->address.addr,"nincs") != 0)
            {
                fprintf(ki,"ADR;HOME:;;%s;%s;;%s\n",mozgo->address.addr,mozgo->address.city,mozgo->address.zip);
            }
            if(strcmp(mozgo->waddr.addr,"nincs") != 0)
            {
                fprintf(ki,"ADR;WORK:;;%s;%s;;%s\n",mozgo->waddr.addr,mozgo->waddr.city,mozgo->waddr.zip);
            }
            if(strcmp(mozgo->ceg,"nincs") != 0)
            {
                fprintf(ki,"ORG:%s;%s\n",mozgo->ceg,mozgo->osztaly);
            }
            if(strcmp(mozgo->beosztas,"nincs") != 0)
            {
                fprintf(ki,"TITLE:%s\n",mozgo->beosztas);
            }
            if(strcmp(mozgo->email,"nincs") != 0)
            {
                fprintf(ki,"EMAIL:%s\n",mozgo->email);
            }
            if(strcmp(mozgo->bday,"nincs") != 0)
            {
                fprintf(ki,"BDAY:%s\n",mozgo->bday);
            }
            fprintf(ki,"END:VCARD\n");

            mozgo = mozgo->kov;
        }
        fclose(ki);
        printf("Sikeres mentes!\n");
        pre();
        return;
    }
    else
    {
        sikertelen("fajlletrehozas");
        return;
    }
}

int vcard_feltolt(Rekord* uj,char* sor)
{
    if(strcmp(sor,"END:VCARD\n") == 0 || sor == NULL)
    {
       // printf("Blokk vege\n");
        return 0;
    }
    if(strcmp(sor,"BEGIN:VCARD\n") == 0 || strcmp(sor,"VERSION:2.1\n") == 0)
    {
        return 1;
    }
    if(sor[0] == 'N' && sor[1] == ':')
    {
        sscanf(sor,"N:%[^;];%[^\n]",uj->name.fname,uj->name.lname);
        return 1;
    }
    if(sor[0] == 'T' && sor[1] == 'E' && sor[2] == 'L')
    {
        if(sor[4] == 'C')
        {
            sscanf(sor,"TEL;CELL;VOICE:%[^\n]",uj->ctel);
        }
        if(sor[4] == 'H')
        {
            sscanf(sor,"TEL;HOME;VOICE:%[^\n]",uj->htel);
        }
        if(sor[4] == 'W')
        {
            sscanf(sor,"TEL;WORK;VOICE:%[^\n]",uj->wtel);
        }
        return 1;
    }
    if(sor[0] == 'A' && sor[1] == 'D' && sor[2] == 'R')
    {
        if(sor[4] == 'H')
        {
            sscanf(sor,"ADR;HOME:;;%[^;];%[^;];;%s",uj->address.addr,uj->address.city,uj->address.zip);
        }
        if(sor[4] == 'W')
        {
            sscanf(sor,"ADR;WORK:;;%[^;];%[^;];;%s",uj->waddr.addr,uj->waddr.city,uj->waddr.zip);
        }
        return 1;
    }
    if(sor[0] == 'O' && sor[1] == 'R' && sor[2] == 'G')
    {
        sscanf(sor,"ORG:%[^;];%[^\n]",uj->ceg,uj->osztaly);
        return 1;
    }
    if(sor[0] == 'T' && sor[1] == 'I' && sor[2] == 'T')
    {
        sscanf(sor,"TITLE:%[^\n]",uj->beosztas);
        return 1;
    }
    if(sor[0] == 'E' && sor[1] == 'M' && sor[2] == 'A')
    {
        sscanf(sor,"EMAIL:%[^\n]",uj->email);
        return 1;
    }
    if(sor[0] == 'B' && sor[1] == 'D' && sor[2] == 'A')
    {
        sscanf(sor,"BDAY:%[^\n]",uj->bday);
        return 1;
    }
    return 1;
}

Rekord* vbeolvas(Rekord* ab)
{
    printf("Kerem adja meg a beolvasni kivant VCF fajl nevet!(kiterjesztes jeloles nelkul)\n");
    char* fajlnev[20];
    scanf("%s",fajlnev);
    strcat(fajlnev,".vcf");
    FILE* be = fopen(fajlnev,"r");
    if(be == NULL)
    {
        sikertelen("fajlnyitas");
        aktiv_ab = false;
        return NULL;
    }
        printf("\nSikeres fajlnyitas!\n\n");
        char sor[501];
        fgets(sor,500,be);
       // printf("%s",sor);
        Rekord* elozo = ab;
        Rekord* uj;
        if(strcmp(sor,"BEGIN:VCARD\n") == 0)
        {
            fgets(sor,500,be);
           // printf("%s",sor);
            if(strcmp(sor,"VERSION:2.1\n") == 0)
            {
                while(sor != NULL)
                {
                    uj = (Rekord*) malloc(sizeof(Rekord));
                    init(uj);
                    uj->kov = elozo;
                    int r = vcard_feltolt(uj,sor);
                    while(r == 1 && sor != NULL)
                    {
                        fgets(sor,500,be);
                        r = vcard_feltolt(uj,sor);
                    }
                    fgets(sor,500,be);
                    elozo = uj;
                    if(feof(be))
                    {
                        break;
                    }
                }
                fclose(be);
                pre();
                return uj;
            }
            else
            {
                printf("Nem kompatibilis vCard verzio!\n");
                return NULL;
            }
        }
        else
        {
            printf("Ismeretlen adatformatum!\n");
            aktiv_ab = 0;
            return NULL;
        }
}
