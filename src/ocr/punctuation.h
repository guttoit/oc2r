#ifndef PUNCTUATION_H
#define PUNCTUATION_H

#include <stdio.h>
#include "line.h"
#include "../vision/image_object.h"

typedef struct _pontucao{
    
    ImgObject *objetoDaImagemDaPontuacao;
    
    Line *linhaDaPontuacao;
    
    char caracterDaPontuacao;
    
}Pontuacao;

Pontuacao* criaEstruturaSinalDePontuacao();

int inicializaSinalDePontuacao(Pontuacao **mPontuacao);

int setObjetoDaImagemDaPontuacao(Pontuacao **mPontuacao, ImgObject **objetoDaImagemDaPontuacao);

int setLinhaDaPontuacao(Pontuacao **mPontuacao, Line **linhaDaPontuacao);

int setCaracterDaPontuacao(Pontuacao **mPontuacao, char caracter);

ImgObject* getObjetoDaImagemDaPontuacao(Pontuacao **mPontuacao);

Line* getLinhaDaPontuacao(Pontuacao **mPontuacao);

char getCaracterDaPontucao(Pontuacao **mPontuacao);

int liberaMemoriaPontuacaoEDependencias(Pontuacao **mPontuacao);

int liberaMemoriaPontuacaoSemDependencias(Pontuacao **mPontuacao);

#endif
