#ifndef CONFIG_H
#define CONFIG_H

/**********************************************************************************/
/**************************     file characteristic     ***************************/
/**********************************************************************************/

#define LARGEUR 1920	// Largeur de l'image 1920
#define HAUTEUR 1080	// Hauteur de l'image 1080 | image de test : 800 / 600
#define NBIMAGE 57 // Nombre total d'images

#define START_IMAGE 4

#define CIRCLE_RADIUS 150

#define JOINT 5	// Jointures des articulation Main Coude Pied Epaule Genoux
#define MAXPIXJOINT 480000	// Jointures des articulation



typedef struct posi{
	int x,y;
}posi;

typedef struct posf{
	float x,y;
}posf;

typedef struct info{
	posi position[MAXPIXJOINT]; // y puis x
	int nb;
	posi centre;
}info;

typedef struct jointure{
	info j[JOINT];

}jointure;

typedef struct hull{
	int min,max;
}hull;

typedef struct stats{
	int lenght;
	posf mean;
	posf devia;
	hull h;
}stats;


/**********************************************************************************/
/**************************     macro function          ***************************/
/**********************************************************************************/

#define	BETWEEN(IN, MIN, MAX) (((IN) > (MIN) && (IN) < (MAX)) ? (1) : (0))

#endif
