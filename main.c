#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "typing.h"


#define N 5
#define BUFF_LEN 100

const char *name="Abdulrahman Aboghanima Ahmed\nis a clever programmer, I love him so much";

const char *test[N]={"This", "is", "a", "Test,", "MAN"};

char buff[BUFF_LEN];




int main()
{
  int rows, cols;
  initscr();
  getmaxyx(stdscr, rows, cols);
  printw("%d %d\n", rows, cols);
  hline(0, 10);
  refresh();


  /*Createing a window for typing in*/
  int t_rows=(rows-rows/3)/2;
  int t_cols=(cols-cols/10)/2;
  WINDOW *typing_win=newwin(0, 0, rows/3, cols/10);

  WINDOW *outer_win=newwin(t_rows, t_cols, rows/3-3, cols/10-3);


  wrefresh(outer_win);

  print_str(typing_win, name);
  whline(typing_win, 0, 10);
  type_and_check(typing_win, name);





  while((getch())!='q'); //Keep  the window unitl you press a charcter

  endwin();


  return 0;
}
