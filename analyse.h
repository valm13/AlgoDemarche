#define LARGEUR 1920
#define HAUTEUR 1080

typedef struct pixelhsv{
	int h,s,v;
}pixelhsv;

typedef struct tabpixel{
	pixelhsv p[1920][1080];
}tabpixel;

typedef struct infocoul{
	int c; // 1=Bleu	2=Vert	3=Rouge
	char v; // Valeur
}infocoul;



typedef struct determ{
	infocoul min,max;
}determ;




void rgbToHsv(DonneesImageRGB *img);

void chargeImage(char nomFichier[11],DonneesImageRGB **img);

void determineMaxColor(char bleu,char vert,char rouge,determ *det);
void determineMinColor(char bleu,char vert,char rouge,determ *det);

int calculS(determ det);
int calculH(determ det,char r,char g,char b);


//Fonctions Inutiles :
void test(DonneesImageRGB *img);
void test2(DonneesImageRGB *img);
