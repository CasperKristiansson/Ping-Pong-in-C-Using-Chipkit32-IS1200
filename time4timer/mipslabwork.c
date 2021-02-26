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

#define TMR2PERIOD ((80000000 / 256) / 10) // 100ms

int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
volatile int* E; 
void labinit( void )
{
  E = (volatile int*)0xbf886100;
  *E &= ~0xff;

  E = (volatile int*) 0xbf886110;
  *E = 0;
  TRISD |= 0x07F0;

	T2CONSET = 0x0070; //Set 1:256 prescaling
	PR2 = TMR2PERIOD;  //Set timeperiod
	TMR2 = 0; //Initialize timer to 0
	T2CONSET = 0x8000; //Start timer by setting bit #15 to 1

  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  //ADDRESS PORTD = 0xbf8860d0
  
  int btns = getbtns();
  int sw = getsw();

  if (btns & 1) {
		mytime = (sw << 4) | (mytime & 0xff0f);
	}
	if (btns & 2) {
		mytime = (sw << 8) | (mytime & 0xf0ff);
	}
	if (btns & 4) {
		mytime = (sw << 12) | (mytime & 0x0fff);
	}

  if (IFS(0) & 0x100) {

		// Reset all event flags.
		IFS(0) = 0;		
		timeoutcount++;

		if (timeoutcount == 10) {

		time2string( textstring, mytime );
		display_string( 3, textstring );
		display_update();
		tick( &mytime );
		display_image(96, icon);
		*E += 0x1;
		timeoutcount = 0;		
		}
	}		


}
