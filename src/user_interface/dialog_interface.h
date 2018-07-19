#ifndef DIALOG_INTERFACE_H
#define DIALOG_INTERFACE_H

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <stdio.h>
#include <stdlib.h>

#include "../msg_handling/msg_handling.h"

typedef struct dialog
{
        GtkWidget *dialog_interface;
        GtkWidget *labelDialog;
        GtkWidget *botaoOk;

}Dialog;

int showDialog(int argc, char **argv, char *mensagem);

void on_window_destroy_dialog(GtkWidget *object, void *dados);

void closeDialog(GtkWidget *object, void *dados);

#endif
