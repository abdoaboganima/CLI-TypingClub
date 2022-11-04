#include <ncurses.h>
#include <string.h>
#include "typing.h"


extern char buff[];


void print_str(WINDOW *win, const char *p)
{
  while(*p){
    waddch(win, *p++);
    wrefresh(win);
    napms(5);
  }
  wprintw(win, "\n");
}




void type_and_check(WINDOW *win, const char *compared_to)
{

  noecho(); /*Turns off the echo of the getch()*/
  int x, y;
  getyx(win, y, x);
  whline(win, 0, 100);
  wmove(win, y+1, 0);

  int numOfNewlines=0;
  int x_value_when_newline_pressed[15]={0};


  int i=0;

  while(i<(int)strlen(compared_to)){

    int ch=wgetch(win);

    if(ch>19&&ch<127){
      buff[i++]=ch;

      if(strncmp(buff, compared_to, i))
        wattron(win, A_BOLD|A_UNDERLINE);

      else
        wattroff(win, A_BOLD|A_UNDERLINE);

      wprintw(win, "%c", ch);
    }

    if(ch==127){ /* The delete character is pressed*/

      getyx(win, y, x);
      if(x==0){ /*We are in the first column and delete is pressed*/
        if(numOfNewlines==0){
          /*Do nothing*/
          i=0;
        }
        else {
          wmove(win, y-1, x_value_when_newline_pressed[--numOfNewlines]);
          --i;
          wclrtobot(win);
        }
      }
      else {
        wmove(win, y, x-1);
        --i;
        wclrtobot(win);
      }
    }


    else if(ch=='\n'){
      getyx(win, y, x);
      x_value_when_newline_pressed[numOfNewlines++]=x;
      buff[i++]='\n';
      wmove(win, y+1, 0); /*Move to the next line*/
    }

    /*for debugging*/
    int yy, xx;
    getyx(win, yy, xx);
    move(4,0);
    printw("y=%d x=%d, #ofnew=%d\n", yy, xx , numOfNewlines);
    for (int i = 0; i < 10; ++i) {
      printw("x[%d]=%d,", i, x_value_when_newline_pressed[i]);
    }
    refresh();
    /*delete after finishing debugging*/

    wrefresh(win);

  }
  wprintw(win, "\n");
  wprintw(win, "The lenght is %d\n", strlen(buff));
  wrefresh(win);
}
