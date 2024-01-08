/* 
 * File:   ccp1_cfg.h
 * Author: Mohamed Osama
 *
 * Created on January 3, 2024, 6:14 PM
 */

#ifndef CCP1_CFG_H
#define	CCP1_CFG_H

/* Section : Includes */
#include"../../Pulse_Meter_CFG.h"
/* Section : Macros Declaration */

#define CCP_CFG_CAPTURE_MODE_SELECTED 0x00
#define CCP_CFG_COMPARE_MODE_SELECTED 0x01
#define CCP_CFG_PWM_MODE_SELECTED     0x02

#define CCP1_CFG_SELECTED_MODE  (CCP_CFG_CAPTURE_MODE_SELECTED)

#if (FREQUENCY_GENERATED_BY == CCP2_COMPARE_MODE)
#define CCP2_CFG_SELECTED_MODE  (CCP_CFG_COMPARE_MODE_SELECTED)
#endif

#if (FREQUENCY_GENERATED_BY == CCP2_PWM_MODE)
#define CCP2_CFG_SELECTED_MODE  (CCP_CFG_PWM_MODE_SELECTED)
#endif


/* Section : Macro Functions Declaration */


/* Section : Data Types Declaration */


/* Section : Functions Declaration */

#endif	/* CCP1_CFG_H */

