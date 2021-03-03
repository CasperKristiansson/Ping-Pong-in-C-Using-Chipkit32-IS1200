#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

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