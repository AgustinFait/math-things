#include "console.h"

void search_function(lexeme *lex);
double find_number();

lexeme next_lexeme()
{
    lexeme lex;
    lex.tipe = -1;
    int c;

    while((c = getchar()) != ' ' && c != '\t' && c != '\n');
    switch(c)
    {
        case SUMA:
        case RESTA:
        case VARIABLE:
        case MULTIPLICACION:
        case DIVISION:
        case EXPONENTIAL:
        case PARENTESIS_CLOSE:
        case PARENTESIS_OPEN:
        lex.tipe = c;
        break;
        case 'e':
        lex.tipe = CONSTANTE;
        lex.value = 2.71828;
        break;
        default:
        ungetc(c,stdin);
        if(isdigit(c))
        {
            lex.tipe = CONSTANTE;
            lex.value = find_number();
        }
        else
        {
            search_function(&lex);
        }
    }
    return lex;
}

double find_number()
{
    char number[20];
    char c;
    for(int i = 0;i < 20;i++)number[i] = '\0';
    for(int i = 0;(isdigit(c = getchar())) || c == '.';i++)number[i] = c;
    ungetc(c,stdin);
    return atof(number);
}

int esLetra(int number) {
    return (number >= 'A' && number <= 'Z') || (number >= 'a' && number <= 'z');
}

void search_function(lexeme *lex)
{
    char function[20];
    char c;
    for(int i = 0;i < 20;i++)function[i] = '\0';
    for(int i = 0;esLetra(c = getchar());i++)function[i] = c;
    ungetc(c,stdin);
    if(!strcmp(function,"ln"))lex->tipe = LN;
    if(!strcmp(function,"sin"))lex->tipe = SIN;
    if(!strcmp(function,"cos"))lex->tipe = COS;
    if(!strcmp(function,"tg"))lex->tipe = TG;
    if(!strcmp(function,"arctg"))lex->tipe = ARCTG;
}
