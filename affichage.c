#include "affichage.h"
#include "define.h"

void affichage(oxy myOxy){
    char* verrouPath = "assets/IHMPython/.verrouData";
    char* dataPath = "assets/IHMPython/data.txt";

    // On vérifie si .verrouData est présent.
    if (access(verrouPath, F_OK) != -1) {
        // Si oui, on quitte la fonction (on ne peut pas écrire et lire en même temps)
        printf(".verrouData already exists! Not writing in data.txt...\n");
        return;
    }
    FILE* verrou;
    // Sinon, on crée le fichier pour éviter la lecture côté front.
    verrou = fopen(verrouPath, "w");

    // Puis on ouvre le fichier data.txt
    FILE *data;
    data = fopen(dataPath, "w");

    // On écrit dans le fichier (les anciennes données seront supprimées si besoin)
    fprintf(data, "%d\n%d", myOxy.spo2, myOxy.pouls);

    // On supprime le verrou pour autoriser la lecture des données.
    fclose(data);
    remove(verrouPath);
}

