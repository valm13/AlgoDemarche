//~ #include <stdlib.h>
//~ #include <stdio.h>
//~ #include <math.h>
//~ #include "GfxLib.h"
//~ #include "BmpLib.h" 
//~ #include "ESLib.h"
//~ #include "GereClic.h"
//~ #include "Bouton.h"
//~ #include "Affichage.h"



//~ void GereSauvegarde (int *EtatFilmer, chaine AucuneIdee, nuage N, int SelecCase)
//~ {
	//~ if (EtatFilmer == 2)
	//~ {
		//~ SauveBinaire (AucuneIdee, N, SelecCase);
		//~ *EtatFilmer == 0;
	//~ }
//~ }


//~ void SauveBinaire (chaine AucuneIdee, nuage N, int SelecCase)
//~ {
	//~ char FichierBinaire;
	//~ strcpy (FichierBinaire, "B");
	//~ strcat (FichierBinaire, SelecCase);
	
	//~ FILE *f;
	//~ f = fopen(FichierBinaire,"wb");

	//~ fwrite (&N, sizeof (nuage),1,f);

	//~ fclose(f);
//~ }


//~ nuage ChargeNuageBinaire (chaine AucuneIdee, int SelecCase)
//~ {
	//~ nuage N;

	//~ strcpy (FichierBinaire, "B");
	//~ strcat (FichierBinaire, SelecCase);
	
	//~ FILE *f;
	//~ f = fopen(FichierBinaire,"rb");

	//~ fread(&N, sizeof(nuage),1,f);
	
	//~ return N;
//~ }
