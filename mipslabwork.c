/* mipslabwork.c
   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):
   This file modified 2017-04-31 by Ture Teknolog 
   Thias file modified 2021-03-02 by Casper Kristiansson and Hampus Nilsson
   For copyright and licensing, see file COPYING */

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t display[32][128];
uint8_t oled_display[512];
int initial_active = 0;

/* Debugging paddle_splits
int i = 0;
int j = 0;
int k = 0;
int m = 0;
Debugging paddle_splits */

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int *trise = (volatile int *)0xbf886100;
  TRISECLR = 0xff;  // Set as output (LED:S)
  TRISDSET = 0xfe0; // Set as input (BTN 2-4, SW 1-4)
  TRISFSET = 0x2;   // Set as input (BTN 1)
  PORTE = 0x0;      // LED:s
}

/* This function is called repetitively from the main program */
void labwork(void) {
  int btns = getbtns();
  int sw = getsw();

  if(sw & 0x1) {
    quit();
  }

  if((!game_active) && (!settings_menu) && (!highscore_active) && (!initial_active)) {
    menu(btns);
  }
  if((!game_active) && (settings_menu)) {
    menu_settings(btns);
  }
  if((!game_active) && (highscore_active)){
    highscore_menu(btns);
  }

  if((game_active) && (game_mode == 1)){
    two_player(btns);
  }

  if((game_active) && (game_mode == 2)){
    one_player(btns);
  }
  if((game_active) && (game_mode == 3)){
    score_mode(btns);
  }
  
  if(initial_active){
    initial_select(btns);
  }

}
