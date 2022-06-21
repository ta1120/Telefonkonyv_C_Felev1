#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "adatkezeles.h"
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include "fajlkezeles.h"
#include "felulet.h"

void input_buffer_urites()
{
    fflush(stdin);
}

void felszabaditas(Rekord* ab)
{
    while(ab != NULL)
    {
        Rekord* next = ab->kov;
        free(ab);
        ab = next;

    }
}

void felszabaditast(Talalat* ab)
{
    while(ab != NULL)
    {
        Talalat* next = ab->kov;
        free(ab);
        ab = next;

    }
}

Rekord* ures_ab()
{
    Rekord* uj;
    uj = (Rekord*) malloc(sizeof(Rekord));
    uj->kov = NULL;
    aktiv_ab = true;
    return uj;
}

Rekord* uj_rekord(Rekord* ab)
{
    {
        Rekord* uj;
        uj = (Rekord*) malloc(sizeof(Rekord));
        uj->kov = ab;
        return uj;
    }

}

void init(Rekord* uj)
{
    strcpy(uj->name.fname,"nincs");
    strcpy(uj->name.lname,"nincs");
    strcpy(uj->address.city,"nincs");
    strcpy(uj->address.zip,"nincs");
    strcpy(uj->address.addr,"nincs");
    strcpy(uj->bday,"nincs");
    strcpy(uj->beosztas,"nincs");
    strcpy(uj->ceg,"nincs");
    strcpy(uj->ctel,"nincs");
    strcpy(uj->email,"nincs");
    strcpy(uj->htel,"nincs");
    strcpy(uj->osztaly,"nincs");
    strcpy(uj->waddr.addr,"nincs");
    strcpy(uj->waddr.city,"nincs");
    strcpy(uj->waddr.zip,"nincs");
    strcpy(uj->wtel,"nincs");
}

Rekord* rekordot_torol(Rekord* ab)
{
    if(dbcheck(ab))
    {
        return ab;
    }
    printf("Keressuk meg a torolni kivant rekordot Nev szerint!\n");
    Rekord* torlendo = megkeres(ab,1);
    if(torlendo != NULL)
    {
        printf("Biztos torolni szeretne a kovetkezo rekordot: %s %s?\n",torlendo->name.lname,torlendo->name.fname);
        printf("[1] Igen (az adatok veglegesen elvesznek)\n[2] Nem\n");
        int sel = menuvalaszt(2);
        if(sel == 1)
        {
            if(torlendo == ab)
            {
                Rekord* next = ab->kov;
                free(ab);
                return next;
            }
            Rekord* mozgo = ab;
            while(mozgo->kov != torlendo)
            {
                mozgo = mozgo->kov;
            }
            mozgo->kov = torlendo->kov;
            free(torlendo);
            printf("Sikeres torles!\n");
            pre();
            return ab;
        }
        else
        {
            printf("Visszateres a fomenube...\n");
            pre();
            return ab;
        }

    }
    else
    {
        sikertelen("kivalasztas!");
        return ab;
    }

}

bool dbcheck(Rekord* ab)
{
    if(!aktiv_ab)
    {
        printf("\nJelenleg nincs aktiv adatbazis!\n");
        pre();
        return 1;
    }
    if(ab->kov == NULL)
    {
        printf("\nAz adatbazis meg nem tartalmaz elemeket.\n");
        pre();
        return 1;
    }
    return 0;
}

bool wkeres(char* a, char* b)
{
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
            if(b[bl] == '\n' || b[bl] == ' ')
            {
                b[bl] = '\0';
            }
            if(strcmp(a,b) == 0)
            {
                return 1;
            }
        }
    return false;
}

