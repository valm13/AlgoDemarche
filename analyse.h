#define LARGEUR 1920	// Largeur de l'image
#define HAUTEUR 1080	// Hauteur de l'image

typedef struct pixelhsv{
	int h; double s,v; // Repere HSV	H: Hue	S: Saturation	V: Value
}pixelhsv;

typedef struct tabpixel{
	pixelhsv p[HAUTEUR][LARGEUR];
}tabpixel;

typedef struct infocoul{
	int c; // 1=Bleu	2=Vert	3=Rouge
	char v; // Valeur
}infocoul;

typedef struct determ{
	infocoul min,max; // Valeur Min et Max + Info sur la couleur correspondante
}determ;




tabpixel rgbToHsv(DonneesImageRGB *img);

void chargeImage(char nomFichier[11],DonneesImageRGB **img);

void determineMaxColor(char bleu,char vert,char rouge,determ *det);
void determineMinColor(char bleu,char vert,char rouge,determ *det);

double calculS(determ det);
int calculH(determ det,char r,char g,char b);


int ChangePixCouleurImg(pixelhsv p, int targuet, int offset);
void identifieColor(tabpixel tp,DonneesImageRGB *img);
