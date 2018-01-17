#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// define screen requirements
const int sc_w = 10;
const int sc_h = 10;
char snake = '*';
int length = 0, is_loop = 1;
int head_row, end_row;
int head_column, end_column;

int *SetZeroToArray(int (*map)[sc_h], int size_width, int size_height);

void PrintScreen(int (*array)[sc_h]);

void PrintEnd();

void Draw(int (*array)[sc_h]);

void CheckExitedCell(int (*map)[sc_h], int h_row, int h_col, char control);

void PrintScreenDebug(int (*array)[sc_h]);

int CreateFirstSnake(int (*map)[sc_h]);

void Move(int (*map)[sc_h], int head_row, int head_column, char operation);

void CheckControl(int (*map)[sc_h], char control);


int main() {
    int array[sc_w][sc_h];
    int *map;

    map = SetZeroToArray(array, sc_w, sc_h);
    CreateFirstSnake(map);

    Draw(map);
    while (is_loop == 1) {
        char control = getch();
        //Move(map, head_row, head_column);
        CheckControl(map, control);
        Draw(map);
        printf("\nlength: %d", length);
        PrintHead();
        PrintEnd();
        PrintScreen(map);
    }
    printf("\nGame Over!!");
    getch();
    return 0;
}

void Move(int (*map)[sc_h], int phead_row, int phead_column, char operation) {
    int fake_row, fake_column;
    int is_continue = 0;
    switch (operation) {
        case 'd':
            if (map[phead_row + 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row + 1;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'w';
            } else if (map[phead_row - 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row - 1;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 's';
            } else if (map[phead_row][phead_column - 1] == 1) {
                fake_column = phead_column - 1;
                fake_row = phead_row;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'd';
            }
            break;
        case 's':
            if (map[phead_row - 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row - 1;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 's';
            } else if (map[phead_row][phead_column + 1] == 1) {
                fake_column = phead_column + 1;
                fake_row = phead_row;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'a';
            } else if (map[phead_row][phead_column - 1] == 1) {
                fake_column = phead_column - 1;
                fake_row = phead_row;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'd';
            }
            break;
        case 'w':
            if (map[phead_row + 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row + 1;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'w';
            } else if (map[phead_row][phead_column + 1] == 1) {
                fake_column = phead_column + 1;
                fake_row = phead_row;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'a';
            } else if (map[phead_row][phead_column - 1] == 1) {
                fake_column = phead_column - 1;
                fake_row = phead_row;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'd';
            }
            break;
        case 'a':
            if (map[phead_row - 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row - 1;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 's';
            } else if (map[phead_row][phead_column + 1] == 1) {
                fake_column = phead_column + 1;
                fake_row = phead_row;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'a';
            } else if (map[phead_row + 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row + 1;
                CheckExitedCell(map, phead_row, phead_column, operation);
                is_continue = 1;
                operation = 'w';
            }
            break;
        default:
            is_continue = 0;
            break;
    }

    if (is_continue == 1) {
        map[fake_row][fake_column] = 0;
        Move(map, fake_row, fake_column, operation);
    }
}

void CheckControl(int (*map)[sc_h], char control) {
    int pre_row = head_row;
    int pre_column = head_column;
    int is_true_control = 1;
    switch (control) {
        case 'w':
            head_row--;
            break;
        case 's':
            head_row++;
            break;
        case 'd':
            head_column++;
            break;
        case 'a':
            head_column--;
            break;
        case 'x':
            is_true_control = 0;
            is_loop = 0;
            break;
        default:
            is_true_control = 0;
            break;
    }
    if (is_true_control == 1) {
        if (head_column <= 9 && head_column >= 0 && head_row <= 9 && head_row >= 0) {
            map[pre_row][pre_column] = 0;
            Move(map, pre_row, pre_column, control);
            CheckExitedCell(map, head_row, head_column, control);
        } else {
            is_loop = 0;

        }
    }

}

void CheckExitedCell(int (*map)[sc_h], int h_row, int h_col, char control) {
    if (map[h_row][h_col] == 1) {
        switch (control) {
            case 'w':
                CheckExitedCell(map, h_row - 1, h_col, control);
                break;
            case 's':
                CheckExitedCell(map, h_row + 1, h_col, control);
                break;
            case 'd':
                CheckExitedCell(map, h_row, h_col + 1, control);
                break;
            case 'a':
                CheckExitedCell(map, h_row, h_col - 1, control);
                break;
        }
    } else {
        map[h_row][h_col] = 1;
    }
}

int CreateFirstSnake(int (*map)[sc_h]) {
    int x, y;

    srand(time(NULL));
    x = rand() % sc_w;
    y = rand() % sc_h;
    head_row = x;
    end_row = x;
    map[x][y] = 1;
    length++;
    if (y + 1 < 10) {
        map[x][y + 1] = 1;
        length++;
        if (y + 2 < 10) {
            map[x][y + 2] = 1;
            length++;
            head_column = y + 2;
            end_column = y;
            return 1;
        } else {
            if (y - 1 > 0) {
                map[x][y - 1] = 1;
                length++;
                end_column = y - 1;
                head_column = y + 1;
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
                end_column = y - 2;
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
    system("cls");
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

void PrintHead() {
    printf("\nrow: %d column: %d\n", head_row, head_column);
}

void PrintEnd() {
    printf("row: %d column: %d\n", end_row, end_column);
}

void delay(int number_of_seconds) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}
