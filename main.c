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

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);



int main(int argc, char **argv)
{
	const rlim_t StackSize = sizeof(image) * LARGEUR * HAUTEUR * 2;
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
	static int EtatMenu = 0;
	static int SelecBouton = 0;
	static bool pleinEcran = false;
	static DonneesImageRGB *img = NULL;
	//~ static DonneesImageRGB imageretour;
	static char nomImage[11];
	static troimat mat;
	static jointure joint;
	switch (evenement)
	{
		case Initialisation:
			demandeTemporisation(20);
			strcpy(nomImage,"TestPic/test.bmp"); 
			printf("\nChargement de l'image\n");
			chargeImage(nomImage,&img); //WORK
			
			printf("Image chargée\n");
			printf("image->largeurImage = %d\n",img->largeurImage);
			
			mat=cree3matrices(img);
			printf("Matrice crée : Fait !\n");
			
			
			//~ for(int k=0;k<600;k++)
			//~ {
				//~ printf("\nmat.r[50][%d]= %d\n",k,mat.r[k][608]);
				//~ printf("mat.g[50][%d]= %d\n",k,mat.v[k][608]); //[y][x]
				//~ printf("mat.b[50][%d]= %d\n",k,mat.b[k][608]);
			//~ }
			
			
			tp=rgbToHsv(mat);
			printf("Transformation RGB->HSV : Fait !\n");
			//~ imageretour.donneesRGB = malloc(image->hauteurImage * image->largeurImage * sizeof(unsigned char) * 3);
			//~ if (imageretour.donneesRGB == NULL)
			//~ {
				//~ fprintf(stderr, "malloc error");
			//~ }
			//~ printf("Malloc image retour fait\n");
			//~ imageretour.hauteurImage = image->hauteurImage;
			//~ imageretour.largeurImage = image->largeurImage;
			joint=identifieColor(tp,img);
			printf("joint.j[0].nb = %d\n",joint.j[0].nb);
			//~ for(int i = 0;i < joint.j[0].nb;i++)
			//~ printf("x = %d\ny = %d\n",joint.j[0].position[i].x,joint.j[0].position[i].y);
			sommePointJoint(&joint);
			
			printf("\nCentre : \nX = %d\nY = %d\n",joint.j[0].centre.x,joint.j[0].centre.y);
			//~ ecrisBMPRGB_Dans(&imageretour,"pic001CONVERT.bmp");
			break;
		
		case Temporisation:
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
			//~ for(int b=0;b<joint.j[0].nb;b++)
			//~ point(joint.j[0].position[b].x,joint.j[0].position[b].y);
			//~ break;
			//~ couleurCourante(255,0,255);
			point(joint.j[0].centre.x,joint.j[0].centre.y);
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

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
