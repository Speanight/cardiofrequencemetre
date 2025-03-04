//
// Created by OMGiT on 03/03/2025.
//

#include "define.h"
#include "affichage.h"
#include "fir.h"
#include "iir.h"

absorp* generate_absorp(const char *filename, int n) {
  /*
    Objectif     +> générer la structure absorp a partir du numéro de la ligne d'un fichier source
    *filename    +> nom du fichier contenant les données
    n            +> numéro de ligne
   */
  /* Ouverture du fichier et gestion erreur s'il n'apparait pas*/

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur ouverture fichier");
        return NULL;
    }
    /* Allocation de la mémoire pour la structure */
    absorp *data = malloc(sizeof(absorp));
    if (!data) {
        printf("Erreur allocation mémoire");
        fclose(file);
        return NULL;
    }

    char buffer[256];
    int current_line = 0;

    /* Récupération des infos contenues dans la fichier a la bonne ligne*/
    while (fgets(buffer, sizeof(buffer), file)) {
        if (current_line == n) {
            sscanf(buffer, "%f,%f,%f,%f", &data->acr, &data->dcr, &data->acir, &data->dcir);
            fclose(file);
            return data;
        }
        current_line++;
    }

    fclose(file);
    free(data);
    return NULL; // Ligne non trouvée
}

void print_absorp(absorp *absorp) {
  /*
    Objectif :
        +> afficher le absorp
    Entrée :
        +> absorp     =>un absorp
    Sortie :
        +> affichage du absorp
   */
    printf("Absorp :  acr = %.2f, dcr = %.2f, acir = %.2f, dcir = %.2f\n",
        absorp->acr,
        absorp->dcr,
        absorp->acir,
        absorp->dcir
    );
}

circular_buffer* generate_circular_buffer(int size) {
  /*
    Objectif :
        +> créer un buffer
    Entrée :
        +> size  => le nombre d'éléments du buffer (maximum)
    Sortie :
        +> crée un buffer de ka bonne taille et initialise le début a 0
        +> NULL si erreur
*/
//    circular_buffer buffer = {0, size};
    circular_buffer* buffer = malloc(sizeof(circular_buffer));

    buffer->size = size;
    buffer->current = 0;

    return buffer;
}

void add_to_circular_buffer(circular_buffer* cb, absorp* data) {
  /*
    Objectif     +> ajouter dans le buffer une structure absorp
    Entrée :
        +> cb    => circular_buffer
        +> data  => absorp
    Sortie :
        +> ajout de data dans le cb
   */
    if (cb->current == cb->size){
        cb->current = 0;
    }
    cb->array[cb->current] = *data;
    cb->current++;
}

absorp* read_from_circular_buffer(circular_buffer* cb, int index) {
  /*
    Objectif :
        +> lire les données contenues dans le buffer grâce a un index
        +> plus l'index est grand plus il vas chercher dans les données sauvegardé précédement
    Entrée :
        +> cb     => buffer contenant les structure
        +> index  => index qui indique la "profondeur" de la recherche
    Sortie :
        +> absorp* => les datas voulues
        +> NULL    => si erreur index
   */
  if (index >= cb->size-1){
    printf("Erreur : index plus grand que la taille");
    return NULL;
  }

  if(cb->current-index>0){
    return &(cb->array[cb->current - index]);
  }
  else {
    return &(cb->array[cb->size + (cb->current - index)]);
  }
}

void print_buffer(circular_buffer* cb) {
  /*
    Objectif :
        +> afficher le contenu du buffer
    Entrée :
        +> cb     => le Buffer
    Sortie :
        +> affichage ...
   */
  printf("affichage du buffer de size : %d\n",cb->size);
  for (int i = 0; i < cb->size; i++){
    print_absorp(&(cb->array[i]));
  }
}

int main() {
    printf("Conteeeeeent\n");

    char* filename = "assets/FichiersLog/log1/log1.dat";

    circular_buffer* cb_origine = generate_circular_buffer(50);
    absorp* currentFir = NULL;
    absorp* lastFir= NULL;

    absorp* currentIir = NULL;
    absorp* lastIir = NULL;

    for(int i = 0; i < 5000; i++){
        absorp *data = generate_absorp(filename, i);
        add_to_circular_buffer(cb_origine, data);
        currentFir = fir(cb_origine);
        currentIir = iir(lastIir, currentFir, lastFir);
        /* Calcuuuuuuuls */

        /* Envoi des données */

//        free(lastIir);
//        free(lastFir);
        lastIir = currentIir;
        lastFir = currentFir;

    }


//    iirTest("assets/FichiersLog/log2/log2_fir.dat");

    return 0;
}