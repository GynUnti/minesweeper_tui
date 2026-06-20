#include "headers.h"

// MAIN FUNCTION
int main(void) {
  Game g;
  initSize(&g);
  initBoard(&g);
  initscr();
  clear();
  while (g.state == STATE_ONGOING) {
    int r, c;
    char flag;
    printBoard(&g);
    printw("Pick your cell (r, c) (add f for flag): ");
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
    if (g.board[r][c] == 'x') {
      printAll(&g);
      printw("\nYou Lose!");
      printw("\n\nPress any key to exit.");
      noecho();
      getch();
      return 0;
    }
    if (g.freeCellsLeft == 0) {
      printAll(&g);
      printw("\nYou Won!");
      printw("\n\nPress any key to exit.");
      noecho();
      getch();
      return 0;
    }
  }
  return 0;
}
