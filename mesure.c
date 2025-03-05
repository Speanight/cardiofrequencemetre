#include "mesure.h"
#include <stdio.h>


void maj_onde(onde* onde, absorp* current, absorp* pred){
 /*
   Objectif :
   		+> Indiquer les valeurs de l'onde pour pouvoir facilement faire des mesures dessus
   Entrée :
   		+> onde 		=> l'onde actuelle que l'ont veut définire
   		+> current		=> le point actuel (serviras a trouver les moment pour lequel l'onde 'coupe' l'axe des abisces)
   		+> pred			=> le point précédent (serviras a trouver le moment pour lequel l'onde coupe l'axe des absicces)
   Sortie :
   		+> mise a jour des infos de l'onde
  */
	 if(pred != NULL){
 		// On met a jour la limite maximale de l'onde
 		if(current->acr > onde->Xmax->acr || current->acir > onde->Xmax->acir){
 			onde->Xmax = current;
 		}
 		// On met a jour la limite minimale de l'onde
 		if(current->acr < onde->Xmin->acr || current->acir < onde->Xmin->acir){
 			onde->Xmin = current;
 		}
 		// On trouve le moment de passage a une nouvelle onde au moment ou l'ont 'remonte' donc que la valeur précédente est négative et l'actuelle positive
 		if(current->acr >0 && pred->acr <0){
 			onde->end = current;
 		}
	 }
	 else{
	   onde->start = current;
	   onde->Xmax = current;
	   onde->Xmin = current;
	}
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

	printf("Start:");
	print_absorp(onde->start);

	if(onde->end != NULL){
    	printf("End:");
	    print_absorp(onde->end);
	}

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
  onde->Xmax = NULL;
  onde->Xmin = NULL;
  onde->start = onde->end;
  onde->end = NULL;

}

oxy mesureTest(char* filename){
	oxy myOxy;

	return myOxy;
}