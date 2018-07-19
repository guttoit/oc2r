#ifndef LETTER_H
#define LETTER_H

#include <stdio.h>
#include <stdlib.h>
#include "accent.h"
#include "../vision/image_object.h"
#include "../msg_handling/msg_handling.h"

typedef struct _letter{
    
    ImgObject *objetoDaImagemLetra;
    
    
    Accent *acentoDaLetra;
    
    char caracterDaLetra;
    
    void (*print) (void *) ;
    
}Letter;

Letter* criaEstrutraLetra();

int inicializaLetra(Letter **mLetra);

int setObjetoDaImagemLetra(Letter **mLetra, ImgObject **objetoDaImagemLetra);

int setAcentoDaLetra(Letter **mLetra, Accent **acentoDaLetra);

int setCaracterDaLetra(Letter **mLetra, char caracterDaLetra);

ImgObject* getObjetoDaImagemLetra(Letter **mLetra);


Accent* getAcentoDaLetra(Letter **mLetra);

char getCaracterDaLetra(Letter **mLetra);

void printInformacaoLetra(void *mLetra);

int liberaMemoriaLetraEDependencias(Letter **letter);

int liberaMemoriaLetraSemDependencias(Letter **letter);

#endif
