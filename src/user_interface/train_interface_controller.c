#include "train_interface_controller.h"

int contadorImagemSalvas = 0;

ControladorJanelaTreino* criaEInicializaControladorTreinamento(InterfaceTreinamento **mJanela){
    
    ControladorJanelaTreino *controlador = (ControladorJanelaTreino*) malloc(sizeof(ControladorJanelaTreino));
    
    controlador->janela = (*mJanela);
    
    controlador->treinamento = criaTreinamento();
    
    if(controlador->treinamento == NULL){
        print_msg(ERR_GENERIC, "train_interface_controller.c/criaEInicializaControlador \
                            /criaTreinamento");
        
        return NULL;
    }
              
    return controlador;
}

int inicializaEdicao(struct controladorJanelaTreinamento *controlador, char *pathImage, char *pathTrain){
    
    controlador->treinamento = geraTreinamentoGenerico(pathImage, pathTrain, RESOLUCAO_PADRAO);
    
    if(controlador->treinamento == NULL)
        return *print_msg(ERR_GENERIC, "train_interface_controller.c/processaImagemInicial \
                            /geraTreinamentoGenerico");
        
    char *pathImageAtual = getPathImageObjetoAtual(controlador->treinamento);
    
    if(pathImageAtual == NULL)
        return *print_msg(ERR_GENERIC, "train_interface_controller.c/inicializaEdicao/getPathImageObjetoAtual");
    else
        setImage(pathImageAtual, controlador->janela);
    
    return INF_NOT_ERR;
}

