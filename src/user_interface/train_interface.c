#include "train_interface.h"

#define PATH_BUILDER "janelaTreino2.glade"

int criaEInicializaInterfaceTreinamento(InterfaceTreinamento **mJanela){
    
    (*mJanela) = g_slice_new(InterfaceTreinamento);
    
    if((*mJanela) == NULL)
        return *print_msg(ERR_MEMORY, "train_interface.c/criaEInicializaInterfaceTreinamento");
    
    return INF_NOT_ERR;
}

int setControladorJanelaTreino(InterfaceTreinamento **mJanela, ControladorJanelaTreino **mControlador){
        
    (*mJanela)->controlador = (*mControlador);
    
    return INF_NOT_ERR;
}

int limpaEditText(GtkEntry *object){
    
    if(object == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/limpaEditText");
    
    gtk_entry_set_text(object, "\0");
    
    return INF_NOT_ERR;
}

int isEntryVazio(GtkEntry *entry){
    
    int numCar = gtk_entry_get_text_length(entry);
    
    if(numCar == 0)
        return 1;
        
    char *text = gtk_entry_get_text(entry);

    while((*text) != '\0')
        if((*text) != ' ')
            return 0;
        else
            text++;
    
    return 1;
}

int finalizar_edicao(GtkWidget *object, InterfaceTreinamento *janela){

    if(janela == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/finalizar_edicao/janela");
    
    if((isEntryVazio(((GtkEntry*)janela->editText))))
        return INF_NOT_ERR;
    
    int resFuncao = finalizaEdicaoCaracter(janela->controlador);
    
    printf("Entrei em finalizaEdicao\n");
    
    if(resFuncao != INF_NOT_ERR)
        return *print_msg(ERR_GENERIC, "train_interface.c/finalizar_edicao/finalizaEdicaoCaracter");
    
    GtkEntry *entry =(GtkEntry*) janela->editText;
    
    limpaEditText(entry);
    gtk_widget_grab_focus(entry);
    
    return INF_NOT_ERR;
}

gboolean key_press (GtkWidget *widget, GdkEvent  *event, InterfaceTreinamento *janela){
        
        GdkEventKey key = event->key;  
        
        if(key.keyval != KEY_NEXT && key.keyval != KEY_BACK && key.keyval != KEY_ENTER && !(key.keyval == KEY_R && key.state == GDK_CONTROL_MASK))
            return 0;
        
        if(key.keyval == KEY_NEXT)
            nextImage(janela);
        
        if(key.keyval == KEY_BACK)
            backImage(janela);
        
        if(key.keyval == KEY_ENTER)
            finalizar_edicao(widget,janela);
        
        if(key.state == GDK_CONTROL_MASK && key.keyval == KEY_R)
			removeObjeto(widget,janela);
		
        return 1;
}

gboolean key_press_entry_imagem(GtkWidget *widget, GdkEvent  *event, InterfaceTreinamento *janela){
	
	GdkEventKey key = event->key; 
	
	if(key.keyval == KEY_ENTER)
		loadImagemTreinamento(widget,janela);
		
	else
		return 0;
		
	return 1;
}


int nextImage(InterfaceTreinamento *janela){

    
    if(janela == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/nextImage/janela");
    
    if(janela->controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/nextImage/janela->controlador");
    
	int resFuncao = exibeProximoObjeto(janela->controlador);
    
    if(resFuncao != INF_NOT_ERR)
		return *print_msg(ERR_PTR_NULL, "train_interface.c/nextImage/exibeProximoObjeto");
	
    return INF_NOT_ERR;
}

int backImage(InterfaceTreinamento *janela){

    if(janela == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/backImage/janela");
    if(janela->controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/backImage/janela->controlador");
    
    int resFuncao = exibeObjetoAnterior(janela->controlador);
    
    if(resFuncao != INF_NOT_ERR)
        return *print_msg(INF_NOT_ERR, "train_interface.c/backImage/exibeObjetoAnterior");
    
    return INF_NOT_ERR;
}

int removeObjeto(GtkWidget *object, InterfaceTreinamento *janela){
    
    if(janela == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/removeObjeto/janela");
    
    if(janela->controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface.c/removeObjeto/janela->controlador");
    
    ControladorJanelaTreino *controlador = (ControladorJanelaTreino*) janela->controlador;
    
    printf("train_interface/antes de removeObjetoTreinamento\n");
    
    int resFuncao = removeObjetoDaListaControlador(controlador);
    
    printf("train_interface/depois de removeObjetoTreinamento\n");
    
    if(resFuncao != INF_NOT_ERR)
         return *print_msg(ERR_GENERIC, "train_interface.c/removeObjeto/removeObjetoDaListaControlador");
    
    gtk_widget_grab_focus(janela->editText);
    
    return INF_NOT_ERR;
}

void setImage(char *pathImage, InterfaceTreinamento *janela){

    //GtkImage *image = (GtkImage) janela->image;
    gtk_image_set_from_file(((GtkImage*)janela->image), pathImage);
    
}

void setTextEntry(InterfaceTreinamento *janela, char caracter){
	
	if(janela == NULL)
		print_msg(ERR_PTR_NULL, "train_interface.c/setEntryText");
	else{
		
		char stringCaracter[2];
		stringCaracter[0] = caracter;
		stringCaracter[1] = '\0';
		
		gtk_entry_set_text(((GtkEntry*)janela->editText), stringCaracter);
	}
	
}

void loadImagemTreinamento(GtkWidget *object, InterfaceTreinamento *janela){
    
    const char* pathImage = gtk_entry_get_text(((GtkEntry*)janela->editTextPathImage));
    char *nameFileTrainin = gtk_entry_get_text(((GtkEntry*)janela->editTextFile));
    
    int isNameFileTraininVazio = isEntryVazio(((GtkEntry*)janela->editTextFile));
    
    ControladorJanelaTreino *controlador = (ControladorJanelaTreino*) janela->controlador;
    
    if(isNameFileTraininVazio)
        nameFileTrainin = DEFAULT_NAME_FILE_TRAININ;
    
    inicializaEdicao(janela->controlador, pathImage, nameFileTrainin);
    
}

int salvarTreinamento(GtkWidget *widget, InterfaceTreinamento *janela){
	
    salvaTreinamentoControlador(janela->controlador);
    
    on_window_destroy(NULL, janela);
	
    return 0;

}

char* getDadosEditTextFile(InterfaceTreinamento *train_interface){
    printf("\n Pegando nome\n");
    
    char *name = gtk_entry_get_text(((GtkEntry*)train_interface->editTextFile));
    
    return name;
}

int iniciaJanela(int argc, char **argv, char *pathXml, InterfaceTreinamento **train_interface){
    
    GtkBuilder *builder = NULL;
    GError *error= NULL;
    
    gtk_init(&argc, &argv );

    builder = gtk_builder_new();
    
    if( ! gtk_builder_add_from_file( builder, pathXml, &error ) ){
        g_warning( "%s", error->message );
       // g_free( error );
        return( 1 );
    }
    
    (*train_interface)->window = GTK_WIDGET( gtk_builder_get_object( builder, "windowTreinamento" ) );
    (*train_interface)->editText = GTK_WIDGET( gtk_builder_get_object( builder, "textEdit" ) );
    (*train_interface)->editTextFile = GTK_WIDGET( gtk_builder_get_object( builder, "editTextFile" ) );
    (*train_interface)->botaoOk = GTK_WIDGET( gtk_builder_get_object( builder, "botaoOk" ) );
    (*train_interface)->botaoRemove = GTK_WIDGET( gtk_builder_get_object( builder, "botaoRemove" ) );
    (*train_interface)->botaoNext = GTK_WIDGET( gtk_builder_get_object( builder, "next" ) );
    (*train_interface)->botaoBack = GTK_WIDGET( gtk_builder_get_object( builder, "back" ) );
    (*train_interface)->botaoSalvar = GTK_WIDGET( gtk_builder_get_object( builder, "botaoSalvar" ) );
    (*train_interface)->image = GTK_WIDGET( gtk_builder_get_object( builder, "image" ) );
    (*train_interface)->editTextPathImage = GTK_WIDGET( gtk_builder_get_object( builder, "entryCaminhoImagem" ) );
    (*train_interface)->botaoLoadImage = GTK_WIDGET( gtk_builder_get_object( builder, "botaoLoad" ) );
    
    gtk_builder_connect_signals( builder, (*train_interface) );

    gtk_widget_show( (*train_interface)->window );

    gtk_main();
    
    return 0;
}

void on_window_destroy(GtkWidget *object, InterfaceTreinamento *janela){

        gtk_main_quit();
}
