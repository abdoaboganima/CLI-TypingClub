#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "typing.h"
#include "examples.h"
#include "menu.h"

#define N 5
#define BUFF_LEN 100

const char *name="Abdulrahman Aboghanima Ahmed\nis a clever programmer, I love him so much";

const char *test[N]={"This", "is", "a", "Test,", "MAN"};

char buff[BUFF_LEN];



const char *  main_menu_items[]={"Lessons",
                            "Scores",
                            "Help",
                            "Exit"};


const char * filenames[]={ "lessons/fj.txt",
                           "lessons/kd.txt",
                           "lessons/ls.txt",
                           "lessons/a;.txt",
                           "lessons/pw.txt",
                           "lessons/pq.txt",
                           "lessons/ik.txt",
                           "lessons/ie.txt",
                           "lessons/ur.txt",
                           "lessons/ty.txt",
                           "lessons/rtyu.txt",
                           "lessons/asdf.txt",
                           "lessons/iked.txt",
                           "lessons/fghj.txt",
                           "lessons/jn.txt",
                           "lessons/fv.txt",
                           "lessons/fvjn.txt",
                           "lessons/custom.txt"};



menu_t  main_menu;
menu_t lessons_menu;

int d;

int main(void)
{

  initscr();
  WINDOW *help_win=newwin(0,0,0,0);
  WINDOW *main_menu_win=newwin(0,0,0,0);
  WINDOW *lessons_menu_win=newwin(0,0,0,0);

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  WINDOW *typing_win=newwin(0, 0, rows/6, cols/10);

  start_color();
  init_pair(1,  COLOR_YELLOW, COLOR_BLACK);
  wbkgd(main_menu_win, COLOR_PAIR(1));


  //make_examples();

  mvwaddstr(help_win, 5, 10, "This is written by Abdulrahman Aboghanima (@abdoaboganima)");
  touchwin(help_win);
  wrefresh(help_win);


  create_menu(&main_menu, "Main Menu", main_menu_items, 4);
  create_menu(&lessons_menu, "Lessons" , filenames, 18);

  do{
    int main_menu_item=select_from_menu(main_menu_win, &main_menu);

    if(main_menu_item==0){
      touchwin(lessons_menu_win);
      int lessons_item=select_from_menu(lessons_menu_win, &lessons_menu);
      print_file(typing_win, filenames[lessons_item]);
      type_and_check_from_file(typing_win, filenames[lessons_item]);
    }

    else if(main_menu_item==2){
      touchwin(help_win);

      noecho();
      wgetch(help_win);

    }
    else if(main_menu_item==3)
      break;

  }while((getch())!='q'); //Keep  the window unitl you press a charcter


  endwin();

  return 0;
}
