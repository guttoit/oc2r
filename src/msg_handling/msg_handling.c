#include "msg_handling.h"

int cod_aux = INF_NOT_ERR;

int* print_msg(int cod_msg, char* name_func){
  
  if(name_func == NULL){
    printf("Erro. A funcao print_msg recebeu parametro(s) nulo(s).\n");
    cod_aux = ERR_PTR_NULL;
    return &cod_aux;
  }
  
  switch(cod_msg){
    
    case INF_NOT_ERR:
      
      printf("INF_NOT_ERR. %s.\n ", name_func);
      cod_aux = INF_NOT_ERR;
      return &cod_aux;
      
    case INF_REINIT_LIST:
      printf("INF_REINIT_LIST. Objeto atual é o ultimo objeto. \
      %s. Reiniciando lista\n ", name_func);
      
      cod_aux = INF_REINIT_LIST;
      return &cod_aux;
      
    case INF_END_LIST:
      printf("INF_END_LIST. Objeto atual e o primeiro objeto. \
      %s. Finalizando lista\n ", name_func);
      
      cod_aux = INF_END_LIST;
      return &cod_aux;
      
    case WAR_GENERIC:
      printf("WAR_GENERIC. Warning em %s.\n ", name_func);
      cod_aux = WAR_GENERIC;
      return &cod_aux;
      
    case WAR_END_FILE:
      printf("WAR_END_FILE. Arquivo esta na posicao final. %s.\n ", name_func);
      cod_aux = WAR_END_FILE;
      return &cod_aux;
      
    case WAR_SET_PTR_NULL:
      printf("WAR_SET_PTR_NULL. Setando variavel ponteiro \
      com valor nulo em %s.\n ", name_func);
      
      cod_aux = WAR_SET_PTR_NULL;
      return &cod_aux;
      
      
    case ERR_PTR_NULL:
      
      printf("ERR_PTR_NULL. A funcao %s recebeu parametros \
      nulos.\n", name_func);
      
      cod_aux = ERR_PTR_NULL;
      return &cod_aux;
      
    case ERR_VAR_INV:
      
      printf("ERR_VAR_INV. A funcao %s recebeu variavei(s) \
      invalida(s).\n", name_func);
      
      cod_aux = ERR_VAR_INV;
      return &cod_aux;
      
    case ERR_PARAM_INV:
      
      printf("ERR_PARAM_INV. A funcao %s recebeu parametros(s) \
      invalido(s).\n", name_func);
      
      cod_aux = ERR_PARAM_INV;
      return &cod_aux;
      
    case ERR_MEMORY:
      
      printf("ERR_MEMORY. Nao foi possivel alocar memoria para o ponteiro \
      na funcao %s.\n", name_func);
      
      cod_aux = ERR_MEMORY;
      return &cod_aux;
      
    case ERR_GENERIC:
      
      printf("ERR_GENERIC. Ocorreu um erro inesperado \
      na funcao %s.\n ", name_func);
      
      cod_aux = ERR_GENERIC;
      return &cod_aux;
      
    case ERR_CONVERTING:
      
      printf("ERR_CONVERTING. Ocorreu um erro de conversao \
      na funcao %s.\n ", name_func);
      
      cod_aux = ERR_CONVERTING;
      return &cod_aux;
      
    case ERR_POS_INV:
      
      printf("ERR_POS_INV. Erro de acesso a posicao invalida \
      na funcao %s.\n ", name_func);
      
      cod_aux = ERR_POS_INV;
      return &cod_aux;
      
    case ERR_TYPE_OBJ_INV:
      
      printf("ERR_TYPE_OBJ_INV. Tipo de objeto invalido na funcao \
      %s.\n ", name_func);
      
      cod_aux = ERR_TYPE_OBJ_INV;
      return &cod_aux;
      
    case ERR_NUM_OUT_DIF:
      
      printf("ERR_NUM_OUT_DIF. Ocorreu um evento inesperado\
      na funcao %s.\n ", name_func);
      
      printf("Provavelmente a quantidade de saidas do objeto treinamento e \
      diferente do vetor de mapeamento objeto_saida.\n ");
      
      cod_aux = ERR_NUM_OUT_DIF;
      return &cod_aux;
      
    case ERR_OBJ_NO_THERE:
      
      printf("ERR_OBJ_NO_THERE. Ocorreu um evento inesperado na funcao %s. \
      Objeto nao existe na lista.\n ", name_func);
      
      cod_aux = ERR_OBJ_NO_THERE;
      return &cod_aux;
      
    case ERR_IO:
      
      printf("ERR_IO. Erro de escrita e/ou leitura de arquivo. Funcao \
      %s.\n ", name_func);
      
      cod_aux = ERR_IO;
      return &cod_aux;
      
    case ERR_FILE_NOT_EXIST:
      
      printf("ERR_FILE_NOT_EXIST. Nao foi possivel abrir um arquivo \
      na funcao %s. Arquivo nao existe\n ", name_func);
      
      cod_aux = ERR_FILE_NOT_EXIST;
      return &cod_aux;
      
    case ERR_OBJ_NULL_LIST:
      printf("ERR_OBJ_NULL_LIST. Objeto da lista nulo %s.\n ", name_func);
      cod_aux = ERR_OBJ_NULL_LIST;
      return &cod_aux;
      
    case ERR_OBJ_LIST_INV:
      printf("ERR_OBJ_LIST_INV. Objeto da lista invalido %s.\n ", name_func);
      cod_aux = ERR_OBJ_LIST_INV;
      return &cod_aux;
      
    case ERR_COLOR_INV:
      printf("ERR_COLOR_INV. Canal de cor invalido %s.\n ", name_func);
      cod_aux = ERR_COLOR_INV;
      return &cod_aux;
      
      
      
    default:
      
      printf("Erro. O codigo de erro passado para a funcao print_msg \
      a parti de %s nao existe.\n", name_func);
      
      cod_aux = ERR_PARAM_INV;
      return &cod_aux;
      
  }
  
}

int* print_big_msg(int cod_msg, char* name_func, char *name_obj){
  
  if(name_func != NULL && name_obj != NULL){
  
    char msg_obj_1[] = "The terms,";
    char msg_obj_2[] = ",presents in function";
    char msg_obj_3[] = "caused some error.";
    
    int len_msg = strlen(name_func) + 
		  strlen(name_obj)  + 
		  strlen(msg_obj_1) + 
		  strlen(msg_obj_2) + 
		  strlen(msg_obj_3) + 1;
    
    char *msg = malloc(len_msg);
    
    sprintf(msg, "%s %s %s %s %s\n", msg_obj_1, 
				     name_obj, 
				     msg_obj_2, 
				     name_func,
				     msg_obj_3);
   
    return print_msg(cod_msg, msg);
  }
  
  return print_msg(cod_msg, name_func);
  
}

