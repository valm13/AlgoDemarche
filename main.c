#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <string.h>
#include <sys/resource.h>
#include "libISEN/GfxLib.h"
#include "libISEN/BmpLib.h"
#include "libISEN/ESLib.h"
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
	static int in = START_IMAGE;
	static image tp;
	static int EtatMenu = 0;
	static int SelecBouton = 0;
	static bool pleinEcran = false;
	static DonneesImageRGB *img = NULL;
	//~ static DonneesImageRGB imageretour;
	static char nomImage[11];
	static troimat mat;
	static jointure pic[NBIMAGE];
	static int speed = 20;
	int touche;
	//Taille image par rapport à la taille de la fenetre 1920 -> 800 / 1080 -> 600
	static int ratio_x;
	static int ratio_y;
	
	switch (evenement)
	{
		case Initialisation:
			demandeTemporisation(200);
			printf("Image numero : %03d\n\n",in);
			sprintf(nomImage,"Pictures2/pic%03d.bmp",in+1);
			printf("\nChargement de l'image\n");
			chargeImage(nomImage,&img);
			printf("Image chargée\n");
			printf("image->largeurImage = %d\n",img->largeurImage);
			mat=cree3matrices(img);
			printf("Matrice crée : Fait !\n");
			tp=rgbToHsv(mat);
			printf("Transformation RGB->HSV : Fait !\n");

			identifieColor(tp,pic,in);
			printf("fin_main\n");
q			printf("pic[%d].j[0].nb = %d\n",in,pic[in].j[0].nb);

			sommePointJoint(&pic[in]);
			in ++;

			printf("\nCentre Rouge img%d : \nX = %d\nY = %d\n",in ,pic[in].j[0].centre.x,pic[in].j[0].centre.y);
//			for(int i=0;i<NBIMAGE;i++)
//			{
//				printf("Image numero : %03d\n\n",i);
//				sprintf(nomImage,"Pictures/pic%03d.bmp",i+1);
//				printf("\nChargement de l'image\n");
//				chargeImage(nomImage,&img);
//				printf("Image chargée\n");
//				printf("image->largeurImage = %d\n",img->largeurImage);
//				mat=cree3matrices(img);
//				printf("Matrice crée : Fait !\n");
//				tp=rgbToHsv(mat);
//				printf("Transformation RGB->HSV : Fait !\n");
//
//				identifieColor(tp,pic,i); // Problème ici
//				printf("fin_main\n");
//				printf("pic[%d].j[0].nb = %d\n",i,pic[i].j[0].nb);
//
//				sommePointJoint(&pic[i]);
//
//				printf("\nCentre Rouge img%d : \nX = %d\nY = %d\n",i,pic[i].j[0].centre.x,pic[i].j[0].centre.y);
//			}
			break;
		
		case Temporisation:
			if( in < NBIMAGE && !pause)
			{
				libereDonneesImageRGB(&img);
				printf("Image numero : %03d\n\n",in);
				sprintf(nomImage,"Pictures2/pic%03d.bmp",in+1);
				printf("\nChargement de l'image\n");
				chargeImage(nomImage,&img);
				printf("Image chargée\n");
				printf("image->largeurImage = %d\n",img->largeurImage);
				mat=cree3matrices(img);
				printf("Matrice crée : Fait !\n");
				tp=rgbToHsv(mat);
				printf("Transformation RGB->HSV : Fait !\n");

				identifieColor(tp,pic,in);
				printf("fin_main\n");
				printf("pic[%d].j[0].nb = %d\n",in,pic[in].j[0].nb);

				sommePointJoint(&pic[in]);

				printf("\nCentre Rouge img%d : \nX = %d\nY = %d\n",in ,pic[in].j[0].centre.x,pic[in].j[0].centre.y);
				in ++;
			}
			ratio_x = img->largeurImage/LargeurFenetre;
			ratio_y = img->hauteurImage/HauteurFenetre;
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			effaceFenetre (255, 255, 255);

			AffMenu (EtatMenu, SelecBouton);
			
			if (img != NULL)
			{
				ecrisImage(0, 0, img->largeurImage, img->hauteurImage, img->donneesRGB);
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
			if(speed < 0)
			{
				speed = 0;
			}
			printf("speed : %d\n", speed);
			demandeTemporisation(speed);
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
