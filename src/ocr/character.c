#include "character.h"

Character* create_init_character(ImgObject *obj_img, 
				 char the_char){

  if(obj_img == NULL){
    print_msg(ERR_PTR_NULL, "character/create_init_character");
  
    return NULL;
  }
  
  Character *character = create_character();
  
  init_character(character, obj_img, the_char);
  
  return character;
}

Character* create_character(){
  
  Character *character = (Character*) malloc(sizeof(Character));
  
  if(character == NULL)
    print_msg(ERR_PTR_NULL, "character/create_character");
  
  return character;
}

int init_character(Character *character,
		   ImgObject *obj_img, 
		   char the_char){

  if(character == NULL || obj_img == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "character/create_character");
  }
  
  character->obj_img = obj_img;
  character->the_char = the_char;
  character->type_character = 0;
  get_type_character(the_char, &character->type_character);
  
  return INF_NOT_ERR;
  
}


int get_type_character(char the_char, int *type){
  
  if(the_char >= LIM_INF_CHAR_NUMERIC && the_char <= LIM_SUP_CHAR_NUMERIC)
    *type = CHAR_TYPE_NUMERIC;
  
  else  if(the_char >= LIM_INF_CHAR_LETTER_UP && the_char <= LIM_SUP_CHAR_LETTER_UP)
    *type = CHAR_TYPE_LETTER_UP;

  else if(the_char >= LIM_INF_CHAR_LETTER_LOW && the_char <= LIM_SUP_CHAR_LETTER_LOW)
    *type = CHAR_TYPE_LETTER_LOW;
  
  else
    *type = CHAR_TYPE_SYMBOL;
  
  return INF_NOT_ERR;
}

int get_char_character(Character *character, char *the_char){
  
  if(character == NULL || the_char == NULL)
    return *print_msg(ERR_PTR_NULL, "character/get_char");
  
  *the_char = character->the_char;
  
  return INF_NOT_ERR;
  
}
//Matheus 12:31 marcos 