#include <stdio.h>
#include "libISEN/BmpLib.h"
#include "analyse.h"
#include "toolbox.h"

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

void chargeImage(char nomFichier[11],DonneesImageRGB **img)	// Charge une image grâce au nom de celle-ci
{
	*img = lisBMPRGB(nomFichier);
	if((*img == NULL))
	{
		fprintf(stderr, "erreur l'image %s n'a pas pu être charger", nomFichier);
	}
}

tabpixel rgbToHsv(DonneesImageRGB *img) //Pour 1 photo
{
	char bleu,vert,rouge;
	int h,s,v;
	tabpixel tp; // Adapter la taille du tableau en dynamique
//	int nbpixel = img->largeurImage*img->hauteurImage;
	determ det;
	if(img->hauteurImage != HAUTEUR || img->largeurImage != LARGEUR)
	{
		fprintf(stderr, "les collone ou/et les lignes des deux images ne correspondent pas");
	}
	for(int i = 0; i < MIN( img->hauteurImage, HAUTEUR); i++)
	{
		
		for(int j = 0; j < MIN(img->largeurImage, LARGEUR); j++)
		{
			bleu=img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 0];
			vert=img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 1];
			rouge=img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 2];
			
			determineMinColor(bleu,vert,rouge,&det);	// Determine le max et le min pour effectuer les calculs de H S et V
			determineMaxColor(bleu,vert,rouge,&det);
			// printf("det.min.c = %d\n",det.min.c);
			// printf("det.max.c = %d\n",det.max.c);
			h=calculH(det,rouge,vert,bleu);
			s=calculS(det);
			v=det.max.v;
			
			printf("%d ", h);

			tp.p[i][j].h=h;	// Rentre les valeurs de H S et V dans un tableau de pixel(une image)
			tp.p[i][j].s=s;
			tp.p[i][j].v=v;
		}
		printf("\n ");
	}
	return tp;
}

void determineMaxColor(char bleu,char vert,char rouge,determ *det)
{

	if(bleu>=vert && bleu >=rouge)
	{
		det->max.c=1;
		det->max.v=bleu;
	}
	else if(vert>=bleu && vert>=rouge)
	{
		det->max.c=2;
		det->max.v=vert;
	}
	else if(rouge>=vert && rouge >=bleu)
	{
		det->max.c=3;
		det->max.v=rouge;
	}
}

void determineMinColor(char bleu,char vert,char rouge,determ *det)
{

	if(bleu<=vert && bleu <=rouge)
	{
		det->min.c=1;
		det->min.v=bleu;
	}
	else if(vert<=bleu && vert<=rouge)
	{
		det->min.c=2;
		det->min.v=vert;
	}
	else if(rouge<=vert && rouge <=bleu)
	{
		det->min.c=3;
		det->min.v=rouge;
	}
}


//~ void test(DonneesImageRGB *img) // Affichage de toutes les données de l'image
//~ {
	//~ for(int i=0;i<421500;i++) //421500 = NbPixel * 3 (RVB)
	//~ {
		//~ printf("%d\n",img->donneesRGB[i]);
	//~ }
//~ }
//~ void test2(DonneesImageRGB *img) // Filtre Rouge, Vert ou Bleu #PourleFun
//~ {
	//~ for(int i=2;i<421500;i=i+3) //421500 = NbPixel * 3 (RVB)
	//~ {
		//~ img->donneesRGB[i]=255;
	//~ }
//~ }

double calculS(determ det)
{
	if(det.max.v==0)
	return 0;
	else
	return 1-((double)det.min.v/det.max.v);

}

int calculH(determ det,char r,char g,char b)
{
	if(det.max.v==det.min.v)
	return 0;
	else if(det.max.c==3) // r
	{
		return (int)(60*((float)(g-b)/(det.max.v-det.min.v))+360)%360;
	}
	else if(det.max.c==2) // v
	{
		return 60*((float)(b-r)/(det.max.v-det.min.v))+120;
	}
	else if(det.max.c==1) // b
	{
		return 60*((float)(r-g)/(det.max.v-det.min.v))+240;
	}
	else
	return -1;
}




int ChangePixCouleurImg(pixelhsv p, int targuet, int offset)
{
	if ((p.h + 180)%360 > targuet - offset && (p.h + 180)%360 < targuet + offset) // Le pixel est bien vert !
	return 1; // On va le mettre en blanc
	else 
	return 0; // On va le mettre en noir
}

void identifieColor(tabpixel tp,DonneesImageRGB *img)
{
		int colorchange;

		hsv pix_hsv;
		rgb pix_rgb;
		if(img->hauteurImage != HAUTEUR || img->largeurImage != LARGEUR)
		{
			fprintf(stderr, "les collone ou/et les lignes des deux images ne correspondent pas");
		}
		for(int i = 0; i < MIN( img->hauteurImage, HAUTEUR); i++)
		{
//			printf("\n");
			for(int j = 0; j < MIN(img->largeurImage, LARGEUR); j++)
			{
				pix_hsv.h = (i+j) % 360;
				pix_hsv.s = ((double)( i )) / (HAUTEUR);
				pix_hsv.v = 1;

				pix_hsv.h = (tp.p[i][j].h + 180)%360;
				pix_hsv.s = 1; //tp.p[i][j].s;
				pix_hsv.v = 1; //((double)tp.p[i][j].v);
				pix_rgb = hsv2rgb(pix_hsv);
				img->donneesRGB[i * img->largeurImage * 3 + j * 3] = pix_rgb.b * 255;
				img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 1] = pix_rgb.g * 255;
				img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 2] = pix_rgb.r * 255;
				//				colorchange=ChangePixCouleurImg(tp.p[i][j], 290, 5);
//				if (colorchange == 1)
//				{
//					img->donneesRGB[i * img->largeurImage * 3 + j * 3]=255;
//					img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 1]=255;
//					img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 2]=255;
//				}
//				else
//				{
//					img->donneesRGB[i * img->largeurImage * 3 + j * 3]=0;
//					img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 1]=0;
//					img->donneesRGB[i * img->largeurImage * 3 + j * 3 + 2]=0;
//				}
			}
			
		}
}
