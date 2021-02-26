/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

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
  
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  *E += 0x1;
  display_image(96, icon);
}
