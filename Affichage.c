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

	//Reconaissance
	t.b[1].p1.x=largeurFenetre()*9/16;
	t.b[1].p1.y=hauteurFenetre()*5/12;
	t.b[1].p2.x=largeurFenetre()*15/16;
	t.b[1].p2.y=hauteurFenetre()*7/12;
	t.b[1].crect.red=52;
	t.b[1].crect.green=152;
	t.b[1].crect.blue=219;
	t.b[1].txt.x=largeurFenetre()*39/64;
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

	return t;
}

void AffMenu (int EtatMenu, int SelecBouton, tabbouton t)
{
		
	if (EtatMenu == 0)
	{
		int i;
		effaceFenetre(44, 62, 80);

		if (SelecBouton != 0) //Pour faire apparaître le bouton Ok
		{
			for(i=0;i<3;i++) 
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
		
		//Encadrement des boutons
		Encadrement (largeurFenetre()*1/16, hauteurFenetre()*5/12, largeurFenetre()*7/16, hauteurFenetre()*7/12, 0, 0, 0);
		Encadrement (largeurFenetre()*9/16, hauteurFenetre()*5/12, largeurFenetre()*15/16, hauteurFenetre()*7/12, 0, 0, 0);

		if (SelecBouton != 0)
		Encadrement (largeurFenetre()*1/16, hauteurFenetre()*1/24, largeurFenetre()*7/32, hauteurFenetre()*2/12, 0, 0, 0);


		if (SelecBouton == 1)  //Apprentissage
		{
			Encadrement (largeurFenetre()*1/16-10, hauteurFenetre()*5/12-10, largeurFenetre()*7/16+10, hauteurFenetre()*7/12+10, 236, 240, 241);
		}

		else if (SelecBouton == 2)  //Reconaissance
		{
			Encadrement (largeurFenetre()*9/16-10, hauteurFenetre()*5/12-10, largeurFenetre()*15/16+10, hauteurFenetre()*7/12+10, 236, 240, 241);
		}

		couleurCourante (0, 0, 0); //Ligne qui sépare l'écran en deux
		ligne(largeurFenetre()*1/2, 0, largeurFenetre()*1/2, hauteurFenetre()); 
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

void sauveTexteBouton()
{
	FILE *f;
	
	f=fopen("FR","wt");
	fprintf(f,"Apprentissage\n");
	fprintf(f,"Reconaissance\n");
	fprintf(f,"Ok\n");


	fclose(f);
}

void lisTexteBouton(tabbouton *t)
{
	FILE *f;

	f=fopen("FR","rt");
	
	fscanf(f,"%s\n",t->b[0].nom);
	fscanf(f,"%s\n",t->b[1].nom);
	fscanf(f,"%s\n",t->b[2].nom);
	fclose(f);
}
