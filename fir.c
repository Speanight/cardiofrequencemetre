#include "fir.h"
#include "define.h"
#include "mesure.h"
#include <stdio.h>

float FIR_TAPS[51]={
        1.4774946e-019,
        1.6465231e-004,
        3.8503956e-004,
        7.0848037e-004,
        1.1840522e-003,
        1.8598621e-003,
        2.7802151e-003,
        3.9828263e-003,
        5.4962252e-003,
        7.3374938e-003,
        9.5104679e-003,
        1.2004510e-002,
        1.4793934e-002,
        1.7838135e-002,
        2.1082435e-002,
        2.4459630e-002,
        2.7892178e-002,
        3.1294938e-002,
        3.4578348e-002,
        3.7651889e-002,
        4.0427695e-002,
        4.2824111e-002,
        4.4769071e-002,
        4.6203098e-002,
        4.7081811e-002,
        4.7377805e-002,
        4.7081811e-002,
        4.6203098e-002,
        4.4769071e-002,
        4.2824111e-002,
        4.0427695e-002,
        3.7651889e-002,
        3.4578348e-002,
        3.1294938e-002,
        2.7892178e-002,
        2.4459630e-002,
        2.1082435e-002,
        1.7838135e-002,
        1.4793934e-002,
        1.2004510e-002,
        9.5104679e-003,
        7.3374938e-003,
        5.4962252e-003,
        3.9828263e-003,
        2.7802151e-003,
        1.8598621e-003,
        1.1840522e-003,
        7.0848037e-004,
        3.8503956e-004,
        1.6465231e-004,
        1.4774946e-019
};


/**
 * Permet le test de l'application du filtre fir : celui-ci a pour objectif d'éliminer les hautes fréquences grâce au
 * tableau de float FIR_TAPS. Le filtre est appliqué sur l'ensemble du fichier, avant de retourner la dernière valeur.
 *
 * @param filename Contient le path vers le fichier à ouvrir.
 * @return Renvoie la dernière donnée récupérée dans le fichier après application du filtre dans une structure absorp.
 */
absorp firTest(char* filename){
  /*
	Filtre toutes les données du fichier associé et renvoie la dernière valeur filtrée
	*/
	absorp myAbsorp;

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur ouverture fichier (firTest)\n");
        return myAbsorp;
    }

    int current_line = 0;
    char fBuffer[256];
    circular_buffer* buffer = malloc(sizeof(circular_buffer));
    buffer->size = 50;
    buffer->current = 0;

    absorp* data = malloc(sizeof(data));

    while (fgets(fBuffer, sizeof(fBuffer), file)) {
        sscanf(fBuffer, "%f,%f,%f,%f", &data->acr, &data->dcr, &data->acir, &data->dcir);
        add_to_circular_buffer(buffer,data);
        current_line++;

        absorp* valAbsorp = fir(buffer);
        myAbsorp = *valAbsorp;
        // Pour satisfaire valgrind et les fuites de mémoire :
        free(valAbsorp);
    }

    myAbsorp = *fir(buffer);

    free(data);
    free(buffer);
    fclose(file);

	return myAbsorp;
}

/**
 * Permet l'exécution du filtre fir avec les valeurs données dans la constante FIR_TAPS en ajoutant les valeurs jusqu'à
 * obtention du résultat final, stocké dans une variable "data" qui est un pointeur de la structure absorp.
 *
 * @param buffer Buffer circulaire vide, endroit où seront stockés les valeurs de manière cyclique.
 * @return Valeur finale après application du filtre, stocké dans un pointeur d'absorp. Besoin de free cette valeur !
 */
absorp* fir(circular_buffer* buffer) {
    // Initialisation d'une valeur absorp.
    absorp* data = malloc(sizeof(absorp));

    // On récupère le dernier élément...
    int lastElem = buffer->current - 1;
    if (lastElem == -1) { // Si c'était le premier, alors on prend le dernier.
        lastElem = buffer->size - 1;
    }

    data->acir = 0;
    data->acr = 0;
    // dcir et dcr n'étant pas modifiées, elles sont donc égales à la dernière valeur.
    data->dcir = buffer->array[lastElem].dcir;
    data->dcr = buffer->array[lastElem].dcr;

    // Boucle ("intégrale" du calcul)
    for (int i = 0; i < buffer->size; i++) {
        // Ajout de chacune des valeurs (via boucle for) à acir et acr de data.
        data->acir += FIR_TAPS[50-i] * buffer->array[(lastElem+i)%buffer->size].acir;
        data->acr += FIR_TAPS[50-i] * buffer->array[(lastElem+i)%buffer->size].acr;
    }

    return data;
}

