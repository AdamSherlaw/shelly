
/*#include <ncurses.h>
#include <string.h>

int main() {
    char str[80];
    int row, col;
    
    initscr();
    getmaxyx(stdscr,row,col);
    raw();
    keypad(stdscr, TRUE);
    //noecho();
    
    printw("Type any character to see it in bold\n");
    getstr(str);
    
    mvprintw(row / 2, (col - strlen(str)) / 2, "%s", str);
    
    //refresh();
    getch();
    endwin();
    
    return 0;
}

*/
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
int main(int argc, char *argv[])
{	initscr();			/* Start curses mode 		*/
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    assume_default_colors(COLOR_BLUE,COLOR_RED);
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_RED);
    
	attron(COLOR_PAIR(1));
	print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
	attroff(COLOR_PAIR(1));
    getch();
	endwin();
    return 0;
}
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{	int length, x, y;
	float temp;
    
	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;
    
	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}