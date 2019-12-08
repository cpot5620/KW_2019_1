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
    start_color();
    attron(COLOR_PAIR(3));
    printw("  --"
           "---------------------------------------------------------------"
           "----------\n");
    printw("        _    _               _        ______               _ "
           "  _  "
           "        \n");
    printw("       | |  | |             | |       | ___ \\             | "
           "| (_) "
           "        \n");
    printw("       | |  | | ___  _ __ __| |___    | |_/ / __ __ _  ___| "
           "|_ _  "
           "___ ___ \n");
    printw("       | |/\\| |/ _ \\| '__/ _` / __|   |  __/ '__/ _` |/ "
           "__| __| "
           "|/ __/ _ \\\n");
    printw("       \\  /\\  / (_) | | | (_| \\__ \\   | |  | | | (_| | "
           "(__| "
           "|_| | "
           "(_|  __/\n");
    printw("        \\/  \\/ \\___/|_|  \\__,_|___/   \\_|  |_|  "
           "\\__,_|\\___|\\__|_|\\___\\___|\n");
    printw("  --"
           "---------------------------------------------------------------"
           "----------\n");
    attroff(COLOR_PAIR(3));
}
int wordPractice() {
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
    attron(COLOR_PAIR(2));
    draw(10, 20, "    -------------------------------");
    draw(11, 20, "   | Word :                        |");
    draw(12, 20, "    -------------------------------");

    move(11, 33);
    for (int j = 0; answer[j] != '\0'; j++) {
        addch(answer[j]);
    }
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    draw(18, 20, "    -------------------------------");
    draw(19, 20, "   | Enter :                       |");
    draw(20, 20, "    -------------------------------");
    move(19, j);
    attroff(COLOR_PAIR(3));

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
            attron(COLOR_PAIR(2));
            draw(10, 20, "    -------------------------------");
            draw(11, 20, "   | Word :                        |");
            draw(12, 20, "    -------------------------------");

            move(11, 33);
            for (int j = 0; answer[j] != '\0'; j++) {
                addch(answer[j]);
            }
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(3));
            draw(18, 20, "    -------------------------------");
            draw(19, 20, "   | Enter :                       |");
            draw(20, 20, "    -------------------------------");
            move(19, j);
            attroff(COLOR_PAIR(3));

            time(&end);
            gap = end - start;
            tasu = 60 * (typing / gap);
            per = (float)tot - (float)red;
            per /= (float)tot;
            per *= 100;
            move(18, 59);
            printw("time : %.1f sec\n", (float)gap);
            move(19, 59);
            printw("ta-su : %.1f\n", tasu);
            move(20, 59);
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
            move(19, j);
            addch(c);
            refresh();
        } else { /// if input is backspacebar
            if (j == 32)
                continue;
            move(19, j);
            addch(*" ");
            move(19, j);
            j--;
            i--;
            typing--;
            refresh();
        }
    }
    endwin();
}
