#include <stdio.h>
#include <stdlib.h>
#include "../user_interface/train_interface_controller.h"
#include "../user_interface/train_interface.h"

int main(int argc, char** argv){

     struct interfaceTreino *janela = NULL;
     int resFuncao = criaEInicializaInterfaceTreinamento(&janela);
     
     if(resFuncao != INF_NOT_ERR)
        return *print_msg(ERR_GENERIC, "createDataTrainingWithInterface.c/functionPrincipal");
        
     struct controladorJanelaTreinamento *controlador = criaEInicializaControladorTreinamento(&janela);
     
    setControladorJanelaTreino(&janela,&controlador);
    
    iniciaJanela(argc, argv, "src/user_interface/janelaTreino2.glade", &janela);
    
    return 0;

}
