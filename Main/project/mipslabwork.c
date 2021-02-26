/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include <stdio.h>
#include <stdlib.h>

uint8_t display[32][128];
uint8_t oled_display[512];

//Game specific variables
float game_active = 0;

//Paddle specific variables
float paddle_height = 8;
float paddle_width = 4;
float paddle_speed = 1;

float paddle1_xPos = 0;
float paddle1_yPos = 32 / 2 - 8;

float paddle2_xPos = 128 - 4;
float paddle2_yPos = 32 / 2 - 8;


//Ball specific variables
float ball_size = 4;
float ball_speedx = 1;
float ball_speedy = 0;

float ball_xPos = 128 / 2 - 4;
float ball_yPos = 32 / 2;


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

// Set array slots to ones or zeros in the 2D array.
void setPixelArray(int xPos, int yPos, int width, int height)
{
  int row, column;
  for (row = 0; row < 32; row++)
  { // y-axis
    for (column = 0; column < 128; column++)
    { // x-axis
      if (row >= yPos && row <= (yPos + height) && column >= xPos && column <= (xPos + width))
      {
        display[row][column] = 1;
      }
    }
  }
}

// Translate the 2D array into the 1D array with 512 slots.
void translateToImage()
{
  int page, column, row, c, k;
  uint8_t powerOfTwo = 1; // Interval: 2^0, 2^1 ... to ... 2^7.
  uint8_t oledNumber = 0;
  int survivalMode = 0;
  for (page = 0; page < 4; page++)
  {
    for (column = 0; column < 128; column++)
    {
      powerOfTwo = 1;
      oledNumber = 0;
      for (row = 0; row < 8; row++)
      {
        if (display[8 * page + row][column])
        {
          oledNumber |= powerOfTwo;
        }
        powerOfTwo <<= 1;
      }
      // Display score in survival mode (Write 8-width letters, one for every time the column is a multiple of 8)
      
      if (survivalMode && page == 0)
      {
        if (column % 8 == 0)
        {
          c = textbuffer[page][column / 8];
        }
        if (!(c & 0x80))
        {
          oledNumber |= font[c * 8 + column % 8]; // Set the hexadecimal number from font[] array and assign to the oledNumber variable.
        }
      }

      oled_display[column + page * 128] = oledNumber;
    }
  }
}


void clearDisplay()
{
  /*CLEARS ALL elements in arrays and sets 0 on them.
    memset(display, 0, sizeof(display));
    memset(oled_display, 0, sizeof(oled_display));
  */
  int row, column, i;
  for (row = 0; row < 32; row++)
  {
    for (column = 0; column < 128; column++)
    {
      display[row][column] = 0; // Clear the array
    }
  }
  for (i = 0; i < 512; i++)
  {
    oled_display[i] = 0; // Clear the array
  }
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  int btns = getbtns();
  int sw = getsw();
  if (btns & 0x1) {
    game_active = 1;
    
	}

  if(game_active == 1){
    
    display_string(0, "");
    display_string(1, "");
    display_string(2, "");
    display_string(3, "");
    display_string(4, "");
    display_update();
    
    clearDisplay();
    setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
    setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
    translateToImage();
    display_image(0, oled_display);
  }
  
    

  /*
  else if(game_active == 0){
    //menu();
    display_string(0, "  PONG!");
	  display_string(1, "> Start");
	  display_string(2, "  Modes");
	  display_string(3, "  High Scores");
	  display_update();
  }
  */
  
  
  delay( 1000 );
  //*E += 0x1;
  //display_image(96, icon);
  
}
