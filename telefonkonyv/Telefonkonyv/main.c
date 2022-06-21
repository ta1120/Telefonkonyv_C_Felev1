#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "adatkezeles.h"
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include "fajlkezeles.h"
#include "felulet.h"

bool aktiv_ab = false;
int main()
{
    Rekord* ab = NULL;
    int sel = 0;
    while(sel != 7)
    {
        menulista();
        sel = menuvalaszt(7);
        switch(sel)
            {
            case 1:
                {
                    int uab = uj_adatbazis(ab);
                    if(uab == 1)
                        {
                            ab = ures_ab();
                            ab = betoltes(ab);

                        }
                    else if (uab == 2)
                    {
                        ab = ures_ab();
                        ab = vbeolvas(ab);
                    }
                    else if(uab == 3)
                        {
                            ab = ures_ab();
                            printf("\nUj adatbazis sikeresen letrehozva!\nMostmar hozzaadhat uj elemet!\n");
                            aktiv_ab=1;
                            pre();
                        }
                    }
            break;
            case 2:
                {
                    listazas(ab);
                }
            break;
            case 3:
                {
                    kereses(ab);
                }
            break;
            case 4:
                {
                    int szerk = szerkeszt();
                    if(szerk == 1)
                        {
                            Rekord* uj = uj_rekord(ab);
                            if(uj != NULL)
                            {
                                if(uj_feltolt(uj) != 1)
                                {
                                    ab = uj;
                                    printf("Sikeresen hozzaadva\n");
                                    pre();
                                }
                                else
                                {
                                    sikertelen("feltoltes");
                                    printf("A rekord nem kerult mentesre.\n");
                                    free(uj);
                                }

                            }
                            else
                                sikertelen("foglalas");
                        }
                    else if(szerk == 2)
                        {
                            rekord_modositasa(ab);
                        }
                    else if(szerk == 3)
                        {
                            ab = rekordot_torol(ab);
                        }
                    }
            break;
            case 5:
                {
                    fajlba_kiir(ab);
                }
            break;
            case 6:
                {
                    exportal(ab);
                }
            break;
            default:;
        }
    }
    felszabaditas(ab);
    printf("Program vege.\n");
    return 0;
}