Rekord* megkeres(Rekord* ab,int typ)
{
    printf("\nAdjon meg a keresett adatot pontosan, vagy\negy db * helyettesito karakterrel!\nMinden nev kilistazasahoz adjon meg * karaktert.\n");
    int db = 0;
    char* nev[100];
    input_buffer_urites();
    fgets(nev,99,stdin);
    Rekord* mozgo = ab;
    Talalat* elozo = NULL;
    while(mozgo->kov != NULL)
    {
        char* nb[100];
        if(typ == 1)
        {
            strcpy(nb,mozgo->name.lname);
            strcat(nb," ");
            strcat(nb,mozgo->name.fname);
        }
        if(typ == 2)
        {
            strcpy(nb,mozgo->ctel);
        }
        if(typ == 3)
        {
            strcpy(nb,mozgo->address.zip);
        }
        if(typ == 4)
        {
            strcpy(nb,mozgo->address.city);
        }
        if(typ == 5)
        {
            strcpy(nb,mozgo->ceg);
        }

        if(strcmp(nb,"nincs") != 0 && wkeres(nb,nev))
        {
            db++;
            Talalat* uj = (Talalat*) malloc(sizeof(Talalat));
            uj->kov = elozo;
            uj->adat = mozgo;
            uj->sorszam = db;
            strcpy(uj->neve,nb);
            elozo = uj;
        }
        mozgo = mozgo->kov;
    }
    if(db != 0 && elozo->kov != NULL)
    {
        printf("\n\n%d db megfelelo elemet talaltam:\n\n",db);
        Talalat* kiir = elozo;
        for(int i = 0;i<db;i++)
        {
            printf("[%d] %s",kiir->sorszam,kiir->neve);
            if(typ != 1)
            {
                printf(" - %s %s\n",kiir->adat->name.lname,kiir->adat->name.fname);
            }
            else
                {
                    printf("\n");
                }
            kiir = kiir->kov;
        }
        printf("\n");
        int sel = menuvalaszt(db);
        Rekord* cel = NULL;
        Talalat* ez = elozo;
        while(ez != NULL)
        {
            if(ez->sorszam == sel)
            {
                cel = ez->adat;
            }
            ez = ez->kov;
        }
        felszabaditast(elozo);
        return cel;
    }
    else if(db != 0 && elozo->kov == NULL)
    {
        Rekord* cel = elozo->adat;
        felszabaditast(elozo);
        printf("\n\nEgyetlen egyezest talaltam:\n\n");
        return cel;
    }
    else
    {
        printf("Nincs talalat!\n");
        return NULL;
    }
}

void ellenorzott_modositas(char* str)
{
    char* t[200];
    input_buffer_urites();
    fgets(t,199,stdin);
    if(!karakter_ellenorzes(t))
    {
        strcpy(str,t);
        printf("Sikeres modositas!\n");
        pre();
    }
    else
    {
        printf("Az adat nem kerult modositasra.\n");
    }
}

void rekord_modositasa(Rekord* ab)
{
    if(dbcheck(ab))
    {
        return;
    }
    printf("Adja meg a modositani kivant rekordhoz tartozo nevet!\n");
    Rekord* uj = megkeres(ab,1);
    if(uj ==NULL)
    {
        sikertelen("kivalasztas");
        return;
    }
    int val = 0;
    while(val != 13)
    {

        printf("Mit szeretne mosdositani a rekordon: %s %s?\n\n",uj->name.lname,uj->name.fname);
        teljes_par_lista();
        val = menuvalaszt(13);
        switch(val)
        {
            case 1:
            {
                printf("Adjon meg egy nevet(vezeteknev): ");
                ellenorzott_modositas(uj->name.lname);

            }
            break;
            case 2:
                {
                    printf("Adjon meg egy nevet(keresztnev): ");
                    ellenorzott_modositas(uj->name.fname);
                }
            break;
            case 3:
                {
                    printf("Adjon meg egy mobiltelefonszamot: ");
                    ellenorzott_modositas(uj->ctel);
                }
            break;
            case 4:
                {
                    printf("Adjon meg egy otthoni telefonszamot: ");
                    ellenorzott_modositas(uj->htel);
                }
            break;
            case 5:
                {
                    printf("Adjon meg egy munkahelyi telefonszamot: ");
                    ellenorzott_modositas(uj->wtel);
                }
            break;
            case 6:
                {
                    printf("Adjon meg egy otthoni cimet(utca es hazszam): ");
                    ellenorzott_modositas(uj->address.addr);
                    printf("Adjon meg egy otthoni cimet(Varos): ");
                    ellenorzott_modositas(uj->address.city);
                    printf("Adjon meg egy otthoni cimet(IRSZ): ");
                    ellenorzott_modositas(uj->address.zip);
                }
            break;
            case 7:
                {
                    printf("Adjon meg egy munkahelyi cimet(utca es hazszam): ");
                    ellenorzott_modositas(uj->waddr.addr);
                    printf("Adjon meg egy munkahelyi cimet(Varos): ");
                    ellenorzott_modositas(uj->waddr.city);
                    printf("Adjon meg egy munkahelyi cimet(IRSZ): ");
                    ellenorzott_modositas(uj->waddr.zip);
                }
            break;
            case 8:
                {
                    printf("Adjon meg egy munkahelyet(cegnev): ");
                    ellenorzott_modositas(uj->ceg);
                }
            break;
            case 9:
                {
                    printf("Adjon meg egy munkahelyet(osztaly): ");
                    ellenorzott_modositas(uj->osztaly);
                }
            break;
            case 10:
                {
                    printf("Adjon meg egy beosztast: ");
                    ellenorzott_modositas(uj->beosztas);
                }
            break;
            case 11:
                {
                    printf("Adjon meg egy e-mail cimet: ");
                    ellenorzott_modositas(uj->email);
                }
            break;
            case 12:
                {
                    printf("Adjon meg egy szuletesnapot (yyyymmdd): ");
                    ellenorzott_modositas(uj->bday);
                }
            break;
            default:;
        }
    }
    printf("Visszateres a fomenube...\n");
    pre();
    return;
}
