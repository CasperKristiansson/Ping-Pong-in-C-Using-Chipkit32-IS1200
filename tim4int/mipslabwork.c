/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog
   This file modified 2021-02-15 by Hampus Nilsson & Casper Kristiansson 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define TMR2PERIOD ((80000000 / 256) / 10) //100 ms


int mytime = 0x5957;
int prime = 1234567;
int timeoutcount = 0;
volatile int *porte = (volatile int *) 0xbf886110;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & 0x00080000){
    
    IFS(0) = 0;
		*(porte)+= 0x1;
  
  }
  if(IFS(0) & 0x100){

    IFS(0) = 0;
    timeoutcount++;

    if(timeoutcount == 10){
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      timeoutcount = 0;
    }
  }
}

/* Lab-specific initialization goes here */
volatile int* E; 
void labinit( void )
{
  E = (volatile int*)0xbf886100;
  *E &= ~0xff;

  E = (volatile int*) 0xbf886110;
  *E = 0;
  TRISD |= 0x07F0; //0xF80F

  T2CONSET = 0x70;
  PR2 = TMR2PERIOD;
  TMR2 = 0;
  T2CONSET = 0x8000;

  
  IPCSET(2) = 6;
  IECSET(0) = 0x100;

  IPCSET(4) = 0x10000000;
  IECSET(0) = 0x00080000;
  //0000   0000 0000  0'0'00 0000 0000 0000 0000
  //32-29 28-25 24-21 20-17
  //0x00040000
  enable_interrupt();

}

/* This function is called repetitively from the main program */
void labwork(void)
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();  
}
