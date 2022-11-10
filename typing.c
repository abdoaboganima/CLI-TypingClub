#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "typing.h"

extern char buff[];

static const char *file_error="File cannot be opened\n";

void print_str(WINDOW *win, const char *p)
{
  while(*p){
    waddch(win, *p++);
    wrefresh(win);
    napms(5);
  }
  wprintw(win, "\n");
}

void print_file(WINDOW *win, const char *p)
{
  wclear(win);
  //  wrefresh(win);
  wattroff(win, A_UNDERLINE|A_BOLD);
  FILE *fp = fopen(p, "r");
  if(fp==NULL){
    wprintw(win, file_error);
    return;
  }

  char c;
  while((c=fgetc(fp))!=EOF)
    waddch(win, c);
  wrefresh(win);
  fclose(fp);
}





void type_and_check(WINDOW *win, const char *compared_to)
{

  noecho(); /*Turns off the echo of the getch()*/
  int x, y;
  getyx(win, y, x);
  whline(win, 0, 10);
  wmove(win, y+1, 0);

  int numOfNewlines=0;
  uint8_t x_value_when_newline_pressed[15]={0};


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


#define MAX_NEWLINES 15

void type_and_check_from_file(WINDOW *win, const char *pathname)
{
  keypad(win, TRUE);
  noecho(); /*Turns off the echo of the getch()*/
  FILE *fp = fopen(pathname, "r"); /*opens the file for read only*/

  if(fp==NULL){
    wprintw(win, file_error);
    wrefresh(win);
    return;
  }

  char ch_fromFile;

  int x, y, prev_x=0;
  getyx(win, y, x);
  mvwhline(win,y+1, x, 0, 50);
  wmove(win, y+2, 0);


  int x_value_when_newline_pressed[MAX_NEWLINES]={0};
  int numOfNewlines=0;

  while((ch_fromFile=fgetc(fp))!=EOF){

    getyx(win, y, x);
    wmove(win, y, x); /*Makes the cursor still be in current window*/

    int ch =wgetch(win);

    if(ch==KEY_HOME || ch==KEY_EXIT)
      break;

    else if(ch<127){

      if(ch!=ch_fromFile)
        /*if the input character is different, differetiate it*/
        wattron(win, A_BOLD|A_UNDERLINE);

      else
        wattroff(win, A_BOLD|A_UNDERLINE);

      wprintw(win, "%c", ch);
    }

    else if(ch==KEY_BACKSPACE || ch==KEY_DC){ /*Handling the delete character*/
      getyx(win, y, x);
      if(x==0){ /*We are in the first column and delete is pressed*/
        if(numOfNewlines==0){
          /*Do nothing*/
          fseek(fp, 0, SEEK_SET);
        }
        else {
          fseek(fp, -2, SEEK_CUR);
          wmove(win, y-1, x_value_when_newline_pressed[--numOfNewlines]);
        }
      }
      else {
        fseek(fp, -2, SEEK_CUR);
        wmove(win, y, x-1);
      }
      wclrtobot(win);
    }
    else
      /*if any other key presse*/
      fseek(fp, -1, SEEK_CUR);


    if(ch=='\n')
      /*Save the last index of the x of the previous line*/
      x_value_when_newline_pressed[numOfNewlines++]=prev_x;


    if(numOfNewlines==MAX_NEWLINES){
      wprintw(win,"You exceeded the maximum # of newlines\n");
      wrefresh(win);
      break;
    }

    getyx(win, y, prev_x);
    wrefresh(win);

  }

  fclose(fp); /*Closes the file*/
}

