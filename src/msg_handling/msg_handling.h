#ifndef MSG_HANDLING_H
#define MSG_HANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//######### Códigos de informação [2 ..102] ##############

#define INF_NOT_ERR 2
#define INF_REINIT_LIST 3
#define INF_END_LIST 4

//######### Códigos de erro [-1 ... -100] #################

#define ERR_MEMORY -1
#define ERR_VAR_INV -2
#define ERR_GENERIC -3
#define ERR_POS_INV -4
#define ERR_TYPE_OBJ_INV -5
#define ERR_CONVERTING -6
#define ERR_PARAM_INV -7
#define ERR_OBJ_NO_THERE -8
#define ERR_PTR_NULL -9
#define ERR_NUM_OUT_DIF -10
#define ERR_IO -11
#define ERR_FILE_NOT_EXIST -12
#define ERR_OBJ_NULL_LIST -13
#define ERR_OBJ_LIST_INV -14
#define ERR_COLOR_INV -15

//######### Codigos de WARNINGS. [-101 até -200] ##############

#define WAR_GENERIC -101
#define WAR_SET_PTR_NULL -102
#define WAR_END_FILE -103
#define WAR_PROB_NEGATIVE -104


/**
 * Imprime msg com o código da mensagem e o nome da funcao que ocorreu o evento.
 * Retorna o código da msg.
 */
int* print_msg(int cod_msg, char* name_func);

/**
 * Imprime msg com o código da mensagem , o nome da funcao que ocorreu o erro
 * e o objeto ou motivo que ocasionou o erro.
 * Retorna o código da msg.
 */
int* print_big_msg(int cod_msg, char* name_func, char *name_obj);

#define debug_obj(obj,msg) if(obj==0){print_msg(WAR_GENERIC,msg); return WAR_GENERIC;}

#endif
