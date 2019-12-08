#include <curses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MAX 100

const char *database[15] = {"Apple",  "Jung", "Cocaine", "Hello", "Elite",
                            "Fail",   "Game", "Halo",    "Icon",  "Jail",
                            "Knight", "Lake", "Monkey",  "Nope"};

typedef struct node {
    char str[MAX]; // output string
    int row, col;  // row col
    struct node *link;
} node;

void function(int signum);
void reset();
void *thread_1(void *none);
int itoa(int n, char *str);
void findWord(char *str);
node *makeNode();
void makePlusOne();
void addQueue(const char *str, int col);
const char *returnWord();
void sdraw(int row, int col, const char *str);
void startGame();

int userHp = 100;
int score = 0;
char scoreText[3] = {0};
int string_location = 0;
int i;
int length = 0;
char cC;
char hpText[3] = {0};
node *ptr = 0;
char enterText[20] = {0};
int enterHere = 0;
int psleep_time = 2;
pthread_t t1;

void function(int signum) {
    if (signum == SIGINT) {
        pthread_cancel(&t1);
        reset();
        curs_set(1);
        clear();
        endwin();
        exit(0);
    }
}

// Queue empty out and memory allocation
void reset() {
    node *temp = NULL;
    node *temp2 = NULL;

    temp = ptr;

    if (temp != NULL) {
        while (length > 0) {
            temp = ptr;

            while (temp->link) {
                temp2 = temp;
                temp = temp->link;
            }

            free(temp);

            if (temp2 != NULL)
                temp2->link = NULL;

            length--;
            temp2 = NULL;
        }
        ptr = NULL;
    }
}

// Put in queue
void addQueue(const char *str, int col) {
    node *temp = 0;
    node *temp2 = 0;

    if (ptr == 0) {
        ptr = makeNode();
        strcpy(ptr->str, str);
        ptr->row = 1;
        ptr->col = col;
    } else {
        temp = makeNode();
        strcpy(temp->str, str);
        temp->row = 1;
        temp->col = col;
        temp->link = ptr;
        ptr = temp;
        makePlusOne();
    }

    length++;

    if (length > 15) {
        while (temp->link) {
            temp2 = temp;
            temp = temp->link;
        }

        userHp -= strlen(temp->str);

        hpText[2] = '\0';

        itoa(userHp, hpText);
        move(17, 64);
        addstr("    ");
        move(17, 64);
        addstr(hpText);

        free(temp);
        temp2->link = 0;

        length--;
    }
}

// Show word on screen
void *thread_1(void *none) {
    int t = psleep_time;

    while (userHp > 0) {

        node *temp = 0;
        addQueue(returnWord(), (rand() % 40) + 17);
        temp = ptr;

        while (temp) {

            sdraw(temp->row, temp->col, temp->str);
            temp = temp->link;
        }

        move(17, 21);

        sleep(t);
    }
}

// integer to string
int itoa(int n, char *str) {
    int temp;

    if (n <= 0) {
        strcpy(str, "0");
        return 0;
    }

    temp = itoa(n / 10, str);

    *(str + temp) = 48 + (n % 10);

    return temp + 1;
}

