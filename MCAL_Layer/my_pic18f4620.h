/* 
 * File:   my_pic18f4620.h
 * Author: Mohamed Osama
 *
 * Created on August 15, 2023, 2:42 PM
 */

#ifndef MY_PIC18F4620_H
#define	MY_PIC18F4620_H
/* Platform Abstraction */
#define PLATFORM REG8
#if PLATFORM == REG8
    /* 8-bit register access method*/
    #define HWREG(_x) (*((volatile uint8*)(_x)))
#elif PLATFORM == REG16
     /* 16-bit register access method*/
    #define HWREG(_x) (*((volatile uint16 *)(_x)))
#elif PLATFORM == REG32
     /* 32-bit register access method*/
    #define HWREG(_x) (*((volatile uint32 *)(_x)))
#else
    #error "platform is not supported"
#endif 
/***************Register Definitions************************/
#define LATA_ADD 0xF89
#define LATA HWREG(LATA_ADD)
#define LATB_ADD 0xF8A
#define LATB HWREG(LATB_ADD)
#define LATC_ADD 0xF8B
#define LATC HWREG(LATC_ADD)
#define LATD_ADD 0xF8C
#define LATD HWREG(LATD_ADD)
#define LATE_ADD 0xF8D
#define LATE HWREG(LATE_ADD)

#define TRISA_ADD 0xF92
#define TRISA HWREG(TRISA_ADD)
#define TRISB_ADD 0xF93
#define TRISB HWREG(TRISB_ADD)
#define TRISC_ADD 0xF94
#define TRISC HWREG(TRISC_ADD)
#define TRISD_ADD 0xF95
#define TRISD HWREG(TRISD_ADD)
#define TRISE_ADD 0xF96
#define TRISE HWREG(TRISE_ADD)

#define PORTA_ADD 0xF80
#define PORTA HWREG(PORTA_ADD)
#define PORTB_ADD 0xF81
#define PORTB HWREG(PORTB_ADD)
#define PORTC_ADD 0xF82
#define PORTC HWREG(PORTC_ADD)
#define PORTD_ADD 0xF83
#define PORTD HWREG(PORTD_ADD)
#define PORTE_ADD 0xF84
#define PORTE HWREG(PORTE_ADD)

/* Bit Positions */
#define RA0 0
#define RA1 1
#define RA2 2
#define RA3 3
#define RA4 4
#define RA5 5
#define RA6 6
#define RA7 7

#define RB0 0
#define RB1 1
#define RB2 2
#define RB3 3
#define RB4 4
#define RB5 5
#define RB6 6
#define RB7 7

#define RC0 0
#define RC1 1
#define RC2 2
#define RC3 3
#define RC4 4
#define RC5 5
#define RC6 6
#define RC7 7

#define RD0 0
#define RD1 1
#define RD2 2
#define RD3 3
#define RD4 4
#define RD5 5
#define RD6 6
#define RD7 7

#define RE0 0
#define RE1 1
#define RE2 2

/**********************INTERRUPT REGISTERS*********************/

typedef union {
  struct {  
   uint8 RBIF   :1;
   uint8 INT0IF :1;
   uint8 TMR0IF :1;
   uint8 RBIE   :1;
   uint8 INT0IE :1;
   uint8 TMR0IE :1;
   uint8 PEIE :1;
   uint8 GIE :1; 
};
  struct {
   uint8      :6;
   uint8 GIEL :1;
   uint8 GIEH :1; 
};
}INTCON_t;

#define INTCON_bits (*((volatile INTCON_t *)(0xFF2)))
#define INTCON (*((volatile uint8 *)(0xFF2)))

typedef struct {
   uint8 RBIP   :1;
   uint8        :1;
   uint8 TMR0IP:1;
   uint8        :1;
   uint8 INTEDG2 :1;
   uint8 INTEDG1:1;
   uint8 INTEDG0 :1;
   uint8 RBPU :1;         
}INTCON2_t;
  
#define INTCON2_bits (*((volatile INTCON2_t *)(0xFF1)))
#define INTCON2 (*((volatile uint8 *)(0xFF1)))

typedef struct {
   uint8 INT1IF :1;
   uint8 INT2IF :1;
   uint8        :1;
   uint8 INT1IE  :1;
   uint8 INT2IE :1;
   uint8        :1;
   uint8 INT1IP :1;
   uint8 INT2IP :1;        
}INTCON3_t;
  
#define INTCON3_bits (*((volatile INTCON3_t *)(0xFF0)))
#define INTCON3 (*((volatile uint8 *)(0xFF0)))

typedef struct {
  uint8  TMR1IF :1;
  uint8  TMR2IF :1;
  uint8  CCP1IF :1;
  uint8  SSPIF :1;
  uint8  TXIF  :1;
  uint8  RCIF  :1;
  uint8  ADIF  :1;
  uint8  PSPIF :1;
}PIR1_t;
  
#define PIR1_bits (*((volatile PIR1_t *)(0xF9E)))
#define PIR1 (*((volatile uint8 *)(0xF9E)))

