typedef char chaine[20];

void Encadrement (float xmin,float ymin,float xmax,float ymax, int Rouge, int Vert, int Bleu); //Crée les contours d'un bouton.
void AffMenu (int EtatMenu, int SelecBouton, tabbouton t, int SelecCase, int EtatFilmer); //Affiche les menus
tabbouton IniBouton ();   // Initialise les boutons

void sauveTexteBouton (int ChoixLangue); // Sauvegarde le txt des boutons
void lisTexteBouton (tabbouton *t, int ChoixLangue); //Lis le txt des boutons
