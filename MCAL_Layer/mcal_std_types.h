/* 
 * File:   mcal_std_types.h
 * Author: mohop
 *
 * Created on August 15, 2023, 1:21 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */
#include "std_libraries.h"
#include "compiler.h" 
/* Section : Data Types Declaration */
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long sint32;

typedef uint8 Std_ReturnType;


/* Section : Macros Declaration */
#define STD_HIGH 0x01
#define STD_LOW  0x00

#define STD_ON 0x01
#define STD_OFF 0x00

#define STD_ACTIVE 0x01
#define STD_IDLE 0x00


#define E_OK (Std_ReturnType)0x01
#define E_NOT_OK (Std_ReturnType)0x00

#define ZERO_INIT 0

/* Section : Macro Functions Declaration */




/* Section : Functions Declaration */

#endif	/* MCAL_STD_TYPES_H */