// finding input string and deleting in queue
void findWord(char *str) {
    node *temp = 0;
    temp = ptr;

    while (temp) {
        if (!strcmp(temp->str, str)) {
            score += strlen(temp->str);
            strcpy(temp->str, "");
            if (score > 50 && psleep_time != 1) {
                psleep_time = 1;
                pthread_cancel(t1);
                pthread_create(&t1, NULL, &thread_1, NULL);
            }
            if (score > 99) {
                pthread_cancel(t1);
                sdraw(1, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(2, 0,
                      "                             clear                      "
                      "          "
                      "    ");
                sdraw(3, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(4, 0,
                      "                                    clear               "
                      "          "
                      "    ");
                sdraw(5, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(6, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(7, 0,
                      "                    clear                               "
                      "          "
                      "    ");
                sdraw(8, 0,
                      "                                                   "
                      "clear          "
                      "    ");
                sdraw(9, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(10, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(11, 0,
                      "                               clear               "
                      "clear          "
                      "    ");
                sdraw(12, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(13, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(14, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(15, 0,
                      "                                                        "
                      "          "
                      "    ");
                sdraw(
                    16, 0,
                    "            "
                    "---------------------------------------------------------"
                    "-");
                sdraw(17, 0,
                      "            | Enter :                     | Score :     "
                      " | HP :   "
                      "   |");
                itoa(score, scoreText);
                move(17, 52);
                addstr("      ");
                move(17, 52);
                addstr(scoreText);
                itoa(userHp, hpText);
                move(17, 64);
                addstr("     ");
                move(17, 64);
                addstr(hpText);
                move(17, 21);
                int a;
                while (a != 0x1B) {
                    a = getch();
                    refresh();
                    cC = 0x1B;
                }
            }
            return;
        } else
            temp = temp->link;
    }
}

// creating node
node *makeNode() {
    node *temp = 0;

    temp = (node *)malloc(sizeof(*temp));
    temp->link = 0;
}

// down one line
void makePlusOne() {
    node *temp = ptr->link;

    while (temp) {
        temp->row += 1;
        temp = temp->link;
    }
}

// selecting word in database
const char *returnWord() {

    if (string_location == 13)
        string_location = 0;
    else
        string_location++;

    return database[string_location];
}

//
void sdraw(int row, int col, const char *str) {
    move(row, 0);
    addstr("                                                            ");
    move(row, col);
    addstr(str);
    refresh();
}

void startGame() {
    signal(SIGINT, function);
    initscr(); /// to use ncurses
    clear();   /// window clear
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    curs_set(0);
    refresh(); /// window refresh
    clear();

    score = 0;
    cC = 0;
    userHp = 100;
    psleep_time = 2;
    ptr = 0;
    database[0] = "Apple";
    database[1] = "Kong";
    database[2] = "Cocaine";
    database[3] = "Hello";
    database[4] = "Elite";
    database[5] = "Fail";
    database[6] = "Game";
    database[7] = "Halo";
    database[8] = "Icon";
    database[9] = "Jail";
    database[10] = "Knight";
    database[11] = "Lake";
    database[12] = "Monkey";
    database[13] = "Nope";
    database[14] = "Lamp";

    attron(COLOR_PAIR(3));
    sdraw(0, 0,
          "            "
          "----------------------------------------------------------");

    sdraw(16, 0,
          "            "
          "----------------------------------------------------------");
    sdraw(17, 0,
          "            | Enter :                     | Score :      | HP :     "
          " |");
    sdraw(18, 0,
          "            "
          "----------------------------------------------------------");
    attroff(COLOR_PAIR(3));
    itoa(score, scoreText);
    move(17, 52);
    addstr("      ");
    move(17, 52);
    addstr(scoreText);
    itoa(userHp, hpText);
    move(17, 64);
    addstr("     ");
    move(17, 64);
    addstr(hpText);

    pthread_create(&t1, NULL, &thread_1, NULL);

    while (userHp > 0) {
        if (cC == 0x1B) {
            pthread_cancel(t1);
            refresh();
            endwin();
            cC = 0;
            break;
        }
        for (enterHere = 0; enterHere < 20 && cC != 0x1B;) {
            cC = getchar();

            if (cC == '\r') {
                enterText[enterHere] = '\0';
                findWord(enterText);

                for (i = 0; i < enterHere + 1; i++) {
                    enterText[i] = '\0';
                }
                attron(COLOR_PAIR(3));
                sdraw(17, 0,
                      "            | Enter :                     | Score :     "
                      " | HP :   "
                      "   |");
                attroff(COLOR_PAIR(3));
                itoa(score, scoreText);
                move(17, 52);
                addstr("   ");
                move(17, 52);
                addstr(scoreText);
                itoa(userHp, hpText);
                move(17, 64);
                addstr("   ");
                move(17, 64);
                addstr(hpText);
                move(17, 21);

                break;
            } else if (cC == 127) {
                if (enterHere > 0) {
                    enterText[--enterHere] = '\0';
                    move(17, 21);
                    addstr("                     ");
                    move(17, 21);
                    addstr(enterText);
                } else {
                    move(17, 21);
                    addstr("                   ");
                }
            } else {
                if (enterHere < 19) {
                    enterText[enterHere++] = cC;
                    move(17, 21);
                    addstr(enterText);
                }
            }
            refresh();
        }
    }

    pthread_join(t1, NULL);
    curs_set(1);
    reset();
    clear();
}
