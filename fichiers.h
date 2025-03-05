#ifndef FICHIERS_H
#define FICHIERS_H
#include <stdio.h>
#include <stdlib.h>
#include "define.h"

FILE* initFichier(char* nomFichier );
absorp lireFichier(FILE* pf, int* etat);
void finFichier(FILE* pf);

absorp* generate_absorp(const char *filename, int n);
void print_absorp(absorp *absorp);

/* =========================Circular Buffer========================= */

typedef struct {
    int current;
    int size;
    absorp array[50];
} circular_buffer;

circular_buffer* generate_circular_buffer(int size);
void init_buffer(circular_buffer *cb);
void add_to_circular_buffer(circular_buffer* cb, absorp* data);
absorp* read_from_circular_buffer(circular_buffer* cb, int index);
void print_buffer(circular_buffer* cb);

#endif

