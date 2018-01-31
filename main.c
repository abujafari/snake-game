/**
 * Developed with <3 by Mohamad Abujafari
 * 9624463
 * Mr.Mehdi Zamanian
 **/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// define screen requirements
const int sc_w = 15;
const int sc_h = 15;
char snake = '*';
int length = 0, is_loop = 1;
int head_row, end_row;
int head_column, end_column;
int time_level = 1000;
int move_count = 0;
int flag_exit = 0;
int sum_food = 0;

void delay(int milliseconds);

void AddToEndSnake(int (*snake)[sc_h], char control);

int CreateChanceNum();

int *SetZeroToArray(int (*map)[sc_h], int size_width, int size_height);

void PrintScreen(int (*array)[sc_h]);

void PrintEnd();

void Draw(int (*array)[sc_h]);

void CheckExitedCell(int (*map)[sc_h], int h_row, int h_col, char control);

void PrintScreenDebug(int (*array)[sc_h]);

int CreateFirstSnake(int (*map)[sc_h]);

int CheckEndToMove(int (*map)[sc_h], int row, int col);

void CountFood(int (*map)[sc_h]);

void CreateFood(int (*snake)[sc_h]);

void Move(int (*map)[sc_h], int phead_row, int phead_column, char operation);

void CheckControl(int (*map)[sc_h], char control);

int waitFor(unsigned int secs);

int main() {
    int array[sc_w][sc_h];
    int *map;
    w:
    is_loop = 1;
    flag_exit = 0;
    move_count = 0;
    length = 0;
    system("cls");
    printf("Enter Level of Difficulty : \n e -> Easy \n r -> Regular \n h -> Hard \n u -> Ultra Hard");
    switch (getch()) {
        case 'e':
            time_level = 500;
            break;
        case 'r':
            time_level = 200;
            break;
        case 'h':
            time_level = 100;
            break;
        case 'u':
            time_level = 40;
            break;
        default:
            goto w;
            break;
    }
    system("cls");
    printf("\tReady??");
    waitFor(1);
    system("cls");
    printf("\tStart");
    waitFor(1);


    map = SetZeroToArray(array, sc_w, sc_h);
    CreateFirstSnake(map);
    CreateFood(map);
    Draw(map);
    char control = 'd';
    while (is_loop == 1) {
        if (kbhit()) {
            control = getch();
        }
        CheckControl(map, control);
        Draw(map);
        printf("\nScore: %d\n", length);
        //delay(time_level);
        _sleep(time_level);

        //PrintScreen(map);


    }
    if (flag_exit != 1) {
        printf("\nGame Over!!");
        printf("\npress r to play again");
    } else {
        printf("press r to play again");
    }
    char ch = getch();
    if (ch == 'r') {
        goto w;
    }
    return 0;
}

