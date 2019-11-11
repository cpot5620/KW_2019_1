#include <curses.h>
#include <stdio.h>
#include <string.h>

void test();

int main() {
    char c;
    char buffer[100];
    int i = 0;
    int j;
    int line = 1;

    initscr(); /// to use ncurses
    clear();   /// window clear
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
                if (buffer[j]) /// we need to add function for comparing two
                               /// words

                    buffer[j] = '\0'; /// after above function, buffer clear
            }
        } else {
            putchar(c);
            buffer[i] = c;
            i++;
        }
    }
    endwin();
}

void test() {
    int line = 0;
    addstr("This is Sample Text");
    line += 2;
    move(line, 0);
    addstr("you can type English");
    line += 2;
    move(line, 0);
    addstr("DSS Project");
}
