#include "object_list.h"

ObjList* criaObjLista(){
    
    ObjList *mObjeto = (ObjList*) malloc(sizeof(ObjList));
    
    if(mObjeto == NULL)
        print_msg(ERR_MEMORY,"criaObjLista");
        
    return mObjeto;
}
  
int initObjLista(ObjList *obj, 
			    void *objInfo, 
			    int tipoDoObjeto, 
			    int (*ptr) (void**)){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,"initObjLista");
        return ERR_PTR_NULL;
    }
    
    if(isTipoObjLista(tipoDoObjeto) == ERR_TYPE_OBJ_INV)
        return *print_msg(ERR_TYPE_OBJ_INV,
				      "initObjLista");
    
    if(objInfo == NULL || ptr == NULL)
      print_msg(WAR_GENERIC,"initObjLista");
      
    if(objInfo == NULL)
      print_msg(WAR_GENERIC,"initObjLista");
    
    
    obj->objetoInformacao = objInfo;
    obj->tipoDoObjeto = tipoDoObjeto;
    obj->proxObjeto = NULL;
    obj->antObjeto = NULL;
    obj->print = &printInfoObjLista ;
    obj->freeObjInfo = ptr;
    
    return INF_NOT_ERR;
}

int isTipoObjLista(int tipoParaVerificar){    
    
  if(tipoParaVerificar >= OBJETO_TIPO_LETRA &&  tipoParaVerificar <= TYPE_OBJ_NEURAL)
    return INF_NOT_ERR;
  else
    return ERR_TYPE_OBJ_INV;
  
}

int setTipoObjLista(ObjList *obj, int tipoDoObjeto){
    
  
  if(obj == NULL){
      print_msg(ERR_PTR_NULL,"setTipoObjLista");
      return ERR_PTR_NULL;
  }
  
  if(isTipoObjLista(tipoDoObjeto) == ERR_TYPE_OBJ_INV){
      
      print_msg(ERR_TYPE_OBJ_INV,"setTipoObjLista");
      return ERR_TYPE_OBJ_INV;
  }
  
  obj->tipoDoObjeto = tipoDoObjeto;
  
  return INF_NOT_ERR;
}

int setObjInfo(ObjList *obj, void *objInfo){
    
    if(obj == NULL)
      return *print_msg(ERR_PTR_NULL,
				      "setObjInfo");
    
    if(objInfo == NULL)
      print_msg(WAR_GENERIC,"setObjInfo");
    
    obj->objetoInformacao = objInfo;
    
    return INF_NOT_ERR;
}

int setProxObjeto(ObjList *obj, ObjList *proxObj){
    
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL,"setProxObjeto");
  
  obj->proxObjeto = proxObj;
  
  return INF_NOT_ERR;
}

int setAntObjeto(ObjList *obj, ObjList *antObjeto){
    
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL,"setAntObjeto");
  
  obj->antObjeto = antObjeto;
  
  return INF_NOT_ERR;
}

int setFuncFreeObjInfo(ObjList *obj, 
		       int(*freeObjInfo) (void**)){
    
  if(obj == NULL){
    return *print_msg(ERR_PTR_NULL,
				    "setFuncFreeObjInfo");
  }
  
  if(freeObjInfo == NULL)
    print_msg(WAR_SET_PTR_NULL ,"setFuncFreeObjInfo");
  
  obj->freeObjInfo = freeObjInfo;
  
  return INF_NOT_ERR;
}

void* getFuncFreeObjInfo(ObjList *obj){
    
  if(obj == NULL){
    print_msg(ERR_PTR_NULL,"getFuncFreeObjInfo");
    return NULL;
  }
  
  
  return obj->freeObjInfo;
}

int get_list_obj_type(ObjList *obj, int *type){
    
  if(obj == NULL){
    print_msg(ERR_PTR_NULL,"object_list/get_list_obj_type");
    return ERR_PTR_NULL;
  }
  
  *type = obj->tipoDoObjeto;
  
  return INF_NOT_ERR;
}

void* get_obj_Info(ObjList *obj){
    
  if(obj == NULL){
    print_msg(ERR_PTR_NULL,"get_obj_Info");
    return NULL;
  }
  
  if(obj->objetoInformacao == NULL){
    print_msg(ERR_PTR_NULL,
			  "object_list.c/get_obj_Info");
    return NULL;
  }
  
  return obj->objetoInformacao;
}

ObjList* getProxObjeto(ObjList *obj){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,"getProxObjeto");
        return NULL;
    }
    
    return obj->proxObjeto;
}

ObjList* getAntObjeto(ObjList *obj){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,"getAntObjeto");
        return NULL;
    }
    
    return obj->antObjeto;
}

void printInfoObjLista(void *mObjeto){
    
    ObjList * mObjetoDaLista = (ObjList *) mObjeto;
    
     if(mObjetoDaLista == NULL){
        print_msg(ERR_PTR_NULL,"printInfoObjLista");
    }
    else{
        
        printf("\n\n -------INFORMACOES OBJETO DA LISTA GENERICA-------\n");
        printf("\n -- Tipo do objeto: %d", mObjetoDaLista->tipoDoObjeto);
        
        
        printf("\n -- Objeto Informacao: \n");
        
        
    }
    
}

int freeObjListaEDep(ObjList **obj){
    
    if((*obj) == NULL){
      print_msg(ERR_PTR_NULL,
			    "freeObjListaEDep");
      return ERR_PTR_NULL;
    }
    
    int (*ptr) (void**) = (*obj)->freeObjInfo;

    int err = INF_NOT_ERR;
    
    if((*obj)->objetoInformacao != NULL && ptr != NULL){
        err = (ptr)(&((*obj)->objetoInformacao));

    }else if(ptr == NULL && (*obj)->objetoInformacao != NULL){
      print_msg(WAR_GENERIC,
			      "freeObjListaEDep");
    }
    
    
    (*obj)->proxObjeto = NULL;
    (*obj)->antObjeto = NULL;
    (*obj)->objetoInformacao = NULL;
    (*obj)->freeObjInfo = NULL;
    (*obj)->print = NULL;
    
    free((*obj));
    
    (*obj) = NULL;
    
    return err;
}

int freeObjListSemDep(ObjList **obj){
    
    if((*obj) == NULL){
        print_msg(ERR_PTR_NULL,"freeObjListSemDep");
        return ERR_PTR_NULL;
    }
    
    (*obj)->proxObjeto = NULL;
    (*obj)->antObjeto = NULL;
    (*obj)->objetoInformacao = NULL;
    (*obj)->freeObjInfo = NULL;
    (*obj)->print = NULL;
    
    free((*obj));
    
    (*obj) = NULL;
    
    return INF_NOT_ERR;
}
