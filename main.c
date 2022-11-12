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



char buff[BUFF_LEN];



const char *  main_menu_items[]={"Lessons",
                            "Scores",
                            "Help",
                            "Exit"};


extern const char *filenames[];
extern const int files_num;

menu_t  main_menu;
menu_t lessons_menu;

int d;



int main(int argc, char *argv[])
{
  if(argc>1){
    if(!strcmp(argv[1], "make_examples"))
      make_examples();
    else{
      printf("Wrong option\n");
      return 1;
    }
  }



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


  mvwaddstr(help_win, 5, 10, "This is written by Abdulrahman Aboghanima (@abdoaboganima)");
  touchwin(help_win);
  wrefresh(help_win);


  create_menu(&main_menu, "Main Menu", main_menu_items, 4);
  create_menu(&lessons_menu, "Lessons" , filenames, files_num);

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
