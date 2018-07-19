#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "object_list.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _list_generic{
    
    ObjList *objInicial;
    ObjList *objFinal;
    
    ObjList *objAtual;
    
    int numObjs;
    
    void (*print) (void*);
    
    int was_list_sorted;
    
}ListGeneric;

ListGeneric* create_init_generic_list();

ListGeneric* criaListaGenerica();

int initListaGenerica(ListGeneric* mLista );

int addObjParaLista(ListGeneric *mLista, ObjList *obj);

int addObjGenericoParaLista(ListGeneric *lista, 
			    void *objeto, 
			    int tipo_obj, 
			    int (*freeObjInfo)(void**));

int setObjInicial(ListGeneric *mLista, ObjList *objInicial);

int setObjFinal(ListGeneric *mLista, ObjList *objFinal);

int setObjAtual(ListGeneric *mLista, ObjList *objAtual);

ObjList* getObjDaLista(ListGeneric *mLista, int posObj);

ObjList* get_initial_list_obj(ListGeneric *mLista);

ObjList* getObjFinal(ListGeneric *mLista);

ObjList* getObjAtual(ListGeneric *mLista);

int getNumObjDaLista(ListGeneric *mLista, int *num);

int is_list_empty(ListGeneric *mLista, int *result);

int nextObjLista(ListGeneric *mLista);

int backObjLista(ListGeneric *mLista);

int removeObjAtualLista(ListGeneric *mLista);

int removeObjDaLista(ListGeneric *mLista, ObjList *mObj);

int invertObjsPosicao(ListGeneric *list, 
		      ObjList *obj_1, 
		      ObjList *obj_2);

int sort_generic_list(ListGeneric *list, 
		      int (*func_compare) (ObjList *obj_1, 
					   ObjList *obj_2,
					   int *result));

void printInfoLista(void *mLista);

int freeListaEDep(ListGeneric **mLista);

int freeListaSemDep(ListGeneric **mLista);


#endif
