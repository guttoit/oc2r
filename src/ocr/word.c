#include "word.h"

Word* criaEstruturaPalavra(){
    
    Word *mPalavra = (Word*) malloc(sizeof(Word));
    
    if(mPalavra == NULL)
        print_msg(ERR_MEMORY,"criaEstruturaPalavra");
        
    return mPalavra;
}

int inicializaPalavra(Word **mPalavra){
    
    if((*mPalavra) == NULL){
        print_msg(ERR_PTR_NULL,"inicializaPalavra");
        return ERR_PTR_NULL;
    }
    
    (*mPalavra)->listaDeObjetosDaPalavra = criaListaGenerica();
    int res = initListaGenerica((*mPalavra)->listaDeObjetosDaPalavra);
    
    (*mPalavra)->linhaDaPalavra = NULL;
    
    (*mPalavra)->tamanhoDaPalavra = 0;
    
    return res;
}

int add_character(Word *word, Letter *character){
    
  int (*ptr)(void**) = (int (*)(void**)) &liberaMemoriaLetraEDependencias;
  
  int res = addObjGenericoParaLista(word->listaDeObjetosDaPalavra,
					(void*)character,
					OBJETO_TIPO_LETRA,
					ptr);
  
  if(res == INF_NOT_ERR)
      word->tamanhoDaPalavra++;
  
  return res;
}


int setListaDeObjetosDaPalavra(Word **mPalavra, ListGeneric **listaDeObjetosDaPalavra){
    
    if((*mPalavra) == NULL){
        print_msg(ERR_PTR_NULL,"setListaDeObjetosDaPalavra");
        return ERR_PTR_NULL;
    }
    
    (*mPalavra)->listaDeObjetosDaPalavra = (*listaDeObjetosDaPalavra);

    return INF_NOT_ERR;
}

int setTamanhoDaPalavra(Word **mPalavra, int tamanhoDaPalavra){
    
    if((*mPalavra) == NULL){
        print_msg(ERR_PTR_NULL,"setTamanhoDaPalavra");
        return ERR_PTR_NULL;
    }
    
    (*mPalavra)->tamanhoDaPalavra = tamanhoDaPalavra;

    return INF_NOT_ERR;
}

int setLinhaDaPalavra(Word **mPalavra, void *linhaDaPalavra){
    
    if((*mPalavra) == NULL){
        print_msg(ERR_PTR_NULL,"setLinhaDaPalavra");
        return ERR_PTR_NULL;
    }
    
    (*mPalavra)->linhaDaPalavra = linhaDaPalavra;

    return INF_NOT_ERR;
}

ListGeneric* getListaDeObjetosDaPalavra(Word **mPalavra){
    
    if((*mPalavra) == NULL){
        print_msg(ERR_PTR_NULL,"getListaDeObjetosDaPalavra");
        return NULL;
    }
    
    return (*mPalavra)->listaDeObjetosDaPalavra;
}

int getTamanhoDaPalavra(Word **mPalavra){
    
    if((*mPalavra) == NULL){
        print_msg(ERR_PTR_NULL,"getTamanhoDaPalavra");
        return ERR_PTR_NULL;
    }
    
    return (*mPalavra)->tamanhoDaPalavra;
}

void* getLinhaDaPalavra(Word **mPalavra){
    
    if((*mPalavra) == NULL){
        print_msg(ERR_PTR_NULL,"getLinhaDaPalavra");
        return NULL;
    }
    
    return (*mPalavra)->linhaDaPalavra;
}


int liberaMemoriaPalavraEDepencencias(Word **word){
    
  if(word != NULL){
    
    if((*word) != NULL){
      
      Word **word = (Word**)word;
    
      int err = INF_NOT_ERR;
      
      if((*word)->listaDeObjetosDaPalavra != NULL){
	  err = freeListaEDep(&(*word)->listaDeObjetosDaPalavra);
	  
	  if(err != INF_NOT_ERR)
	      return err;
      }
      
      (*word)->linhaDaPalavra = NULL;
      
      free((*word));
    }
  } 
  
  return INF_NOT_ERR;
}

int liberaMemoriaPalavraSemDepencencias(Word **word){
    
  if(word != NULL){
  
    if((*word) != NULL){
      
      Word **word = (Word**)word;
  
      (*word)->listaDeObjetosDaPalavra = NULL;
      
      (*word)->linhaDaPalavra = NULL;
      
      free((*word));
    }
  
  }
        
  return INF_NOT_ERR;

  
}

