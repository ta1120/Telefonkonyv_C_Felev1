#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include <string.h>
#include "adatkezeles.h"
#include "fajlkezeles.h"
#include "felulet.h"

bool karakter_ellenorzes(char* str)
{
    int h = strlen(str)-1;
    if(h < 0)
    {
            strcpy(str,"nincs");
            printf("\n\n[Figyelem!] Az adatmezo erteke ures.\n");
            pre();
            return 1;
    }
    char *pos;
    if ((pos=strchr(str, '\n')) != NULL)
    {
        *pos = '\0';
    }
    for(int i = 0;i<h;i++)
    {
        if(str[i]< 32 || str[i] > 126)
        {
            strcpy(str,"nincs");
            printf("\n\n[Figyelem!] Tiltott karakter a bemeneten! Ez az adat nem kerul eltarolasra.\n");
            pre();
            return 1;
        }
    }
    return 0;
}

int uj_feltolt(Rekord* uj)
{
    init(uj);
    printf("Adjon meg egy nevet(vezeteknev keresztnev): ");
    scanf("%s %s",uj->name.lname,uj->name.fname);
    if(karakter_ellenorzes(uj->name.fname) || karakter_ellenorzes(uj->name.lname))
    {
        return 1;
    }
    char valasz = kitoltes("Mobiltelefonszam");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy mobiltelefonszamot: ");
            input_buffer_urites();
            gets(uj->ctel);
            karakter_ellenorzes(uj->ctel);

        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");

        break;
    }
    valasz = kitoltes("Otthoni telefonszam");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy otthoni telefonszamot: ");
            input_buffer_urites();
            gets(uj->htel);
            karakter_ellenorzes(uj->htel);

        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    valasz = kitoltes("Munkahelyi telefonszam");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy munkahelyi telefonszamot: ");
            input_buffer_urites();
            gets(uj->wtel);
            karakter_ellenorzes(uj->wtel);

        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    valasz = kitoltes("Otthoni lakcim");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy otthoni cimet(utca es hazszam): ");
            input_buffer_urites();
            gets(uj->address.addr);
            printf("Adjon meg egy otthoni cimet(Varos): ");
            input_buffer_urites();
            gets(uj->address.city);
            printf("Adjon meg egy otthoni cimet(IRSZ): ");
            input_buffer_urites();
            gets(uj->address.zip);
            if(karakter_ellenorzes(uj->address.addr) || karakter_ellenorzes(uj->address.city) || karakter_ellenorzes(uj->address.zip))
            {
                strcpy(uj->address.addr,"nincs");
                strcpy(uj->address.city,"nincs");
                strcpy(uj->address.zip,"nincs");
            }
        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    valasz = kitoltes("Munkahelyi cim");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy munkahelyi cimet(utca es hazszam): ");
            input_buffer_urites();
            gets(uj->waddr.addr);
            printf("Adjon meg egy munkahelyi cimet(Varos): ");
            input_buffer_urites();
            gets(uj->waddr.city);
            printf("Adjon meg egy munkahelyi cimet(IRSZ): ");
            input_buffer_urites();
            gets(uj->waddr.zip);
            if(karakter_ellenorzes(uj->waddr.addr) || karakter_ellenorzes(uj->waddr.city) || karakter_ellenorzes(uj->waddr.zip))
            {
                strcpy(uj->waddr.addr,"nincs");
                strcpy(uj->waddr.city,"nincs");
                strcpy(uj->waddr.zip,"nincs");
            }
        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    valasz = kitoltes("Munkahely");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy munkahelyet(cegnev): ");
            input_buffer_urites();
            gets(uj->ceg);
            if(karakter_ellenorzes(uj->ceg))
            {
                strcpy(uj->ceg,"nincs");
            }
            printf("Adjon meg egy munkahelyet(osztaly): ");
            input_buffer_urites();
            gets(uj->osztaly);
            karakter_ellenorzes(uj->osztaly);

        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    valasz = kitoltes("Beosztas");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy beosztast: ");
            scanf("%s",uj->beosztas);
            karakter_ellenorzes(uj->beosztas);
        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    valasz = kitoltes("E-mail cim");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy e-mail cimet: ");
            scanf("%s",uj->email);
            karakter_ellenorzes(uj->email);
        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    valasz = kitoltes("Szuletesnap");
    switch(valasz)
    {
        case 'y':
        {
            printf("Adjon meg egy szuletesnapot (yyyymmdd): ");
            scanf("%s",uj->bday);
            karakter_ellenorzes(uj->bday);
        }
        break;
        case 'x':
            return 0;
        break;
        default:printf("Mezo kihagyva\n");
        break;
    }
    return 0;
}

