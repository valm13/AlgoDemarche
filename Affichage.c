#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GfxLib.h"
#include "BmpLib.h" 
#include "ESLib.h"

void creaBouton (float xmin,float ymin,float xmax,float ymax)
{
	epaisseurDeTrait(2);
	couleurCourante (0,0,0);
	ligne (xmin, ymin, xmax, ymin);
	ligne (xmax, ymin, xmax, ymax);
	ligne (xmax, ymax, xmin, ymax);
	ligne (xmin, ymax, xmin, ymin);
	
}


void AffMenu (&EtatMenu, SelecBouton)
{
	if (EtatMenu == 0)
	{
		effaceFenetre(110, 110, 110);

		couleurCourante (0, 0, 0);
		ligne (largeurFenetre()/2, 0, largeurFenetre()/2, hauteurFenetre()); 	// Séparation
		
		//Interieur des Boutons
		couleurCourante(150, 150, 150);
		rectangle (largeurFenetre()/6, hauteurFenetre()/3, largeurFenetre()*2/6, hauteurFenetre()*2/3);
		rectangle (largeurFenetre()*4/6, hauteurFenetre()/3, largeurFenetre()*5/6, hauteurFenetre()*2/3);
		rectangle (largeurFenetre()/24, hauteurFenetre()/6, largeurFenetre()*6/24, hauteurFenetre()*2/12);

		
		//Contour des boutons

		//Apprentissage
		couleurCourante (0, 0, 0);
		creaBouton (largeurFenetre()/6, hauteurFenetre()/3, largeurFenetre()*2/6, hauteurFenetre()*2/3);

		//Reconnaissance
		couleurCourante (0, 0, 0);
		creaBouton (largeurFenetre()*4/6, hauteurFenetre()/3, largeurFenetre()*5/6, hauteurFenetre()*2/3);

		//Lancer
		couleurCourante (0, 0, 0);
		creaBouton (largeurFenetre()/24, hauteurFenetre()/6, largeurFenetre()*6/24, hauteurFenetre()*2/12);


	if (SelecBouton == 1)  //Apprentissage
	{
		couleurCourante (0, 0, 0);
		creaBouton (largeurFenetre()/6+20, hauteurFenetre()/3+20, largeurFenetre()*2/6+20, hauteurFenetre()*2/3+20);
	}

	else if (SelecBouton == 2)  //Reconnaissance
	{
		couleurCourante (0, 0, 0);
		creaBouton (largeurFenetre()*4/6+20, hauteurFenetre()/3+20, largeurFenetre()*5/6+20, hauteurFenetre()*2/3+20);
	}
	
}
