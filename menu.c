#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


//Menu variables
float current_menu = 1;
float settings_menu = 0;

void menu(int btns) {
  delay(200);
  if(current_menu == 1) {
    display_string(0, "> Two Player");
    display_string(1, "  One Player");
    display_string(2, "  Settings");

    if (getbtns() & 0x1) {
      reset_game();
      game_mode = 1;
      game_active = 1;
      string_clear();
    }
  }
  else if(current_menu == 2) {
    display_string(0, "  Two Player");
    display_string(1, "> One Player");
    display_string(2, "  Settings");

    if (getbtns() & 0x1) {
      reset_game();
      game_mode = 2;
      game_active = 1;
      string_clear();
    }
  }
  else if(current_menu == 3) {
    display_string(0, "  Two Player");
    display_string(1, "  One Player");
    display_string(2, "> Settings");

    if (getbtns() & 0x1) {
      settings_menu = 1;
      current_menu = 1;
      string_clear();
    }
  }

  else if(current_menu == 4) {
    display_string(0, "  One Player");
    display_string(1, "  Settings");
    display_string(2, "> Score Mode");

    if (getbtns() & 0x1) {
      reset_game();
      game_mode = 3;
      game_active = 1;
      string_clear();
    }
  }

  if ((getbtns() & 0x2) && (current_menu < 4)) {
    current_menu++;
  }
  if ((getbtns() & 0x4) && (current_menu > 1)) {
    current_menu--;
  }

  display_update();
}

void menu_settings(int btns) {
  delay(200);
  if(current_menu == 1) {
    display_string(0, ">  Easy");
    display_string(1, "   Normal");
    display_string(2, "   Hard");

    if (getbtns() & 0x1) {
      ai_difficulty = 4;
      settings_menu = 0;
      current_menu = 1;
      string_clear();
    }
  }
  else if (current_menu == 2) {
    display_string(0, "   Easy");
    display_string(1, ">  Normal");
    display_string(2, "   Hard");

    if (getbtns() & 0x1) {
      ai_difficulty = 3;
      settings_menu = 0;
      current_menu = 1;
      string_clear();
    }
  }
  else if (current_menu == 3) {
    display_string(0, "   Easy");
    display_string(1, "   Normal");
    display_string(2, ">  Hard");

    if (getbtns() & 0x1) {
      ai_difficulty = 1;
      settings_menu = 0;
      current_menu = 1;
      string_clear();
    }
  }

  if ((getbtns() & 0x2) && (current_menu < 3)) {
    current_menu++;
  }
  if ((getbtns() & 0x4) && (current_menu > 1)) {
    current_menu--;
  }

  display_update();
}