typedef struct {
  uint8  CCP2IF :1;
  uint8  TMR3IF :1;
  uint8  HLVDIF :1;
  uint8  BCLIF :1;
  uint8  EEIF  :1;
  uint8        :1;
  uint8  CMIF  :1;
  uint8  OSCFIF :1;  
}PIR2_t;
  
#define PIR2_bits (*((volatile PIR2_t *)(0xFA1)))
#define PIR2 (*((volatile uint8 *)(0xFA1)))


typedef struct {
  uint8  TMR1IE :1;
  uint8  TMR2IE :1;
  uint8  CCP1IE :1;
  uint8  SSPIE :1;
  uint8  TXIE  :1;
  uint8  RCIE  :1;
  uint8  ADIE  :1;
  uint8  PSPIE :1;
}PIE1_t;
  
#define PIE1_bits (*((volatile PIE1_t *)(0xF9D)))
#define PIE1 (*((volatile uint8 *)(0xF9D)))

typedef struct {
  uint8  CCP2IE :1;
  uint8  TMR3IE :1;
  uint8  HLVDIE :1;
  uint8  BCLIE  :1;
  uint8  EEIE   :1;
  uint8         :1;
  uint8  CMIE   :1;
  uint8  OSCFIE :1;
}PIE2_t;
  
#define PIE2_bits (*((volatile PIE2_t *)(0xFA0)))
#define PIE2 (*((volatile uint8 *)(0xFA0)))

typedef struct {
  uint8  TMR1IP :1;
  uint8  TMR2IP :1;
  uint8  CCP1IP :1;
  uint8  SSPIP  :1;
  uint8  TXIP  :1;
  uint8  RCIP  :1;
  uint8  ADIP  :1;
  uint8  PSPIP :1; 
}IPR1_t;
  
#define IPR1_bits (*((volatile IPR1_t *)(0xF9F)))
#define IPR1 (*((volatile uint8 *)(0xF9F)))

typedef struct {
  uint8  CCP2IP :1;
  uint8  TMR3IP :1;
  uint8  HLVDIP :1;
  uint8  BCLIP  :1;
  uint8  EEIP   :1;
  uint8         :1;
  uint8  CMIP   :1;
  uint8  OSCFIP :1; 
}IPR2_t;
  
#define IPR2_bits (*((volatile IPR2_t *)(0xFA2)))
#define IPR2 (*((volatile uint8 *)(0xFA2)))

typedef struct {
  uint8  BOR :1;
  uint8  POR :1;
  uint8  PD  :1;
  uint8  TO  :1;
  uint8  RI  :1;
  uint8      :1;
  uint8  SBOREN    :1;
  uint8  IPEN :1; 
}RCON_t;
  
#define RCON_bits (*((volatile RCON_t *)(0xFD0)))
#define RCON (*((volatile uint8 *)(0xFD0)))

/**********************************************/
/*EEPROM Registers*/
#define EEDATA (*((volatile uint8 *)(0xFA8)))
#define EEADR (*((volatile uint8 *)(0xFA9)))
#define EEADRH (*((volatile uint8 *)(0xFAA)))
#define EECON2 (*((volatile uint8 *)(0xFA7)))
#define EECON1 (*((volatile uint8 *)(0xFA6)))

typedef struct {
  uint8  RD :1;
  uint8  WR  :1;
  uint8  WREN  :1;
  uint8  WRERR :1;
  uint8  FREE :1;
  uint8       :1;
  uint8  CFGS    :1;
  uint8  EEPGD    :1; 
}EECON1_t;

#define EECON1_bits (*((volatile EECON1_t *)(0xFA6)))

/********************ADC Registers************************/
typedef union {
  struct {  
   uint8 ADON   :1;
   uint8 GO_DONE :1;
   uint8 CHS0 :1;
   uint8 CHS1   :1;
   uint8 CHS2 :1;
   uint8 CHS3 :1;
   uint8      :1;
   uint8      :1; 
};
  struct {
   uint8      :2;
   uint8 CHS  :4;
   uint8      :2; 
};
}ADCON0_t;

#define ADCON0_bits (*((volatile ADCON0_t *)(0xFC2)))
#define ADCON0 (*((volatile uint8 *)(0xFC2)))

typedef union {
  struct {  
   uint8 PCFG0   :1;
   uint8 PCFG1 :1;
   uint8 PCFG2 :1;
   uint8 PCFG3   :1;
   uint8 VCFG0 :1;
   uint8 VCFG1 :1;
   uint8      :1;
   uint8      :1; 
};
  struct {
   uint8 PCFG  :4;
   uint8 VCFG  :2;
   uint8       :2;  
};
}ADCON1_t;

#define ADCON1_bits (*((volatile ADCON1_t *)(0xFC1)))
#define ADCON1 (*((volatile uint8 *)(0xFC1)))

typedef union {
  struct {  
   uint8 ADCS0   :1;
   uint8 ADCS1  :1;
   uint8 ADCS2  :1;
   uint8 ACQT0   :1;
   uint8 ACQT1 :1;
   uint8 ACQT2 :1;
   uint8       :1;
   uint8 ADFM   :1; 
};
  struct {
   uint8 ADCS  :3;
   uint8 ACQT  :3;
   uint8       :1;  
   uint8       :1;
};
}ADCON2_t;

