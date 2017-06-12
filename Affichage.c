#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GfxLib.h"
#include "BmpLib.h" 
#include "ESLib.h"
#include "GereClic.h"
#include "Bouton.h"
#include "Affichage.h"


void Encadrement (float xmin,float ymin,float xmax,float ymax, int Rouge, int Vert, int Bleu)
{
	epaisseurDeTrait(2);
	couleurCourante (Rouge, Vert, Bleu);
	ligne (xmin, ymin, xmax, ymin);
	ligne (xmax, ymin, xmax, ymax);
	ligne (xmax, ymax, xmin, ymax);
	ligne (xmin, ymax, xmin, ymin);
	
	
}

tabbouton IniBouton ()
{
	tabbouton t;
	t.nbbts=3;

    //Apprentissage
	t.b[0].p1.x=largeurFenetre()*1/16;
	t.b[0].p1.y=hauteurFenetre()*5/12;
	t.b[0].p2.x=largeurFenetre()*7/16;
	t.b[0].p2.y=hauteurFenetre()*7/12;
	t.b[0].crect.red=52;
	t.b[0].crect.green=152;
	t.b[0].crect.blue=219;
	t.b[0].txt.x=largeurFenetre()*7/64;
	t.b[0].txt.y=hauteurFenetre()*23/48;
	t.b[0].ctexte.red=0;
	t.b[0].ctexte.green=0;
	t.b[0].ctexte.blue=0;
	t.b[0].police=34;

	//Reconnaissance
	t.b[1].p1.x=largeurFenetre()*9/16;
	t.b[1].p1.y=hauteurFenetre()*5/12;
	t.b[1].p2.x=largeurFenetre()*15/16;
	t.b[1].p2.y=hauteurFenetre()*7/12;
	t.b[1].crect.red=52;
	t.b[1].crect.green=152;
	t.b[1].crect.blue=219;
	t.b[1].txt.x=largeurFenetre()*38/64;
	t.b[1].txt.y=hauteurFenetre()*23/48;
	t.b[1].ctexte.red=0;
	t.b[1].ctexte.green=0;
	t.b[1].ctexte.blue=0;
	t.b[1].police=34;

	//OK
	t.b[2].p1.x=largeurFenetre()*1/16; 
	t.b[2].p1.y=hauteurFenetre()*1/24;
	t.b[2].p2.x=largeurFenetre()*7/32;
	t.b[2].p2.y=hauteurFenetre()*2/12;
	t.b[2].crect.red=231;
	t.b[2].crect.green=76;
	t.b[2].crect.blue=60;
	t.b[2].txt.x=largeurFenetre()*15/128;
	t.b[2].txt.y=hauteurFenetre()*8/96;
	t.b[2].ctexte.red=0;
	t.b[2].ctexte.green=0;
	t.b[2].ctexte.blue=0;
	t.b[2].police=34;

	//Menu
	t.b[3].p1.x=largeurFenetre()*1/16; 
	t.b[3].p1.y=hauteurFenetre()*1/24;
	t.b[3].p2.x=largeurFenetre()*7/32;
	t.b[3].p2.y=hauteurFenetre()*2/12;
	t.b[3].crect.red=231;
	t.b[3].crect.green=76;
	t.b[3].crect.blue=60;
	t.b[3].txt.x=largeurFenetre()*11/128;
	t.b[3].txt.y=hauteurFenetre()*8/96;
	t.b[3].ctexte.red=0;
	t.b[3].ctexte.green=0;
	t.b[3].ctexte.blue=0;
	t.b[3].police=34;

	//1
	t.b[4].p1.x=largeurFenetre()*1/16; 
	t.b[4].p1.y=hauteurFenetre()*20/24;
	t.b[4].p2.x=largeurFenetre()*3/16;
	t.b[4].p2.y=hauteurFenetre()*23/24;
	t.b[4].crect.red=52;
	t.b[4].crect.green=152;
	t.b[4].crect.blue=219;
	t.b[4].txt.x=largeurFenetre()*14/128;
	t.b[4].txt.y=hauteurFenetre()*84/96;
	t.b[4].ctexte.red=0;
	t.b[4].ctexte.green=0;
	t.b[4].ctexte.blue=0;
	t.b[4].police=34;

	//2
	t.b[5].p1.x=largeurFenetre()*4/16; 
	t.b[5].p1.y=hauteurFenetre()*20/24;
	t.b[5].p2.x=largeurFenetre()*6/16;
	t.b[5].p2.y=hauteurFenetre()*23/24;
	t.b[5].crect.red=52;
	t.b[5].crect.green=152;
	t.b[5].crect.blue=219;
	t.b[5].txt.x=largeurFenetre()*38/128;
	t.b[5].txt.y=hauteurFenetre()*84/96;
	t.b[5].ctexte.red=0;
	t.b[5].ctexte.green=0;
	t.b[5].ctexte.blue=0;
	t.b[5].police=34;

	//3
	t.b[6].p1.x=largeurFenetre()*7/16; 
	t.b[6].p1.y=hauteurFenetre()*20/24;
	t.b[6].p2.x=largeurFenetre()*9/16;
	t.b[6].p2.y=hauteurFenetre()*23/24;
	t.b[6].crect.red=52;
	t.b[6].crect.green=152;
	t.b[6].crect.blue=219;
	t.b[6].txt.x=largeurFenetre()*62/128;
	t.b[6].txt.y=hauteurFenetre()*84/96;
	t.b[6].ctexte.red=0;
	t.b[6].ctexte.green=0;
	t.b[6].ctexte.blue=0;
	t.b[6].police=34;
	
	//Filmer désactivé
	t.b[7].p1.x=largeurFenetre()*9/32; 
	t.b[7].p1.y=hauteurFenetre()*1/24;
	t.b[7].p2.x=largeurFenetre()*22/32;
	t.b[7].p2.y=hauteurFenetre()*2/12;
	t.b[7].crect.red=52;
	t.b[7].crect.green=152;
	t.b[7].crect.blue=219;
	t.b[7].txt.x=largeurFenetre()*53/128;
	t.b[7].txt.y=hauteurFenetre()*8/96;
	t.b[7].ctexte.red=0;
	t.b[7].ctexte.green=0;
	t.b[7].ctexte.blue=0;
	t.b[7].police=34;
	
	//Filmer activé
	t.b[8].p1.x=largeurFenetre()*9/32; 
	t.b[8].p1.y=hauteurFenetre()*1/24;
	t.b[8].p2.x=largeurFenetre()*22/32;
	t.b[8].p2.y=hauteurFenetre()*2/12;
	t.b[8].crect.red=231;
	t.b[8].crect.green=76;
	t.b[8].crect.blue=60;
	t.b[8].txt.x=largeurFenetre()*53/128;
	t.b[8].txt.y=hauteurFenetre()*8/96;
	t.b[8].ctexte.red=0;
	t.b[8].ctexte.green=0;
	t.b[8].ctexte.blue=0;
	t.b[8].police=34;

	//4
	t.b[9].p1.x=largeurFenetre()*10/16; 
	t.b[9].p1.y=hauteurFenetre()*20/24;
	t.b[9].p2.x=largeurFenetre()*12/16;
	t.b[9].p2.y=hauteurFenetre()*23/24;
	t.b[9].crect.red=52;
	t.b[9].crect.green=152;
	t.b[9].crect.blue=219;
	t.b[9].txt.x=largeurFenetre()*86/128;
	t.b[9].txt.y=hauteurFenetre()*84/96;
	t.b[9].ctexte.red=0;
	t.b[9].ctexte.green=0;
	t.b[9].ctexte.blue=0;
	t.b[9].police=34;

	//5
	t.b[10].p1.x=largeurFenetre()*13/16; 
	t.b[10].p1.y=hauteurFenetre()*20/24;
	t.b[10].p2.x=largeurFenetre()*15/16;
	t.b[10].p2.y=hauteurFenetre()*23/24;
	t.b[10].crect.red=52;
	t.b[10].crect.green=152;
	t.b[10].crect.blue=219;
	t.b[10].txt.x=largeurFenetre()*110/128;
	t.b[10].txt.y=hauteurFenetre()*84/96;
	t.b[10].ctexte.red=0;
	t.b[10].ctexte.green=0;
	t.b[10].ctexte.blue=0;
	t.b[10].police=34;
		
	return t;
}

