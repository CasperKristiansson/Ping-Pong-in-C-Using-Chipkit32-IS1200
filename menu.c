#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


//Menu variables
float current_menu = 1;
float settings_menu = 0;

char c = "A";
int initials_menu = 1;
char initial_1;
char initial_2;
char initial_3;
char highscore_temp;
int highscore_active = 0;

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
      current_menu = 1;
      string_clear();
    }
  }

  else if(current_menu == 5) {
    display_string(0, "  Settings");
    display_string(1, "  Score Mode");
    display_string(2, "> Highscore");

    if (getbtns() & 0x1) {
      reset_game();
      highscore_active = 1;
      current_menu = 1;
      string_clear();
    }
  }

  if ((getbtns() & 0x2) && (current_menu < 5)) {
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

void highscore_menu (int btns) {

  display_string(0, highscore_1);
  display_string(1, highscore_2);
  display_string(2, highscore_3);

  if ((getbtns() & 0x1)) {
    highscore_active = 0;
  }
}

void initial_select(int btns) {
  delay(200);

  if (initials_menu == 1) {
    display_string(0, c);
    display_string(1, initial_2);
    display_string(2, initial_3);

      if (getbtns() & 0x1) {
        initial_1 = c;
        initials_menu = 2;
        char c = "A";
    }
  }
  if (initials_menu == 2) {
    display_string(0, initial_1);
    display_string(1, c);
    display_string(2, initial_3);

      if (getbtns() & 0x1) {
        initial_2 = c;
        initials_menu = 3;
        char c = "A";
    }
  }
  if (initials_menu == 3) {
    display_string(0, initial_1);
    display_string(1, initial_2);
    display_string(2, c);

      if (getbtns() & 0x1) {
        initial_3 = c;
        highscore_temp = ("%d%d%d", initial_1, initial_2, initial_3);
    }
  }

  if ((getbtns() & 0x2) && (c != "Z")) {
    c++;
  }
  if ((getbtns() & 0x4) && (c != "A")) {
    c--;
  }
  
  display_update();
}