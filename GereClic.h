/****************************************************
 Nom : EncadrementBouton
 Description : Selection of Learning phase or recognition phase
 Valeur retournée : 
 Paramètre en entrée : int EtatMenu
 Paramètre en entrée / sortie : int *SelecBouton
 Paramètres en sortie : 
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void EncadrementBouton (int *SelecBouton, int EtatMenu);
/****************************************************
 Nom : ClicLangue
 Description : Selection of the language
 Valeur retournée : 
 Paramètre en entrée : int EtatMenu
 Paramètre en entrée / sortie : int *SelecBouton
 Paramètres en sortie : 
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void ClicLangue (int *ChoixLangue, int EtatMenu);
/****************************************************
 Nom : ClicOk
 Description : Set var to 0 when go back to the menu
 Valeur retournée : 
 Paramètre en entrée :
 Paramètre en entrée / sortie : int *EtatMenu, int *SelecBouton, int *SelecCase, int *EtatFilmer
 Paramètres en sortie : 
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void ClicOk (int *EtatMenu, int *SelecBouton, int *SelecCase, int *EtatFilmer);
/****************************************************
 Nom : ClicApprentissage
 Description : Change between the name selected
 Valeur retournée : 
 Paramètre en entrée : int EtatMenu
 Paramètre en entrée / sortie : int *SelecBouton
 Paramètres en sortie : 
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void ClicApprentissage (int EtatMenu, int *SelecCase);
/****************************************************
 Nom : ClicFilmer
 Description : Manage the click on filming button
 Valeur retournée : 
 Paramètre en entrée : int EtatMenu, int SelecCase, int SelecBouton
 Paramètre en entrée / sortie : int *SelecBouton
 Paramètres en sortie : 
 Auteur : Damien Fontes
 Date de création : 28/06/2017
 Modifications (date, auteur et nature) :
 ***************************************************/
void ClicFilmer (int *EtatFilmer, int EtatMenu, int SelecCase, int SelecBouton);
