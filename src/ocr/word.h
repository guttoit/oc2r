#ifndef ESTRUTURA_PALAVRA
#define ESTRUTURA_PALAVRA

#include <stdio.h>
#include <stdlib.h>
#include "letter.h"
#include "../data_structure/list_generic.h"

typedef struct _word{
    
    //Podem ser objetos da word: Letras, sinais de punctuation
    
    ListGeneric *listaDeObjetosDaPalavra;
    
    int tamanhoDaPalavra;
    
    void *linhaDaPalavra; //Ponteiro para a linha na qual a plavra se encontra
    
}Word;

Word* criaEstruturaPalavra();

int inicializaPalavra(Word **mPalavra);

int add_character(Word *word, Letter *character);

int setListaDeObjetosDaPalavra(Word **mPalavra, ListGeneric **listaDeObjetosDaPalavra);

int setTamanhoDaPalavra(Word **mPalavra, int tamanhoDaPalavra);

int setLinhaDaPalavra(Word **mPalavra, void *linhaDaPalavra);

ListGeneric* getListaDeObjetosDaPalavra(Word **mPalavra);

int getTamanhoDaPalavra(Word **mPalavra);

void* getLinhaDaPalavra(Word **mPalavra);


int liberaMemoriaPalavraEDepencencias(Word **mPalavra);

int liberaMemoriaPalavraSemDepencencias(Word **mPalavra);

#endif
