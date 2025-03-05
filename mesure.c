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

void calculs(onde* onde, int* spo2, int* bpm){
  /*
	Objesctifs :
		+> effectuer les calculs et les insérer dans les 'int*' associé
		+> préparer l'onde pour recommencer
	Entrée :
		+> onde 	=> caractéristiques de l'ondes
		+> spo2 	=> un pointeur pour pouvoir utiliser en dehors de la fonctions les données calculées
		+> Bpm		=> un pointeur pour pouvoir utiliser en dehors de la fonctions les données calculées
   */

  printf("Lol j'en ai aucune idée de ce que je dois calculer !!\n");
	/* Calucls*/


  	/* Préparations de la nouvelle onde */
//  onde->start = onde->end;
//  onde->end = NULL;

}

oxy mesureTest(char* filename){
	oxy myOxy;

	return myOxy;
}