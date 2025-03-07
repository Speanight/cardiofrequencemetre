#include <stdio.h>
#include <stdlib.h>
#include <ftd2xx.h>
#include <unistd.h>
#include "define.h"
#include "lecture.h"
#include "affichage.h"
#include "mesure.h"
#include "iir.h"
#include "fir.h"


#define TRAME_SIZE 21

//fonction pour lire une trame et extraire les valeurs
absorp* lecture(FT_HANDLE ftHandle) {
    FT_STATUS status;
    unsigned char buffer[TRAME_SIZE];
    DWORD bytesRead = 0;
    absorp* data = malloc(sizeof(absorp));
    data->acir = 0;
    data->acr = 0;
    data->dcir = 0;
    data->dcr = 0;

    //lit la trame complète
    status = FT_Read(ftHandle, buffer, TRAME_SIZE, &bytesRead);
    if (status != FT_OK || bytesRead != TRAME_SIZE) {
        printf("Erreur de lecture USB ou manque de valeurs dans trame !\n");
        return data;
    }

    // Afficher les données lues en hexadécimal
    for (int i = 0; i < bytesRead; i++) {
        printf("%X ", buffer[i]);
    }
    printf("\n");

    return data;
}

int main() {
    FT_STATUS status;
    FT_HANDLE handle;

    // Connexion au périphérique FTDI
    status = FT_Open(0, &handle);
    if (status != FT_OK) {
        printf("Impossible d'ouvrir le périphérique FTDI.\n");
        return 1;
    }
    else {
        printf("Périphérique ouvert ! \n");


        FT_STATUS ftStatus;
        FT_DEVICE_LIST_INFO_NODE *devInfo;
        DWORD numDevs;
        // create the device information list
        ftStatus = FT_CreateDeviceInfoList(&numDevs);
        if (ftStatus == FT_OK) {
            printf("Number of devices is %d\n",numDevs);
        }
        if (numDevs > 0) {
            // allocate storage for list based on numDevs
            devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
            // get the device information list
            ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
            if (ftStatus == FT_OK) {
                for (int i = 0; i < numDevs; i++) {
                    printf("Dev %d:\n",i);
                    printf(" Flags=0x%x\n",devInfo[i].Flags);
                    printf(" Type=0x%x\n",devInfo[i].Type);
                    printf(" ID=0x%x\n",devInfo[i].ID);
                    printf(" LocId=0x%x\n",devInfo[i].LocId);
                    printf(" SerialNumber=%s\n",devInfo[i].SerialNumber);
                    printf(" Description=%s\n\n",devInfo[i].Description);
                }
            }
        }
    }

//    // Configuration de la liaison série
//    FT_SetBaudRate(handle, 9600);
//    FT_SetDataCharacteristics(handle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
//    FT_SetFlowControl(handle, FT_FLOW_NONE, 0, 0);


    circular_buffer* cb_origine = generate_circular_buffer(50);

    // Initialisation
    absorp* currentFir = malloc(sizeof(absorp));
    absorp* lastFir= malloc(sizeof(absorp));

    absorp* currentIir = malloc(sizeof(absorp));
    absorp* lastIir = malloc(sizeof(absorp));
    onde* onde = malloc(sizeof(onde));
    oxy* myOxy = malloc(sizeof(oxy));

    int firstRead = 0;

    while (1) {
        absorp* mesure = lecture(handle);
        //Conversion directement dans le printf pour afficher en entier
//        printf("ACR: %.0f | DCR: %.0f | ACIR: %.0f | DCIR: %.0f\n", mesure->acr, mesure->dcr, mesure->acir, mesure->dcir);
        // Extraction
        add_to_circular_buffer(cb_origine, mesure);

        // Filtrage
        currentFir = fir(cb_origine);
        currentIir = iir(lastIir, currentFir, lastFir);

        // Cas du premier élément
        if(firstRead == 0) {
            onde->time = 0;
            onde->Xmax = currentIir;
            onde->Xmin = currentIir;
            firstRead = 1;
        }
        else {
//            print_absorp(lastFir);
            if (maj_onde(onde, currentIir, lastIir) == 1) {
                // Calculs
//                printf("MAJ ONDE!");
//                calculs(onde, myOxy);
//                affichage(*myOxy);

                // Remise à zéro.
                onde->time = 0;
                onde->Xmin = currentIir;
                onde->Xmax = currentIir;
            }
        }
        free(lastIir);
        free(lastFir);

        lastIir = currentIir;
        lastFir = currentFir;

        usleep(2000);
    }

    FT_Close(handle);
    return 0;
}