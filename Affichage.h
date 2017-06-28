typedef char chaine[20];
/****************************************************
 Nom : Encadrement
 Description : Create a border around a button
 Valeur retournée : 
 Paramètre en entrée : float xmin,float ymin,float xmax,float ymax, int Rouge, int Vert, int Bleu
 Paramètre en entrée / sortie :
 Paramètres en sortie : 
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void Encadrement (float xmin,float ymin,float xmax,float ymax, int Rouge, int Vert, int Bleu);
/****************************************************
 Nom : AffMenu
 Description : Display menu
 Valeur retournée : 
 Paramètre en entrée : int EtatMenu, int SelecBouton, tabbouton t, int SelecCase, int EtatFilmer
 Paramètre en entrée / sortie :
 Paramètres en sortie : 
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void AffMenu (int EtatMenu, int SelecBouton, tabbouton t, int SelecCase, int EtatFilmer);
/****************************************************
 Nom : IniBouton
 Description : Initialize buttons
 Valeur retournée : tabbouton
 Paramètre en entrée : 
 Paramètre en entrée / sortie :
 Paramètres en sortie : tabbouton
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
tabbouton IniBouton ();   // Initialise les boutons
/****************************************************
 Nom : sauveTexteBouton
 Description : Save the text of buttons into a file
 Valeur retournée : tabbouton
 Paramètre en entrée : 
 Paramètre en entrée / sortie :
 Paramètres en sortie : tabbouton
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void sauveTexteBouton (int ChoixLangue); // Sauvegarde le txt des boutons
void lisTexteBouton (tabbouton *t, int ChoixLangue); //Lis le txt des boutons
