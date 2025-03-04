#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*! ------------------------------------------------------------*/
  
  /*\struct absorp/*/

  /*\brief measures*/

/*! ------------------------------------------------------------*/

typedef struct{
		float acr;  /*!< AC R */
		float dcr;  /*!< DC R */
		float acir;  /*!< AC IR */
		float dcir;  /*!< DC IR */
	} absorp;

absorp* generate_absorp(const char *filename, int n);

void print_absorp(absorp *absorp);


/* Circular Buffer */

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
/*! ------------------------------------------------------------
  
  \struct oxy
 
  \brief   
  
  ------------------------------------------------------------*/

typedef struct{
		int spo2;  /*!< SPO2 */
		int pouls;  /*!< Pouls */
	} oxy;

#endif // DEFINE_H
