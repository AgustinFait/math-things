#include "matrices.h"

void sumar(double *a, double *b);
void restar(double *a,double *b);
double sum_arrays(double *array1,double * array2,int size);
double matrix_multiplicate_positive_diagonals(matrix m);
double matrix_multiplicate_negative_diagonals(matrix m);
double  matrix_2x2_det(matrix m);
double  matrix_3x3_det(matrix m);
double matrix_general_det(matrix m);

matrix* matrix_create(int columnas,int filas)
{
    matrix *m = malloc(sizeof(matrix));
    m->columnas = columnas;
    m->filas = filas;
    m->datos = malloc(sizeof(double*)*filas);
    for(int i = 0; i< filas;i++)m->datos[i] = malloc(sizeof(double)*columnas);
    void set_zeros(double* d){*d = 0;}
    matrix_iteration(m,set_zeros);
    return m; 
}

void matrix_destroy(matrix* m)
{
    for(int i = 0;i < m->filas;i++)free(m->datos[i]);
    free(m->datos);
    free(m);
}


void matrix_set(matrix *m,int row,int column,double value)
{
    if(m->columnas <= column || m->filas <= row)return;

    m->datos[row][column] = value;
}

double matrix_get(matrix m,int row,int column)
{
    return m.datos[row][column];
}

void sumar(double *a, double *b){*a += *b;}
void restar(double *a,double *b){*a -= *b;}

void matrix_iteration(matrix *m,void operation(double*))
{
    for(int row = 0;row < m->filas;row++)
    {
        for(int column = 0;column < m->columnas;column++)
        {
            operation(&(m->datos[row][column]));
        }
    }
}


void matrix_double_iteration(matrix *matrix1,matrix *matrix2,void operation(double*,double*))
{
    if(matrix1->columnas != matrix2->columnas || matrix1->filas != matrix2->filas)return;

    for(int row = 0;row < matrix1->filas;row++)
    {
        for(int column = 0;column < matrix1->columnas;column++)
        {
            operation(&(matrix1->datos[row][column]),&(matrix2->datos[row][column]));
        }
    }
}

matrix *matrix_initialize_by_console()
{
    printf("Enter the number of rows of the matrix ");
    char r[5], co[5];
    int rows_quantity,columns_quantity;
    int i = 0;
    for(int i = 0,c;(c = getchar()) != '\n';i++)r[i] = c;
    rows_quantity = atoi(r);
    printf("Enter the number of columns of the matrix ");
    for(int i = 0,c;(c = getchar()) != '\n';i++)co[i] = c;
    columns_quantity = atoi(co);
    matrix *new = matrix_create(columns_quantity,rows_quantity);

    void enter_values(double* d)
    {
        int c;
        while((c = getchar()) == ' ' || c == '\n' ||  c == '\t');
        ungetc(c,stdin);
        char number[15];
        for(int i = 0;i < 15;i++)number[i] = '\0';
        for(int i = 0;(c = getchar()) != '\n' && c != ' ' && c != '\t';i++)number[i] = c;
        *d = atof(number);
    }

    printf("Enter the values\n");
    matrix_iteration(new,enter_values);
    return new;
}

matrix *matrix_show(matrix m)
{
    for(int row = 0;row < m.filas;row++)
    {
        for(int column = 0;column < m.columnas;column++)
        {
            printf("%f ",matrix_get(m,row,column));
        }
        printf("\n");
    }
}

double* matrix_row(matrix m,int index)
{
    double *row = malloc(sizeof(double)*m.columnas);
    for(int i = 0;i < m.columnas;i++)row[i] = matrix_get(m,index,i);
    return row;
}

double* matrix_column(matrix m, int index)
{
    double *column = malloc(sizeof(double)*m.filas);
    for(int i = 0;i < m.filas;i++)column[i] = matrix_get(m,i,index);
    return column;
}

void matrix_multiplicate_by_number(matrix* matrix1,double number)
{
    void multiplicate(double *d)
    {
        (*d) *= number;
    }

    matrix_iteration(matrix1,multiplicate);
}

void matrix_sum(matrix* matrix1,matrix matrix2){matrix_double_iteration(matrix1,&matrix2,sumar);}

void matrix_sub(matrix* matrix1,matrix matrix2){matrix_double_iteration(matrix1,&matrix2,restar);}

double sum_arrays(double *array1,double * array2,int size)
{
    double result = 0;
    for(int i = 0;i < size;i++)result += array1[i]*array2[i];
    return result;
}

matrix* matrix_multiplicate(matrix matrix1,matrix matrix2)
{
    if(matrix1.columnas != matrix2.filas)return NULL;

    matrix *result = matrix_create(matrix2.columnas,matrix1.filas);
    for(int rows = 0;rows < result->filas;rows++)
    {
        double *row = matrix_row(matrix1,rows);
        for(int columns = 0;columns < result->columnas;columns++)
        {
            double *column = matrix_column(matrix2,columns);
            matrix_set(result,rows,columns,sum_arrays(row,column,matrix2.filas));
            free(column);
        }
        free(row);
    }
    return result;
}

