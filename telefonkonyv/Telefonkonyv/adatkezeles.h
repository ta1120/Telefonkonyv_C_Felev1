#ifndef ADATKEZELES_H_INCLUDED
#define ADATKEZELES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include "fajlkezeles.h"
#include "felulet.h"

void felszabaditas(Rekord* ab);

void felszabaditast(Talalat* ab);

Rekord* ures_ab();

Rekord* uj_rekord(Rekord* ab);

void init(Rekord* uj);

bool dbcheck(Rekord* ab);

bool wkeres(char* a, char* b);

Rekord* megkeres(Rekord* ab,int typ);

Rekord* rekordot_torol(Rekord* ab);

void rekord_modositasa(Rekord* ab);

void input_buffer_urites();

void ellenorzott_modositas(char* str);

#endif // ADATKEZELES_H_INCLUDED
