#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <stdlib.h>
#include "../vision/image_object.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_ocr.h"
#include "../util/util_macros.h"

typedef struct _character{
    
    ImgObject *obj_img;		
    
    char the_char;
    
    int type_character; //Letter, accent, punctuation or others
    
}Character;

Character* create_character();

Character* create_init_character(ImgObject *obj_img, 
				 char the_char);

int init_character(Character *character,
		    ImgObject *obj_img, 
		    char the_char);


int get_type_character(char the_char, int *type);

int get_char_character(Character *character, char *the_char);

#endif
