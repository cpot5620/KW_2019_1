#include <curses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
void printResource(void *none);
void tt_draw(int raw, int col, char *str);
void sIgHandler(int signum);
int sleepTime = 3;
int user_score = 0;
int computer_score = 0;
int *status;
char input;
bool Gameover = false;

void tt_draw(int row, int col, char *str) {
    move(row, 0);
    addstr("                    ");
    move(row, col);
    addstr(str);
    refresh();
}

int game_stage = 1;
pthread_t tttid = 0;
pthread_t ttid = 0;

int Row = 20;
char tt_data[35][20] = {
    "apartment", "autumn",  "balloon",   "beautiful",  "build",      "calendar",
    "cold",      "earth",   "exercise",  "farm",       "finger",     "gentle",
    "ground",    "happy",   "juice",     "knife",      "lamp",       "morning",
    "piano",     "problem", "question",  "restaurant", "service",    "silver",
    "smile",     "table",   "telephone", "think",      "vacation",   "waste",
    "year",      "zoo",     "friend",    "computer",   "competition"};
char tt_answer[35][20] = {
    '\0',
};

void copy(char answer[][20], char data[][20]) {
    for (int i = 0; i < 35; ++i) {
        strcpy(answer[i], data[i]);
    }
}

void printResource(void *none) {
    while (true) {
        if (input == 0x1B)
            pthread_exit(0);
        if (computer_score + user_score == 35) {
            clear();
            attron(COLOR_PAIR(1));
            tt_draw(22, 5, "    -------------------------------");
            tt_draw(23, 5, "   | Enter :                       |");
            tt_draw(24, 5, "    -------------------------------");
            attroff(COLOR_PAIR(1));

            refresh();
            move(23, 18);
            if (user_score > computer_score) {
                mvprintw(4, 4, "__   __            _    _ _         _  ");
                mvprintw(5, 4, "\\ \\ / /           | |  | (_)       | | ");
                mvprintw(6, 4, " \\ V /___  _   _  | |  | |_ _ __   | | ");
                mvprintw(7, 4, "  \\ // _ \\| | | | | |/\\| | | '_ \\  | | ");
                mvprintw(8, 4, "  | | (_) | |_| | \\  /\\  / | | | | |_| ");
                mvprintw(9, 4, "  \\_/\\___/ \\__,_|  \\/  \\/|_|_| |_| (_) ");

                if (game_stage == 3) {
                    mvprintw(4, 4,
                             " _____                                           "
                             "   _ ");
                    mvprintw(5, 4,
                             "|  __ \\                                         "
                             "   | |");
                    mvprintw(6, 4,
                             "| |  \\/ __ _ _ __ ___   ___    _____   _____ _ "
                             "__  | |");
                    mvprintw(
                        7, 4,
                        "| | __ / _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ "
                        "'__| | |");
                    mvprintw(
                        8, 4,
                        "| |_\\ \\ (_| | | | | | |  __/ | (_) \\ V /  __/ |   "
                        " |_|");
                    mvprintw(9, 4,
                             " \\____/\\__,_|_| |_| |_|\\___|  \\___/ \\_/ "
                             "\\___|_|    (_)");
                    game_stage++;
                    sleep(3);
                    pthread_exit(0);
                }

            } else {
                mvprintw(
                    4, 4,
                    " _____                                              _ ");
                mvprintw(
                    5, 4,
                    "|  __ \\                                            | |");
                mvprintw(
                    6, 4,
                    "| |  \\/ __ _ _ __ ___   ___    _____   _____ _ __  | |");
                mvprintw(7, 4,
                         "| | __ / _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ "
                         "'__| | |");
                mvprintw(8, 4,
                         "| |_\\ \\ (_| | | | | | |  __/ | (_) \\ V /  __/ |   "
                         " |_|");
                mvprintw(9, 4,
                         " \\____/\\__,_|_| |_| |_|\\___|  \\___/ \\_/ "
                         "\\___|_|    (_)");
                sleep(3);
                pthread_exit(0);
            }
            tt_draw(15, 12, "Please Wait... Moving to next stage...");

            sleep(3);
            clear();
            attron(COLOR_PAIR(1));
            tt_draw(22, 5, "    -------------------------------");
            tt_draw(23, 5, "   | Enter :                       |");
            tt_draw(24, 5, "    -------------------------------");
            attroff(COLOR_PAIR(1));

            move(23, 18);
            sleepTime--;
            game_stage++;
            user_score = 0;
            computer_score = 0;
            attron(COLOR_PAIR(2));
            mvprintw(20, 45, "-------------------------------");
            mvprintw(21, 45, "    COMPUTER    |      ME      ");
            mvprintw(22, 45, "-------------------------------");
            mvprintw(23, 45, "       %d              %d      ", computer_score,
                     user_score);
            mvprintw(24, 45, "-------------------------------");
            attroff(COLOR_PAIR(2));
            refresh();
        }
        Row = 2;
        move(Row, 0);
        for (int i = 0; i < 35; i++) {
            printw("  %-13s", tt_answer[i]);
            if ((i + 1) % 5 == 0) {
                Row += 2;
                move(Row, 0);
            }
        }
        refresh();
        usleep(50000);
    }
}

