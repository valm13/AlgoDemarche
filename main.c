#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <string.h>
#include <sys/resource.h>
#include "libISEN/GfxLib.h"
#include "libISEN/BmpLib.h"
#include "libISEN/ESLib.h"
#include "Affichage.h"
#include "reconnaissance.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);



int main(int argc, char **argv)
{
	const rlim_t StackSize = sizeof(image) * 2 * 3;
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		printf("Changing stack limit from %ld to %ld\n", rl.rlim_cur, rl.rlim_cur + StackSize );
		rl.rlim_cur += StackSize;
		result = setrlimit(RLIMIT_STACK, &rl);
	}
	else
	{
		fprintf(stderr, "error, can't read stack information\n");
	}
	if (result == 0)
	{
		initialiseGfx(argc, argv);
		prepareFenetreGraphique("Analyseur de Demarche", LargeurFenetre, HauteurFenetre);
	
		/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
		lanceBoucleEvenements();
	}
	else
	{
		fprintf(stderr, "error, insufficen system memory\n");
	}
	
	return 0;
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static image tp;
	static bool pleinEcran = false;
	static DonneesImageRGB *img = NULL;
	//~ static DonneesImageRGB imageretour;
	static char nomImage[11];
	static troimat mat;
	static jointure pic[NBIMAGE];
	//Taille image par rapport à la taille de la fenetre 1920 -> 800 / 1080 -> 600
	static int ratio_x;
	static int ratio_y;
	
	switch (evenement)
	{
		case Initialisation:
			demandeTemporisation(20);
			for(int i=0;i<NBIMAGE;i++)
			{
				printf("Image numero : %d\n\n",i);
				//~ sprintf(nomImage,"TestPic2/%d.bmp",i+1);
				sprintf(nomImage,"Valentincirculaire/pic%03d.bmp",i+1);
				printf("\nChargement de l'image\n");
				chargeImage(nomImage,&img);
				printf("Image chargée\n");
				mat=cree3matrices(img);
				printf("Matrice crée : Fait !\n");
				tp=rgbToHsv(mat);
				printf("Transformation RGB->HSV : Fait !\n");
				identifieColor(tp,pic,i); // Problème ici
				printf("pic[%d].j[0].nb = %d\n",i,pic[i].j[0].nb);
				sommePointJoint(&pic[i]);	
				if(i <NBIMAGE-1)
				libereDonneesImageRGB(&img);
			}
			ratio_x = img->largeurImage/LargeurFenetre;
			ratio_y = img->hauteurImage/HauteurFenetre;
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			effaceFenetre (255, 255, 255);
			
			if (img != NULL)
			{
				//~ ecrisImage(0, 0, img->largeurImage, img->hauteurImage, img->donneesRGB);
			}
			
			else
			{
				printf("the picture can't be print\n");
			}
			couleurCourante(0,0,0);

	
				for(int t=0;t<NBIMAGE;t++)
				{
					for(int k=0;k<JOINT;k++)
					{	
						switch(k)
						{
							case 0:
							couleurCourante(0,255,0);
							break;
							case 1:
							couleurCourante(0,0,255);
							break;
							case 2:
							couleurCourante(0,100,0);
							break;
							case 3:
							
							couleurCourante(100,0,0);
							break;
							case 4:
							couleurCourante(0,0,100);
							break;
						}
						point(pic[t].j[k].centre.x/ratio_x,pic[t].j[k].centre.y/ratio_y);
						if(t+1!=NBIMAGE)
							ligne(pic[t].j[k].centre.x/ratio_x,pic[t].j[k].centre.y/ratio_y,
							pic[t+1].j[k].centre.x/ratio_x,pic[t+1].j[k].centre.y/ratio_y);
					}

				}

			
		case Clavier:
			//~ printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
					libereDonneesImageRGB(&img);
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
