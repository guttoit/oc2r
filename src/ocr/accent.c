#include "accent.h"

Accent* create_accent(){
    
    Accent *mAcento = (Accent*) malloc(sizeof(Accent));
    
    if(mAcento == NULL)
        print_msg(ERR_MEMORY,"create_accent");
        
    return mAcento;
}

int init_accent(Accent **mAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"init_accent");
        return ERR_PTR_NULL;
    }
    
    (*mAcento)->objetoDaImagemDoAcento = NULL;

    (*mAcento)->letraDoAcento = NULL;

    (*mAcento)->caracterDoAcento = '\0';
    
    return INF_NOT_ERR;
}

int set_obj_img_accent(Accent **mAcento, ImgObject **objetoDaImagemDoAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"set_obj_img_accent");
        return ERR_PTR_NULL;
    }
    
    (*mAcento)->objetoDaImagemDoAcento = (*objetoDaImagemDoAcento);
    
    return INF_NOT_ERR;
}

int set_letter_accent(Accent **mAcento, void *letraDoAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"set_letter_accent");
        return ERR_PTR_NULL;
    }
    
    (*mAcento)->letraDoAcento = letraDoAcento;
    
    return INF_NOT_ERR;
}

int set_char_accent(Accent **mAcento, char caracter){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"set_char_accent");
        return ERR_PTR_NULL;
    }
    
    (*mAcento)->caracterDoAcento = caracter;
    
    return INF_NOT_ERR;
}

ImgObject* get_obj_img_accent(Accent **mAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"get_obj_img_accent");
        return NULL;
    }
    
    return (*mAcento)->objetoDaImagemDoAcento;
}

void* get_letter_accent(Accent **mAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"get_letter_accent");
        return NULL;
    }
    
    return (*mAcento)->letraDoAcento;
}

char get_char_accent(Accent **mAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"get_char_accent");
        return '\0';
    }
    
    return (*mAcento)->caracterDoAcento;
}

int free_accent_and_components(Accent **mAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"free_accent_and_components");
        return ERR_PTR_NULL;
    }
    
    int err = INF_NOT_ERR;
    
    if((*mAcento)->objetoDaImagemDoAcento != NULL){
        err = freeObjDaImg(&(*mAcento)->objetoDaImagemDoAcento);
        
        if(err != INF_NOT_ERR)
            return err;
    }
    
    (*mAcento)->letraDoAcento = NULL;
    
    free((*mAcento));
    
    return INF_NOT_ERR;
}

int free_accent(Accent **mAcento){
    
    if((*mAcento) == NULL){
        print_msg(ERR_PTR_NULL,"free_accent");
        return ERR_PTR_NULL;
    }
    
    (*mAcento)->objetoDaImagemDoAcento = NULL;
        
    (*mAcento)->letraDoAcento = NULL;
        
    free((*mAcento));
    
    return INF_NOT_ERR;
}
