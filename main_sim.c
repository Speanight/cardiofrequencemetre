//
// Created by OMGiT on 03/03/2025.
//

#include "define.h"

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
    absorp *data = (absorp*)malloc(sizeof(absorp));
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

circular_buffer* generate_circular_buffer(int size){
  /*
    Objectif :
        +> créer un buffer
    Entrée :
        +> size  => le nombre d'éléments du buffer (maximum)
    Sortie :
        +> crée un buffer de ka bonne taille et initialise le début a 0
        +> NULL si erreur
*/
    circular_buffer *buffer = (circular_buffer*)malloc(sizeof(circular_buffer));
    if (!buffer) {
        printf("Erreur allocation mémoire");
        return NULL;
    }

    buffer->array = malloc(size * sizeof(absorp*));
    buffer->size = size;
    buffer->current = 0;
    return buffer;
}

void add_to_circular_buffer(circular_buffer* cb, absorp* data){
  /*
    Objectif     +> ajouter dans le buffer une structure absorp
    Entrée :
        +> cb    => circular_buffer
        +> data  => absorp
    Sortie :
        +> ajout de data dans le cb
   */
  cb->current++;
  if (cb->current == cb->size){
    cb->current = 0;
  }
  cb->array[cb->current] = data;
}

absorp* read_from_circular_buffer(circular_buffer* cb, int index){
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
    return cb->array[cb->current - index]
  }
  else {
    return cb->array[cb->size + (cb->current - index)];
  }
}

int main() {
    printf("Conteeeeeent\n");
    int ligne = 2; // Exemple : lire la ligne 2
    absorp *data = generate_absorp("assets/Fichiers log/log1/log1.dat", ligne);

    if (data) {
        printf("Ligne %d : acr = %.2f, dcr = %.2f, acir = %.2f, dcir = %.2f\n",
               ligne, data->acr, data->dcr, data->acir, data->dcir);
        free(data);
    } else {
        printf("Erreur : impossible de générer la structure absorp\n");
    }

    return 0;
}