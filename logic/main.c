#include "headers.h"

// MAIN FUNCTION
int main(void) {
  Game g;
  tuiInit();
  gameSetup(&g);
  initBoard(&g);
  initColors();
  while (g.state == STATE_ONGOING) {
    int r, c;
    char flag;
    printBoard(&g);
    printw("Pick your cell (r, c) (press f after Enter for flag): ");
    scanw("%d%d", &r, &c);
    while ((flag = getch()) != '\n') {
      refresh();
      if (flag == 'f') {
        break;
      }
    }
    if (flag == 'f') {
      flagToggle(&g, r, c);
      continue;
    }
    if (g.firstMove) {
      placeBomb(&g, r, c);
      numGen(&g);
      g.firstMove = false;
    }
    domainExpansion(&g, r, c);
    winCheck(&g, r, c);
  }
  printAll(&g);
  if (g.state == STATE_WON) printw("YOU WON!\nPress any key to exit.");
  else printw("YOU LOST!\nPress any key to exit.");
  refresh();
  getch();
  endwin();
  return 0;
}
