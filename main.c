#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "Affichage.h"
#include "analyse.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);



int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("Analyseur de Demarche", LargeurFenetre, HauteurFenetre);
	
	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	
	return 0;
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static int EtatMenu = 0;
	static int SelecBouton = 0;
	static bool pleinEcran = false;
	static DonneesImageRGB *image = NULL;
	static char nomImage[11];
	switch (evenement)
	{
		case Initialisation:
			demandeTemporisation(20);
			strcpy(nomImage,"pic001.bmp");
			printf("\nChargement de l'image\n");
			//image = lisBMPRGB(nomImage);
			chargeImage(nomImage,&image);
			printf("Image chargée\n");
			printf("image->largeurImage = %d\n",image->largeurImage);
			rgbToHsv(image);
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			effaceFenetre (255, 255, 255);

			AffMenu (EtatMenu, SelecBouton);
			
			if (image != NULL)
			{
				ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
			}
			
			else
			{
				printf("the picture can't be print\n");
			}
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
					libereDonneesImageRGB(&image);
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure le systeme pour ne plus generer de message Temporisation
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
