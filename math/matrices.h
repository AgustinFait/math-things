#ifndef MATRICES_H
#define MATRICES_H

#include <stdlib.h>
#include<stdio.h>
#include <stdbool.h>

struct matriz
{
    int columnas;
    int filas;
    double **datos;
};

typedef struct matriz matrix;

matrix* matrix_create(int columnas,int filas);
void matrix_destroy(matrix* m);
void matrix_set(matrix *m,int row,int column,double value);
double matrix_get(matrix m,int row,int column);
void matrix_iteration(matrix *m,void operation(double*));
void matrix_double_iteration(matrix *matrix1,matrix *matrix2,void operation(double*,double*));
matrix *matrix_initialize_by_console();
matrix *matrix_show(matrix m);

//both of this need to be freed
double* matrix_row(matrix m,int index);
double* matrix_column(matrix m, int index);

void matrix_multiplicate_by_number(matrix* matrix1,double number);
void matrix_sum(matrix* matrix1,matrix matrix2);
void matrix_sub(matrix* matrix1,matrix matrix2);
matrix* matrix_multiplicate(matrix matrix1,matrix matrix2);


matrix *matrix_identity(int column_rows);
matrix *matrix_diagonal(matrix m);
matrix *matrix_upper(matrix m);
matrix *matrix_under(matrix m);
matrix *matrix_without(matrix m,int row,int column);
bool matrix_is_square(matrix m);
bool matrix_is_diagonal(matrix m);
bool matrix_is_diagonal_dominant(matrix m);
matrix *matrix_diagonal_inverse(matrix m);

double matrix_det(matrix m);


#endif