void AffMenu (int EtatMenu, int SelecBouton, tabbouton t, int SelecCase, int EtatFilmer)
{
	int i;
		
	if (EtatMenu == 0) //Affichage du Menu de selection
	{

		if (SelecBouton != 0) //Pour faire apparaître tous les boutons
		{
			for(i=0; i<3; i++) 
			{
				couleurCourante(t.b[i].crect.red,t.b[i].crect.green,t.b[i].crect.blue);
				rectangle(t.b[i].p1.x,t.b[i].p1.y,t.b[i].p2.x,t.b[i].p2.y);
				couleurCourante(t.b[i].ctexte.red,t.b[i].ctexte.green,t.b[i].ctexte.blue);
				afficheChaine(t.b[i].nom,t.b[i].police,t.b[i].txt.x,t.b[i].txt.y);
			}
		}

		else if (SelecBouton == 0) //Pour ne pas faire apparaître le bouton Ok
		{
			for (i=0; i<2; i++)
			{
				couleurCourante(t.b[i].crect.red,t.b[i].crect.green,t.b[i].crect.blue);
				rectangle(t.b[i].p1.x,t.b[i].p1.y,t.b[i].p2.x,t.b[i].p2.y);
				couleurCourante(t.b[i].ctexte.red,t.b[i].ctexte.green,t.b[i].ctexte.blue);
				afficheChaine(t.b[i].nom,t.b[i].police,t.b[i].txt.x,t.b[i].txt.y);
			}
		}

		couleurCourante (255, 255, 255);
		rectangle (largeurFenetre()*1/16, hauteurFenetre()*44/48, largeurFenetre()*5/64, hauteurFenetre()*45/48);

		//Encadrement des boutons
		Encadrement (largeurFenetre()*1/16, hauteurFenetre()*5/12, largeurFenetre()*7/16, hauteurFenetre()*7/12, 0, 0, 0);
		Encadrement (largeurFenetre()*9/16, hauteurFenetre()*5/12, largeurFenetre()*15/16, hauteurFenetre()*7/12, 0, 0, 0);
		Encadrement (largeurFenetre()*1/16, hauteurFenetre()*44/48, largeurFenetre()*5/64, hauteurFenetre()*45/48, 0, 0, 0);
		
		if (SelecBouton != 0)
			Encadrement (largeurFenetre()*1/16, hauteurFenetre()*1/24, largeurFenetre()*7/32, hauteurFenetre()*2/12, 0, 0, 0);


		if (SelecBouton == 1)  //Apprentissage
			Encadrement (largeurFenetre()*1/16-10, hauteurFenetre()*5/12-10, largeurFenetre()*7/16+10, hauteurFenetre()*7/12+10, 236, 240, 241);

		else if (SelecBouton == 2)  //Reconaissance
			Encadrement (largeurFenetre()*9/16-10, hauteurFenetre()*5/12-10, largeurFenetre()*15/16+10, hauteurFenetre()*7/12+10, 236, 240, 241);

		couleurCourante (0, 0, 0); //Ligne qui sépare l'écran en deux
		ligne(largeurFenetre()*1/2, 0, largeurFenetre()*1/2, hauteurFenetre()); 
	}

	

	else if (SelecBouton != 0) // On est dans apprentissage ou reconaissance
	{
		couleurCourante(t.b[3].crect.red,t.b[3].crect.green,t.b[3].crect.blue);
		rectangle(t.b[3].p1.x,t.b[3].p1.y,t.b[3].p2.x,t.b[3].p2.y);
		couleurCourante(t.b[3].ctexte.red,t.b[3].ctexte.green,t.b[3].ctexte.blue);
		afficheChaine(t.b[3].nom,t.b[3].police,t.b[3].txt.x,t.b[3].txt.y);

		Encadrement (largeurFenetre()*1/16, hauteurFenetre()*1/24, largeurFenetre()*7/32, hauteurFenetre()*2/12, 0, 0, 0); //Menu

		

		if (SelecBouton == 1) //Mode Apprentissage
		{
			
			for (i=4; i<7; i++)
			{
				couleurCourante(t.b[i].crect.red,t.b[i].crect.green,t.b[i].crect.blue);
				rectangle(t.b[i].p1.x,t.b[i].p1.y,t.b[i].p2.x,t.b[i].p2.y);
				couleurCourante(t.b[i].ctexte.red,t.b[i].ctexte.green,t.b[i].ctexte.blue);
				afficheChaine(t.b[i].nom,t.b[i].police,t.b[i].txt.x,t.b[i].txt.y);
			}

			for (i=9; i<11; i++)
			{
				couleurCourante(t.b[i].crect.red,t.b[i].crect.green,t.b[i].crect.blue);
				rectangle(t.b[i].p1.x,t.b[i].p1.y,t.b[i].p2.x,t.b[i].p2.y);
				couleurCourante(t.b[i].ctexte.red,t.b[i].ctexte.green,t.b[i].ctexte.blue);
				afficheChaine(t.b[i].nom,t.b[i].police,t.b[i].txt.x,t.b[i].txt.y);
			}

			
			//Encadrement des boutons 1 à 5 
			Encadrement (largeurFenetre()*1/16, hauteurFenetre()*20/24, largeurFenetre()*3/16, hauteurFenetre()*23/24, 0, 0, 0); //1
			Encadrement (largeurFenetre()*4/16, hauteurFenetre()*20/24, largeurFenetre()*6/16, hauteurFenetre()*23/24, 0, 0, 0); //2
			Encadrement (largeurFenetre()*7/16, hauteurFenetre()*20/24, largeurFenetre()*9/16, hauteurFenetre()*23/24, 0, 0, 0); //3
			Encadrement (largeurFenetre()*10/16, hauteurFenetre()*20/24, largeurFenetre()*12/16, hauteurFenetre()*23/24, 0, 0, 0); //4
			Encadrement (largeurFenetre()*13/16, hauteurFenetre()*20/24, largeurFenetre()*15/16, hauteurFenetre()*23/24, 0, 0, 0); //5

			if (SelecCase == 1) //1
				Encadrement (largeurFenetre()*1/32, hauteurFenetre()*39/48, largeurFenetre()*7/32, hauteurFenetre()*47/48, 0, 0, 0);

			
			if (SelecCase == 2) //2
				Encadrement (largeurFenetre()*7/32, hauteurFenetre()*39/48, largeurFenetre()*13/32, hauteurFenetre()*47/48, 0, 0, 0);

			
			if (SelecCase == 3) //3
				Encadrement (largeurFenetre()*13/32, hauteurFenetre()*39/48, largeurFenetre()*19/32, hauteurFenetre()*47/48, 0, 0, 0);
				
			if (SelecCase == 4) //4
				Encadrement (largeurFenetre()*19/32, hauteurFenetre()*39/48, largeurFenetre()*25/32, hauteurFenetre()*47/48, 0, 0, 0);

			
			if (SelecCase == 5) //5
				Encadrement (largeurFenetre()*25/32, hauteurFenetre()*39/48, largeurFenetre()*31/32, hauteurFenetre()*47/48, 0, 0, 0);


			// Boutons delete
			couleurCourante (231, 76, 60);
			rectangle (largeurFenetre()*4/64, hauteurFenetre()*93/96, largeurFenetre()*5/64, hauteurFenetre()*95/96); //1
			rectangle (largeurFenetre()*16/64, hauteurFenetre()*93/96, largeurFenetre()*17/64, hauteurFenetre()*95/96); //2
			rectangle (largeurFenetre()*28/64, hauteurFenetre()*93/96, largeurFenetre()*29/64, hauteurFenetre()*95/96); //3
			rectangle (largeurFenetre()*40/64, hauteurFenetre()*93/96, largeurFenetre()*41/64, hauteurFenetre()*95/96); //4
			rectangle (largeurFenetre()*52/64, hauteurFenetre()*93/96, largeurFenetre()*53/64, hauteurFenetre()*95/96); //5
			
			// Encadrement Boutons delete les démarche enregistrées
			Encadrement (largeurFenetre()*4/64, hauteurFenetre()*93/96, largeurFenetre()*5/64, hauteurFenetre()*95/96, 0, 0, 0); //1
			Encadrement (largeurFenetre()*16/64, hauteurFenetre()*93/96, largeurFenetre()*17/64, hauteurFenetre()*95/96, 0, 0, 0); //2
			Encadrement (largeurFenetre()*28/64, hauteurFenetre()*93/96, largeurFenetre()*29/64, hauteurFenetre()*95/96, 0, 0, 0); //3
			Encadrement (largeurFenetre()*40/64, hauteurFenetre()*93/96, largeurFenetre()*41/64, hauteurFenetre()*95/96, 0, 0, 0); //4
			Encadrement (largeurFenetre()*52/64, hauteurFenetre()*93/96, largeurFenetre()*53/64, hauteurFenetre()*95/96, 0, 0, 0); //5


			if (SelecCase != 0) //Filmer
			{
				if (EtatFilmer == 0)
				{
					couleurCourante(t.b[7].crect.red,t.b[7].crect.green,t.b[7].crect.blue);
					rectangle(t.b[7].p1.x,t.b[7].p1.y,t.b[7].p2.x,t.b[7].p2.y);
					couleurCourante(t.b[7].ctexte.red,t.b[7].ctexte.green,t.b[7].ctexte.blue);
					afficheChaine(t.b[7].nom,t.b[7].police,t.b[7].txt.x,t.b[7].txt.y);
					Encadrement (largeurFenetre()*9/32, hauteurFenetre()*1/24, largeurFenetre()*22/32, hauteurFenetre()*2/12, 0, 0, 0); 
				}

				if (EtatFilmer == 1)
				{
					couleurCourante(t.b[8].crect.red,t.b[8].crect.green,t.b[8].crect.blue);
					rectangle(t.b[8].p1.x,t.b[8].p1.y,t.b[8].p2.x,t.b[7].p2.y);
					couleurCourante(t.b[8].ctexte.red,t.b[8].ctexte.green,t.b[8].ctexte.blue);
					afficheChaine(t.b[8].nom,t.b[8].police,t.b[8].txt.x,t.b[8].txt.y);
					Encadrement (largeurFenetre()*9/32, hauteurFenetre()*1/24, largeurFenetre()*22/32, hauteurFenetre()*2/12, 0, 0, 0); 
				}
			}
			
		}

		if (SelecBouton == 2) //mode Reconaissance
		{
			if (EtatFilmer == 0 )
			{
				couleurCourante(t.b[7].crect.red,t.b[7].crect.green,t.b[7].crect.blue);
				rectangle(t.b[7].p1.x,t.b[7].p1.y,t.b[7].p2.x,t.b[7].p2.y);
				couleurCourante(t.b[7].ctexte.red,t.b[7].ctexte.green,t.b[7].ctexte.blue);
				afficheChaine(t.b[7].nom,t.b[7].police,t.b[7].txt.x,t.b[7].txt.y);
				Encadrement (largeurFenetre()*9/32, hauteurFenetre()*1/24, largeurFenetre()*22/32, hauteurFenetre()*2/12, 0, 0, 0); 
			}

			if (EtatFilmer == 1)
			{
				couleurCourante(t.b[8].crect.red,t.b[8].crect.green,t.b[8].crect.blue);
				rectangle(t.b[8].p1.x,t.b[8].p1.y,t.b[8].p2.x,t.b[7].p2.y);
				couleurCourante(t.b[8].ctexte.red,t.b[8].ctexte.green,t.b[8].ctexte.blue);
				afficheChaine(t.b[8].nom,t.b[8].police,t.b[8].txt.x,t.b[8].txt.y);
				Encadrement (largeurFenetre()*9/32, hauteurFenetre()*1/24, largeurFenetre()*22/32, hauteurFenetre()*2/12, 0, 0, 0); 
			}
		}
	}
	else;
}

