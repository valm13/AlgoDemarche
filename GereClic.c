#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GfxLib.h"
#include "BmpLib.h" 
#include "ESLib.h"
#include "GereClic.h"
#include "Bouton.h"
#include "Affichage.h"

void EncadrementBouton (int *SelecBouton)
{
	if (abscisseSouris() > largeurFenetre()*1/16 && ordonneeSouris() > hauteurFenetre()*5/12 && abscisseSouris() < largeurFenetre()*7/16 && ordonneeSouris() < hauteurFenetre()*7/12)
		*SelecBouton = 1;

	if (abscisseSouris() > largeurFenetre()*9/16 && ordonneeSouris() > hauteurFenetre()*5/12 && abscisseSouris() < largeurFenetre()*15/16 && ordonneeSouris() < hauteurFenetre()*7/12)
		*SelecBouton = 2;

}


void ClicOk (int *EtatMenu, int SelecBouton)
{
	if (*EtatMenu == 0 && SelecBouton != 0 && abscisseSouris() > largeurFenetre()*1/16 && ordonneeSouris() > hauteurFenetre()*1/24 && abscisseSouris() < largeurFenetre()*7/32 && ordonneeSouris() < hauteurFenetre()*2/12)
	*EtatMenu = 1;
}
