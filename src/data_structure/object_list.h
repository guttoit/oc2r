#ifndef LIST_OBJECT_H
#define LIST_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _object_list{
    
    void *objetoInformacao;
    
    int tipoDoObjeto;
    
    struct _object_list *proxObjeto;
    
    struct _object_list *antObjeto;
    
    void (*print) (void *);
    
    int (*freeObjInfo) (void**);
    
}ObjList;

ObjList* criaObjLista();

int initObjLista(ObjList *obj, 
			    void *objInfo, 
			    int tipoDoObjeto, 
			    int (*ptr) (void**));

int isTipoObjLista(int tipoParaVerificar);

int setTipoObjLista(ObjList *obj, int tipoDoObjeto);

int setObjInfo(ObjList *obj, void *objInfo);

int setProxObjeto(ObjList *obj, ObjList *proxObj);

int setAntObjeto(ObjList *obj, ObjList *antObjeto);

int setFuncFreeObjInfo(ObjList *obj, 
		       int(*freeObjInfo) (void**));

void* getFuncFreeObjInfo(ObjList *obj);

int get_list_obj_type(ObjList *obj, int *type);

void* get_obj_Info(ObjList *obj);

ObjList* getProxObjeto(ObjList *obj);

ObjList* getAntObjeto(ObjList *obj);

void printInfoObjLista(void *mObjetoDaLista);

int freeObjListaEDep(ObjList **obj);

int freeObjListSemDep(ObjList **obj);

#endif