void computer(void *none) {
    int random;
    srand((unsigned int)time(NULL));
    sleep(sleepTime);
    while (1) {
        if (input == 0x1B)
            pthread_exit(0);
        random = rand() % 35;
        if (tt_answer[random][0] != '\0') {
            for (int i = 0; i < 20; i++) {
                tt_answer[random][i] = '\0';
            }
            computer_score++;
            attron(COLOR_PAIR(2));
            mvprintw(20, 45, "-------------------------------");
            mvprintw(21, 45, "    COMPUTER    |      ME      ");
            mvprintw(22, 45, "-------------------------------");
            mvprintw(23, 45, "       %d              %d      ", computer_score,
                     user_score);
            mvprintw(24, 45, "-------------------------------");
            attroff(COLOR_PAIR(2));
            refresh();
        }
        sleep(sleepTime);
        if (computer_score + user_score == 35) {
            copy(tt_answer, tt_data);
            sleep(sleepTime);
            if (game_stage == 3) {
                pthread_exit(0);
            }
        }
    }
}

int resourceTake() {
    char buffer[20] = {'\0'};
    int j = 18;
    bool tf;
    int i = 0;
    int answer_index;

    signal(SIGINT, sIgHandler);
    initscr(); /// to use ncurses
    clear();   /// window clear
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh(); /// window refresh
    game_stage = 1;
    Gameover = false;
    sleepTime = 3;
    computer_score = 0;
    user_score = 0;
    input = 0;
    for (int k = 0; k < 25; k++)
        memset(tt_answer[k], '\0', 20);
    copy(tt_answer, tt_data);
    attron(COLOR_PAIR(1));
    tt_draw(22, 5, "    -------------------------------");
    tt_draw(23, 5, "   | Enter :                       |");
    tt_draw(24, 5, "    -------------------------------");

    move(23, j);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(20, 45, "-------------------------------");
    mvprintw(21, 45, "    COMPUTER    |      ME      ");
    mvprintw(22, 45, "-------------------------------");
    mvprintw(23, 45, "       %d              %d      ", computer_score,
             user_score);
    mvprintw(24, 45, "-------------------------------");
    attroff(COLOR_PAIR(2));
    refresh();
    copy(tt_answer, tt_data);
    pthread_create(&tttid, NULL, printResource, NULL);
    pthread_create(&ttid, NULL, computer, NULL);
    while (input != 0x1B) {
        input = getchar();
        if (game_stage == 4 || Gameover) {
            sleep(3);
            break;
        }
        if (input == '\r') { // move to forward of line
            tf = false;
            j = 18;
            for (int k = 0; k < 35; k++) {
                if (strcmp(buffer, tt_answer[k]) == 0 && buffer[0] != '\0') {
                    tf = true;
                    answer_index = k;
                    break;
                }
            }
            if (tf) { /// erase word
                for (int i = 0; i < 20; i++)
                    tt_answer[answer_index][i] = '\0';
                user_score++;
            }

            for (int j = 0; j < 20; j++) {
                buffer[j] = '\0'; /// to clear array
            }
            attron(COLOR_PAIR(1));
            tt_draw(22, 5, "    -------------------------------");
            tt_draw(23, 5, "   | Enter :                       |");
            tt_draw(24, 5, "    -------------------------------");

            move(23, j);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(2));
            mvprintw(20, 45, "-------------------------------");
            mvprintw(21, 45, "    COMPUTER    |      ME      ");
            mvprintw(22, 45, "-------------------------------");
            mvprintw(23, 45, "       %d              %d      ", computer_score,
                     user_score);
            mvprintw(24, 45, "-------------------------------");
            attroff(COLOR_PAIR(1));
            refresh();
            i = 0;
        } else if (input != 127) {
            if (j == 38)
                continue;
            buffer[i] = input;
            j++;
            i++;
            move(23, j);
            addch(input);
            refresh();
        } else { /// if input is backspacebar
            if (j == 18)
                continue;
            move(23, j);
            addch(*" ");
            move(23, j);
            j--;
            i--;
            refresh();
        }
    }
    pthread_cancel(&tttid);
    pthread_cancel(&ttid);
    // pthread_join(ttid, (void **)&status);
    // pthread_join(tttid, (void **)&status);
    curs_set(1);
    clear();
    endwin();

    return 0;
}

void sIgHandler(int signum) {
    if (signum == SIGINT) {
        pthread_cancel(&tttid);
        pthread_cancel(&ttid);
        curs_set(1);
        clear();
        endwin();
        exit(0);
    }
}
