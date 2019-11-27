#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void draw(int row, int col, char *str) {
    move(row, 0);
    addstr("                    ");
    move(row, col);
    addstr(str);
}
void printWordsPractice() {
    printw("       _    _               _        ______               _ "
           "  _  "
           "        \n");
    printw("      | |  | |             | |       | ___ \\             | "
           "| (_) "
           "        \n");
    printw("      | |  | | ___  _ __ __| |___    | |_/ / __ __ _  ___| "
           "|_ _  "
           "___ ___ \n");
    printw("      | |/\\| |/ _ \\| '__/ _` / __|   |  __/ '__/ _` |/ "
           "__| __| "
           "|/ __/ _ \\\n");
    printw("      \\  /\\  / (_) | | | (_| \\__ \\   | |  | | | (_| | "
           "(__| "
           "|_| | "
           "(_|  __/\n");
    printw("       \\/  \\/ \\___/|_|  \\__,_|___/   \\_|  |_|  "
           "\\__,_|\\___|\\__|_|\\___\\___|\n");
}
int main() {
    int index = 0;
    char buffer[20];
    char answer[20];
    char c;
    int i = 0, red = 0, j = 32;
    int typing = 0, tot = 0;
    time_t start = 0, end = 0;
    float gap = 0, tasu = 1;
    float per;
    char data[][20] = {
        "botanical garder", "sand",     "pheasant",      "present",
        "winter",           "elephant", "lens",          "telescope",
        "magnet",           "monitor",  "baby carriage", "farm"};

    initscr(); /// to use ncurses
    clear();   /// window clear
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh(); /// window refresh

    for (int j = 0; j < 20; j++) {
        buffer[j] = '\0'; /// to clear array
        answer[j] = '\0';
    }
    for (int j = 0; data[index][j] != '\0'; j++) {
        answer[j] = data[index][j];
    }
    printWordsPractice();
    index++;
    attron(COLOR_PAIR(1));
    draw(9, 20, "    -------------------------------");
    draw(10, 20, "   | Word :                        |");
    draw(11, 20, "    -------------------------------");

    move(10, 33);
    for (int j = 0; answer[j] != '\0'; j++) {
        addch(answer[j]);
    }
    attroff(COLOR_PAIR(1));
    draw(16, 20, "    -------------------------------");
    draw(17, 20, "   | Enter :                       |");
    draw(18, 20, "    -------------------------------");
    move(17, j);

    refresh();
    time(&start);
    while (c != 0x1B) { /// ESC is 0x1B in ASCII
        c = getchar();
        if (c == '\r') { // move to forward of line
            clear();
            printWordsPractice();
            gap = 0;
            per = 0;
            tot = 0;
            red = 0;
            i = 0;
            j = 32;
            while (answer[i] != '\0') {
                if (buffer[i] != answer[i]) {
                    red++;
                }
                tot++;
                i++;
            }
            for (int j = 0; j < 20; j++) {
                buffer[j] = '\0'; /// to clear array
                answer[j] = '\0';
            }
            for (int j = 0; data[index][j] != '\0'; j++) {
                answer[j] = data[index][j];
            }
            if (index == 11)
                index = 0;
            else
                index++;
            attron(COLOR_PAIR(1));
            draw(9, 20, "    -------------------------------");
            draw(10, 20, "   | Word :                        |");
            draw(11, 20, "    -------------------------------");

            move(10, 33);
            for (int j = 0; answer[j] != '\0'; j++) {
                addch(answer[j]);
            }
            attroff(COLOR_PAIR(1));
            draw(16, 20, "    -------------------------------");
            draw(17, 20, "   | Enter :                       |");
            draw(18, 20, "    -------------------------------");
            move(17, j);

            time(&end);
            gap = end - start;
            tasu = 60 * (typing / gap);
            per = (float)tot - (float)red;
            per /= (float)tot;
            per *= 100;
            move(13, 1);
            printw("time : %.1f sec\n", (float)gap);
            move(14, 1);
            printw("ta-su : %.1f\n", tasu);
            move(15, 1);
            printw("accuracy : %.1f %\n", per);
            typing = 0;
            tasu = 1;
            i = 0;
            time(&start);
            refresh();
        } else if (c != 127) {
            if (j == 52)
                continue;
            buffer[i] = c;
            j++;
            i++;
            typing++;
            move(17, j);
            addch(c);
            refresh();
        } else { /// if input is backspacebar
            if (j == 32)
                continue;
            move(17, j);
            addch(*" ");
            move(17, j);
            j--;
            i--;
            typing--;
            refresh();
        }
    }
    endwin();
}
