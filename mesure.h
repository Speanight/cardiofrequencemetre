#include "define.h"
#include "fichiers.h"

typedef struct {
  absorp* Xmax;
  absorp* Xmin;
  int time;
} onde;

int maj_onde(onde* onde, absorp* currentIir, absorp* lastIir);

void print_onde(onde* onde);

int calcul_SPO2(float ratio);

void calculs(onde* onde, oxy* myOxy);

oxy mesureTest(char* filename);



	
