#include <ncurses.h>
#include <stdio.h>

int main(void) {
    char c;
    initscr();

    while (c != 0x1B) {
        clear();
        refresh();
        printw("---------------------------------------------------------------"
               "----------\n");
        printw("______               _   _            _____           _        "
               "     \n");
        printw(
            "| ___ \\             | | (_)          |_   _|         (_)       "
            "     \n");
        printw("| |_/ / __ __ _  ___| |_ _  ___ ___    | |_   _ _ __  _ _ __   "
               "__ _ \n");
        printw("|  __/ '__/ _` |/ __| __| |/ __/ _ \\   | | | | | '_ \\| | '_ "
               "\\ / _` |\n");
        printw("| |  | | | (_| | (__| |_| | (_|  __/   | | |_| | |_) | | | | | "
               "(_| |\n");
        printw("\\_|  |_|  \\__,_|\\___|\\__|_|\\___\\___|   \\_/\\__, | "
               ".__/|_|_| "
               "|_|\\__, |\n");
        printw("                                           __/ | |             "
               "__/ |\n");
        printw("                                          |___/|_|            "
               "|___/ \n");
        printw("---------------------------------------------------------------"
               "----------\n");

        printw("1. Practic writing\n");
        printw("2. SansungBe game\n");
        printw("3. Practice words\n");
        c = getch();
        if (c == '1')
            typing();
        else if (c == '3')
            wordPractice();
    }
    endwin();
}
