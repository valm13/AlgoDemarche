typedef struct points{
	int x,y;
}points;

typedef struct pos{
	float x,y;
}pos;

typedef struct color{
	int red,green,blue;
}color;

typedef struct bouton{
	color crect,ctexte;
	points p1,p2;
	pos txt;
	int police;
	char nom[25];
}bouton;

typedef struct tabbouton{
	int nbbts;
	bouton b[150];
}tabbouton;

