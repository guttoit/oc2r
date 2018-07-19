#ifndef UTIL_FANN_H
#define UTIL_FANN_H

#include <stdio.h>
#include <stdlib.h>
#include "util_ocr.h"
#include "util_io_string.h"
#include "../data_structure/matrix.h"
#include "../msg_handling/msg_handling.h"


char *geraDadosMatTreinoFann(Matrix *mat_dados, char *saida_des);

float* create_fann_input(Matrix *mat_dados);

float* copy_fann_output(float *fann_output, int size_out);

int* get_fill_layers(int n_layers, int *neurons_hidden, int size_input);

char* create_fann_header(int n_samples, int size_sample, int size_output);

int print_ann_input(float *ann_in, int n_inputs);

/*
ListGeneric* initImageProcessing(IplImage *imgIn, int resolution);

struct treino *geraTreinamentoGenerico(char *pathImagem, char *pathTrain, int resolution);

int finalizaEdicaoObjetoAtual(struct treino *treinamento, char caracter);

int salvaTreinamentoLogicaTreino(struct treino *treinamento, char *nameFile);

int avancaObjetoEditar(struct treino *treinamento);

int retrocedeObjetoEditar(struct treino **treinamento);

int removeObjetoTreinamento(struct treino *treinamento);

char *saveImageObjetoTreino(struct objetoTreino *training_object);

char *getPathImageObjetoAtual(struct treino *treinamento);

char getCaracterObjetoAtual(struct treino *treinamento);

char* converteDadosParaFANN(char *dados);
*/
#endif
