#ifndef _CONSOLE_
#define _CONSOLE_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct tipe_and_value{
    int tipe;
    double value;
};

typedef struct  tipe_and_value lexeme;

enum cosas
{
    VARIABLE = 'x',
    CONSTANTE,
    SUMA = '+',
    RESTA = '-',
    MULTIPLICACION = '*',
    DIVISION = '/',
    COMPOSCICION,
    LN,
    SIN,
    COS,
    TG,
    ARCTG,
    EXPONENTIAL = '^',
    PARENTESIS_OPEN = '(',
    PARENTESIS_CLOSE = ')'
};

lexeme next_lexeme();
lexeme lexeme_create(int tipe,double value);
#endif