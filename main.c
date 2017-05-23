#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "GereClic.h"
#include "Bouton.h"
#include "Affichage.h"


#define LargeurFenetre 800
#define HauteurFenetre 600


void cercle(float centreX, float centreY, float rayon);

void gestionEvenement(EvenementGfx evenement);



int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	
	lanceBoucleEvenements();
	
	return 0;
}




void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20;
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;

	
	for (index = 0; index < Pas; ++index)
	{
		const double angle = 2.*M_PI*index/Pas;
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
	}
	
}


void gestionEvenement(EvenementGfx evenement)
{
	static int EtatMenu = 0;
	static int SelecBouton = 0;
	static tabbouton t;
	static bool pleinEcran = false; 

	
	switch (evenement)
	{
		case Initialisation:
			rafraichisFenetre();
			sauveTexteBouton();
			
			demandeTemporisation(1);
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			effaceFenetre (255, 255, 255);

			AffMenu (EtatMenu, SelecBouton, t);
			t = IniBouton ();
			lisTexteBouton(&t); 
			demandeTemporisation(2);
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q':
				case 'q':
					libereDonneesImageRGB(&image);
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran;
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					demandeTemporisation(-1);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				EncadrementBouton (&SelecBouton);
				ClicOk (&EtatMenu, SelecBouton);
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}
