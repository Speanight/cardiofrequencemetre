#include "mesure.h"
#include <stdio.h>


int maj_onde(onde* onde, absorp* currentIir, absorp* lastIir){
 /*
   Objectif :
   		+> Indiquer les valeurs de l'onde pour pouvoir facilement faire des mesures dessus
   Entrée :
   		+> onde 		=> l'onde actuelle que l'ont veut définire
   		+> current		=> le point actuel (serviras a trouver les moment pour lequel l'onde 'coupe' l'axe des abisces)
   		+> pred			=> le point précédent (serviras a trouver le moment pour lequel l'onde coupe l'axe des absicces)
   Sortie :
   		+> mise a jour des infos de l'onde
   		+> Le int vaut 0 en général, et 1 en cas de passage à une autre onde. (passage vals. - à +)
  */

    onde->time++;
    if (currentIir->acr > onde->Xmax->acr || currentIir->acir > onde->Xmax->acir) {
        onde->Xmax = currentIir;
    }

    if (currentIir->acr < onde->Xmin->acr || currentIir->acir < onde->Xmin->acir) {
        onde->Xmin = currentIir;
    }

    if (lastIir->acr < 0 && currentIir->acr > 0) {
        printf("Passage à une autre onde !\n");
        print_absorp(onde->Xmin);
        print_absorp(onde->Xmax);
        printf("Temps : %d\n", onde->time);
        printf("|---------------------|\n");

        return 1;
    }
    return 0;
}

void print_onde(onde* onde){
  /*
	Objectif :
		+> Afficher les caractéristiques de l'onde
	Entrée :
		+> onde
	Sortie :
		+> données de l'onde textuellement
   */
  	printf("Onde :\n");

  	printf("Xmax :");
  	print_absorp(onde->Xmax);

	printf("Xmin:");
	print_absorp(onde->Xmin);

//	printf("Start:");
//	print_absorp(onde->start);
//
//	if(onde->end != NULL){
//    	printf("End:");
//	    print_absorp(onde->end);
//	}

}

void calculs(onde* onde, oxy* myOxy){
  /*
	Objesctifs :
		+> effectuer les calculs et les insérer dans les 'int*' associé
		+> préparer l'onde pour recommencer
	Entrée :
		+> onde 	=> caractéristiques de l'ondes
		+> spo2 	=> un pointeur pour pouvoir utiliser en dehors de la fonctions les données calculées
		+> Bpm		=> un pointeur pour pouvoir utiliser en dehors de la fonctions les données calculées
   */

	/* Calucls*/

  	/* Calculs SPO2 */
	float ptpACR = onde->Xmax->acr - onde->Xmin->acr;
	float ptpACIR = onde->Xmax->acir - onde->Xmin->acir;

//    Valeur non spécifiques pour DCR et DCIR donc on peut prendre c'elle que l'ont veut
    float ptpDCR = onde->Xmax->dcr;
	float ptpDCIR = onde->Xmax->dcir;
//    printf("PTP ACR : %f \nPTP ACIR : %f\n", ptpACR, ptpACIR);
    float RsIr = (ptpACR/ptpDCR) / (ptpACIR/ptpDCIR);
    int ret_spo2 = calcul_SPO2(RsIr);

    /* Calculs BPM */
    // On considère que l'ont prend une donnée toutes les 2ms
    int time = (onde->time)*2;
    int ret_bpm = 60000/time;

    /* Affichage des bpm et spo2 */
    printf("SPO2 : %d\nBPM : %d\n", ret_spo2, ret_bpm);

    /* Ajout dans les int* */
    myOxy->spo2 = ret_spo2;
    myOxy->pouls = ret_bpm;
}

int calcul_SPO2(float ratio){
  /*
	Objectifs :
		+> émuler la fonction spo2(ratio) pour avoir les bons % correspondant au ratio
	Entrée :
		+> ratio 	=> RSIR calculé précédement
	Sortie :
		+> SPO2		=> le spo2 déduit
   */
	if(ratio<1){
		return 100-(ratio-0.4)*25;
    }
    else {
    	return 85-(ratio-1)*35.42;
    }

}

oxy mesureTest(char* filename){
	oxy myOxy;

	return myOxy;
}