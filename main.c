#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <sys/resource.h>
#include "libISEN/GfxLib.h"
#include "libISEN/BmpLib.h"
#include "libISEN/ESLib.h"
#include <math.h> 
#include "GereClic.h"
#include "Bouton.h"
#include "Affichage.h"
#include "matrice.h"
#include "analyse.h"
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
	static bool pause = true;
	static image tp;
	static int EtatMenu = 0;
	static int SelecBouton = 0;
	static int SelecCase = 0;
	static int EtatFilmer = 0;
	static int ChoixLangue = 1;
	static int z = 0;
	
	static tabbouton t;
	static bool pleinEcran = false; 

	static DonneesImageRGB *image = NULL;
	static char nomImage[11];
	static troimat mat;
	static jointure pic[NBIMAGE];
	static stats statistiques[JOINT];
	static int speed = 20;
	int touche;
	static int in = START_IMAGE;
	//Taille image par rapport à la taille de la fenetre 1920 -> 800 / 1080 -> 600
	
	switch (evenement)
	{
		case Initialisation:
			rafraichisFenetre();
			demandeTemporisation(400);
			sauveTexteBouton( ChoixLangue);
			t = IniBouton ();
			break;
		
		case Temporisation:
			if (EtatFilmer == true && in < (NBIMAGE - 1))
			{
				if(in == START_IMAGE)
				{
//					system("./script.sh");
				}
				libereDonneesImageRGB(&image);
				printf("Image numero : %03d\n\n",in);
				sprintf(nomImage,"Pictures/pic%03d.bmp",in+1);
				printf("\nChargement de l'image\n");
				chargeImage(nomImage,&image);
				printf("Image chargée\n");
				printf("image->largeurImage = %d\n",image->largeurImage);
				mat=cree3matrices(image);
				printf("Matrice crée : Fait !\n");
				tp = rgbToHsv(mat);
				printf("Transformation RGB->HSV : Fait !\n");

				identifieColor(tp, pic, in);
				printf("fin_main\n");
				printf("pic[%d].j[0].nb = %d\n",in,pic[in].j[0].nb);

				sommePointJoint(&pic[in]);
				++ in;
			}
			else if (in >= (NBIMAGE - 1) && z==0)
			{
				EtatFilmer = false;
				printf("\nSauvegarde des statistiques :\t");
				apprentissage(pic, statistiques,1);
				printf("Fait\n");
				printf("Affichage des statistiques : \n");
				afficheStats(statistiques);
				z=1;
			}

			rafraichisFenetre();
			break;
			
		case Affichage:
			
			effaceFenetre(44, 62, 80);

			lisTexteBouton(&t, ChoixLangue);
			AffMenu (EtatMenu, SelecBouton, t, SelecCase, EtatFilmer);
			if (EtatFilmer == true)
			{
				if (image != NULL)
				{
					ecrisImage(0, 0, image->largeurImage, image->hauteurImage, image->donneesRGB);
				}

				else
				{
					printf("the picture can't be print\n");
				}
				couleurCourante(0,0,0);

				for(int t=START_IMAGE;t<in-1;t++)
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

				case 'p':
					pause = !pause;
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
			printf("ASCII %d\n", touche);
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
			printf("speed : %d\n", speed);
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
				if (EtatFilmer == 1)
				{
					in = START_IMAGE;
				}

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
			t = IniBouton ();
			break;
	}
}