matrix *matrix_identity(int column_rows)
{
    matrix *identity = matrix_create(column_rows,column_rows);
    for(int i = 0;i < column_rows;i++)matrix_set(identity,i,i,1);
    return identity;
}

matrix *matrix_diagonal(matrix m)
{
    if(!matrix_is_square(m))return NULL;
    matrix *diagonal = matrix_create(m.columnas,m.filas);
    for(int i = 0;i <m.filas;i++)matrix_set(diagonal,i,i,matrix_get(m,i,i));
    return diagonal;
}

matrix *matrix_upper(matrix m)
{
    matrix *upper = matrix_create(m.columnas,m.filas);
    for(int row = 0;row < m.filas;row++)
    {
        for(int column = row+1;column < m.columnas;column++)
        {
            matrix_set(upper,row,column,matrix_get(m,row,column));
        }
    }
    return upper;
}

matrix *matrix_under(matrix m)
{
    matrix *under = matrix_create(m.columnas,m.filas);
    for(int row = m.filas-1;row > -1;row--)
    {
        for(int column = row-1;column > -1;column--)
        {
            matrix_set(under,row,column,matrix_get(m,row,column));
        }
    }
    return under;
}

matrix *matrix_without(matrix m,int row,int column)
{
    matrix *new = matrix_create(m.columnas-1,m.filas-1);
    for(int current_row = 0,assignin_row = 0;current_row < new->filas;current_row++,assignin_row++)
    {
        if(assignin_row == row)assignin_row++;
        for(int current_column = 0,assignin_column = 0;current_column < new->columnas;current_column++,assignin_column++)
        {
            if(assignin_column == column)assignin_column++;
            matrix_set(new,current_row,current_column,matrix_get(m,assignin_row,assignin_column));
        }
    }
    return new;
}

bool matrix_is_square(matrix m){return m.columnas == m.filas;}

bool matrix_is_diagonal(matrix m)
{
    for(int row = 0;row < m.filas;row++)
    {
        for(int column = 0;column < m.columnas;column++)
        {
            if(column != row)if(matrix_get(m,row,column))return false;
        }
    }
    return true;
}

bool matrix_is_diagonal_dominant(matrix m) 
{
    double diagonal,acum = 0;
    for(int row = 0;row < m.filas;row++)
    {
        for(int column = 0;column < m.columnas;column++)
        {
            if(column != row)acum += _abs64(matrix_get(m,row,column));
            else diagonal = matrix_get(m,row,column);
            if(acum > diagonal)return false;
        }
        acum = 0;
        diagonal = __DBL_MAX__;
    }
    return true;
}

matrix *matrix_diagonal_inverse(matrix m)
{
    matrix *inverse = matrix_create(m.columnas,m.filas);
    for(int i = 0;i < m.columnas;i++)matrix_set(inverse,i,i,1/matrix_get(m,i,i));
    return inverse;
}
double  matrix_2x2_det(matrix m)
{
    return matrix_get(m,0,0)*matrix_get(m,1,1) - matrix_get(m,1,0)*matrix_get(m,0,1);
}

double matrix_multiplicate_positive_diagonals(matrix m)
{
    double general_acumulator = 0;
    for(int i = 0;i <  m.columnas;i++)
    {
        int row = 0,column = i,diagonal_acumulator = 1;
        while(row  < m.filas)
        {
            diagonal_acumulator *= matrix_get(m,row,column);
            row++;
            column = (++column)%m.columnas;
        }
        general_acumulator += diagonal_acumulator;
    }
    return general_acumulator;
}

double matrix_multiplicate_negative_diagonals(matrix m)
{
    double general_acumulator = 0;
    for(int i = m.columnas - 1;i >= 0;i--)
    {
        int row = 0,column = i;
        double diagonal_acumulator = 1;
        while(row  < m.filas)
        {
            diagonal_acumulator *= matrix_get(m,row,column);
            row++;
            if((--column) < 0)column = m.columnas - 1;
        }
        general_acumulator += diagonal_acumulator;
    }
    return general_acumulator;
}

double  matrix_3x3_det(matrix m)
{
    return matrix_multiplicate_positive_diagonals(m) - matrix_multiplicate_negative_diagonals(m);
}

double matrix_general_det(matrix m)
{
    double result = 0;
    for(int i = 0;i < m.columnas;i++)
    {
        double escalar = matrix_get(m,0,i);
        int sign;
        if(!(i%2))sign = 1;
        else sign = -1;
        matrix *smaller_matrix = matrix_without(m,0,i);
        result += escalar*sign*matrix_det(*smaller_matrix);
        matrix_destroy(smaller_matrix);
    }
    return result;
}
double matrix_det(matrix m)
{
    if(!matrix_is_square(m))return __DBL_MAX__;
    switch(m.columnas)
    {
        case 2:
            return matrix_2x2_det(m);
        break;
        case 3:
            return matrix_3x3_det(m);
        break;
        default:
            return matrix_general_det(m);
    }
}

