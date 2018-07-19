#ifndef ACCENT_H
#define ACCENT_H

#include <stdio.h>
#include "../vision/image_object.h"
 
typedef struct _accent{
    
    ImgObject *objetoDaImagemDoAcento;

    void *letraDoAcento;

    char caracterDoAcento;
    
}Accent;

Accent* create_accent();

int init_accent(Accent **mAcento);

int set_obj_img_accent(Accent **mAcento,ImgObject **objetoDaImagemDoAcento);

int set_letter_accent(Accent **mAcento, void *letraDoAcento);

int set_char_accent(Accent **mAcento, char caracter);

ImgObject* get_obj_img_accent(Accent **mAcento);

void* get_letter_accent(Accent **mAcento);

char get_char_accent(Accent **mAcento);

int free_accent_and_components(Accent **mAcento);

int free_accent(Accent **mAcento);

#endif
