#ifndef FELULET_H_INCLUDED
#define FELULET_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include <string.h>
#include "adatkezeles.h"
#include "fajlkezeles.h"

extern bool aktiv_ab;
typedef struct Nev
{
    char fname[50];
    char lname[50];
}Nev;

typedef struct Cim
{
    char addr[150];
    char city[50];
    char zip[30];
}Cim;

typedef struct Rekord
{
    Nev name;
    char ctel[40];
    char htel[40];
    char wtel[40];
    Cim address;
    Cim waddr;
    char ceg[150];
    char osztaly[150];
    char beosztas[100];
    char email[80];
    char bday[9];
    struct Rekord* kov;
}Rekord;

typedef struct Talalat
{
    int sorszam;
    Rekord* adat;
    char* neve[100];
    struct talalat *kov;
}Talalat;

bool karakter_ellenorzes(char* str);

int uj_feltolt(Rekord* uj);

int szerkeszt();

int uj_adatbazis(Rekord* ab);

void parlista();

void ismert_parameterek_megjelenitese(Rekord* ab);

void teljes_par_lista();

void listazas(Rekord* ab);

void menulista();

char kitoltes(char* mezo);

void pre();

void sikertelen(char* hiba);

void kereses(Rekord* ab);

int menuvalaszt(int max);

#endif // FELULET_H_INCLUDED
