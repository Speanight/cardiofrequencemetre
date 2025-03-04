#include "iir.h"
#include "define.h"

absorp iirTest(char* filename){
	absorp	myAbsorp;
	
	return myAbsorp;

}

absorp iir(circular_buffer* cb_fir, circular_buffer* cb_iir){
	/*
	Objectif :
		+> filtrer par iir les données de sorties enregistrées dans le cb_fir
	Entrée :
		+> cb_fir 	=> données filtrées par le fir
		+> cb_irr	=> données filtré actuel et précédemeent par le iir
	Sortie :
		+> absorp 	=> dernière valeur filtrée
		+> mise a jour du circular buffer cb_cir avec les valeurs actuels
	 */

	absorp* currentFirAbsorp = read_from_circular_buffer(cb_fir,0);
	absorp* lastFirAbsorp = read_from_circular_buffer(cb_fir,1);

	absorp* currentIirAbsorp;
	absorp* lastIirAbsorp = read_from_circular_buffer(cb_iir,0);

    float alpha = 0.992;

    currentIirAbsorp->acr = currentFirAbsorp->acr - lastFirAbsorp->acr + alpha * lastIirAbsorp->acr;
    currentIirAbsorp->dcr = currentFirAbsorp->dcr;
	currentIirAbsorp->acir = currentFirAbsorp->acir - lastFirAbsorp->acir + alpha * lastIirAbsorp->acir;
	currentIirAbsorp->dcir = currentFirAbsorp->dcir;

    add_to_circular_buffer(cb_iir,currentIirAbsorp);

    return *currentIirAbsorp;
}

