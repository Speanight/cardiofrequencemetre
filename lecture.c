#include "lecture.h"
#include <stdio.h>
#include <math.h>

absorp* create_absorp_from_bits(char* bits){
    /*
    Objectif :
        +> créer un absorp a partir des données de sorties du GPIO
    Entrée :
        +> Les données qui sortent du GPIO sous forme d'un string
    Sortie :
        +> un absorp
     */

    absorp* absorp = malloc(sizeof(absorp));
    /*
     ACR => 4octets (4*8 = 32 bits)
     virgule => 1octet (8bits)
     DCR => 4octets (4*8 = 32 bits)
     virgule => 1octet (8bits)
     ACiR => 4octets (4*8 = 32 bits)
     virgule => 1octet (8bits)
     DCiR => 4octets (4*8 = 32 bits)

     LF => 1 octet (8 bits)
     CR => 1 octet (8bits)

     total lengt bits = 680 bits
     */
    char ACR[33],
        vir1[9],
        DCR[33],
        vir2[9],
        ACiR[33],
        vir3[9],
        DCiR[33];

    // On découpe chaques moceaux qui nous intéresse en sortie
    sscanf(bits, "%32s%8s%32s%8s%32s%8s%32s", ACR,vir1, DCR, vir2, ACiR, vir3,DCiR);

    // vérification des négatifs
    int acr_conf = 1;
    int dcr_conf = 1;
    int acir_conf =1;
    int dcir_conf =1;

    if(ACR[0]%48==1){ //Le %48 permet de trasformer le '1' en 1 grâce a la table ascii
      acr_conf = -1;
    }
    if(DCR[0]%48==1){
        dcr_conf = -1;
    }
    if(ACiR[0]%48==1){
        acir_conf = -1;
    }
    if(DCiR[0]%48==1){
        dcir_conf = -1;
    }

    float acrtemp, dcrtemp, acirtemp, dcirtemp = 0;
    float currentPow;

    // On boucle pour convertir en décimal
    for(int i=31;i>1;i--){
      currentPow = pow(2,31-i);

      acrtemp  += (ACR[i]%48)*currentPow*acr_conf;
      dcrtemp  += (DCR[i]%48)*currentPow*dcr_conf;
      acirtemp += (ACiR[i]%48)*currentPow*acir_conf;
      dcirtemp += (DCiR[i]%48)*currentPow*dcir_conf;

//      printf("curretnPow => %f, currentI => %d\n", currentPow, i);
//      printf("ACR[i] => %d, acr => %f\n",ACR[i]%48, acrtemp);
//      printf("DCR[i] => %d, dcr => %f\n",DCR[i]%48, dcrtemp);
//      printf("ACiR[i] => %d, acr => %f\n",ACiR[i]%48, acirtemp);
//      printf("DCiR[i] => %d, dcr => %f\n",DCiR[i]%48, dcirtemp);
//      printf("----------->>>>>\n");
    }

    // On ajoute dans le absorp
    absorp->acr  = acrtemp;
    absorp->dcr  = dcrtemp;
    absorp->acir = acirtemp;
    absorp->dcir = dcirtemp;

//    print_absorp(absorp);

    return absorp;


}