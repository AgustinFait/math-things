#include"main.h"


int main()
{
    matrix *m = matrix_initialize_by_console();

    matrix_show(*m);

    // matrix *m2 = matrix_initialize_by_console();

    // matrix_show(*m2);
    
    double det = matrix_det(*m);

    printf("%f",det);

    matrix *d = matrix_diagonal(*m);
    matrix *upper = matrix_upper(*m);
    matrix *under = matrix_under(*m);

    matrix_show(*d);
    matrix_show(*upper);
    matrix_show(*under);

}