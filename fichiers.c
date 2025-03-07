#include <stdio.h>
#include "fichiers.h"
#include "define.h"

/**
 * Fonction permettant l'ouverture d'un fichier.
 *
 * @param nomFichier Contient le path vers le fichier.
 * @return Objet "fichier" ouvert.
 */
FILE* initFichier(char* nomFichier ){

    FILE* pf=fopen(nomFichier,"r");
    if(pf==NULL){
        printf("dans fichiers.c : erreur ouverture fichier %s\n",nomFichier);
        exit(EXIT_FAILURE);
    }
    return pf;
}

/**
 * Permet de lire les données d'un fichier sous le format acr,dcr,acir,dcir.
 *
 * @param pf Fichier à lire
 * @param etat Pointeur de int, contenant le return du fscanf.
 * @return Structure absorp contenant les valeurs à la ligne lue.
 */
absorp lireFichier(FILE* pf, int* etat){
    absorp myAbsorp;
    char x,y;
    int a=0,b=0,c=0,d=0;
    *etat=fscanf(pf,"%d,%d,%d,%d",&a,&b,&c,&d);
    myAbsorp.acr=a;
    myAbsorp.dcr=b;
    myAbsorp.acir=c;
    myAbsorp.dcir=d;
    return myAbsorp;
}

/**
 * Ferme un fichier.
 *
 * @param pf Fichier à fermer.
 */
void finFichier(FILE* pf){
    fclose(pf);
}