tabbouton lisDescriptionBouton(chaine nomFichier) // Fonctionne
{
	tabbouton t;
	FILE *f;
	f=fopen(nomFichier,"rb");
	fread(&(t.nbbts),sizeof(int),1,f);
	for(int i=0;i<t.nbbts;i++)
	{
	fread(&(t.b[i].p1.x),sizeof(int),1,f);
	fread(&(t.b[i].p1.y),sizeof(int),1,f);
	fread(&(t.b[i].p2.x),sizeof(int),1,f);
	fread(&(t.b[i].p2.y),sizeof(int),1,f);
	
	fread(&(t.b[i].crect.red),sizeof(int),1,f);
	fread(&(t.b[i].crect.green),sizeof(int),1,f);
	fread(&(t.b[i].crect.blue),sizeof(int),1,f);

	fread(&(t.b[i].txt.x),sizeof(int),1,f);
	fread(&(t.b[i].txt.y),sizeof(int),1,f);
	
	fread(&(t.b[i].ctexte.red),sizeof(int),1,f);
	fread(&(t.b[i].ctexte.green),sizeof(int),1,f);
	fread(&(t.b[i].ctexte.blue),sizeof(int),1,f);

	fread(&(t.b[i].police),sizeof(int),1,f);
	}
	fclose(f);
	return t;
}

