
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
}*/

#include <ncurses.h>

int main() {
    int ch;  char c[30];
    int i = 0;
    int h, w;
    int row = 0;
    
    initscr();
    cbreak();
    //noecho();
    
    keypad(stdscr, true);
    
    getmaxyx(stdscr, h, w);
    
    
    mvprintw(0, 0, "Shelly>>");
   
    //move(10,10);
    
    while( (ch = getch()) != 'q') {
        //erase();
        //move(10,1);
        //printw("You pressed : %c with value %d\n", ch, ch);
        //printw("%c",ch);
        c[i++] = ch;
        if (ch == '\n') {
            //mvprintw(11, 1, "Newline\n");
            move(++row, 0);
            continue;
        }
        //mvprintw(11, 1, "Press another key, or 'q' to quit\n");
        //move(20,0);
        refresh();
    }
    
    for (int j = 0; j < i; j++) {
        printw("%c\n", c[j]);
    }
    refresh();
    
    endwin();
}


