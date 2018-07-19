#ifndef UTIL_OCR_H
#define UTIL_OCR_H

#include <stdio.h>
#include <stdlib.h>
#include "../msg_handling/msg_handling.h"

#define LIM_INF_ASCII 33   //Equivale ao caracter '!' na tabela ascII
#define LIM_SUP_ASCII 126  //Equivale ao caracter '~' na tabela ascII

#define LIM_INF_CHAR_NUMERIC 48   //Equivale ao caracter '0'
#define LIM_SUP_CHAR_NUMERIC 57   //Equivale ao caracter '9'

#define LIM_INF_CHAR_LETTER_UP 65   //Equivale ao caracter 'A'
#define LIM_SUP_CHAR_LETTER_UP 90   //Equivale ao caracter 'Z'

#define LIM_INF_CHAR_LETTER_LOW 97   //Equivale ao caracter 'a'
#define LIM_SUP_CHAR_LETTER_LOW 122   //Equivale ao caracter 'z'

#define TAM_VETOR_SAIDA (LIM_SUP_ASCII - LIM_INF_ASCII  + 1)

int get_index_output_desired(char *valReferencia, int *index);

int getCharSaidaDesejada(int index_output_desired, char *valSaidaDes);

char* getVetorReferencia();

char *getVetorSaidaDesejada(int index_output_desired);

int get_size_vect_out(int *size);


#endif