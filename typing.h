#ifndef TYPING_H_
#define TYPING_H_
#include <ncurses.h>




void print_str(WINDOW *win, const char *p);

void type_and_check(WINDOW *win, const char *compared_to);

void type_and_check_from_file(WINDOW *win, const char *pathname);

void print_file(WINDOW *win, const char *p);




#endif /* TYPING_H_ */
