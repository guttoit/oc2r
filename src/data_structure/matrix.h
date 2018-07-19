#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _mat{
    
    int linhas;  
    int colunas;
    
    int *matrix;
    
}Matrix;

Matrix* criaEstrutraMatriz();

int inicializaMatriz(Matrix **mMatriz, int linhas, int colunas);

int getTipoMatriz(Matrix **mMatriz);

int getNumLinhas(Matrix **mMatriz);

int getNumColunas(Matrix **mMatriz);

int* getConteudoDaMatriz(Matrix **mMatriz);

int setElementoDaMatriz(Matrix **mMatriz, int l, int c, int valor);

void printMatriz(Matrix *matrix);

void printMatrizTexto(char *matrix, int rows, int cols);

int calc_center_x_pondered(Matrix *matrix, int *center_x);

char* toStringMatriz(Matrix *matrix);

char* to_string_matrix_transladed_to_origin(Matrix *matrix);

char* to_string_matrix_transladed_to_center(Matrix *matrix);

char* to_string_matrix_human_view(Matrix *matrix);

/**
 Pega a posição do pixel mais a esquerda e mais a baixo, para transladar
 a matrix para o início do eixo x e início do eixo y. Então, retorna o numero
 de deslocamentos necessários para x e y.
 Ex.: pmEsq -> x = 10 => Xrelativo = x - 10;
      pmBaixo -> y = 5 => Yrelativo = y - 5;
 */
int* calculaDeslocamentos(Matrix *matrix);

//char *transladaMatrizParaOrigem(char *dados, int rows, int cols, int *deslocamentos);

int transladaMatrizParaCentro(Matrix *matrix);

int transladaEstruturaMatrizParaOrigem(Matrix *matrix);

int liberaMemoriaMatrizEDependencias(Matrix **mMatriz);

#endif