void Move(int (*map)[sc_h], int phead_row, int phead_column, char operation) {
    if (CheckScope(phead_row, phead_column) == 0) {
        return;
    }
    char pre_operation = operation;
    int fake_row, fake_column; //for initializing variables
    int is_continue = 0;
    switch (operation) {
        case 'd':
            if (map[phead_row][phead_column - 1] == 1) {
                fake_column = phead_column - 1;
                fake_row = phead_row;
                if (CheckScope(fake_row, fake_column) != 0) {

                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'd';
                }
            } else if (map[phead_row - 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row - 1;
                if (CheckScope(fake_row, fake_column) != 0) {
                    /*if (fake_row == head_row && (fake_column - 1) == head_column) {
                        break;
                    }*/
                    if (CheckEndToMove(map, fake_row, fake_column - 1) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 's';
                }
            } else if (map[phead_row + 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row + 1;
                if (CheckScope(fake_row, fake_column) != 0) {

                    if (CheckEndToMove(map, fake_row, fake_column - 1) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'w';
                }
            }
            break;
        case 's':
            if (map[phead_row - 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row - 1;
                if (CheckScope(fake_row, fake_column) != 0) {
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 's';
                }
            } else if (map[phead_row][phead_column + 1] == 1) {
                fake_column = phead_column + 1;
                fake_row = phead_row;
                if (CheckScope(fake_row, fake_column) != 0) {
                    if (CheckEndToMove(map, fake_row - 1, fake_column) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'a';
                }
            } else if (map[phead_row][phead_column - 1] == 1) {
                fake_column = phead_column - 1;
                fake_row = phead_row;
                if (CheckScope(fake_row, fake_column) != 0) {
                    if (CheckEndToMove(map, fake_row - 1, fake_column) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'd';
                }
            }
            break;
        case 'w':
            if (map[phead_row + 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row + 1;
                if (CheckScope(fake_row, fake_column) != 0) {
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'w';
                }
            } else if (map[phead_row][phead_column + 1] == 1) {
                fake_column = phead_column + 1;
                fake_row = phead_row;
                if (CheckScope(fake_row, fake_column) != 0) {
                    if (CheckEndToMove(map, fake_row + 1, fake_column) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'a';
                }
            } else if (map[phead_row][phead_column - 1] == 1) {
                fake_column = phead_column - 1;
                fake_row = phead_row;
                if (CheckScope(fake_row, fake_column) != 0) {
                    if (CheckEndToMove(map, fake_row + 1, fake_column) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'd';
                }
            }
            break;
        case 'a':
            if (map[phead_row][phead_column + 1] == 1) {
                fake_column = phead_column + 1;
                fake_row = phead_row;
                if (CheckScope(fake_row, fake_column) != 0) {
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'a';
                }

            } else if (map[phead_row - 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row - 1;
                if (CheckScope(fake_row, fake_column) != 0) {
                    if (CheckEndToMove(map, fake_row, fake_column + 1) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 's';
                }

            } else if (map[phead_row + 1][phead_column] == 1) {
                fake_column = phead_column;
                fake_row = phead_row + 1;
                if (CheckScope(fake_row, fake_column) != 0) {
                    if (CheckEndToMove(map, fake_row, fake_column + 1) == 0) {
                        break;
                    }
                    CheckExitedCell(map, phead_row, phead_column, operation);
                    is_continue = 1;
                    operation = 'w';
                }
            }
            break;
        default:
            is_continue = 0;
            break;
    }

    if (is_continue == 1) {
        move_count++;
        map[fake_row][fake_column] = 0;
        if (move_count == length - 1) {
            end_row = phead_row;
            end_column = phead_column;
        }
        if (move_count < length - 1) {
            Move(map, fake_row, fake_column, operation);
        }

    }
}

void CheckControl(int (*map)[sc_h], char control) {
    CountFood(map);
    if (sum_food == 0) {
        CreateFood(map);
    }
    move_count = 0;
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
            flag_exit = 1;
            is_true_control = 0;
            is_loop = 0;
            break;
        default:
            is_true_control = 0;
            break;
    }
    if (is_true_control == 1) {
        if (CheckScope(head_row, head_column) == 0) {
            is_loop = 0;
            return;
        }
        if (head_column <= sc_h - 1 && head_column >= 0 && head_row <= sc_w - 1 && head_row >= 0) {
            if (map[head_row][head_column] == 2) {
                length++;
                CreateFood(map);
                AddToEndSnake(map, control);
            } else if (map[head_row][head_column] == 1) {
                is_loop = 0;
                return;
            }
            map[pre_row][pre_column] = 0;
            Move(map, pre_row, pre_column, control);
            CheckExitedCell(map, head_row, head_column, control);
        } else {
            is_loop = 0;
        }
    }

}

void CheckExitedCell(int (*map)[sc_h], int h_row, int h_col, char control) {
    /*if (map[h_row][h_col] == 1) {
        switch (control) {
            case 'w':
                CheckExitedCell(map, h_row - 1, h_col, 'w');
                break;
            case 's':
                CheckExitedCell(map, h_row + 1, h_col, 's');
                break;
            case 'd':
                CheckExitedCell(map, h_row, h_col + 1, 'd');
                break;
            case 'a':
                CheckExitedCell(map, h_row, h_col - 1, 'a');
                break;
            default:

                break;

        }
    } else {
        map[h_row][h_col] = 1;
    }*/
    map[h_row][h_col] = 1;
}

int CreateFirstSnake(int (*map)[sc_h]) {
    int x, y;

    srand(time(NULL));
    x = rand() % sc_w;
    y = rand() % (sc_h - 5);
    head_row = x;
    end_row = x;
    map[x][y] = 1;
    length++;
    if (y + 1 < sc_w) {
        map[x][y + 1] = 1;
        length++;
        if (y + 2 < sc_w) {
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
	int i,j;
    for (i = 0; i < size_width; i++) {
        for (j = 0; j < size_height; j++) {
            *(*(map + i) + j) = 0;
        }
    }
    return *map;
}

void PrintScreenDebug(int (*array)[sc_h]) {
    printf("\n");
    int i,j;
    for (i = 0; i < sc_w; i++) {
        for (j = 0; j < sc_h; j++) {
            printf("#[%d][%d] =>%d  ", i, j, *(*(array + i) + j));
        }
        printf("\n");
    }
}

void PrintScreen(int (*array)[sc_h]) {
	int i,j;
    for (i = 0; i < sc_w; i++) {
        for (j = 0; j < sc_h; j++) {
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
    int i,j;
    for (i = 0; i < sc_h; i++) {
        for (j = 0; j < sc_w; j++) {
            printf(".");
            if (array[i][j] == 1) {
                if (i == head_row && j == head_column) {
//                    printf("@");
                    printSnake();
                } else if (i == end_row && j == end_column) {
//                    printf("$");
                    printSnake();
                } else {
                    printSnake();
                }
            } else if (array[i][j] == 2) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\npress x to exit");
    //printf("\nmove Count %d", move_count);
    //printf("\nfood Count %d", sum_food);
    //PrintScreen(array);
}

void PrintHead() {
    printf("\nhead => row: %d column: %d\n", head_row, head_column);
}

void PrintEnd() {
    printf("end => row: %d column: %d\n", end_row, end_column);
}

int waitFor(unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
    return 1;
}

void CreateFood(int (*snake)[sc_h]) {
    int x, y;
    x = rand() % sc_w;
    y = rand() % sc_w;

    if (snake[x][y] == 1) {
        CreateFood(snake);
    } else {
        snake[x][y] = 2;
    }

}

void AddToEndSnake(int (*snake)[sc_h], char control) {
    int row, col;
    if (snake[end_row + 1][end_column] == 1) {
        row = end_row - 1;
        col = end_column;
    } else if (snake[end_row - 1][end_column] == 1) {
        row = end_row + 1;
        col = end_column;
    } else if (snake[end_row][end_column + 1] == 1) {
        row = end_row;
        col = end_column - 1;
    } else if (snake[end_row][end_column - 1] == 1) {
        row = end_row;
        col = end_column + 1;
    }
    int row_flag = 1, col_flag = 1;

    if (row < 0 || row >= sc_w) {
        row_flag = 0;
    }
    if (col < 0 || col >= sc_w) {
        col_flag = 0;
    }

    if (row_flag == 1 && col_flag == 1) {
        snake[row][col] = 1;
        return;
    }
    length--;
}

int CheckEndToMove(int (*map)[sc_h], int row, int col) {
    /*if (row == head_row && col == head_column) {
        return 0;
    }*/
    if (move_count == length) {
        if (map[row][col] == 1) {
            return 0;
        }
    }
    return 1;
}

int CheckScope(int row, int col) {
    if (row < 0 || row >= sc_w || col < 0 || col >= sc_w) {
        return 0;
    }
    return 1;
}

void CountFood(int (*map)[sc_h]) {
    sum_food = 0;
    int i,j;
    for (i = 0; i < sc_w; i++) {
        for (j = 0; j < sc_h; j++) {
            if (*(*(map + i) + j) == 2) {
                sum_food++;
            }
        }
    }
}