int szerkeszt()
{
    printf("****************************************\n");
    printf("[Almenu: Szerkesztes]\n\n");
    printf("[1] Uj bejegyzes\n");
    printf("[2] Meglevo modositasa\n");
    printf("[3] Bejegyzes torlese\n");
    printf("[4] Vissza a fomenube\n\n");
    return menuvalaszt(4);
}
int uj_adatbazis(Rekord* ab)
{
    if(aktiv_ab && ab->kov != NULL)
    {
        printf("Szeretne menteni a jelenlegi adatbazist?\n[1] Igen\n[2] Nem\n\n");
        int val =menuvalaszt(2);
        if(val == 1)
        {
            fajlba_kiir(ab);
        }
        felszabaditas(ab);
        ab->kov = NULL;
        ab = NULL;
        aktiv_ab = false;
    }
    printf("****************************************\n");
    printf("[Almenu: Uj adatbazis]\n\n");
    printf("[1] Beolvasas CSV fajlbol\n");
    printf("[2] Beolvasas VCF fajlbol\n");
    printf("[3] Ures adatbazis letrehozasa\n");
    printf("[4] Vissza a fomenube\n\n");

    return menuvalaszt(4);

}

void parlista()
{

    printf("[1] [Nev]\n");
    printf("[2] Telefonszam\n");
    printf("[3] Iranyitoszam\n");
    printf("[4] Telepules\n");
    printf("[5] Munkahely\n");
    printf("[6] Vissza a fomenube\n");
}

void ismert_parameterek_megjelenitese(Rekord* ab)
{
    printf("Nev: %s %s\n\n",ab->name.lname,ab->name.fname);
    if(strcmp(ab->ctel,"nincs") != 0)
    {
        printf("Mobiltelefonszam: %s\n\n",ab->ctel);
    }
    if(strcmp(ab->htel,"nincs") != 0)
    {
        printf("Otthoni telefonszam: %s\n\n",ab->htel);
    }
    if(strcmp(ab->wtel,"nincs") != 0)
    {
        printf("Munkahelyi telefonszam: %s\n\n",ab->wtel);
    }
    if(strcmp(ab->address.addr,"nincs") != 0 && strcmp(ab->address.city,"nincs") != 0 && strcmp(ab->address.zip,"nincs") != 0)
    {
        printf("Cim: %s\n",ab->address.addr);
        printf("Varos: %s\n",ab->address.city);
        printf("IRSZ: %s\n\n",ab->address.zip);
    }
    if(strcmp(ab->waddr.addr,"nincs") != 0 && strcmp(ab->waddr.city,"nincs") != 0 && strcmp(ab->waddr.zip,"nincs") != 0)
    {
        printf("Munkahely cime: %s\n",ab->waddr.addr);
        printf("M.h. varos: %s\n",ab->waddr.city);
        printf("M.h. IRSZ: %s\n\n",ab->waddr.zip);
    }
    if(strcmp(ab->ceg,"nincs") != 0)
    {
        printf("Munkahely neve: %s\n\n",ab->ceg);
    }
    if(strcmp(ab->osztaly,"nincs") != 0)
    {
        printf("Munkahelyi osztaly: %s\n\n",ab->osztaly);
    }
    if(strcmp(ab->beosztas,"nincs") != 0)
    {
        printf("Beosztas: %s\n\n",ab->beosztas);
    }
    if(strcmp(ab->email,"nincs") != 0)
    {
        printf("E-mail cim: %s\n\n",ab->email);
    }
    if(strcmp(ab->bday,"nincs") != 0)
    {
        printf("Szuletesnap: %s\n\n",ab->bday);
    }
}

