#ifndef TRAIN_INTERFACE_H
#define TRAIN_INTERFACE_H

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <stdio.h>
#include <stdlib.h>
#include "train_interface_controller.h"

#define KEY_NEXT 65363
#define KEY_BACK 65361
#define KEY_ENTER 65293
#define KEY_R 114

typedef struct interfaceTreino
{
        GtkWidget *window;
        GtkWidget *editText;
        GtkWidget *editTextFile;
        GtkWidget *botaoOk;
        GtkWidget *botaoRemove;
        GtkWidget *botaoNext;
        GtkWidget *botaoBack;
        GtkWidget *botaoSalvar;
        GtkWidget *image;
        GtkWidget *editTextPathImage;
        GtkWidget *botaoLoadImage;
        struct controladorJanelaTreinamento *controlador;

}InterfaceTreinamento;

int criaEInicializaInterfaceTreinamento(InterfaceTreinamento **mJanela);

int setControladorJanelaTreino(InterfaceTreinamento **mJanela, struct controladorJanelaTreinamento **mControlador);

void on_window_destroy(GtkWidget *object, InterfaceTreinamento *janela);

int finalizar_edicao(GtkWidget *object, InterfaceTreinamento *janela);

gboolean key_press (GtkWidget *widget, GdkEvent  *event,  InterfaceTreinamento *janela);

gboolean key_press_entry_imagem(GtkWidget *widget, GdkEvent  *event, InterfaceTreinamento *janela);

int salvarTreinamento(GtkWidget *widget, InterfaceTreinamento *janela);

int nextImage(InterfaceTreinamento *janela);

int backImage(InterfaceTreinamento *janela);

int removeObjeto(GtkWidget *object, InterfaceTreinamento *janela);

void setImage(char *pathImage, InterfaceTreinamento *janela);

void setTextEntry(InterfaceTreinamento *janela, char caracter);

char* getDadosEditTextFile(InterfaceTreinamento *train_interface);

void loadImagemTreinamento(GtkWidget *object, InterfaceTreinamento *janela);

int iniciaJanela(int argc, char **argv, char *pathXml, InterfaceTreinamento **train_interface);

#endif
