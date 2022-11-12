#ifndef MENU_H_
#define MENU_H_
#include <ncurses.h>





struct menu{

  const char * menu_name;
  const char * menu_items[25];
  uint8_t size;

};


typedef struct menu menu_t;


void create_menu(menu_t *menu, const char * const menu_name, const char **menu_items, const uint8_t menu_size);


int select_from_menu(WINDOW *win, const menu_t *const menu);

void draw_menu(WINDOW *win,  const menu_t *const menu, int item);


#endif /* MENU_H_ */
