#include "s21_matrix.h"

// void print_matrix(int rows, int columns, matrix_t *result);
// void fill_matrix(int rows, int columns, matrix_t *result);

// int main() {
//     int rows = 3;
//     int columns = 3;
//     matrix_t A;
//     // matrix_t B;
//     matrix_t result;

//     // ---------------  CREATE --------------
//     s21_create_matrix(rows, columns, &A);
//     // s21_create_matrix(2, 3, &B);

//     // ---------------  CHECK --------------
//     fill_matrix(rows, columns, &A);
//     // fill_matrix(2, 3, &B);
//     print_matrix(rows, columns, &A);
//     // print_matrix(2, 3, &B);

//     // // ---------------  EQUALITY --------------
//     // int res_eq = s21_eq_matrix(&A, &B);
//     // printf("res_eq: %d\n", res_eq);

//     // ---------------  SUM --------------
//     // int res_sum = s21_sum_matrix(&A, &B, &result);
//     // printf("res_sum: %d\n", res_sum);
//     // print_matrix(rows, columns, &result);

//     // // ---------------  SUB --------------
//     // int res_sub = s21_sub_matrix(&A, &B, &result);
//     // printf("res_sub: %d\n", res_sub);
//     // print_matrix(rows, columns, &result);

//     // // ---------------  MULT_NUM --------------
//     // double number = 10;
//     // int res_mult = s21_mult_number(&A, number, &result);
//     // printf("res_mult: %d\n", res_mult);
//     // print_matrix(rows, columns, &result);

//     // // ---------------  MULT_MATRIX --------------
//     // int res_mult_m = s21_mult_matrix(&A, &B, &result);
//     // printf("res_mult_m: %d\n", res_mult_m);
//     // print_matrix(3, 3, &result);

//     // // ---------------  TRANSPOSE --------------
//     // int res_trans = s21_transpose(&A, &result);
//     // printf("res_trans: %d\n", res_trans);
//     // print_matrix(rows, columns, &result);

//     // // ---------------  CALC --------------
//     // int res_calc = s21_calc_complements(&A, &result);
//     // printf("res_calc: %d\n", res_calc);
//     // print_matrix(rows, columns, &result);

//     // // ---------------  DETERMINANT --------------
//     double determinant;
//     int res_determinant = s21_determinant(&A, &determinant);
//     printf("res_determinant: %d\n", res_determinant);
//     printf("%f\n", determinant);

//     // // ---------------  INVERSE --------------
//     // int res_inverse = s21_inverse_matrix(&A, &result);
//     // printf("res_inverse: %d\n", res_inverse);
//     // print_matrix(rows, columns, &result);

//     // ---------------  REMOVE --------------
//     s21_remove_matrix(&result);
// }

// void fill_matrix(int rows, int columns, matrix_t *result) {
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < columns; j++) {
//             int num = 0;
//             scanf("%d", &num);
//             result->matrix[i][j] = num;
//         }
//     }
// }

// void print_matrix(int rows, int columns, matrix_t *result) {
//     int count = 0;
//     printf("\nmatrix:\n");
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < columns; j++) {
//             printf("%.0f ", result->matrix[i][j]);
//             count += 1;
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

int matrix_is_correct(matrix_t *matrix) {
    int code = OK;

    if (matrix != NULL && matrix->matrix != NULL && matrix->rows < 1 && matrix->columns < 1)
        code = INCORRECT_MATRIX;

    return code;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;
        result->matrix = calloc(rows, sizeof(double *));

        if (result->matrix != NULL) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = calloc(columns, sizeof(double));
            }
            code = OK;
        }
    }
    return code;
}

