void EncadrementBouton (int *SelecBouton, int EtatMenu); // Permet de selectionner un mod

void ClicLangue (int *ChoixLangue, int EtatMenu); // Permet le changement de langue
void ClicOk (int *EtatMenu, int *SelecBouton, int *SelecCase, int *EtatFilmer); //Change d'état le menu et remet à 0 les variables quand on revient dans le menu
void ClicApprentissage (int EtatMenu, int *SelecCase); //Change d'état en fonction du prénom choisi
void ClicFilmer (int *EtatFilmer, int EtatMenu, int SelecCase, int SelecBouton); //Change d'état quand on appui sur filmer