#define ADCON2_bits (*((volatile ADCON2_t *)(0xFC0)))
#define ADCON2 (*((volatile uint8 *)(0xFC0)))

/********************************************/
/* Timer0 Registers*/

typedef union {
  struct {  
   uint8 T0PS0   :1;
   uint8 T0PS1 :1;
   uint8 T0PS2 :1;
   uint8 PSA   :1;
   uint8 T0SE :1;
   uint8 T0CS :1;
   uint8 T08BIT :1;
   uint8 TMR0ON :1; 
};
  struct {
   uint8 T0PS  :3;
   uint8       :5;  
};
}T0CON_t;

#define T0CON_bits (*((volatile T0CON_t *)(0xFD5)))
#define T0CON (*((volatile uint8 *)(0xFD5)))
#define TMR0L (*((volatile uint8 *)(0xFD6)))
#define TMROH (*((volatile uint8 *)(0xFD7)))

/* Timer1 Registers*/

typedef union {
  struct {  
   uint8 TMR1ON  :1; 
   uint8 TMR1CS  :1;
   uint8 T1SYNC  :1;
   uint8 T1OSCEN :1;
   uint8 T1CKPS0 :1;
   uint8 T1CKPS1 :1;
   uint8 T1RUN   :1;
   uint8 RD16    :1;
};
  struct {
   uint8         :4;
   uint8 T1CKPS  :2;
   uint8         :2;
};
}T1CON_t;

#define T1CON_bits (*((volatile T1CON_t *)(0xFCD)))
#define T1CON (*((volatile uint8 *)(0xFCD)))
#define TMR1L (*((volatile uint8 *)(0xFCE)))
#define TMR1H (*((volatile uint8 *)(0xFCF)))

/* Timer2 Registers*/

typedef union {
  struct {  
   uint8 T2CKPS0   :1; 
   uint8 T2CKPS1   :1;
   uint8 TMR2ON    :1;
   uint8 T2OUTPS0  :1;
   uint8 T2OUTPS1  :1;
   uint8 T2OUTPS2  :1;
   uint8 T2OUTPS3  :1;
   uint8           :1;
};
  struct {
   uint8 T2CKPS  :2;
   uint8         :1;
   uint8 T2OUTPS :4;
   uint8         :1;    
};
}T2CON_t;

#define T2CON_bits (*((volatile T2CON_t *)(0xFCA)))
#define T2CON (*((volatile uint8 *)(0xFCA)))
#define TMR2 (*((volatile uint8 *)(0xFCC)))
#define PR2 (*((volatile uint8 *)(0xFCB)))
/* Timer3 Registers*/

typedef union {
  struct {  
   uint8 TMR3ON  :1; 
   uint8 TMR3CS  :1;
   uint8 T3SYNC  :1;
   uint8 T3CCP1 :1;
   uint8 T3CKPS0 :1;
   uint8 T3CKPS1 :1;
   uint8 T3CCP2   :1;
   uint8 RD16    :1;
};
  struct {
   uint8         :4;
   uint8 T3CKPS  :2;
   uint8         :2;
};
}T3CON_t;

#define T3CON_bits (*((volatile T3CON_t *)(0xFB1)))
#define T3CON (*((volatile uint8 *)(0xFB1)))
#define TMR3L (*((volatile uint8 *)(0xFB2)))
#define TMR3H (*((volatile uint8 *)(0xFB3)))
/***************************************/
/* CCPx Module Registers */
typedef union {
  struct {  
   uint8 CCP1M0  :1; 
   uint8 CCP1M1  :1;
   uint8 CCP1M2  :1;
   uint8 CCP1M3  :1;
   uint8 DC1B0   :1;
   uint8 DC1B1   :1;
   uint8         :1;
   uint8         :1;
};
  struct {
   uint8 CCP1M   :4;
   uint8 DC1B    :2;
   uint8         :2;
};
}CCP1CON_t;

#define CCP1CON_bits (*((volatile CCP1CON_t *)(0xFBD)))
#define CCP1CON (*( (volatile uint8 *)(0xFBD) ) )
#define CCPR1L (*( (volatile uint8 *)(0xFBE) ) )
#define CCPR1H (*( (volatile uint8 *)(0xFBF) ) )

typedef union {
  struct {  
   uint8 CCP2M0  :1; 
   uint8 CCP2M1  :1;
   uint8 CCP2M2  :1;
   uint8 CCP2M3  :1;
   uint8 DC2B0   :1;
   uint8 DC2B1   :1;
   uint8         :1;
   uint8         :1;
};
  struct {
   uint8 CCP2M   :4;
   uint8 DC2B    :2;
   uint8         :2;
};
}CCP2CON_t;

#define CCP2CON_bits (*((volatile CCP2CON_t *)(0xFBA)))
#define CCP2CON (*( (volatile uint8 *)(0xFBA) ) )
#define CCPR2L (*( (volatile uint8 *)(0xFBB) ) )
#define CCPR2H (*( (volatile uint8 *)(0xFBC) ) )

/*****************************************************/


#endif	/* MY_PIC18F4620_H */