void sauveTexteBouton (int ChoixLangue)
{
	FILE *f;

		f=fopen("FR","wt");
		
		fprintf(f,"Apprentissage\n");
		fprintf(f,"Reconnaissance\n");
		fprintf(f,"Ok\n");
		fprintf(f,"Menu\n");
		fprintf(f,"1\n");
		fprintf(f,"2\n");
		fprintf(f,"3\n");
		fprintf(f,"Filmer\n");
		fprintf(f,"Filmer\n");
		fprintf(f,"4\n");
		fprintf(f,"5\n");

		fclose (f);


		f=fopen("EN","wt");

		fprintf(f,"Learning\n");
		fprintf(f,"Recognition\n");
		fprintf(f,"Ok\n");
		fprintf(f,"Menu\n");
		fprintf(f,"1\n");
		fprintf(f,"2\n");
		fprintf(f,"3\n");
		fprintf(f,"Filming\n");
		fprintf(f,"Filming\n");
		fprintf(f,"4\n");
		fprintf(f,"5\n");	

		fclose(f);
}

void lisTexteBouton (tabbouton *t, int ChoixLangue)
{
	
	FILE *f;

	if (ChoixLangue == 0)
		f=fopen("FR","rt");

	else if (ChoixLangue == 1)
		f=fopen("EN","rt");

	fscanf(f,"%s\n",t->b[0].nom);
	fscanf(f,"%s\n",t->b[1].nom);
	fscanf(f,"%s\n",t->b[2].nom);
	fscanf(f,"%s\n",t->b[3].nom);
	fscanf(f,"%s\n",t->b[4].nom);
	fscanf(f,"%s\n",t->b[5].nom);
	fscanf(f,"%s\n",t->b[6].nom);
	fscanf(f,"%s\n",t->b[7].nom);
	fscanf(f,"%s\n",t->b[8].nom);
	fscanf(f,"%s\n",t->b[9].nom);
	fscanf(f,"%s\n",t->b[10].nom);

	fclose(f);
}
