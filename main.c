#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// define screen requirements
const int sc_w = 10;
const int sc_h = 10;
char snake = '*';
int length = 0;
int head_row;
int head_column;

int *SetZeroToArray(int (*map)[sc_h], int size_width, int size_height);

void PrintScreen(int (*array)[sc_h]);

void Draw(int (*array)[sc_h]);

void PrintScreenDebug(int (*array)[sc_h]);

int CreateFirstSnake(int (*map)[sc_h]);


int main() {
    int array[sc_w][sc_h];
    int *map;

    map = SetZeroToArray(array, sc_w, sc_h);
    CreateFirstSnake(map);

    Draw(map);
    printf("\nlength: %d", length);
    PrintHead();
    //PrintScreen(map);
    getch();
    return 0;
}

int CreateFirstSnake(int (*map)[sc_h]) {
    int x, y;

    srand(time(NULL));
    x = rand() % sc_w;
    y = rand() % sc_h;
    head_row = x;
    map[x][y] = 1;
    length++;
    if (y + 1 < 10) {
        map[x][y + 1] = 1;
        length++;
        if (y + 2 < 10) {
            map[x][y + 2] = 1;
            length++;
            head_column = y + 2;
            return 1;
        } else {
            if (y - 1 > 0) {
                map[x][y - 1] = 1;
                length++;
                head_column = y +1;
                return 1;
            }
        }
    } else {
        if (y - 1 > 0) {
            map[x][y - 1] = 1;
            length++;
            if (y - 2 > 0) {
                map[x][y - 2] = 1;
                length++;
                head_column = y;
                return 1;
            }
        }
    }
    return 0;
}

int *SetZeroToArray(int (*map)[sc_h], int size_width, int size_height) {
    for (int i = 0; i < size_width; ++i) {
        for (int j = 0; j < size_height; ++j) {
            *(*(map + i) + j) = 0;
        }
    }
    return *map;
}

void PrintScreenDebug(int (*array)[sc_h]) {
    printf("\n");
    for (int i = 0; i < sc_w; ++i) {
        for (int j = 0; j < sc_h; ++j) {
            printf("#[%d][%d] =>%d  ", i, j, *(*(array + i) + j));
        }
        printf("\n");
    }
}

void PrintScreen(int (*array)[sc_h]) {
    for (int i = 0; i < sc_w; ++i) {
        for (int j = 0; j < sc_h; ++j) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

void printSnake() {
    printf("%c", snake);
}

void Draw(int (*array)[sc_h]) {
    for (int i = 0; i < sc_h; ++i) {
        for (int j = 0; j < sc_w; ++j) {
            if (array[i][j] == 1) {
                printSnake();
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
void PrintHead(){
    printf("\nrow: %d column: %d\n",head_row,head_column);
}