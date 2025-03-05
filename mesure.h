#include "define.h"
#include "fichiers.h"

typedef struct {
  absorp* Xmax;
  absorp* Xmin;
  int time;
} onde;

void maj_onde(onde* onde, absorp* current, absorp* pred);

void print_onde(onde* onde);

int calcul_SPO2(float ratio);

void calculs(onde* onde, int* spo2, int* bpm);

oxy mesureTest(char* filename);



	
