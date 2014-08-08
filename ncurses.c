
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

int main(int ac, char **av) {
    int ch;
    char c[30];
    int i = 0;
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    mvprintw(0, 0, "press a key: ");
   
    while( (ch = getch()) != 'q') {
        erase();
        move(0,0);
        printw("You pressed : %c with value %d\n", ch, ch);
        
        c[i++] = ch;
        printw("You pressed : %c\n", c[i]);
        if (ch == '\n') {
            printw("Newline\n");
            continue;
        }
        printw("Press another key, or 'q' to quit\n");
        refresh();
    }
    
    for (int j = 0; j < i; j++) {
        printw("%c\n", c[j]);
    }
    refresh();
    
    endwin();
}