int finalizaEdicaoCaracter(ControladorJanelaTreino *controlador){
    
    if(controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/finalizaEdicaoCaracter/train_interface->controlador");
    
    InterfaceTreinamento *train_interface = controlador->janela;
    
    char caracter = getFirstCharText( ((GtkEntry*)train_interface->editText) );
    
    printf("Caracter pegado = %c\n", caracter);
    
    int resFuncao = finalizaEdicaoObjetoAtual(controlador->treinamento, caracter);
    
    if(resFuncao != INF_NOT_ERR)
        return *print_msg(resFuncao, "train_interface_controller.c/finalizaEdicaoCaracter");
    
    resFuncao = exibeProximoObjeto(controlador);
    
    if(resFuncao != INF_NOT_ERR)
        return *print_msg(ERR_GENERIC, "train_interface_controller.c/finalizaEdicaoCaracter/exibeProximoObjeto");
    
    return INF_NOT_ERR;
}



int salvaTreinamentoControlador(ControladorJanelaTreino *controlador){
    
    if(controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/salvaTreinamentoControlador");
    
    char *nameFile = getDadosEditTextFile(controlador->janela);
    
    if(nameFile == NULL || isNameVazio(nameFile))
        return *print_msg(ERR_GENERIC, "train_interface_controller.c/salvaTreinamentoControlador/nameFile com problema");
    
    int res = salvaTreinamentoLogicaTreino(controlador->treinamento, nameFile);
    
    if(res != INF_NOT_ERR)
        return *print_msg(ERR_GENERIC, "train_interface_controller.c/salvaTreinamentoControlador");
    
    return INF_NOT_ERR;
}

int isNameVazio(char *name){
    
    int isVazio = 1;
    
    while(*name != '\0' && isVazio){
        isVazio = (*name == '\n' || *name == ' ') ? 1 : 0;
        name++;
    }
    
    return isVazio;
}

int exibeProximoObjeto(ControladorJanelaTreino *controlador){
    
    if(controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/exibeProximoObjeto");
    
    int resFuncao = avancaObjetoEditar(controlador->treinamento);

   // if(resFuncao == ERR_OBJ_NULL_LIST)
        //exibeAlerta("Erro ao avançar objeto. Reiniciando lista...");
    
    //else if(resFuncao == INF_REINIT_LIST)
        //exibeAlerta("Fim da lista. Reiniciando lista...");

    if(resFuncao != INF_NOT_ERR)
        return *print_msg(resFuncao, "train_interface_controller.c/exibeProximoObjeto/avancaObjetoEditar");
    
    return exibeObjetoAtual(controlador);
    
}

int exibeObjetoAnterior(ControladorJanelaTreino *controlador){
    
    if(controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/exibeProximoObjeto");
    
    int resFuncao = retrocedeObjetoEditar(&(controlador->treinamento));

    //if(resFuncao == ERR_OBJ_NULL_LIST)
        //exibeAlerta("Erro ao avançar objeto. Reiniciando lista...");
        //i = 0;
  //  else if(resFuncao == INF_END_LIST)
        //exibeAlerta("Inicio da lista. Finalizando lista...");

    if(resFuncao != INF_NOT_ERR)
        return *print_msg(resFuncao, "train_interface_controller.c/exibeObjetoAnterior/retrocedeObjetoEditar");
    
    return exibeObjetoAtual(controlador);
    
}

int exibeObjetoAtual(ControladorJanelaTreino *controlador){
    
    if(controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/exibeObjetoAtual");
    
    char *pathImageAtual = getPathImageObjetoAtual(controlador->treinamento);
    
    if(pathImageAtual == NULL)
        return *print_msg(ERR_GENERIC, "train_interface_controller.c/exibeObjetoAtual/getPathImageObjetoAtual");
    
    setImage(pathImageAtual, controlador->janela);
    
    setTextEntry(controlador->janela, getCaracterObjetoAtual(controlador->treinamento));
    
    return INF_NOT_ERR;
}

int exibeAlerta(char *mensagem){
    
    return showDialog(0, NULL, mensagem);
}

int setPathFileTreinamento(ControladorJanelaTreino *controlador, char *path){
    
    if(controlador == NULL ||  path == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/setPathFileTreinamento");
    
    if(controlador->treinamento == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/setPathFileTreinamento/\
                            controlador->treinamento == NULL");
        
        controlador->treinamento->pathFileTrain = path;
    
    return INF_NOT_ERR;
}

char* incrementaContadorImagensSalvas(char *pathImageInicial){
    
    char *pathDir = PATH_IMG_CARCTER_SALVOS;
    
    int sizePath = strlen(pathImageInicial) + strlen(pathDir);
    
    char *pathCaracterAtual = (char*) malloc( sizePath * sizeof(char) + sizeof(int) + 1 + 3);
    
    sprintf(pathCaracterAtual, "%s%s%d.png\0", pathDir, pathImageInicial, contadorImagemSalvas);
    
    contadorImagemSalvas++;
    
    printf("\nPathCaracterAtual = %s", pathCaracterAtual);
    
    return pathCaracterAtual;
}

int salvaImagemCaracterEscolhido(ControladorJanelaTreino *controlador){
    
    if(controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/salvaImagemCaracterEscolhido");
    
    char *path = incrementaContadorImagensSalvas(controlador->treinamento->pathImage);
    
    /*ObjList *objAtual = controlador->treinamento->->objAtual;
     *    
     *    if(objAtual == NULL)
     *		return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/salvaImagemCaracterEscolhido/objAtual");
     *    
     *    ImgObject *objetoImagem = getObjetoDaImagemFromObjetoDaLista(&objAtual); 
     *	
     *	if(objetoImagem == NULL)
     *		return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/salvaImagemCaracterEscolhido/\bobjDaImg\b");
     *	
     *	if(objetoImagem->imgObjeto == NULL)
     *		return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/salvaImagemCaracterEscolhido");
     *	
     *	if(path == NULL)
     *		return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/salvaImagemCaracterEscolhido/path");
     *	
     *	int resFuncao = save_img(path, objetoImagem->imgObjeto);
     *	
     *	if(resFuncao != INF_NOT_ERR)
     *		return *print_msg(resFuncao, "train_interface_controller.c/salvaImagemCaracterEscolhido/save_img");
     */ 
    return INF_NOT_ERR; 
}

int removeObjetoDaListaControlador(ControladorJanelaTreino *controlador){
    
    if(controlador == NULL)
        return *print_msg(ERR_PTR_NULL, "train_interface_controller.c/removeObjetoDaListaControlador");
    
    ObjList *objeto = NULL;
    
    int resFuncao = removeObjetoTreinamento(controlador->treinamento);
    
    if(resFuncao != INF_NOT_ERR)
        return *print_msg(resFuncao, "train_interface_controller.c/removeObjetoDaListaControlador");
    
    return exibeObjetoAtual(controlador);
    
}

char* getText(GtkEntry *entry){
    char *ptr = gtk_entry_get_text(entry);
    
    return ptr;
}

char getFirstCharText(GtkEntry *entry){
    char caracter;
    char *ptr = getText(entry);
    
    if(ptr[0] == '\\' && ptr[1] == '0')
        caracter = ' ';
    else
        caracter = ptr[0];
    
    return caracter;
}
