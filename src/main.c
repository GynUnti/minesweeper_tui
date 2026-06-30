#include "headers.h"

// MAIN FUNCTION
int main(void) {
  Game g;
  tuiInit();
  gameSetup(&g);
  initBoard(&g);
  initColors();
  WINDOW* gameboard = createBoard(&g);
  while (g.state == STATE_ONGOING) {
    navigation(&g, gameboard);
  }
  printAll(&g);
  if (g.state == STATE_WON) printw("YOU WON!\nPress any key to exit.");
  else printw("YOU LOST!\nPress any key to exit.");
  refresh();
  getch();
  endwin();
  return 0;
}