void teljes_par_lista()
{
    printf("[1] Vezeteknev\n");
    printf("[2] Keresztnev\n");
    printf("[3] Mobiltelefonszam\n");
    printf("[4] Otthoni telefonszam\n");
    printf("[5] Munkahelyi telefonszam\n");
    printf("[6] Lakcim\n");
    printf("[7] Munkahely cime\n");
    printf("[8] Munkahely - vallalat\n");
    printf("[9] Munkahely - osztaly\n");
    printf("[10] Beosztas\n");
    printf("[11] E-mail cim\n");
    printf("[12] Szuletesnap\n");
    printf("[13] [Semmit sem szeretnek modositani.]\n\n");
}

void listazas(Rekord* ab)
{
    if(dbcheck(ab))
    {
        return;
    }
    Rekord* mozgo = ab;
    printf("Jelenleg az adatbazisban szereplo nevek:\n");
    while(mozgo->kov != NULL)
    {
        printf("%s %s\n",mozgo->name.lname,mozgo->name.fname);
        mozgo = mozgo->kov;
    }
    pre();
}

void menulista()
{
    printf("****************************************\n");
    printf("[Fomenu: Telefonkonyv]\n\n");
    printf("[1] Uj adatbazis letrehozasa\n");
    printf("[2] Adatbazis listazasa\n");
    printf("[3] Kereses az adatbazisban\n");
    printf("[4] Adatbazis szerkesztese\n");
    printf("[5] Adatbazis mentese\n");
    printf("[6] Exportalas vCard fajlba\n");
    printf("[7] Kilepes\n\n");
}

char kitoltes(char* mezo)
{
    printf("\nSzeretned kitolteni a kovetkezo mezot: %s?\n\n",mezo);
    printf("y: igen\nx: feltoltes befejezese\nn: mezo atugrasa\n");
    char valasz;
    scanf("%c",&valasz);
    while(valasz != 'y' && valasz != 'n' && valasz != 'x')
    {
        scanf("%c",&valasz);
    }

    return valasz;
}

void pre()
{
    printf("A tovabblepeshez nyomja meg az Entert!\n");
    input_buffer_urites();
    getchar();

}

void sikertelen(char* hiba)
{
    printf("Sikertelen %s!\n",hiba);
    pre();
}

int menuvalaszt(int max)
{
    printf("Menupont kivalasztasa a sorszam begepelesevel lehetseges.\n\n");
    printf("Valasztott menupont szama: \n");
    int sel;
    while(scanf("%d",&sel) != 1)
    {
        printf("Ervenytelen menupont!\n1 es %d kozotti szamot adjon meg!\n\n",max);
        printf("Valasztott menupont szama: \n");
        getchar();
    }

    while(sel < 1 || sel > max)
    {
        printf("Ervenytelen menupont!\n1 es %d kozotti szamot adjon meg!\n\n",max);
        printf("Valasztott menupont szama: \n");
        getchar();
        scanf("%d",&sel);
    }
    return sel;
}

void kereses(Rekord* ab)
{
    if(dbcheck(ab))
    {
        return;
    }
    printf("****************************************\n");
    printf("Milyen parameter alapjan szeretne keresni?\n");
    parlista();
    int val = menuvalaszt(6);
    if(val == 6)
    {
        return;
    }
    Rekord* cel = megkeres(ab,val);
    if(cel != NULL)
    {
            ismert_parameterek_megjelenitese(cel);
            pre();
    }
    else
    {
            printf("Nem talaltam egyezest.\n");
            pre();
    }
}
