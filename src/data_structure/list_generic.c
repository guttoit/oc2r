#include "list_generic.h"

ListGeneric* create_init_generic_list(){
  
  ListGeneric *list = criaListaGenerica();
  
  int cod_err = initListaGenerica(list);
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err, 
		  "list_generic/create_init_generic_list", 
		  "list");
    
    return NULL;
  }
    
  return list;
}

ListGeneric* criaListaGenerica(){
  
  ListGeneric *mListaGenerica = (ListGeneric*) malloc(sizeof(ListGeneric));
  
  if(mListaGenerica == NULL)
    print_msg(ERR_MEMORY,"criaListaGenerica");
  
  return mListaGenerica;  
}

int initListaGenerica(ListGeneric *mLista){
  
  if(mLista == NULL){
    print_msg(ERR_MEMORY,"initListaGenerica");
    return ERR_MEMORY;
  }
  
  mLista->objInicial = NULL;
  mLista->objFinal = NULL;
  mLista->objAtual = NULL;
  mLista->numObjs = 0;
  mLista->was_list_sorted = FALSE;
  mLista->print = &printInfoLista;
  
  return INF_NOT_ERR;
}

int addObjParaLista(ListGeneric *mLista, ObjList *obj){
  
  if(mLista == NULL || obj == NULL){
    print_msg(ERR_PTR_NULL,"addObjParaLista");
    return ERR_PTR_NULL;
  }
  
  //Caso seja a primeira vez que adiciona
  
  if(mLista->objInicial == NULL && mLista->objFinal == NULL){     
    
    mLista->objInicial = obj;
    mLista->objFinal = obj;
    mLista->objAtual = obj;
    
    obj->antObjeto = NULL;
    obj->proxObjeto = NULL; 
    
    //Caso a lista tenha dado erro no ultimo objeto
  }else if(mLista->objFinal == NULL){
    
    ObjList *mObjetoAux = mLista->objInicial;
    
    while(mObjetoAux->proxObjeto != NULL)
      mObjetoAux = mObjetoAux->proxObjeto;
    
    mLista->objFinal = mObjetoAux;
    
    obj->antObjeto = mLista->objFinal;
    
    mLista->objFinal->proxObjeto = obj; 
    
    mLista->objFinal = obj;
    
    //Caso a lista tenha dado erro no primeiro objeto
  }else if(mLista->objInicial == NULL){
    
    ObjList *mObjetoAux = mLista->objFinal;
    
    while(mObjetoAux->antObjeto != NULL)
      mObjetoAux = mObjetoAux->antObjeto;
    
    mLista->objInicial = mObjetoAux;
    
    obj->antObjeto = mLista->objFinal;
    
    mLista->objFinal->proxObjeto = obj; 
    
    mLista->objFinal = obj;
    
    //Caso padrao
  }else{
    
    obj->antObjeto = mLista->objFinal;
    
    mLista->objFinal->proxObjeto = obj; 
    
    mLista->objFinal = obj;
    
    mLista->objFinal->proxObjeto = NULL;
  }
  
  mLista->numObjs += 1;
  
  return INF_NOT_ERR;
  
}

int addObjGenericoParaLista(ListGeneric *lista, 
			       void *objeto, 
			       int tipo_obj, int (*freeObjInfo)(void**)){
  
  int err = INF_NOT_ERR;
  
  ObjList *obj_lista = criaObjLista();
  
  err = initObjLista(obj_lista, objeto, tipo_obj, freeObjInfo);
  
  if(err != INF_NOT_ERR){
    if(obj_lista != NULL)
      freeObjListaEDep(&obj_lista);
    
    return *print_msg(err,"addObjGenericoParaLista");
  }
  
  err = addObjParaLista(lista, obj_lista);
  
  if(err != INF_NOT_ERR)
    print_msg(err,"addObjGenericoParaLista");
  
  return err;
}

int setObjInicial(ListGeneric *mLista, ObjList *objInicial){
  
  if(mLista == NULL){
    print_msg(ERR_PTR_NULL,"setObjInicial");
    return ERR_PTR_NULL;
  }
  
  mLista->objInicial = objInicial;
  
  return INF_NOT_ERR;
}

int setObjFinal(ListGeneric *mLista, ObjList *objFinal){
  
  if(mLista == NULL){
    print_msg(ERR_PTR_NULL,"setObjFinal");
    return ERR_PTR_NULL;
  }
  
  mLista->objFinal = objFinal;
  
  return INF_NOT_ERR;
}

int setObjAtual(ListGeneric *mLista, ObjList *objAtual){
  
  if(mLista == NULL){
    print_msg(ERR_PTR_NULL,"setObjAtual");
    return ERR_PTR_NULL;
  }
  
  mLista->objAtual = objAtual;
  
  return INF_NOT_ERR;
}

