#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include "GereClic.h"
#include "Bouton.h"
#include <string.h>
#include <sys/resource.h>
#include "libISEN/GfxLib.h"
#include "libISEN/BmpLib.h"
#include "libISEN/ESLib.h"
#include "Affichage.h"
#include "matrice.h"
#include "analyse.h"
#include "reconnaissance.h"

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
	static int EtatMenu = 0;
	static int SelecBouton = 0;
	static int SelecCase = 0;
	static int EtatFilmer = 0;
	static int ChoixLangue = 0;
	
	static tabbouton t;
	static bool pleinEcran = false; 

	static DonneesImageRGB *image = NULL;
	static char nomImage[11];
	static troimat mat;
	static jointure pic[NBIMAGE];
	static int speed = 20;
	int touche;
	static int in = START_IMAGE;
	//Taille image par rapport à la taille de la fenetre 1920 -> 800 / 1080 -> 600
	static int ratio_x;
	static int ratio_y;
	
	switch (evenement)
	{
		case Initialisation:
			image = lisBMPRGB("Pictures/pic001.bmp");
			rafraichisFenetre();
			demandeTemporisation(-1);
			sauveTexteBouton( ChoixLangue);
			t = IniBouton ();
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			effaceFenetre(44, 62, 80);

			lisTexteBouton(&t, ChoixLangue);
			AffMenu (EtatMenu, SelecBouton, t, SelecCase, EtatFilmer);
			
			if (image != NULL)
			{
//				ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
			}
			
			else
			{
				printf("the picture can't be print\n");
			}
			couleurCourante(0,0,0);

	
				for(int t=START_IMAGE;t<in-1;t++)//NBIMAGE;t++)
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
						point(pic[t].j[k].centre.x,pic[t].j[k].centre.y);
						if(t+1!=NBIMAGE)
							ligne(pic[t].j[k].centre.x,pic[t].j[k].centre.y,pic[t+1].j[k].centre.x,pic[t+1].j[k].centre.y);
					}

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
					in = START_IMAGE;
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
				default :
					break;

			}
			rafraichisFenetre();
			break;
			
		case ClavierSpecial:
			touche = toucheClavier();
//			printf("ASCII %d\n", touche);
			switch (touche) {
				case 13:
					speed+=10;
					break;
				case 14:
					speed-=10;
					break;
				default:
					break;
			}
			if(speed < -1)
			{
				speed = -1;
			}
//			printf("speed : %d\n", speed);
			demandeTemporisation(speed);
			rafraichisFenetre();
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
//				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				EncadrementBouton (&SelecBouton, EtatMenu);
				ClicLangue (&ChoixLangue, EtatMenu);
				ClicOk (&EtatMenu, &SelecBouton, &SelecCase, &EtatFilmer);
				ClicApprentissage (EtatMenu, &SelecCase);
				ClicFilmer (&EtatFilmer, EtatMenu, SelecCase, SelecBouton);

			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
//				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			rafraichisFenetre();
//			printf ("\n\nEM = %d et SB = %d",EtatMenu, SelecBouton);
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
