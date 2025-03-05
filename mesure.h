#include "define.h"
#include "fichiers.h"

typedef struct {
  absorp* Xmax;
  absorp* Xmin;
  int time;
} onde;

int maj_onde(onde* onde, absorp* currentIir, absorp* lastIir);

void print_onde(onde* onde);

void calculs(onde* onde, int* spo2, int* bpm);

oxy mesureTest(char* filename);



	