ObjList* getObjDaLista(ListGeneric *mLista, int posObj){
  
  if(mLista == NULL){
    print_msg(ERR_PTR_NULL,"getObjDaLista");
    return NULL;
  }
  
  if(posObj < 0){
    print_msg(ERR_VAR_INV,"getObjDaLista");
    return NULL;
  }
  
  ObjList *objetoAux = mLista->objInicial;
  int i=0;
  
  while(i < posObj &&  objetoAux != NULL){
    objetoAux = objetoAux->proxObjeto;
    i++;
  }
  
  if(i < posObj && objetoAux == NULL)
    print_msg(ERR_POS_INV,"getObjDaLista");
  
  return objetoAux;
}

ObjList* get_initial_list_obj(ListGeneric *mLista){
  
  if(mLista == NULL){
    print_msg(ERR_PTR_NULL,"get_initial_list_obj");
    return NULL;
  }
  
  return mLista->objInicial;
}

ObjList* getObjFinal(ListGeneric *mLista){
  
  if(mLista == NULL){
    print_msg(ERR_PTR_NULL,"getObjFinal");
    return NULL;
  }
  
  return mLista->objFinal;
}

ObjList* getObjAtual(ListGeneric *mLista){
  
  if(mLista == NULL){
    print_msg(ERR_PTR_NULL,"getObjAtual");
    return NULL;
  }
  
  return mLista->objAtual;
}

int getNumObjDaLista(ListGeneric *mLista, int *num){
  
  if(mLista == NULL || num == NULL)
    return *print_msg(ERR_PTR_NULL,"getNumObjDaLista");
  
  *num = mLista->numObjs;
  
  return INF_NOT_ERR;
}

int is_list_empty(ListGeneric *mLista, int *result){
  
  if(mLista == NULL || result == NULL){
    return *print_big_msg(ERR_PTR_NULL,
			  "list_generic/is_list_empty",
			  "mLista");
  }
  
  *result = mLista->numObjs == 0 ? TRUE : FALSE;
  
  return INF_NOT_ERR;
}

int nextObjLista(ListGeneric *mLista){
  
  if(mLista == NULL)
    return *print_msg(ERR_PTR_NULL,"nextObjLista/mListaGenerica nula");
  
  if( mLista->objAtual == NULL){
    
    print_msg(ERR_OBJ_NULL_LIST,"nextObjLista/objAtual nulo");
    
    mLista->objAtual = mLista->objInicial;
    
    return ERR_OBJ_NULL_LIST;
  }
  
  if(mLista->objAtual->proxObjeto == NULL){
    
    mLista->objAtual = mLista->objInicial;
    
    return INF_REINIT_LIST;
  }
  
  mLista->objAtual = mLista->objAtual->proxObjeto;
  
  return  INF_NOT_ERR;
  
}

int backObjLista(ListGeneric *mLista){
  
  if(mLista == NULL)
    return *print_msg(ERR_PTR_NULL,"backObjLista/mListaGenerica nula");
  
  if( mLista->objAtual == NULL){
    
    print_msg(ERR_OBJ_NULL_LIST,"backObjLista/objAtual nulo");
    
    mLista->objAtual = mLista->objInicial;
    
    return ERR_OBJ_NULL_LIST;
  }
  
  if(mLista->objAtual->antObjeto == NULL){
    
    mLista->objAtual = mLista->objFinal;
    
    print_msg(INF_END_LIST,"backObjLista/objAtual é o inicial ");
    
    return INF_END_LIST;
  }
  
  mLista->objAtual = mLista->objAtual->antObjeto;
  
  return INF_NOT_ERR;
  
}

int removeObjAtualLista(ListGeneric *mLista){
  
  if(mLista == NULL)
    return *print_msg(ERR_PTR_NULL, "list_generic.c/removeObjAtualLista");
  
  if(mLista->objAtual == NULL)
    return *print_msg(ERR_GENERIC, "list_generic.c/removeObjAtualLista");
  
  return removeObjDaLista(mLista, mLista->objAtual);
  
}

