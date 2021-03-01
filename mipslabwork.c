/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t display[32][128];
uint8_t oled_display[512];

//Menu variables
float current_menu = 1;
float settings_menu = 0;

//Game specific variables
float game_active = 0;
float game_mode = 0;
float score_player1 = 0;
float score_player2 = 0;
int ai_difficulty = 4; // 4Easy, 2Medium, 1Hard
int player = 0;

//Paddle specific variables
float paddle_height = 8;
float paddle_width = 3;
float paddle_speed = 1;

float paddle1_xPos = 0;
float paddle1_yPos = 32 / 2 - 2;

float paddle2_xPos = 128 - 4;
float paddle2_yPos = 32 / 2 - 2;

//Ball specific variables
float ball_size = 4;
float ball_speedx = 1;
float ball_speedy = 0;

float ball_xPos = 128 / 2 - 5;
int ball_yPos = 32 / 2;


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
void setPixelArray(int xPos, int yPos, int width, int height) {
  int row, column;

  for (row = 0; row < 32; row++) {
    for (column = 0; column < 128; column++) {
      if (row >= yPos && row <= (yPos + height) && column >= xPos && column <= (xPos + width)) {
        display[row][column] = 1;
      }
    }
  }
}

// Translate the 2D array into the 1D array with 512 slots.
void translateToImage() {
  int page, column, row, c, k;
  uint8_t powerOfTwo = 1;
  uint8_t oledNumber = 0;
  int survivalMode = 0;

  for(page = 0; page < 4; page++) {
    for(column = 0; column < 128; column++) {
      powerOfTwo = 1;
      oledNumber = 0;

      for(row = 0; row < 8; row++) {
        if(display[8 * page + row][column]) {
          oledNumber |= powerOfTwo;
        }
        powerOfTwo <<= 1;
      }
      oled_display[column + page * 128] = oledNumber;
    }
  }
}

void clearDisplay() {
  int row, column, i;

  for(row = 0; row < 32; row++) {
    for(column = 0; column < 128; column++) {
      display[row][column] = 0;
    }
  }

  for (i = 0; i < 512; i++) {
    oled_display[i] = 0;
  }
}

void menu(btns) {
  delay(200);
  if(current_menu == 1) {
    display_string(0, "> Two Player");
    display_string(1, "  One Player");
    display_string(2, "  Settings");

    if (btns & 0x1) {
      game_mode = 1;
      game_active = 1;
      string_clear();
    }
  }
  else if(current_menu == 2) {
    display_string(0, "  Two Player");
    display_string(1, "> One Player");
    display_string(2, "  Settings");

    if (btns & 0x1) {
      game_mode = 2;
      game_active = 1;
      string_clear();
    }
  }
  else if(current_menu == 3) {
    display_string(0, "  Two Player");
    display_string(1, "  One Player");
    display_string(2, "> Settings");

    if (btns & 0x1) {
      settings_menu = 1;
      current_menu = 1;
      string_clear();
    }
  }

  if ((btns & 0x2) && (current_menu < 3)) {
    current_menu++;
  }
  if ((btns & 0x4) && (current_menu > 1)) {
    current_menu--;
  }

  display_update();
}

void menu_settings(btns) {
  delay(200);
  if(current_menu == 1) {
    display_string(0, ">  Easy");
    display_string(1, "   Normal");
    display_string(2, "   Hard");
    display_string(3, "   Back");

    if (btns & 0x1) {
      ai_difficulty = 4;
    }
  }
  else if (current_menu == 2) {
    display_string(0, "   Easy");
    display_string(1, ">  Normal");
    display_string(2, "   Hard");
    display_string(3, "   Back");

    if (btns & 0x1) {
      ai_difficulty = 2;
    }
  }
  else if (current_menu == 3) {
    display_string(0, "   Easy");
    display_string(1, "   Normal");
    display_string(2, ">  Hard");
    display_string(3, "   Back");

    if (btns & 0x1) {
      ai_difficulty = 1;
    }
  }
  else if (current_menu == 4) {
    display_string(0, "   Easy");
    display_string(1, "   Normal");
    display_string(2, "   Hard");
    display_string(3, ">  Back");

    if (btns & 0x1) {
      settings_menu = 0;
      current_menu = 1;
      string_clear();
    }
  }

  if ((btns & 0x2) && (current_menu < 4)) {
    current_menu++;
  }
  if ((btns & 0x4) && (current_menu > 1)) {
    current_menu--;
  }

  display_update();
}

void player_movement_two(btns) {
  if ((btns & 0x1) && (paddle2_yPos < (32 - paddle_height))) {
    paddle2_yPos += paddle_speed;
  }
  if ((btns & 0x2) && (paddle2_yPos > 0)) {
    paddle2_yPos -= paddle_speed;
  }
  if ((btns & 0x4) && (paddle1_yPos < (32 - paddle_height))) {
    paddle1_yPos += paddle_speed;
  }
  if ((btns & 0x8) && (paddle1_yPos > 0)) {
    paddle1_yPos -= paddle_speed;
  }
}

