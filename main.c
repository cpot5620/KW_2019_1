#include <curses.h>
#include <stdio.h>
#include <string.h>

void test();
char text[100] = "ABCDEFGHIJKLMN abcdefgh";
int main() {
    char c;
    char buffer[100];
    int i = 0;
    int j;
    int line = 1;

    initscr(); /// to use ncurses
    clear();   /// window clear
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh(); /// window refresh

    for (j = 0; j < 100; j++)
        buffer[j] = '\0'; /// to clear array

    test();

    move(1, 0);

    refresh(); // window refresh

    while (c != 0x1B) { /// ESC is 0x1B in ASCII
        c = getchar();
        if (c == '\r') { // move to forward of line
            line += 2;
            move(line, 0);
            printf("\r");
            refresh();
            i = 0;

            for (j = 0; j < 100; j++) {
                buffer[j] = '\0'; /// buffer clear
            }
        } else {

            buffer[i] = c;
            addch(c);
            if (buffer[i] != text[i]) {
                move(line - 1, i);
                attron(COLOR_PAIR(1));
                addch(text[i]);
                attroff(COLOR_PAIR(1));
                move(line, i + 1);
            }
            i++;
            refresh();
        }
    }
    endwin();
}

void test() {
    int line = 0;
    addstr(text);
}