int removeObjDaLista(ListGeneric *mLista, ObjList *mObj){
  
  if(mObj == NULL || mLista == NULL)
    return *print_msg(ERR_PTR_NULL, "list_generic.c/removeObjDaLista");
  
  int isObjetoAtual = mLista->objAtual == mObj;
  int isObjetoInicial = mLista->objInicial == mObj;
  int isObjetoFinal = mLista->objFinal == mObj;
  int haveProxObj = mObj->proxObjeto != NULL;
  int haveAntObj = mObj->antObjeto != NULL;
  
  if(haveProxObj || haveAntObj){
    
    if(haveProxObj && haveAntObj){
      mObj->proxObjeto->antObjeto = mObj->antObjeto;
      mObj->antObjeto->proxObjeto = mObj->proxObjeto;
    }
    
    else if(haveProxObj){
      //Tem que ser objeto inicial ja que nao tem antObjeto
      if(!isObjetoInicial)
	return *print_msg(ERR_OBJ_LIST_INV, "list_generic.c/removeObjDaLista");
      
      mLista->objInicial = mObj->proxObjeto;
      mObj->proxObjeto->antObjeto = mObj->antObjeto; //recebe nulo
      
    }else{
      //Tem que ser objeto Final ja que nao tem proxObjeto
      if(!isObjetoFinal)
	return *print_msg(ERR_OBJ_LIST_INV, "list_generic.c/removeObjDaLista");
      
      mLista->objFinal = mObj->antObjeto;
      mObj->antObjeto->proxObjeto = mObj->proxObjeto; //recebe nulo
    }
    
    //Se for objeto atual
    if(isObjetoAtual){
      mLista->objAtual = isObjetoFinal ? mObj->antObjeto : 
      mObj->proxObjeto;
    }
    
  }else{
    
    //Tem que ser objeto inicial, final e atual ja que nao tem nem antObjeto nem proxObjeto
    if(isObjetoFinal && isObjetoInicial && isObjetoAtual){
      
      mLista->objInicial = NULL;
      mLista->objFinal = NULL;
      mLista->objAtual = NULL;
      
    }else
      return *print_msg(ERR_OBJ_LIST_INV, "list_generic.c/removeObjDaLista");
    
  }
  
  mObj->proxObjeto = NULL;
  mObj->antObjeto = NULL;
  
  mLista->numObjs -= 1;
  
  freeObjListSemDep(&mObj);

  return INF_NOT_ERR;
}

int verify_sort_of_objs(ObjList *obj_1, ObjList *obj_2, int *result){
  
  ObjList *obj_aux_1 = obj_1;
  ObjList *obj_aux_2 = obj_2;
  
  if(obj_aux_1 == NULL || obj_aux_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "list_generic/verify_sort_of_objs");
  
  if(obj_aux_1 == obj_aux_2){
    *result = OBJ_1_AND_2_ARE_EQUAL;
  
    return INF_NOT_ERR;
  }
  
  while(obj_aux_1->proxObjeto != obj_aux_2 && obj_aux_1->proxObjeto != NULL)
    obj_aux_1 = obj_aux_1->proxObjeto;
  
  
  if(obj_aux_1->proxObjeto == obj_aux_2)
    *result = OBJ_2_IS_MAJOR;
  else
    *result = OBJ_1_IS_MAJOR;
  
  return INF_NOT_ERR;
  
}

int invertObjsPosicao(ListGeneric *list, ObjList *obj_1, ObjList *obj_2){
  
  int cod_err = INF_NOT_ERR;
  int sort_of_objs = 0;
  
  cod_err = verify_sort_of_objs(obj_1, obj_2, &sort_of_objs);
  
  if(cod_err != INF_NOT_ERR)
    return *print_msg(cod_err, "list_generic/invertObjsPosicao");
  
  if(sort_of_objs == OBJ_1_AND_2_ARE_EQUAL)
    return INF_NOT_ERR;
  
  if(sort_of_objs == OBJ_1_IS_MAJOR){
    
    ObjList *obj_aux = obj_1;
    obj_1 = obj_2;
    obj_2 = obj_aux;

  }
  
  if(obj_1->proxObjeto == obj_2){
    
    if(obj_1->antObjeto != NULL)
      obj_1->antObjeto->proxObjeto = obj_2;
    
    if(obj_2->proxObjeto != NULL)
      obj_2->proxObjeto->antObjeto= obj_1;
    
    
    obj_2->antObjeto = obj_1->antObjeto;
    obj_1->antObjeto = obj_2;
    
    obj_1->proxObjeto = obj_2->proxObjeto;
    obj_2->proxObjeto = obj_1;
    
  }else{
    
    ObjList *obj_temp = NULL;
    
    if(obj_1->antObjeto != NULL)
      obj_1->antObjeto->proxObjeto = obj_2;
    
    if(obj_2->proxObjeto != NULL)
      obj_2->proxObjeto->antObjeto = obj_1;
    
    if(obj_1->proxObjeto != NULL)
      obj_1->proxObjeto->antObjeto= obj_2;
    
    if(obj_2->antObjeto != NULL)
      obj_2->antObjeto->proxObjeto = obj_1;
    
    
    obj_temp = obj_2->antObjeto;
    
    obj_2->antObjeto = obj_1->antObjeto;
    obj_1->antObjeto = obj_temp;
    
    obj_temp = obj_2->proxObjeto;
    
    obj_2->proxObjeto = obj_1->proxObjeto;
    obj_1->proxObjeto = obj_temp;
  }
  
  if(list->objInicial == obj_1)
    list->objInicial = obj_2;
  
  else if(list->objInicial == obj_2)
    list->objInicial = obj_1;
  
  if(list->objFinal == obj_2)
    list->objFinal = obj_1;
  
  else if (list->objFinal == obj_1)
    list->objFinal = obj_2;
  
  ObjList *temp = obj_2;
  obj_2 = obj_1;
  obj_1 = temp;
  
  return INF_NOT_ERR;
}

