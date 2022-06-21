#ifndef FAJLKEZELES_H_INCLUDED
#define FAJLKEZELES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include <string.h>
#include "adatkezeles.h"
#include "felulet.h"

void sorbol_feltolt(Rekord* uj, char* sor);

Rekord* betoltes(Rekord* ab);

void fajlba_kiir(Rekord* ab);

void exportal(Rekord* ab);

int vcard_feltolt(Rekord* uj,char* sor);

Rekord* vbeolvas(Rekord* ab);

#endif // FAJLKEZELES_H_INCLUDED
