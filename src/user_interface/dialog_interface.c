#include "dialog_interface.h"

#define PATH_DIALOG "dialog_interface.glade"

void on_window_destroy_dialog(GtkWidget *object, void *dados){

        gtk_main_quit();
}

void closeDialog(GtkWidget *object, void *dados){
		
	on_window_destroy(object, dados);
}

int showDialog(int argc, char **argv, char *mensagem){
		
	Dialog *caixaDialog = g_slice_new(Dialog);
	
	if(caixaDialog == NULL)
        return *print_msg(ERR_MEMORY, "dialog_interface.c/showDialog");
        
    GtkBuilder *builder = NULL;
    GError *error= NULL;
    
    gtk_init(&argc, &argv );

    builder = gtk_builder_new();
    
    if( !gtk_builder_add_from_file( builder, PATH_DIALOG, &error ) ){
        g_warning( "%s", error->message );
       // g_free( error );
        return 1;
    }
    
    caixaDialog->dialog_interface = GTK_WIDGET( gtk_builder_get_object( builder, "dialog" ) );
    caixaDialog->labelDialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialogLabel" ) );
    caixaDialog->botaoOk = GTK_WIDGET( gtk_builder_get_object( builder, "dialogButton" ) );
    
    setTextDialog(caixaDialog->labelDialog, mensagem);
    
    gtk_builder_connect_signals( builder, caixaDialog );

    gtk_widget_show( caixaDialog->dialog_interface );

    gtk_main();
    
    return 0;

}

int setTextDialog(GtkLabel *label, char *text){
	
	gtk_label_set_text(label, text);
	
	return INF_NOT_ERR;
}