int sort_generic_list(ListGeneric *list, 
		      int (*func_compare) (ObjList *obj_1, 
					   ObjList *obj_2,
					   int *result)){
  
  int result = 0;
  
  ObjList *obj_actual = get_initial_list_obj(list);
  
  ObjList *obj_minor = obj_actual;
  
  ObjList *obj_aux = NULL;
  
  while(obj_actual != NULL){
    
    obj_aux = obj_actual;
    obj_minor = obj_aux;
    
    while(obj_aux != NULL){
      
      func_compare(obj_minor, obj_aux, &result);
      
      if(result == OBJ_1_IS_MAJOR)
	obj_minor = obj_aux;
      
      obj_aux = obj_aux->proxObjeto;
    
      
    }
    
    invertObjsPosicao(list, obj_actual, obj_minor);
    
    obj_actual = obj_minor->proxObjeto;
    
  }
  
  list->was_list_sorted = TRUE;
  
  return INF_NOT_ERR;
}

void printInfoLista(void *mLista){
  
  ListGeneric *mListaGen = (ListGeneric *) mLista;
  
  if(mListaGen == NULL){
    print_msg(ERR_PTR_NULL,"printInfoLista");
  }
  else{
    
    printf("\n\n -------INFORMACOES SOBRE LISTA GENERICA-------\n");
    printf("\n Nº de objetos: %d", mListaGen->numObjs);
    
    if(mListaGen->objInicial == NULL && mListaGen->numObjs > 0)
      printf("\n Lista com defeito. O numero de objetos e maior que zero e o objeto inicial nao existe.");
    
    ObjList *objAux = mListaGen->objInicial;
    
    while(objAux != NULL){
      objAux->print(objAux);
      objAux = objAux->proxObjeto;
    }
    
  }
}

int freeListaEDep(ListGeneric **mLista){
  
  if(mLista != NULL){
    
    if((*mLista) != NULL){
      
      if((*mLista)->objInicial != NULL){
      
	int err = INF_NOT_ERR;
  
	ObjList **objetoAux = &(*mLista)->objInicial;
	ObjList *objTemp = *objetoAux;
	
	(*mLista)->objInicial = NULL;
	
	(*mLista)->objFinal = NULL;
	
	(*mLista)->objAtual = NULL;
	
	while((*objetoAux) != NULL){
	  
	  objTemp = (*objetoAux)->proxObjeto;
	  
	  err = freeObjListaEDep(objetoAux);
	  
	  if(err != INF_NOT_ERR)
	    return err;
	  
	  (*objetoAux) = objTemp;
	  
	  (*mLista)->numObjs--; 
	}
	
	(*mLista)->numObjs = 0;
	
	free((*mLista));
	
	(*mLista) = NULL;

      }
	
    }
  
    
  }
  
  
  return INF_NOT_ERR;
}

int freeListaSemDep(ListGeneric **mLista){
  
  if(mLista != NULL){
    
    if((*mLista) != NULL){
      
      if((*mLista)->objInicial != NULL){
      
	int err = INF_NOT_ERR;
  
	ObjList **objetoAux = &(*mLista)->objInicial;
	ObjList *objTemp = *objetoAux;
	
	(*mLista)->objInicial = NULL;
	
	(*mLista)->objFinal = NULL;
	
	(*mLista)->objAtual = NULL;
	
	while((*objetoAux) != NULL){
	  
	  objTemp = (*objetoAux)->proxObjeto;
	  
	  if(objTemp != NULL)
	    objTemp->antObjeto = NULL;
	  
	  err = freeObjListSemDep(objetoAux);
	  
	  if(err != INF_NOT_ERR)
	    return err;
	  
	  (*objetoAux) = objTemp;
	  
	  (*mLista)->numObjs--; 
	}
	
	(*mLista)->numObjs = 0;
	
	free((*mLista));
	
	(*mLista) = NULL;

      }
	
    }
  
    
  }
  
  return INF_NOT_ERR;
}
