#include "mesure.h"
#include <stdio.h>
#include <stdbool.h>

/**
* Objectif :+> Indiquer les valeurs de l'onde pour pouvoir facilement faire des mesures dessus
 * @param onde			=> l'onde actuelle que l'ont veut définire
 * @param currentIir	=> le point actuel (serviras a trouver les moment pour lequel l'onde 'coupe' l'axe des abisces)
 * @param lastIir		=> le point précédent (serviras a trouver le moment pour lequel l'onde coupe l'axe des absicces)
 *
 * @return				+> mise a jour des infos de l'onde
 *						+> Le int vaut 0 en général, et 1 en cas de passage à une autre onde. (passage vals. - à +)
 */
int maj_onde(onde* onde, absorp* currentIir, absorp* lastIir){
	//On ajoute le 2ms a la durée de l'onde
    onde->time++;

	// On vérifie si le point de l'onde actuel est plus élevé que le point enregistré (on change si oui)
    if (currentIir->acr > onde->Xmax->acr || currentIir->acir > onde->Xmax->acir) {
        onde->Xmax = currentIir;
    }

	// On vérifie si le point de l'onde actuel est plus bas que le point enregistré (on change si oui)
    if (currentIir->acr < onde->Xmin->acr || currentIir->acir < onde->Xmin->acir) {
        onde->Xmin = currentIir;
    }

	//On vérifie si l'onde traverse l'axe des abcisses pour envoyer un signa dans le cas ou l'onde est terminée
    return lastIir->acr < 0 && currentIir->acr > 0;
}

/**
* Objectif :+> Afficher les caractéristiques de l'onde
 * @param onde
 */
void print_onde(onde* onde){
  	printf("Onde :\n");

  	printf("Xmax :");
  	print_absorp(onde->Xmax);

	printf("Xmin:");
	print_absorp(onde->Xmin);

	printf("Durée : %dms\n", (onde->time)*2);
}

/**
* Objectifs :
		+> effectuer les calculs et les insérer dans les 'int*' associé
		+> préparer l'onde pour recommencer
 * @param onde		=> caractéristiques de l'ondes
 * @param myOxy		=> contient les résultats des calculs pour les envoyer en dehors de la fonction
 */
void calculs(onde* onde, oxy* myOxy){
	/* Calucls*/

  	/* Calculs SPO2 */
	// calcul des valeur crète a crète
	float ptpACR = onde->Xmax->acr - onde->Xmin->acr;
	float ptpACIR = onde->Xmax->acir - onde->Xmin->acir;

//    Valeur non spécifiques pour DCR et DCIR donc on peut prendre c'elle que l'ont veut
    float DCR = onde->Xmax->dcr;
	float DCIR = onde->Xmax->dcir;
//    printf("PTP ACR : %f \nPTP ACIR : %f\n", ptpACR, ptpACIR);
    float RsIr = (ptpACR/DCR) / (ptpACIR/DCIR);
	// printf("RsIr : %f\n", RsIr);

    int ret_spo2 = calcul_SPO2(RsIr);

    /* Calculs BPM */
    // On considère que l'ont prend une donnée toutes les 2ms
    const int time = (onde->time)*2;
    const int ret_bpm = 60000/time;

    /* Affichage des bpm et spo2 */
 //    printf("SPO2 : %d\nBPM : %d\n", ret_spo2, ret_bpm);
 //    printf("-------------->>>>>>>\n");

    /* Ajout dans la structure Oxy* */
    myOxy->spo2 = ret_spo2;
    myOxy->pouls = ret_bpm;
}

/**
* Objectifs :+> émuler la fonction spo2(ratio) pour avoir les bons % correspondant au ratio
 * @param ratio		=> RSIR calculé dans la fonction 'calcul'
 * @return			=> le spo2 déduit
 */
int calcul_SPO2(float ratio){
	if(ratio<1){
		return 100-(ratio-0.4)*25;
    }
    else {
    	return 85-(ratio-1)*35.42;
    }

}

/**
 * Objectif : éffectuer des test directement depuis un fichier pour vérifier le fonctionnement de mesure et qui renvoie les dernier résultats
 * @param filename		+> le nomb du fichier contenant les valeurs a tester
 * @return				+> le dernier Oxy calculé (les dernier BPM et SPO2)
 */
oxy mesureTest(char* filename){
	oxy myOxy;

	// Ouverture du fichier
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Erreur ouverture fichier (firTest)\n");
		// Initialisation de valeurs par défaut
		myOxy.pouls=0;
		myOxy.spo2=0;
		return myOxy;
	}

	char fBuffer[256];
	absorp* lastIir = NULL;

	// On crée l'onde et le Oxy qui contiendras les valeurs précédentes
	onde* myonde = malloc(sizeof(onde));
	oxy* tempOxy = malloc(sizeof(oxy));

	// Nous permet de ne pas éxecuter la première occurence (nous avons besoin d'au minimum deux valeurs pour faire nos calculs d'onde)
    bool first_turn = true;

	while (fgets(fBuffer, sizeof(fBuffer), file)) {
		absorp* currentIir = malloc(sizeof(absorp));
		sscanf(fBuffer, "%f,%f,%f,%f", &currentIir->acr, &currentIir->dcr, &currentIir->acir, &currentIir->dcir);
		if(first_turn){
			// Dans le cas de la première valeur on définis notre onde en fonction d'elle
            myonde->time = 0;
            myonde->Xmax = currentIir;
            myonde->Xmin = currentIir;
            first_turn = false;
        }
        else {
        	// on met a jour les paramètres de l'onde et on vérifie si l'onde est terminée
          	if (maj_onde(myonde, currentIir, lastIir) == 1) {
				calculs(myonde, tempOxy);
				// Remise à zéro de l'onde
          		myonde->time = 0;
          		myonde->Xmin = currentIir;
          		myonde->Xmax = currentIir;
          	}
		}
        lastIir = currentIir;
    }
	myOxy = *tempOxy;
	return myOxy;
}