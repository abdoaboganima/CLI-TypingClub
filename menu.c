#include <ncurses.h>
#include <stdint.h>

#include "menu.h"






void create_menu(menu_t *menu, const char * const menu_name, const char **menu_items, const uint8_t menu_size)
{
  menu->menu_name=menu_name;
  menu->size=menu_size;

  for (int i=0; i < menu_size; ++i)
    menu->menu_items[i]=menu_items[i];

}


int select_from_menu(WINDOW *win, const menu_t * const menu)
{
  noecho();
  keypad(win, TRUE);
  int item=0;
  draw_menu(win, menu, item);
  int key;
  do {
    key=wgetch(win);
    switch (key) {
    case KEY_DOWN:
      if(item<menu->size-1)
        item++;
      break;

    case KEY_UP:
      if(item>0)
        item--;

    default:
      break;
    }
    draw_menu(win, menu, item);

  } while (key!='\n');
  echo();
  wclear(win);
  wrefresh(win);

  return item;
}



void draw_menu(WINDOW *win,  const menu_t *const menu, int item)
{
  wclear(win);
  int y, x, ymax, xmax;
  getmaxyx(win, ymax, xmax);

  getyx(win, y, x);
  wattron(win, A_BOLD);
  mvwaddstr(win,y+2, 0, menu->menu_name);
  wattroff(win, A_BOLD);

  int j=menu->size>(ymax/2)?1:2;

  for (int i=0; i < menu->size; ++i) {

    getyx(win, y, x);

    if(i==item)
      wattron(win, A_REVERSE|A_BOLD);

    mvwaddstr(win, y+j, 10, menu->menu_items[i]);
    wattroff(win, A_REVERSE|A_BOLD);

  }
  mvwaddstr(win, ymax-2, 0, "Use arrow keys to move, Enter to select");

  wrefresh(win);
}
