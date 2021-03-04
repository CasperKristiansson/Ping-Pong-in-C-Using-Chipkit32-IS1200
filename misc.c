#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

void quit() {
  delay(1000);
  PORTE = 0x0;

  ai_difficulty = 4;
  game_active = 0;
  game_mode = 0;
  player_lives = 3;
  score_player1 = 0;
  score_player2 = 0;

  clearDisplay();
  translateToImage();
  display_image(0, oled_display);
}
void quit_ai() {
  delay(1000);
  PORTE = 0x0;

  ai_difficulty = 4;
  game_active = 0;
  game_mode = 0;
  player_lives = 3;
  score_player2 = 0;
  initial_active = 1;
  
  string_clear();
  clearDisplay();
  translateToImage();
  display_image(0, oled_display);
  quit();
}



void reset_game() {
 /* Debugging paddle_splits
  i = 0;
  j = 0;
  k = 0;
  m = 0;
 Debugging paddle_splits */

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

void itoas(int n, char m[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         m[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         m[i++] = '-';
     m[i] = '\0';
     reverse(m);
 }

 void reverse(char m[])
 {
     int i, j;
     char d;
 
     for (i = 0, j = sizeof(m)-1; i<j; i++, j--) {
         d = m[i];
         m[i] = m[j];
         m[j] = d;
     }
 }