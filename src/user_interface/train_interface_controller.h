#ifndef TRAIN_INTERFACE_CONTROLLER_H
#define TRAIN_INTERFACE_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include "train_interface.h"
#include "dialog_interface.h"
#include "../data_structure/list_generic.h"
#include "../util/util_cv.h"
#include "../vision/pre_img_processing.h"

typedef struct controladorJanelaTreinamento{
    
    struct interfaceTreino *janela;
    struct treino *treinamento;
    
}ControladorJanelaTreino;

ControladorJanelaTreino* criaEInicializaControladorTreinamento(struct interfaceTreino **mJanela);

int inicializaEdicao(struct controladorJanelaTreinamento *controlador, char *pathImage, char *pathTrain);

int finalizaEdicaoCaracter(ControladorJanelaTreino *controlador);

int salvaTreinamentoControlador(ControladorJanelaTreino *controlador);

int exibeObjetoAtual(ControladorJanelaTreino *controlador);

int exibeProximoObjeto(ControladorJanelaTreino *controlador);

int exibeObjetoAnterior(ControladorJanelaTreino *controlador);

int exibeAlerta(char *mensagem);

int setPathFileTreinamento(ControladorJanelaTreino *controlador, char *path);

char* incrementaContadorImagensSalvas(char *pathImageInicial);

int salvaImagemCaracterEscolhido(ControladorJanelaTreino *controlador);

int removeObjetoDaListaControlador(ControladorJanelaTreino *controlador);

char* getText(GtkEntry *entry);

char getFirstCharText(GtkEntry *entry);

#endif