// add result code???
void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
    }

    if (A->rows)
        A->rows = 0;

    if (A->columns)
        A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    if (matrix_is_correct(A) != OK ||
        matrix_is_correct(B) != OK ||
        A->columns != B->columns ||
        A->rows != B->rows)
        return FAILURE;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6)
                return FAILURE;
        }
    }
    return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK && matrix_is_correct(B) == OK) {
        code = CALC_ERROR;

        if (A->rows == B->rows && A->columns == B->columns) {
            code = s21_create_matrix(A->rows, A->columns, result);
            if (code == OK) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                    }
                }
            }
        }
    }
    return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK && matrix_is_correct(B) == OK) {
        code = CALC_ERROR;

        if (A->rows == B->rows && A->columns == B->columns) {
            code = s21_create_matrix(A->rows, A->columns, result);
            if (code == OK) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                    }
                }
            }
        }
    }
    return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK) {
        code = s21_create_matrix(A->rows, A->columns, result);
        if (code == OK) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] * number;
                }
            }
        }
    }
    return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK && matrix_is_correct(B) == OK) {
        code = CALC_ERROR;
        if (A->columns == B->rows) {
            code = s21_create_matrix(A->rows, B->columns, result);
            if (code == OK) {
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < B->columns; j++) {
                        for (int k = 0; k < B->rows; k++) {
                            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                        }
                    }
                }
            }
        }
    }
    return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK) {
        code = s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    }
    return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK) {
        code = CALC_ERROR;

        if (A->rows == A->columns) {
            code = s21_create_matrix(A->columns, A->rows, result);
            if (code == OK)
                code = my_calc(A, result);
        }
    }
    return code;
}

int my_calc(matrix_t *A, matrix_t *result) {
    int code = OK;
    result->matrix[0][0] = 1;
    if (A->rows != 1) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                double determinant;
                matrix_t minor_matrix;
                code = my_minor(i + 1, j + 1, A, &minor_matrix);
                if (code == OK) {
                    code = s21_determinant(&minor_matrix, &determinant);
                    if (code == OK)
                        result->matrix[i][j] = pow((-1), i + j) * determinant;
                }
                s21_remove_matrix(&minor_matrix);
            }
        }
    }
    return code;
}

int my_minor(int row, int column, matrix_t *A, matrix_t *minor_matrix) {
    int code = INCORRECT_MATRIX;

    if (A->matrix != NULL) {
        code = s21_create_matrix(A->rows - 1, A->columns - 1, minor_matrix);
        if (code == OK) {
            int m, n;
            for (int i = 0; i < A->rows; i++) {
                m = i;
                if (i > row - 1)
                    m--;

                for (int j = 0; j < A->columns; j++) {
                    n = j;
                    if (j > column - 1)
                        n--;

                    if (i != row - 1 && j != column - 1)
                        minor_matrix->matrix[m][n] = A->matrix[i][j];
                }
            }
        }
    }
    return code;
}

int s21_determinant(matrix_t *A, double *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK) {
        code = CALC_ERROR;

        if (A->rows == A->columns) {
            code = OK;
            *result = A->matrix[0][0];
            if (A->rows != 1) {
                *result = my_determinant(A);
            }
        }
    }
    return code;
}

int my_determinant(matrix_t *A) {
    double result = 0;
    if (A->rows == 2) {
        result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        for (int i = 0; i < A->rows; i++) {
            matrix_t minor_matrix;
            my_minor(1, i + 1, A, &minor_matrix);
            result += pow((-1), i) * A->matrix[0][i] * my_determinant(&minor_matrix);
            s21_remove_matrix(&minor_matrix);
        }
    }
    return result;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int code = INCORRECT_MATRIX;

    if (matrix_is_correct(A) == OK) {
        code = CALC_ERROR;

        double determinant;
        s21_determinant(A, &determinant);

        if (fabs(determinant - 0) > 1e-6) {
            matrix_t calc_matrix;
            code = s21_calc_complements(A, &calc_matrix);
            if (code == OK) {
                matrix_t trans_matrix;
                code = s21_transpose(&calc_matrix, &trans_matrix);
                if (code == OK) {
                    int num = 1 / determinant;
                    s21_mult_number(&trans_matrix, num, result);
                }
                s21_remove_matrix(&trans_matrix);
            }
            s21_remove_matrix(&calc_matrix);
        }
    }
    return code;
}
