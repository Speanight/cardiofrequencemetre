#include "define.h"
/**
 * Permet de générer la structure absorp à partir du numéro de la ligne d'un fichier source.
 *
 * @param filename Path du fichier contenant les données
 * @param n Numéro de ligne à lire
 * @return Pointeur d'une structure absorp, contenant les valeurs lues selon les paramètres passés. Valeur à free !
 */
absorp* generate_absorp(const char *filename, int n) {
    // Ouverture du fichier.
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur ouverture fichier");
        return NULL;
    }

    // Allocation de la mémoire pour la structure
    absorp *data = malloc(sizeof(absorp));
    if (!data) {
        printf("Erreur allocation mémoire");
        fclose(file);
        return NULL;
    }

    char buffer[256];
    int current_line = 0;

    // Récupération des infos contenues dans la fichier a la bonne ligne
    while (fgets(buffer, sizeof(buffer), file)) {
        // Si on est à la bonne ligne...
        if (current_line == n) {
            // Alors on récupère les données et on les place dans les valeurs de data.
            sscanf(buffer, "%f,%f,%f,%f", &data->acr, &data->dcr, &data->acir, &data->dcir);
            fclose(file);
            // Puis on return data.
            return data;
        }
        current_line++;
    }

    // Sinon, on free le tout et on renvoie null.
    fclose(file);
    return NULL;
}

/**
 * Permet d'afficher absorp dans la console pour des raisons de débuggage.
 *
 * @param absorp Abosrp à lire.
 */
void print_absorp(absorp *absorp) {
    printf("Absorp :  acr = %.2f, dcr = %.2f, acir = %.2f, dcir = %.2f\n",
        absorp->acr,
        absorp->dcr,
        absorp->acir,
        absorp->dcir
    );
}

/* =========================Circular Buffer========================= */
/**
 * Permet de créer un buffer circulaire de la taille spécifiée (doit être inférieure à 50 en accord avec la structure !)
 *
 * @param size Taille du buffer à créer.
 * @return Buffer généré. Renvoie NULL en cas d'erreur. Besoin de free la valeur !
 */
circular_buffer* generate_circular_buffer(int size) {
    circular_buffer* buffer = malloc(sizeof(circular_buffer));

    buffer->size = size;
    buffer->current = 0;

    return buffer;
}

/**
 * Permet d'ajouter une structure absorp à la bonne place dans un buffer circulaire.
 *
 * @param cb Pointeur au buffer dans lequel ajouter la valeur
 * @param data Valeur à ajouter.
 */
void add_to_circular_buffer(circular_buffer* cb, absorp* data) {
    // Si on est à la fin du buffer...
    if (cb->current == cb->size){
        // ALors on revient au début pour boucler.
        cb->current = 0;
    }
    // Ensuite, on ajoute la valeur dans le buffer.
    cb->array[cb->current] = *data;
    cb->current++;
}

/**
 * Permet de lire les données contenues dans un buffer à un index spécifié. Plus l'index est grand, plus on cherchera
 * une valeur ancienne. (On ne prend pas en compte la modification de l'index dynamique, mais seulement la position
 * relative avec la "tête" de la structure)
 *
 * @param cb Buffer circulaire à observer.
 * @param index Index à regarder.
 * @return Renvoie un pointeur à l'absorp obtenu, NULL en cas d'erreur d'index.
 */
absorp* read_from_circular_buffer(circular_buffer* cb, int index) {
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

/**
 * Permet d'afficher le contenu d'un buffer dans la console pour du débuggage.
 *
 * @param cb Buffer à lir .
 */
void print_buffer(circular_buffer* cb) {
  printf("affichage du buffer de size : %d\n",cb->size);
  for (int i = 0; i < cb->size; i++){
    print_absorp(&(cb->array[i]));
  }
}
