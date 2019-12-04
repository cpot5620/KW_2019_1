#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <curses.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX 100
const char *database[15] = { "Apple", "Jung", "Cocaine", "Hello", "Elite", "Fail", "Game", "Halo", "Icon", "Jail", "knight", "Lake", "Monkey", "Nope" };

typedef struct node {
	char str[MAX]; // 출력 문자
	int row, col; // 출력 행열
	int mode; // 출력 모드
	node *link;
}node;

void function(int signum);
void reset();
void* thread_1(void *none);
int itoa(int n, char *str);
void findWord(char *str);
node *makeNode();
void makePlusOne();
void addQueue(const char *str, int col);
const char *returnWord();
void draw(int row, int col, const char *str);
void startGame();

int hp = 100;
int string_location = 0;
int i;
int length = 0;
char hpText[3] = { 0 };
node *ptr = 0;
char enterText[20] = { 0 };
int enterHere = 0;
int sleep_time = 1;

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

// Show word on screen
void* thread_1(void *none) {
  int t = sleep_time;

  while (hp > 0) {
    node *temp = 0;
    addQueue(returnWord(), (rand() % 40) + 8);
    temp = ptr;

    while (temp) {
      draw(temp->row, temp->col, temp->str);
      temp = temp->link;
    }

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

  *(str + temp) = 48 + (n %10);

  return temp + 1;
}

// finding input string and deleting in queue
void findWord(char *str) {
  node *temp = 0;
  temp = ptr;

  while (temp) {
    if (!strcmp(temp->str, str)) {
      strcpy(temp->str, "");
      return;
    }
    else
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
  node *temp = ptr -> link;

  while (temp) {
    temp->row += 1;
    temp = temp->link;
  }
}

// Put in queue
void addQueue(char *str, int col) {
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

// selecting word in database
const char *returnWord() {

  if (string_location == 13)
    string_location = 0;
  else string_location++;

  return database[string_location];
}

//
void draw(int row, int col, char *str) {
  move(row, 0);
  addstr("                                                            ");
  move(row, col);
  addstr(str);
  refresh();
}

void startGame() {
  pthread_t t1;
	int test = 5;
	int *testtest;

  clear();

  draw(16, 0, "   ---------------------------------------------------------");
  draw(17, 0, "   | Enter :                                    | HP :     |");
  draw(18, 0, "   ---------------------------------------------------------");

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

        draw(17, 0, "   | Enter :                                        | HP :     |");
        move(17, 12);

        break;
      }
      else if (c == 127) {
        if (enterHere > 0) {
          enterText[--enterHere] = '\0';
          move(17, 12);
          addstr("                 ");
          move(17, 12);
          addstr(enterText);
        }
        else {
          move(17, 12);
          addstr("                 ");
        }
      }
      else {
        enterText[enterHere++] = c;
        move(17, 12);
        addstr(enterText);
      }

      refresh();
    }
  }
  pthread_join(t1, NULL);

  reset();
  clear();
}

int main(int args, const char *argv[]) {
	startGame();
}
