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
                            "knight", "Lake", "Monkey",  "Nope"};

typedef struct node {
    char str[MAX]; // 출력 문자
    int row, col;  // 출력 행열
    int mode;      // 출력 모드
    struct node *link;
} node;

void function(int signum);
void reset();
void *thread_1(void *none);
int itoa(int n, char *str);
void findWord(char *str);
node *makeNode();
void makePlusOne();
void addSQueue(const char *str, int col);
const char *returnWord();
void Sandraw(int row, int col, const char *str);
void startGame();

int hp = 100;
int score = 49;
char scoreText[3] = {0};
int string_location = 0;
int i;
int length = 0;
char hpText[3] = {0};
node *ptr = 0;
char enterText[20] = {0};
int enterHere = 0;
int thread_sleep_time = 2;
pthread_t t1;
void function(int signum) {
    reset();     // Release memory
    curs_set(1); // cursor activation
    endwin();    // consol window close
    exit(1);     // program termination
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
<<<<<<< HEAD
void addSQueue(const char *str, int col) {
  node *temp = 0;
  node *temp2 = 0;

  if (ptr == 0) {
    ptr = makeNode();
    strcpy(ptr->str, str);
    ptr->row = 1;
    ptr->col = col;
  }
  else {
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
=======
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
>>>>>>> 1962d5e3f2cf2efe2a580ce5eecaf99636e4e628
    }

    length++;

    if (length > 15) {
        while (temp->link) {
            temp2 = temp;
            temp = temp->link;
        }

        hp -= strlen(temp->str);

        hpText[2] = '\0';

        itoa(hp, hpText);
        move(17, 55);
        addstr("    ");
        move(17, 55);
        addstr(hpText);

        free(temp);
        temp2->link = 0;

        length--;
    }
}

// Show word on screen
<<<<<<< HEAD
void* thread_1(void *none) {
  int t = thread_sleep_time ;

  while (hp > 0) {
    node *temp = 0;
    addSQueue(returnWord(), (rand() % 40) + 8);
    temp = ptr;
=======
void *thread_1(void *none) {
    int t = sleep_time;

    while (hp > 0) {
        node *temp = 0;
        addQueue(returnWord(), (rand() % 40) + 8);
        temp = ptr;
>>>>>>> 1962d5e3f2cf2efe2a580ce5eecaf99636e4e628

        while (temp) {

<<<<<<< HEAD
			Sandraw(temp->row, temp->col, temp->str);
      temp = temp->link;
    }
=======
            draw(temp->row, temp->col, temp->str);
            temp = temp->link;
        }
>>>>>>> 1962d5e3f2cf2efe2a580ce5eecaf99636e4e628

        move(17, 12);

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
<<<<<<< HEAD
  node *temp = 0;
  temp = ptr;

  while (temp) {
    if (!strcmp(temp->str, str)) {
			score += strlen(temp->str);
			strcpy(temp->str, "");
			if (score > 50 && thread_sleep_time  != 1) {
				thread_sleep_time  = 1;
				pthread_cancel(t1);
				pthread_create(&t1, NULL, &thread_1, NULL);
			}
			if (score > 100) {
				pthread_cancel(t1);
				Sandraw(1 , 0, "                                                             ");
				Sandraw(2 , 0, "                    clear                                    ");
				Sandraw(3 , 0, "                                                             ");
				Sandraw(4 , 0, "                           clear                             ");
				Sandraw(5 , 0, "                                                             ");
				Sandraw(6 , 0, "                                                             ");
				Sandraw(7 , 0, "           clear                                             ");
				Sandraw(8 , 0, "                                          clear              ");
				Sandraw(9 , 0, "                                                             ");
				Sandraw(10, 0, "                                                             ");
				Sandraw(11, 0, "                      clear               clear              ");
				Sandraw(12, 0, "                                                             ");
				Sandraw(13, 0, "                                                             ");
				Sandraw(14, 0, "                                                             ");
				Sandraw(15, 0, "                                                             ");
				Sandraw(16, 0, "   ----------------------------------------------------------");
				Sandraw(17, 0, "   | Enter :                     | Score :      | HP :      |");
				itoa(score, scoreText);
				move(17, 43);
				addstr("      ");
				move(17, 43);
				addstr(scoreText);
			  itoa(hp, hpText);
			  move(17, 55);
			  addstr("     ");
			  move(17, 55);
			  addstr(hpText);
				move(17, 12);
			}
      return;
=======
    node *temp = 0;
    temp = ptr;

    while (temp) {
        if (!strcmp(temp->str, str)) {
            score += strlen(temp->str);
            strcpy(temp->str, "");
            if (score > 50) {
                sleep_time = 1;
                pthread_cancel(t1);
                pthread_create(&t1, NULL, &thread_1, NULL);
            }
            if (score > 100) {
                pthread_cancel(t1);
                draw(1, 0,
                     "                                                         "
                     "    ");
                draw(2, 0,
                     "                    clear                                "
                     "    ");
                draw(3, 0,
                     "                                                         "
                     "    ");
                draw(4, 0,
                     "                           clear                         "
                     "    ");
                draw(5, 0,
                     "                                                         "
                     "    ");
                draw(6, 0,
                     "                                                         "
                     "    ");
                draw(7, 0,
                     "           clear                                         "
                     "    ");
                draw(8, 0,
                     "                                          clear          "
                     "    ");
                draw(9, 0,
                     "                                                         "
                     "    ");
                draw(10, 0,
                     "                                                         "
                     "    ");
                draw(11, 0,
                     "                      clear               clear          "
                     "    ");
                draw(12, 0,
                     "                                                         "
                     "    ");
                draw(13, 0,
                     "                                                         "
                     "    ");
                draw(14, 0,
                     "                                                         "
                     "    ");
                draw(15, 0,
                     "                                                         "
                     "    ");
                draw(16, 0,
                     "   "
                     "---------------------------------------------------------"
                     "-");
                draw(17, 0,
                     "   | Enter :                     | Score :      | HP :   "
                     "   |");
                itoa(score, scoreText);
                move(17, 43);
                addstr("      ");
                move(17, 43);
                addstr(scoreText);
                itoa(hp, hpText);
                move(17, 55);
                addstr("     ");
                move(17, 55);
                addstr(hpText);
                move(17, 12);
            }
            return;
        } else
            temp = temp->link;
>>>>>>> 1962d5e3f2cf2efe2a580ce5eecaf99636e4e628
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
<<<<<<< HEAD
void Sandraw(int row, int col,const char *str) {
  move(row, 0);
  addstr("                                                            ");
  move(row, col);
  addstr(str);
  refresh();
=======
void draw(int row, int col, const char *str) {
    move(row, 0);
    addstr("                                                            ");
    move(row, col);
    addstr(str);
    refresh();
>>>>>>> 1962d5e3f2cf2efe2a580ce5eecaf99636e4e628
}

void startGame() {
    initscr(); /// to use ncurses
    clear();   /// window clear
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh(); /// window refresh
    clear();
    draw(0, 0, "   ----------------------------------------------------------");
    draw(16, 0,
         "   ----------------------------------------------------------");
    draw(17, 0,
         "   | Enter :                     | Score :      | HP :      |");
    draw(18, 0,
         "   ----------------------------------------------------------");

    itoa(score, scoreText);
    move(17, 43);
    addstr("      ");
    move(17, 43);
    addstr(scoreText);
    itoa(hp, hpText);
    move(17, 55);
    addstr("     ");
    move(17, 55);
    addstr(hpText);

<<<<<<< HEAD
  clear();
	Sandraw(0 , 0, "   ----------------------------------------------------------");
  Sandraw(16, 0, "   ----------------------------------------------------------");
  Sandraw(17, 0, "   | Enter :                     | Score :      | HP :      |");
  Sandraw(18, 0, "   ----------------------------------------------------------");

	itoa(score, scoreText);
	move(17, 43);
	addstr("      ");
	move(17, 43);
	addstr(scoreText);
  itoa(hp, hpText);
  move(17, 55);
  addstr("     ");
  move(17, 55);
  addstr(hpText);

  pthread_create(&t1, NULL, &thread_1, NULL);

  while (hp > 0) {
    for (enterHere = 0; enterHere < 20;) {
      int c = getch();

      if (c == '\n') {
        enterText[enterHere] = '\0';
        findWord(enterText);

        for (i = 0; i < 20; i++) {
          enterText[i] = '\0';
        }

        Sandraw(17, 0, "   | Enter :                     | Score :      | HP :      |");
				itoa(score, scoreText);
				move(17, 43);
				addstr("      ");
				move(17, 43);
				addstr(scoreText);
			  itoa(hp, hpText);
			  move(17, 55);
			  addstr("     ");
			  move(17, 55);
			  addstr(hpText);
				move(17, 12);

        break;
      }
      else if (c == 127) {
        if (enterHere > 0) {
          enterText[--enterHere] = '\0';
          move(17, 12);
          addstr("                     ");
          move(17, 12);
          addstr(enterText);
        }
        else {
          move(17, 12);
          addstr("                     ");
=======
    pthread_create(&t1, NULL, &thread_1, NULL);

    while (hp > 0) {
        for (enterHere = 0; enterHere < 20;) {
            int c = getch();

            if (c == '\n') {
                enterText[enterHere] = '\0';
                findWord(enterText);

                for (i = 0; i < 20; i++) {
                    enterText[i] = '\0';
                }

                draw(17, 0,
                     "   | Enter :                     | Score :      | HP :   "
                     "   |");
                itoa(score, scoreText);
                move(17, 43);
                addstr("      ");
                move(17, 43);
                addstr(scoreText);
                itoa(hp, hpText);
                move(17, 55);
                addstr("     ");
                move(17, 55);
                addstr(hpText);
                move(17, 12);

                break;
            } else if (c == 127) {
                if (enterHere > 0) {
                    enterText[--enterHere] = '\0';
                    move(17, 12);
                    addstr("                     ");
                    move(17, 12);
                    addstr(enterText);
                } else {
                    move(17, 12);
                    addstr("                     ");
                }
            } else {
                enterText[enterHere++] = c;
                move(17, 12);
                addstr(enterText);
            }

            refresh();
>>>>>>> 1962d5e3f2cf2efe2a580ce5eecaf99636e4e628
        }
    }
    pthread_join(t1, NULL);

    reset();
    clear();
}
