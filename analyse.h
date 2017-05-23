#define LARGEUR 1920	// Largeur de l'image
#define HAUTEUR 1080	// Hauteur de l'image

typedef struct pixelhsv{
	int h,s,v; // Repere HSV	H: Hue	S: Saturation	V: Value
}pixelhsv;

typedef struct tabpixel{
	pixelhsv p[LARGEUR][HAUTEUR];
}tabpixel;

typedef struct infocoul{
	int c; // 1=Bleu	2=Vert	3=Rouge
	char v; // Valeur
}infocoul;

typedef struct determ{
	infocoul min,max; // Valeur Min et Max + Info sur la couleur correspondante
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
