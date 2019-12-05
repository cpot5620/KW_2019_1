#include <ncurses.h>
#include <signal.h>
#include <stdio.h>

int main(void) {
    char c;
    initscr();
    start_color();
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    attron(A_BOLD);
    while (c != 0x1B) {

        clear();
        curs_set(0);
        refresh();
        attron(COLOR_PAIR(3));
        printw("  --"
               "---------------------------------------------------------------"
               "----------\n");
        printw(
            "      ______               _   _            _____           _    "
            "    "
            "     \n");
        printw(
            "      | ___ \\             | | (_)          |_   _|         (_)  "
            "     "
            "     \n");
        printw(
            "      | |_/ / __ __ _  ___| |_ _  ___ ___    | |_   _ _ __  _ _ "
            "__   "
            "__ _ \n");
        printw("      |  __/ '__/ _` |/ __| __| |/ __/ _ \\   | | | | | '_ \\| "
               "| '_ "
               "\\ / _` |\n");
        printw(
            "      | |  | | | (_| | (__| |_| | (_|  __/   | | |_| | |_) | | | "
            "| | "
            "(_| |\n");
        printw("      \\_|  |_|  \\__,_|\\___|\\__|_|\\___\\___|   \\_/\\__, | "
               ".__/|_|_| "
               "|_|\\__, |\n");
        printw(
            "                                                 __/ | |         "
            "    "
            "__/ |\n");
        printw("                                                |___/|_|       "
               "     "
               "|___/ \n");
        printw("  --"
               "---------------------------------------------------------------"
               "----------\n");
        attroff(COLOR_PAIR(3));
        attron(COLOR_PAIR(2));
        draw(13, 20, "    -------------------------------");
        draw(14, 20, "   |       1. Practice words       |");
        draw(15, 20, "    -------------------------------");
        draw(16, 20, "    -------------------------------");
        draw(17, 20, "   |       2. Practice writing     |");
        draw(18, 20, "    -------------------------------");
        draw(19, 20, "    -------------------------------");
        draw(20, 20, "   |       3. Breaking bricks      |");
        draw(21, 20, "    -------------------------------");
        draw(22, 20, "    -------------------------------");
        draw(23, 20, "   |       4. Acid Rain Game       |");
        draw(24, 20, "    -------------------------------");
        attroff(COLOR_PAIR(2));
        refresh();
        c = getch();
        if (c == '2')
            typing();
        else if (c == '1')
            wordPractice();
        else if (c == '3')
            bricks();
        else if (c == '4')
            startGame();
    }
    curs_set(1);
    endwin();
}
