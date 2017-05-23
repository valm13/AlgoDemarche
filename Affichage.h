typedef char chaine[20];

void Encadrement (float xmin,float ymin,float xmax,float ymax, int Rouge, int Vert, int Bleu); //Crée les contours d'un bouton.
void AffMenu (int EtatMenu, int SelecBouton, tabbouton t); //Affiche le menu
tabbouton IniBouton ();   // Initialise les boutons

void sauveTexteBouton(); // Sauvegarde le txt des boutons
void lisTexteBouton(tabbouton *t); //Lis le txt des boutons
