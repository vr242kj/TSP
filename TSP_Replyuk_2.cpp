#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>
#include <math.h>

float get_weight(int a, int b, float **ary, int rows, int cols, float w[], int nrow);

int function(int *x, int z, float **ary, int rows, int cols, float w[], int nrow, bool check[], int Nrow, int NODES);

int *insertion(int *a, int size, float **ary, int rows, int cols, float w[], int nrow);

float get_total(int *a, int size, float **ary, int rows, int cols, float w[], int nrow);


int *a, *c;
float *b;
int size = 1;
//int NODES = 4;
int node = 0;


int main() {
    srand(time(NULL));

    FILE *file = fopen("inp.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int rows;
    //int rows = 21;
    const int cols = 3;
    printf("Rows: ");
    scanf("%d", &rows);

    int NODES = (1 + sqrt(1 + (4 * 2 * rows))) / 2;

    printf("Uzlov: %d\n", NODES);

    a = (int *) malloc(NODES + 1 * sizeof(int));
    c = (int *) malloc((NODES) * sizeof(int));//7


    float **ary = (float **) malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        ary[i] = (float *) malloc(cols * sizeof(float));
    }


    int **ary2 = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        ary2[i] = (int *) malloc(2 * sizeof(int));
    }


    float w[rows];
    bool check[rows];
  
    while (!feof(file)) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fscanf(file, "%f", &ary[i][j]);
                w[i] = ary[i][2];
                printf("%f ", ary[i][j]);
            }
            printf("\n");
        }
    }

    fclose(file);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 2; j++) {
            ary2[i][j] = (int) ary[i][j];
            //printf("%d ", ary[i][j]);
        }
        //printf("\n");
    }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //printf("%.f ", ary[i][j]);
        }
        //printf("\n");
    }


    for (int i = 0; i < rows; i++) {
        check[i] = true;
    }

    c[0] = 1;
    for (int i = 1; i <= NODES; i++) {
        c[i] = 0;
    }

    


    a[0] = ary2[rand() % rows][rand() % 1];
    c[a[0]] = 1;
    printf("Randomne cislo: %d\n", a[0]);


    while (node < NODES - 1) {

        int min = function(a, size, ary, rows, cols, w, rows, check, rows, NODES);
        //printf("min: %d\n", min);
        c[min] = 1;
        a[++node] = min;
        size++;


        if (size > 2) {
            a = insertion(a, size, ary, rows, cols, w, rows);
            /*	for(int i = 0;i<size;i++){
                printf("Node(insert)-%d-",a[i]);
            }*/
        }
    }
    // Cesta 

    fprintf(out, "%0.2f\n", get_total(a, size, ary, rows, cols, w, rows));

    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            printf("%d,", a[i]);
            fprintf(out, "%d,", a[i]);
            printf("%d\n", a[0]);
            fprintf(out, "%d\n", a[0]);
            break;
        }
        printf("%d,", a[i]);
        fprintf(out, "%d,", a[i]);

    }
    printf("Total: %0.2f", get_total(a, size, ary, rows, cols, w, rows));
    fclose(out);

    for (int i = 0; i < rows; i++) {
        free(ary2[i]);
    }
    free(ary2);

    for (int i = 0; i < rows; i++) {
        free(ary[i]);
    }
    free(ary);

    free(a);
    free(b);
    free(c);

    return 0;
}


float get_total(int *a, int size, float **ary, int rows, int cols, float w[], int nrow) {
    float total = 0;
    for (int i = 0; i < size - 1; i++) {
        total += get_weight(a[i], a[i + 1], ary, rows, cols, w, nrow);
        //printf("Total - %d ",total);
    }
    total += get_weight(a[size - 1], a[0], ary, rows, cols, w, nrow);
    return total;
}

float get_weight(int a, int b, float **ary, int rows, int cols, float w[], int nrow) {
    for (int i = 0; i < rows; i++) {
        if (((ary[i][0] == a) && (ary[i][1] == b)) || (ary[i][0] == b) && (ary[i][1] == a)) {
            return w[i];
        }
    }
    return 0;
}

int *insertion(int *a, int size, float **ary, int rows, int cols, float w[], int nrow) {

    b = (float *) malloc(100 * sizeof(float));
    float min;
    int MIN = 0;

    for (int i = 0; i < size; i++) {
        if (i < size - 2) {
            b[i] = get_weight(a[i], a[size - 1], ary, rows, cols, w, nrow) +
                   get_weight(a[size - 1], a[i + 1], ary, rows, cols, w, nrow) -
                   get_weight(a[i + 1], a[i], ary, rows, cols, w, nrow);
        } else {
            b[i] = get_weight(a[i], a[size - 1], ary, rows, cols, w, nrow) +
                   get_weight(a[size - 1], a[0], ary, rows, cols, w, nrow) -
                   get_weight(a[0], a[i], ary, rows, cols, w, nrow);
        }
    }
    min = b[0];
    for (int i = 1; i < size - 1; i++) {
        if (min > b[i]) {
            min = b[i];
            MIN = i;
        }
    }
    //int last = a[size-1];
    int ost = a[size - 1];
    a[size - 1] = 0;
    //size--;

    for (int i = size - 1; i >= MIN + 1; i--) {
        a[i + 1] = a[i];
    }
    a[MIN + 1] = ost;

    free(b);
    return a;
}

int function(int *x, int z, float **ary, int rows, int cols, float w[], int nrow, bool check[], int Nrow, int NODES) {
    int f = 0;
    int chek = 0;
    float min = 10000;
    if (size == 1) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < 2; j++) {
                if (ary[i][j] == a[0]) {
                    if (min >= w[i]) {
                        min = w[i];
                        chek = i;

                        if (j == 0) {
                            f = (int) ary[i][j + 1];
                        } else {
                            f = (int) ary[i][j - 1];
                        }
                        //b[0] = min;
                        //a[1] = ary[i][j+1];
                        //test = i;
                    }
                }
            }
        }
        check[chek] = false;
        return f;
    } else if (size == NODES - 1) {
        for (int i = 1; i <= NODES; i++) {
            if (c[i] == 0) {
                return i;
            }
        }
    } else {
        for (int z = 0; z < size; z++) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < 2; j++) {
                    if (a[z] == ary[i][j]) {
                        if (min > w[i] && check[i] != false) {
                            min = w[i];
                            chek = i;
                            if (j == 0) {
                                f = (int) ary[i][j + 1];
                            } else {
                                f = (int) ary[i][j - 1];
                            }
                        }
                    }
                }
            }
        }
    }

    check[chek] = false;
    return f;
}

