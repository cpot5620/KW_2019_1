#include <curses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
void makeResource(void *none);
void bb_draw(int raw, int col, char *str);
void sigHandler(int signum);
int count = 1;
int sleep_time = 3000000;
int score_user = 0;
int indx = 0;
char c;
bool gameover = false;

void bb_draw(int row, int col, char *str) {
    move(row, 0);
    addstr("                    ");
    move(row, col);
    addstr(str);
    refresh();
}

int stage = 1;
pthread_t tid = 0;
int row = 20;
char bb_data[][20] = {"culture",       "education",  "symbol",    "hawk",
                      "communication", "foundation", "glory",     "situation",
                      "solution",      "population", "effort",    "competition",
                      "lock",          "master",     "unity",     "nurse",
                      "section",       "schedule",   "row",       "bowl",
                      "giraffe",       "comfort",    "tradition", "effect"};
char bb_answer[][20];
void makeResource(void *none) {
    srand(time(NULL));
    int random;
    while (true) {
        if (c == 0x1B) {
            pthread_exit(0);
        }
        if (score_user >= 10) {
            clear();
            attron(COLOR_PAIR(1));
            bb_draw(22, 20, "    -------------------------------");
            bb_draw(23, 20, "   | Enter :                       |");
            bb_draw(24, 20, "    -------------------------------");
            attroff(COLOR_PAIR(1));
            move(23, 32);
            bb_draw(
                1, 1,
                " _____                             _         _       _   _   "
                "            _ ");
            bb_draw(
                2, 1,
                "/  __ \\                           | |       | |     | | (_)  "
                "           | |");
            bb_draw(
                3, 1,
                "| /  \\/ ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  "
                "___  _ __   | |");
            bb_draw(
                4, 1,
                "| |    / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| "
                "|/ "
                "_ \\| '_ \\  | |");
            bb_draw(
                5, 1,
                "| \\__/\\ (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | "
                "(_) | | | | |_|");
            bb_draw(6, 1,
                    " \\____/\\___/|_| |_|\\__, |_|  "
                    "\\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_| (_)");
            bb_draw(
                7, 1,
                "                    __/ |                                    "
                "              ");
            bb_draw(
                8, 1,
                "                   |___/                                     "
                "              ");
            if (stage == 4) {
                bb_draw(10, 33, "Game Finish !");
                sleep(3);
                for (int k = 0; k < indx; k++)
                    memset(bb_answer[k], '\0', sizeof(bb_answer[k]));
                stage++;
                pthread_exit(0);
            }
            bb_draw(10, 22, "Please Wait... Moving to next stage...");
            sleep(3);
            clear();
            attron(COLOR_PAIR(1));
            bb_draw(22, 20, "    -------------------------------");
            bb_draw(23, 20, "   | Enter :                       |");
            bb_draw(24, 20, "    -------------------------------");
            attroff(COLOR_PAIR(1));
            move(23, 32);
            for (int k = 0; k < indx; k++)
                memset(bb_answer[k], '\0', sizeof(bb_answer[k]));
            count = 0;
            indx = 0;
            sleep_time -= 800000;
            stage++;
            score_user = 0;
            refresh();
        }
        for (int i = 0; i <= 21; i++) {
            bb_draw(i, 32, "                            ");
        }
        row = 20;
        random = rand() % 24;
        for (int i = 0; bb_data[random][i] != '\0'; i++)
            bb_answer[indx][i] = bb_data[random][i];
        for (int i = 0; i < count; i++) {
            if (row < 0) {
                clear();
                bb_draw(
                    1, 9,
                    " _____                        _____                      "
                    "  ");
                bb_draw(
                    2, 9,
                    "|  __ \\                      |  _  |                     "
                    "  ");
                bb_draw(
                    3, 9,
                    "| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __       "
                    "  ");
                bb_draw(
                    4, 9,
                    "| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__| "
                    "     "
                    "  ");
                bb_draw(
                    5, 9,
                    "| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |    "
                    " _ _ "
                    "_ ");
                bb_draw(
                    6, 9,
                    " \\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|    "
                    "(_|_|_)");
                gameover = true;
                pthread_exit(0);
            }
            if (bb_answer[i][0] == '\0')
                continue;
            bb_draw(row - 1, 32, "----------------");
            bb_draw(row, 35, "                ");
            move(row, 35);
            for (int j = 0; bb_answer[i][j] != '\0'; j++) {
                addch(bb_answer[i][j]);
            }
            bb_draw(row + 1, 32, "----------------");
            row -= 3;
        }
        indx++;
        count++;
        usleep(sleep_time);
    }
}

int bricks() {
    char buffer[20] = {'\0'};
    int j = 32;
    bool tf;
    int i = 0;
    int answer_index;
    signal(SIGINT, sigHandler);
    initscr(); /// to use ncurses
    clear();   /// window clear
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh(); /// window refresh
    gameover = false;
    stage = 1;
    sleep_time = 3000000;
    count = 1;
    indx = 0;
    c = 0;
    for (int k = 0; k < 25; k++)
        memset(bb_answer[k], '\0', sizeof(bb_answer[k]));
    attron(COLOR_PAIR(1));
    bb_draw(22, 20, "    -------------------------------");
    bb_draw(23, 20, "   | Enter :                       |");
    bb_draw(24, 20, "    -------------------------------");
    move(23, j);
    attroff(COLOR_PAIR(1));
    refresh();
    pthread_create(&tid, NULL, makeResource, NULL);
    while (c != 0x1B) {
        c = getchar();
        if (stage == 5 || gameover) {
            sleep(3);
            break;
        }
        if (c == '\r') { // move to forward of line
            tf = false;
            j = 32;
            for (int k = 0; k < indx; k++) {
                if (strcmp(buffer, bb_answer[k]) == 0) {
                    tf = true;
                    answer_index = k;
                    break;
                }
            }
            if (tf) {
                memset(bb_answer[answer_index], '\0',
                       sizeof(bb_answer[answer_index]));
                int erase_row = abs(score_user - answer_index);
                bb_draw(20 - ((erase_row)*3 - 1), 32,
                        "                            ");
                bb_draw(20 - ((erase_row)*3), 32,
                        "                            ");
                bb_draw(20 - ((erase_row)*3 + 1), 32,
                        "                            ");
                score_user++;
            }

            for (int j = 0; j < 20; j++) {
                buffer[j] = '\0'; /// to clear array
            }
            attron(COLOR_PAIR(1));
            bb_draw(22, 20, "    -------------------------------");
            bb_draw(23, 20, "   | Enter :                       |");
            bb_draw(24, 20, "    -------------------------------");
            move(23, j);
            attroff(COLOR_PAIR(1));
            refresh();
            i = 0;
        } else if (c != 127) {
            if (j == 52)
                continue;
            buffer[i] = c;
            j++;
            i++;
            move(23, j);
            addch(c);
            refresh();
        } else { /// if input is backspacebar
            if (j == 32)
                continue;
            move(23, j);
            addch(*" ");
            move(23, j);
            j--;
            i--;
            refresh();
        }
    }
    pthread_detach(&tid);
    curs_set(1);
    clear();
    endwin();

    return 0;
}

void sigHandler(int signum) {
    if (signum == SIGINT) {
        pthread_cancel(&tid);
        curs_set(1);
        clear();
        endwin();
        exit(0);
    }
}
