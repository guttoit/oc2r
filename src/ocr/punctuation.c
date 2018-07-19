#include "punctuation.h"

Pontuacao* criaEstruturaSinalDePontuacao(){
    
    Pontuacao *mPontuacao = (Pontuacao*) malloc(sizeof(Pontuacao));
    
    if(mPontuacao == NULL)
        print_msg(ERR_MEMORY,"criaEstruturaSinalDePontuacao");
        
    return mPontuacao;
}

int inicializaSinalDePontuacao(Pontuacao **mPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"inicializaSinalDePontuacao");
        return ERR_PTR_NULL;
    }
    
    (*mPontuacao)->objetoDaImagemDaPontuacao = NULL;

    (*mPontuacao)->linhaDaPontuacao = NULL;
    
    (*mPontuacao)->caracterDaPontuacao = '\0';
    
    return INF_NOT_ERR;
}

int setObjetoDaImagemDaPontuacao(Pontuacao **mPontuacao, ImgObject **objetoDaImagemDaPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"setObjetoDaImagemDaPontuacao");
        return ERR_PTR_NULL;
    }
    
    (*mPontuacao)->objetoDaImagemDaPontuacao = (*objetoDaImagemDaPontuacao);
    
    return INF_NOT_ERR;
}

int setLinhaDaPontuacao(Pontuacao **mPontuacao, Line **linhaDaPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"setLinhaDaPontuacao");
        return ERR_PTR_NULL;
    }
    
    (*mPontuacao)->linhaDaPontuacao = (*linhaDaPontuacao);
    
    return INF_NOT_ERR;
}

int setCaracterDaPontuacao(Pontuacao **mPontuacao, char caracter){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"setCaracterDaPontuacao");
        return ERR_PTR_NULL;
    }
    
    (*mPontuacao)->caracterDaPontuacao = caracter;
    
    return INF_NOT_ERR;
}

ImgObject* getObjetoDaImagemDaPontuacao(Pontuacao **mPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"getObjetoDaImagemDaPontuacao");
        return NULL;
    }
    
    return (*mPontuacao)->objetoDaImagemDaPontuacao;
}

Line* getLinhaDaPontuacao(Pontuacao **mPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"getLinhaDaPontuacao");
        return NULL;
    }
    
    return (*mPontuacao)->linhaDaPontuacao;
}

char getCaracterDaPontucao(Pontuacao **mPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"getCaracterDaPontucao");
        return '\0';
    }
    
    return (*mPontuacao)->caracterDaPontuacao;
}

int liberaMemoriaPontuacaoEDependencias(Pontuacao **mPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"liberaMemoriaPontuacaoEDependencias");
        return ERR_PTR_NULL;
    }
    
    int err = INF_NOT_ERR;
    
    if((*mPontuacao)->objetoDaImagemDaPontuacao != NULL){
        err = freeObjDaImg(&((*mPontuacao)->objetoDaImagemDaPontuacao));
        
        if(err != INF_NOT_ERR)
            return err;
    }
    
    if((*mPontuacao)->linhaDaPontuacao != NULL){
        err = free_line_and_objs(&(*mPontuacao)->linhaDaPontuacao);
        
        if(err != INF_NOT_ERR)
            return err;
    }
    
    free((*mPontuacao));
    
    return INF_NOT_ERR;
}

int liberaMemoriaPontuacaoSemDependencias(Pontuacao **mPontuacao){
    
    if((*mPontuacao) == NULL){
        print_msg(ERR_PTR_NULL,"liberaMemoriaPontuacaoSemDependencias");
        return ERR_PTR_NULL;
    }
    
    (*mPontuacao)->objetoDaImagemDaPontuacao = NULL;
    
    (*mPontuacao)->linhaDaPontuacao = NULL;
        
    free((*mPontuacao));
    
    return INF_NOT_ERR;
}

