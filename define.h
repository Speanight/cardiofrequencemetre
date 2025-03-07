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


/*! ------------------------------------------------------------
  
  \struct oxy
 
  \brief   
  
  ------------------------------------------------------------*/

typedef struct{
		int spo2;  /*!< SPO2 */
		int pouls;  /*!< Pouls */
	} oxy;


/* Struct circular buffer */
typedef struct {
    int current;
    int size;
    absorp array[50];
} circular_buffer;

/* Struct onde */
typedef struct {
  absorp* Xmax;
  absorp* Xmin;
  int time;
} onde;

#endif // DEFINE_H
