#include "headers.h"

void tuiInit(void) {
  initscr();
  cbreak();
}

void gameSetup(Game* g) {
  clear();
  echo();
  int xMax, yMax;
  int winWid = 35, winHei = 7;
  getmaxyx(stdscr, yMax, xMax);
  WINDOW* win = newwin(winHei, winWid, (yMax-winHei)/2, (xMax-winWid)/2);
  refresh();
  box(win, 0, 0);

  mvwprintw(win, 2, 2, "Rows number (1-%d): ", MAX_ROW);
  mvwprintw(win, 3, 2, "Columns number (1-%d): ", MAX_COL);
  mvwprintw(win, 4, 2, "Bombs number: ");
  wrefresh(win);
  
  wmove(win, 2, 27);
  wscanw(win, "%d", &(g->rows));
  if (g->rows > MAX_ROW) {
    g->rows = MAX_ROW;
    mvwprintw(win, 2, 27, "%d   ", MAX_ROW);
  }
  else if (g->rows < 1) {
    g->rows = 1;
    mvwprintw(win, 2, 27, "1    ");
  }
  wrefresh(win);

  wmove(win, 3, 27);
  wscanw(win, "%d", &(g->cols));  
  if (g->cols > MAX_COL) {
    g->cols = MAX_COL;
    mvwprintw(win, 3, 27, "%d   ", MAX_COL);
  }
  else if (g->cols < 1) {
    g->cols = 1;
    mvwprintw(win, 3, 27, "1    ");
  }
  wrefresh(win);

  mvwprintw(win, 4, 14, " (1-%d): ", g->rows * g->cols - 1);
  wmove(win, 4, 27);
  wrefresh(win);
  wscanw(win, "%d", &(g->bombs)); 
  
  g->freeCellsLeft = g->rows * g->cols - g-> bombs;
  g->state = STATE_ONGOING; /* Start the game */
  clear();
}

void initColors(void) {
  start_color();
  use_default_colors();

  init_pair(CP_HIDDEN, COLOR_WHITE, COLOR_BLUE);
  init_pair(CP_EMPTY, -1, -1);
  init_pair(CP_BOMB, COLOR_WHITE, COLOR_RED);
  init_pair(CP_FLAG, COLOR_YELLOW, COLOR_BLUE);
  init_pair(CP_N1, COLOR_CYAN, -1);
  init_pair(CP_N2, COLOR_BLUE, -1);
  init_pair(CP_N3, COLOR_YELLOW, -1);
  init_pair(CP_N4, COLOR_GREEN, -1);
  init_pair(CP_N5, COLOR_BLUE, -1);
  init_pair(CP_N6, COLOR_MAGENTA, -1);
  init_pair(CP_N7, COLOR_CYAN, -1);
  init_pair(CP_N8, COLOR_RED, -1);
}

int colorAttrAssign(char c) {
  switch (c) {
    case 'x': return CP_BOMB;
    case 'f': return CP_FLAG;
    case ' ': return CP_EMPTY;
    case '#': return CP_HIDDEN;
    case '1': return CP_N1; 
    case '2': return CP_N2;
    case '3': return CP_N3;
    case '4': return CP_N4;
    case '5': return CP_N5;
    case '6': return CP_N6;
    case '7': return CP_N7;
    case '8': return CP_N8;
    default:  return CP_EMPTY;  /* shouldn't happen, but safe fallback */
  }
}

void printBoard(Game* g) {
  clear();
  int rows = g->rows;
  int cols = g->cols;
  WINDOW* visibleBoard = newwin(rows, cols*3, 1, 3);
  for (int c = 0; c < cols; c++) {
    mvprintw(0, (c+1)*3, "%2d", c);
  }
  for (int r = 0; r < rows; r++) {
    mvprintw(r+1, 0, " %2d", r);
    for (int c = 0; c < cols; c++) {
      char val = g->visible[r][c];
      wattron(visibleBoard, COLOR_PAIR(colorAttrAssign(val)));
      mvwprintw(visibleBoard, r, c*3,"|%c|", val);
      wattroff(visibleBoard, COLOR_PAIR(colorAttrAssign(val)));
    }
  }
  printw("\n\n");
  refresh();
  wrefresh(visibleBoard);
}

void printAll(Game* g) {
  clear();
  int rows = g->rows;
  int cols = g->cols;
  WINDOW* board = newwin(rows, cols*3, 1, 3);
  for (int c = 0; c < cols; c++) {
    mvprintw(0, (c+1)*3, "%2d", c);
  }
  for (int r = 0; r < rows; r++) {
    mvprintw(r+1, 0, " %2d", r);
    for (int c = 0; c < cols; c++) {
      char val = g->board[r][c];
      wattron(board, COLOR_PAIR(colorAttrAssign(val)));
      mvwprintw(board, r, c*3,"|%c|", val);
      wattroff(board, COLOR_PAIR(colorAttrAssign(val)));
    }
  }
  printw("\n\n");
  refresh();
  wrefresh(board);
}


