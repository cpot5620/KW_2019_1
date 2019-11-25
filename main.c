#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// user input number to select the writing
int choose() {
    int choice;
    printf("choose number\n");
    printf("1. Guliver's Travels\n");
    printf("2. Rapunzel\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    fflush(stdin);
    return choice;
}
// store txt file line by line to array
char **alloArray(FILE *fp) {
    int lines_allocated = 128;
    int max_line_len = 100;

    /* Allocate lines of text */
    char **words = (char **)malloc(sizeof(char *) * lines_allocated);
    if (words == NULL) {
        fprintf(stderr, "Out of memory (1).\n");
        exit(1);
    }
    for (int i = 0; 1; i++) {
        int j;

        /* Have we gone over our line allocation? */
        if (i >= lines_allocated) {
            int new_size;

            /* Double our allocation and re-allocate */
            new_size = lines_allocated * 2;
            words = (char **)realloc(words, sizeof(char *) * new_size);
            if (words == NULL) {
                fprintf(stderr, "Out of memory.\n");
                exit(3);
            }
            lines_allocated = new_size;
        }
        /* Allocate space for the next line */
        words[i] = malloc(max_line_len);
        if (words[i] == NULL) {
            fprintf(stderr, "Out of memory (3).\n");
            exit(4);
        }
        if (fgets(words[i], max_line_len - 1, fp) == NULL)
            break;

        /* Get rid of CR or LF at end of line */
        for (j = strlen(words[i]) - 1;
             j >= 0 && (words[i][j] == '\n' || words[i][j] == '\r'); j--)
            ;
        words[i][j + 1] = '\0';
    }
    return words;
}
// open the selected txt file
char **word(int n) {
    int lines_allocated = 128;
    int max_line_len = 100;
    char **words;

    if (n == 1) {
        FILE *fp = fopen("Guliver'sTravels.txt", "r");
        if (fp == NULL) {
            fprintf(stderr, "Error opening file.\n");
            exit(2);
        }

        words = alloArray(fp);
        /* Close file */
        fclose(fp);
    } else if (n == 2) {
        FILE *fp = fopen("Rapunzel.txt", "r");
        if (fp == NULL) {
            fprintf(stderr, "Error opening file.\n");
            exit(2);
        }

        words = alloArray(fp);
        /* Close file */
        fclose(fp);
    }

    return words;
}
// print 10 lines
void printWriting(int n) {
    char **words = word(n);
    int line = 0;
    // just print 10 lines
    for (int j = 0; j < 10; ++j) {
        move(line, 0);
        addstr(words[j]);
        line += 2;
    }
    int i = 23;
    for (; i >= 0; i--)
        free(words[i]);
    free(words);
}

int main() {
    char **words;
    int i = 0;
    int j = 0;
    int m = 0;
    char c;
    char buffer[100];
    int line = 1;
    time_t start = 0, end = 0;
    float gap = 0, tasu = 1;
    int typing = 0;
    int choice;
    int red = 0;
    float per;
    // read a number to select the writing
    choice = choose();
    words = word(choice);

    initscr(); /// to use ncurses
    clear();   /// window clear
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh(); /// window refresh

    for (j = 0; j < 100; j++)
        buffer[j] = '\0'; /// to clear array

    printWriting(choice);
    time(&start);
    move(1, 0);

    refresh(); // window refresh

    while (c != 0x1B) { /// ESC is 0x1B in ASCII
        c = getchar();
        if (c == '\r') { // move to forward of line
            line += 2;
            m += 1;
            move(line, 0);
            printf("\r");
            refresh();
            i = 0;

            for (j = 0; j < 100; j++) {
                buffer[j] = '\0'; /// buffer clear
            }
            if (line == 21) {
                time(&end);
                gap = end - start;
                tasu = 60 * (typing / gap);
                per = (float)typing - (float)red;
                per /= (float)typing;
                per *= 100;

                // move(24, 1);
                printw("time : %.1f sec\n", (float)gap);
                printw("ta-su : %.1f\n", tasu);
                printw("accuracy : %.1f %\n", per);

                printw("if you want to quit, press key 'ESC'\n");
            }
        } else {
            if (c != 127) {
                buffer[i] = c;
                addch(c);
                if (buffer[i] != words[m][i]) {
                    move(line - 1, i);
                    attron(COLOR_PAIR(1));
                    addch(words[m][i]);
                    attroff(COLOR_PAIR(1));
                    move(line, i + 1);
                    red++;
                }
                i++;
                typing++;
                refresh();
            } else { /// if input is backspacebar
                if (i == 0)
                    continue;
                i--;
                typing--;
                red--;
                move(line, i);
                addch(*" ");
                move(line - 1, i);
                addch(words[m][i]);
                move(line, i);
                refresh();
            }
        }
    }

    i = 23;
    /* Good practice to free memory */
    for (; i >= 0; i--)
        free(words[i]);
    free(words);
    endwin();
}
