#ifndef CURSOR_H
#define	CURSOR_H

    #define CLEAR               printf("\033[2J\033[1;1H")

    // Положение курсора
    #define HOME                printf("\033[1;1H")
    #define STORE_CURSOR        printf("\033[s")
    #define RESET_CURSOR        printf("\033[u")
    #define CLEAR_EOL           printf("\033[K")
    #define CURSOR(row, column) printf("\033[%02d;%02dH", row, column)

    // Выбор цвета
    #define RESET_COLOR printf("\033[0m")

    #define BLACK       0
    #define RED         1
    #define GREEN       2
    #define YELLOW      3
    #define BLUE        4
    #define MAGENTA     5
    #define CYAN        6
    #define WHITE       7
    #define UNDEF       -1

    // Выбор оформления
    #define NONE        0
    #define BOLD        1
    #define DIM         2
    #define UNDERLINE   4
    #define BLINK       5
    #define REVERSE     7

    #define COLOR(bgcolor, fgcolor)         printf("\033[%02d;%02dm", (bgcolor + 30), (fgcolor + 40))
    #define COLOR_A(bgcolor, fgcolor, attr) printf("\033[%02d;%02d;%1dm", (bgcolor + 30), (fgcolor + 40), attr)
#endif	/* CURSOR_H */