void player_movement_one(btns) {
  if ((btns & 0x4) && (paddle1_yPos < (32 - paddle_height))) {
    paddle1_yPos += paddle_speed;
  }
  if ((btns & 0x8) && (paddle1_yPos > 0)) {
    paddle1_yPos -= paddle_speed;
  }
}

/*

bollens y speed fungerar inte riktigt some den ska

*/
void 
paddle_hit() {
  if (ball_xPos == paddle_width) {
    if (((ball_yPos + ball_size) > paddle1_yPos) && (ball_yPos) < (paddle1_yPos + paddle_height)) {
      ball_speedx = -(ball_speedx);
    
      if ((ball_yPos + ball_size / 2) < paddle1_yPos + paddle_height / 2 && ball_speedy > -1.5) {
          ball_speedy -= 0.3;
      }
      if ((ball_yPos + ball_size / 2) > paddle1_yPos + paddle_height / 2 && ball_speedy < -1.5) {
          ball_speedy += 0.3;
      }
    /*

    Add increasing ball speed after paddle hit

    */
    }
    else {
      goal(2);
    }
  }

  if (ball_xPos == (128 - paddle_width - 4)) {
    if (((ball_yPos + ball_size) > paddle2_yPos) && (ball_yPos) < (paddle2_yPos + paddle_height)) {
      ball_speedx = -(ball_speedx);

      if ((ball_yPos + ball_size / 2) < paddle2_yPos + paddle_height / 2 && ball_speedy > -1.5) {
          ball_speedy -= 0.3;
      }
      if ((ball_yPos + ball_size / 2) > paddle2_yPos + paddle_height / 2 && ball_speedy < -1.5) {
          ball_speedy += 0.3;
    }
    /*

    Add increasing ball speed after paddle hit

    */
    }
    else {
      goal(1);
    }
  }
}

void goal(player) {
  if (player == 1) {
    score_player1 += 1;
  }
  if (player == 2) {
    score_player2 += 1;
  }

  if (score_player1 == 1) {
    PORTE |= 0x80;
  }
  if (score_player1 == 2){
    PORTE |= 0xC0;
  }
  if (score_player1 == 3){
    PORTE |= 0xE0;
  }
  if (score_player1 == 4){
    PORTE |= 0xF0;
    quit();
  }
  
  if (score_player2 == 4){
    PORTE |= 0x8;
    quit();
  }
  if (score_player2 == 3){
    PORTE |= 0x4;
  }
  if (score_player2 == 2){
    PORTE |= 0x2;
  }
  if (score_player2 == 1){
    PORTE |= 0x1;
  }

  reset_game();
}

void quit() {
  delay(3000);
  game_active = 0;
  game_mode = 0;

  clearDisplay();
  translateToImage();
  display_image(0, oled_display);
}

void reset_game() {
  paddle1_xPos = 0;
  paddle1_yPos = 32 / 2 - 2;

  paddle2_xPos = 128 - 4;
  paddle2_yPos = 32 / 2 - 2;

  ball_xPos = 128 / 2 - 5;
  ball_yPos = 32 / 2;

  if (score_player1 > score_player2) {
    ball_speedx = -1;
  }
  else if (score_player1 < score_player2) {
    ball_speedx = 1;
  }
  else {
    ball_speedx = 1;
  }
  ball_speedy = 0;

  clearDisplay();
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
  translateToImage();
  display_image(0, oled_display);
  delay(1000);
}

void string_clear() {
  display_string(0, "");
  display_string(1, "");
  display_string(2, "");
  display_string(3, "");
  display_string(4, "");
  display_update();
}

void ball_movement() {
  ball_xPos += ball_speedx;
  ball_yPos += ball_speedy;

  if (ball_yPos < 0 || ball_yPos > (31 - ball_size)) {
    ball_speedy = -(ball_speedy);
  }
}

void ai_move(void) {
  if ((ball_yPos % ai_difficulty) == 0) {
    if ((ball_yPos < paddle2_yPos) && (paddle2_yPos > 0)) {
      paddle2_yPos -= paddle_speed;
    }
    if ((ball_yPos > paddle2_yPos) && (paddle2_yPos < (32 - paddle_height))) {
      paddle2_yPos += paddle_speed;
    }
  }
}

void one_player(btns) {
  player_movement_one(btns);
  ai_move();
  ball_movement();
  paddle_hit();

  clearDisplay();
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
  translateToImage();
  display_image(0, oled_display);
}

void two_player(btns) {
  player_movement_two(btns);
  ball_movement();
  paddle_hit();

  clearDisplay();
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
  translateToImage();
  display_image(0, oled_display);
}

/* This function is called repetitively from the main program */
void labwork(void) {
  int btns = getbtns();
  int sw = getsw();

  if((!game_active) && (!settings_menu)) {
    menu(btns);
  }
  if((!game_active) && (settings_menu)) {
    menu_settings(btns);
  }

  if((game_active) && (game_mode == 1)){
    two_player(btns);
  }

  if((game_active) && (game_mode == 2)){
    one_player(btns);
  }
}
