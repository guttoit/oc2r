#include "letter.h"

Letter* criaEstrutraLetra(){

    Letter *mLetra = (Letter*) malloc(sizeof(Letter));
    
    if(mLetra == NULL)
        print_msg(ERR_MEMORY,"criaEstrutraLetra");
        
    return mLetra;
    
}

int inicializaLetra(Letter **mLetra){
    
    if((*mLetra) == NULL){
        print_msg(ERR_PTR_NULL,"inicializaLetra");
        return ERR_PTR_NULL;
    }
    
    (*mLetra)->objetoDaImagemLetra = NULL;
    
//    (*mLetra)->linhaDaLetra = NULL;
    
    (*mLetra)->acentoDaLetra = NULL;
    
    (*mLetra)->caracterDaLetra = '\0';
    
    (*mLetra)->print =  &printInformacaoLetra;
    
    return INF_NOT_ERR;
}

int setObjetoDaImagemLetra(Letter **mLetra, ImgObject **objetoDaImagemLetra){
    
    if((*mLetra) == NULL || (*objetoDaImagemLetra) == NULL ){
        print_msg(ERR_PTR_NULL,"setObjetoDaImagemLetra");
        return ERR_PTR_NULL;
    }
    
    (*mLetra)->objetoDaImagemLetra = (*objetoDaImagemLetra);
    
    
    return INF_NOT_ERR;
}

/*int setLinhaDaLetra(Letter **mLetra, Line **linhaDaLetra){
    
    if((*mLetra) == NULL || (*linhaDaLetra) == NULL){
        print_msg(ERR_PTR_NULL,"setLinhaDaLetra");
        return ERR_PTR_NULL;
    }
    
    (*mLetra)->linhaDaLetra = (*linhaDaLetra);
    
    return INF_NOT_ERR;
}*/

int setAcentoDaLetra(Letter **mLetra, Accent **acentoDaLetra){
    
    if((*mLetra) == NULL || (*acentoDaLetra) == NULL){
        print_msg(ERR_PTR_NULL,"setAcentoDaLetra");
        return ERR_PTR_NULL;
    }
    
    (*mLetra)->acentoDaLetra = (*acentoDaLetra);
    
    return INF_NOT_ERR; 
}

int setCaracterDaLetra(Letter **mLetra, char caracterDaLetra){
    
    if((*mLetra) == NULL){
        print_msg(ERR_PTR_NULL,"setAcentoDaLetra");
        return ERR_PTR_NULL;
    }
    
    (*mLetra)->caracterDaLetra = caracterDaLetra;
    
    return INF_NOT_ERR;
}

/*int criaLetraComObjetoECaracter(Letter ** mLetra, struct \bobjDaImg\b **objeto, char caracter){
        
        if((*mLetra) != NULL){
            (*mLetra)->objetoDaImagemLetra = (*objeto);
            (*mLetra)->caracterDaLetra = caracter;
            (*objeto)->tipoDoObjetoDaImagem = OBJETO_TIPO_LETRA;
            
        }else{
           // (*mLetra) = criaEstrutraLetra();
           // inicializaLetra(mLetra);
            //criaLetraComObjetoECaracter(mLetra, objeto, caracter);
        }
        
        return INF_NOT_ERR;
        
}*/

ImgObject* getObjetoDaImagemLetra(Letter **mLetra){
    
    if((*mLetra) == NULL){
        print_msg(ERR_PTR_NULL,"getObjetoDaImagemLetra");
        return NULL;
    }
    
    return (*mLetra)->objetoDaImagemLetra;
}

/*Line* getLinhaDaLetra(Letter **mLetra){
    
    if((*mLetra) == NULL){
        print_msg(ERR_PTR_NULL,"getLinhaDaLetra");
        return NULL;
    }
    
    return (*mLetra)->linhaDaLetra;
}*/

Accent* getAcentoDaLetra(Letter **mLetra){
    
    if((*mLetra) == NULL){
        print_msg(ERR_PTR_NULL,"getAcentoDaLetra");
        return NULL;
    }
    
    return (*mLetra)->acentoDaLetra;
}

char getCaracterDaLetra(Letter **mLetra){
    
    if((*mLetra) == NULL){
        print_msg(ERR_PTR_NULL,"getCaracterDaLetra");
        return '\0';
    }
    
    return (*mLetra)->caracterDaLetra;
}

void printInformacaoLetra(void *mLetra){
    
    Letter *let = (Letter *) mLetra;
        
    printf("\n\n -------INFORMACOES SOBRE A LETRA-------\n");
    printf("\n -- Caracter da letter %c", let->caracterDaLetra);
    
    printf("\n --Construir funcao print para linha da letter e accent.");
        
}

int liberaMemoriaLetraEDependencias(Letter **letter){
    
  if(letter != NULL){
    
    if((*letter) != NULL){
      
      int err = INF_NOT_ERR;
    
      if((*letter)->objetoDaImagemLetra != NULL){
	  err = freeObjDaImg(&(*letter)->objetoDaImagemLetra);
	  
	  if(err != INF_NOT_ERR)
	      return err;
      }
      
      if((*letter)->acentoDaLetra != NULL)
	  err = free_accent_and_components(&(*letter)->acentoDaLetra);
      
      if(err != INF_NOT_ERR)
	  return err;
      
      free((*letter));
    }
  }
    
  return INF_NOT_ERR;
  
}

int liberaMemoriaLetraSemDependencias(Letter **letter){
    
  if(letter != NULL){
    
    if((*letter) != NULL){
      
      (*letter)->objetoDaImagemLetra = NULL;
        
      (*letter)->acentoDaLetra = NULL;
    
      free((*letter));
    }
  }
      
  return INF_NOT_ERR;
  
}
