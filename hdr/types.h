#ifndef TYPES_H
#define TYPES_H

#define NO_ID -1
#define ERR_RETURN -100
#define DOLAR_TO_EURO 0.82
#define EURO_TO_DOLAR 1.22
#define CHAR_MAX 10000


typedef enum {
    ERR = 0,
    OK
}status;

typedef enum {
    FALSE = 0,
    TRUE
}boolean;

void green();
void red();
void defaults();
void yellow();

#endif