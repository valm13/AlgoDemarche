#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GfxLib.h"
#include "BmpLib.h" 
#include "ESLib.h"
#include "GereClic.h"
#include "Bouton.h"
#include "Affichage.h"

void EncadrementBouton (int *SelecBouton, int EtatMenu) //Permet de selectionner Apprentissage ou Reconaissance
{
	if (EtatMenu == 0 && abscisseSouris() > largeurFenetre()*1/16 && ordonneeSouris() > hauteurFenetre()*5/12 && abscisseSouris() < largeurFenetre()*7/16 && ordonneeSouris() < hauteurFenetre()*7/12)
		*SelecBouton = 1;

	if (EtatMenu == 0 && abscisseSouris() > largeurFenetre()*9/16 && ordonneeSouris() > hauteurFenetre()*5/12 && abscisseSouris() < largeurFenetre()*15/16 && ordonneeSouris() < hauteurFenetre()*7/12)
		*SelecBouton = 2;

}


void ClicLangue (int *ChoixLangue, int EtatMenu) //Permet de changer de langue
{
	if (EtatMenu == 0 && abscisseSouris() > largeurFenetre()*1/16 && ordonneeSouris() > hauteurFenetre()*44/48 && abscisseSouris() < largeurFenetre()*5/64 && ordonneeSouris() < hauteurFenetre()*45/48)
	{
		if (*ChoixLangue == 0)
			*ChoixLangue = 1;
	
		else if (*ChoixLangue == 1)
			*ChoixLangue = 0;
	}
}


void ClicOk (int *EtatMenu, int *SelecBouton, int *SelecCase, int *EtatFilmer) //Permet de changer sortir du Menu et de remettre des variables à 0
{
	if (*EtatMenu == 0 && SelecBouton != 0 && abscisseSouris() > largeurFenetre()*1/16 && ordonneeSouris() > hauteurFenetre()*1/24 && abscisseSouris() < largeurFenetre()*7/32 && ordonneeSouris() < hauteurFenetre()*2/12)
		*EtatMenu = 1;

	else if (*EtatMenu == 1 && SelecBouton != 0 && abscisseSouris() > largeurFenetre()*1/16 && ordonneeSouris() > hauteurFenetre()*1/24 && abscisseSouris() < largeurFenetre()*7/32 && ordonneeSouris() < hauteurFenetre()*2/12)
	{
		*EtatMenu = 0;
		*SelecBouton = 0;
		*SelecCase = 0;
		*EtatFilmer = 0;
	}
}


void ClicApprentissage (int EtatMenu, int *SelecCase) //Change la variable en fonction de la case sélectionnée
{
	if (EtatMenu == 1 && abscisseSouris() > largeurFenetre()*1/16 && ordonneeSouris() > hauteurFenetre()*20/24 && abscisseSouris() < largeurFenetre()*3/16 && ordonneeSouris() < hauteurFenetre()*23/24)
		*SelecCase = 1;
	
	else if (EtatMenu == 1 && abscisseSouris() > largeurFenetre()*4/16 && ordonneeSouris() > hauteurFenetre()*20/24 && abscisseSouris() < largeurFenetre()*6/16 && ordonneeSouris() < hauteurFenetre()*23/24)
		*SelecCase = 2;

	else if (EtatMenu == 1 && abscisseSouris() > largeurFenetre()*7/16 && ordonneeSouris() > hauteurFenetre()*20/24 && abscisseSouris() < largeurFenetre()*9/16 && ordonneeSouris() < hauteurFenetre()*23/24)
		*SelecCase = 3;
		
	else if (EtatMenu == 1 && abscisseSouris() > largeurFenetre()*10/16 && ordonneeSouris() > hauteurFenetre()*20/24 && abscisseSouris() < largeurFenetre()*12/16 && ordonneeSouris() < hauteurFenetre()*23/24)
		*SelecCase = 4;
		
	else if (EtatMenu == 1 && abscisseSouris() > largeurFenetre()*13/16 && ordonneeSouris() > hauteurFenetre()*20/24 && abscisseSouris() < largeurFenetre()*15/16 && ordonneeSouris() < hauteurFenetre()*23/24)
		*SelecCase = 5;

}


void ClicFilmer (int *EtatFilmer, int EtatMenu, int SelecCase, int SelecBouton) // Cahnge d'état si on filme
{
	if (EtatMenu == 1 && abscisseSouris() > largeurFenetre()*9/32 && ordonneeSouris() > hauteurFenetre()*1/24 && abscisseSouris() < largeurFenetre()*22/32 && ordonneeSouris() < hauteurFenetre()*2/12)
	{
		system("./script.sh");
		printf("fimer\n");
		if ( SelecBouton == 1 && SelecCase !=0)
		{
				*EtatFilmer = true;
		}
		if (SelecBouton == 2 )
		{

			*EtatFilmer = true;;
		}
	}
}

