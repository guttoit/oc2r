#include "character_seed.h"



CharSeed* create_init_char_seed(ImgObject *obj_img, 
				float *ann_out,
				int size_ann_out){
  
  if(obj_img == NULL || ann_out == NULL){
    print_msg(ERR_GENERIC, "character_seed/create_init_char_seed");
  
    return NULL;
  }
  
  CharSeed *charSeed = (CharSeed*) malloc(sizeof(CharSeed));
  
  if(charSeed == NULL){
    print_msg(ERR_MEMORY, "character_seed/create_init_char_seed");
    return NULL;
  }
  
  charSeed->obj_img = obj_img;
  charSeed->char_vector = getVetorReferencia();
  charSeed->ann_output = copy_fann_output(ann_out, size_ann_out);
  charSeed->size_ann_out = size_ann_out;
  charSeed->context_probability = NULL;
  charSeed->ptr_word_of_char = NULL;
  
  charSeed->best_char_in_context = ' ';
  charSeed->best_char_out_context = ' ';
  
  get_best_character_text_out_context(charSeed, 
				      &(charSeed->best_char_out_context));
  
  get_best_character_text_in_context(charSeed, 
				      &(charSeed->best_char_in_context));
  
  
  return charSeed;
}


int compare_x_relative_position_char_seeds(CharSeed *char_s_1, 
					   CharSeed *char_s_2,
					   int *result){
  
  if(char_s_1 == NULL || char_s_2 == NULL || result == NULL)
    return *print_big_msg(ERR_PTR_NULL, 
			  "character_seed/compare_position_char_seeds", 
			  "obj_1, obj_2, result");
  
  ImgObject *obj_img_1 = get_obj_img_from_char_seed(char_s_1);
  ImgObject *obj_img_2 = get_obj_img_from_char_seed(char_s_2);
  
  if(obj_img_1 == NULL || obj_img_2 == NULL)
    return *print_big_msg(ERR_GENERIC, 
			  "char_seed/compare_position_char_seeds", 
			  "obj_img_1, obj_img_2");
  
  int x_left_1 = 0;
  int x_left_2 = 0;
  
  get_img_obj_x_more_left(obj_img_1,&x_left_1);
  get_img_obj_x_more_left(obj_img_2,&x_left_2);   
  
  if(x_left_1 < x_left_2)  
    *result = OBJ_2_IS_MAJOR;
  
  else if(x_left_1 > x_left_2)
    *result = OBJ_1_IS_MAJOR;
  
  else
    *result = OBJ_1_AND_2_ARE_EQUAL;
   
  
  return INF_NOT_ERR;
}

int compare_y_relative_position_char_seeds(CharSeed *char_s_1, 
					   CharSeed *char_s_2,
					   int *result){
  
  if(char_s_1 == NULL || char_s_2 == NULL || result == NULL)
    return *print_big_msg(ERR_PTR_NULL, 
			  "character_seed/compare_position_char_seeds", 
			  "obj_1, obj_2, result");
  
  ImgObject *obj_img_1 = get_obj_img_from_char_seed(char_s_1);
  ImgObject *obj_img_2 = get_obj_img_from_char_seed(char_s_2);
  
  if(obj_img_1 == NULL || obj_img_2 == NULL)
    return *print_big_msg(ERR_GENERIC, 
			  "char_seed/compare_position_char_seeds", 
			  "obj_img_1, obj_img_2");
  
  int y_up_1 = 0;
  int y_up_2 = 0;
  
  get_img_obj_y_more_up(obj_img_1,&y_up_1);
  get_img_obj_y_more_up(obj_img_2,&y_up_2);   
  
  if(y_up_1 < y_up_2)  
    *result = OBJ_2_IS_MAJOR;
  
  else if(y_up_1 > y_up_2)
    *result = OBJ_1_IS_MAJOR;
  
  else
    *result = OBJ_1_AND_2_ARE_EQUAL;
   
  
  return INF_NOT_ERR;
}

ImgObject* get_obj_img_from_char_seed(CharSeed *charSeed){
  
  if(charSeed == NULL){
    print_msg(ERR_PTR_NULL, "character_seed/get_obj_img_from_char_seed");
    return NULL;
  }
  
  return charSeed->obj_img;
}

Character* get_best_character_out_context(CharSeed *charSeed){
  
  if(charSeed == NULL){
    print_msg(ERR_PTR_NULL, "character_seed/get_best_character_out_context");
    return NULL;
  }
  
  if(charSeed->char_vector == NULL){
    print_msg(ERR_GENERIC, "character_seed/get_best_character_out_context");
    return NULL;
  }
  
  int cod_err = INF_NOT_ERR;
  
  int size_vect_char = 0;
  cod_err = get_size_vect_out(&size_vect_char);
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err, 
		  "character_seed/get_best_character_out_context", 
		  "size_vect_char");
    return NULL;
  }
  
  
  int index = 0;
  
  cod_err = get_index_best_value_ann_output(charSeed, &index);
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err,
		  "character_seed/get_best_character_out_context",
		  "index");
    return NULL;
  }
  
  
  if(index > size_vect_char){
    print_big_msg(cod_err,
		  "character_seed/get_best_character_out_context",
		  "index/size_vect_char");
    return NULL;
  }
  
  
  char the_char = charSeed->char_vector[index];
  
  Character *character = create_init_character(charSeed->obj_img, 
					       the_char);
  
  return character;
  
}

Character* get_best_character_in_context(CharSeed *charSeed){
  
  if(charSeed == NULL){
    print_msg(ERR_PTR_NULL, "character_seed/get_best_character_in_context");
    return NULL;
  }
  
  if(charSeed->char_vector == NULL){
    print_msg(ERR_GENERIC, "character_seed/get_best_character_in_context");
    return NULL;
  }
  
  int cod_err = INF_NOT_ERR;
  
  int size_vect_char = 0;
  cod_err = get_size_vect_out(&size_vect_char);
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err, 
		  "character_seed/get_best_character_in_context", 
		  "size_vect_char");
    return NULL;
  }
  
  
  int index = 0;
  
  cod_err = get_index_best_value_ann_output(charSeed, &index);
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err,
		  "character_seed/get_best_character_in_context",
		  "index");
    return NULL;
  }
  
  
  if(index > size_vect_char){
    print_big_msg(cod_err,
		  "character_seed/get_best_character_in_context",
		  "index/size_vect_char");
    return NULL;
  }
  
  
  char the_char = charSeed->char_vector[index];
  
  Character *character = create_init_character(charSeed->obj_img, 
					       the_char);
  
  return character;
}

int get_best_character_text_out_context(CharSeed *charSeed, char *the_char){
  
  Character *character = get_best_character_out_context(charSeed);
  
  if(character == NULL)
    return *print_big_msg(ERR_GENERIC,
			  "character_seed/get_best_character_text_out_context",
			  "character");
  
  char best_char = ' ';
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = get_char_character(character, &best_char);
  
  *the_char = best_char;
  
  return cod_err;
  
}

int get_best_character_text_in_context(CharSeed *charSeed, char *the_char){
  
  Character *character = get_best_character_in_context(charSeed);
  
  if(character == NULL)
    return *print_big_msg(ERR_GENERIC,
			  "character_seed/get_best_character_text_in_context",
			  "character");
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = get_char_character(character, the_char);
  
  return cod_err;
}

int get_index_best_value_ann_output(CharSeed *charSeed, int *index){
  
  if(charSeed == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "character_seed/get_index_best_value_ann_output");
  }
  
  if(charSeed->ann_output == NULL){
    return *print_msg(ERR_GENERIC, 
		      "character_seed/get_index_best_value_ann_output");
  }
  
  float val_temp = charSeed->ann_output[0]; 
  
  int i_best = 0 ;
  int num_output = 0;
  get_size_vect_out(&num_output);
  
  int i;
  for(i = 1; i < num_output; i++){
    
    if(charSeed->ann_output[i] > val_temp){
      i_best = i;
      val_temp = charSeed->ann_output[i];
    }
    
  }
  
  *index = i_best;
  
  return INF_NOT_ERR;
}

int get_char_seed_best_probability(CharSeed *charSeed, float *value){
  
  
  int cod_err = INF_NOT_ERR;
  int index = 0;
  
  cod_err = get_index_best_value_ann_output(charSeed, &index);
  
  if(cod_err != INF_NOT_ERR){
    return *print_msg(cod_err, 
		      "character_seed/get_char_seed_best_probability");
  }
  
  if(index >= charSeed->size_ann_out || index < 0){
    return *print_msg(ERR_GENERIC, 
		      "character_seed/get_char_seed_best_probability");
  }
  
  *value = charSeed->ann_output[index];
  
  return INF_NOT_ERR;
}

int get_char_seed_x_more_left(CharSeed *char_seed, int *x){
  
  if(char_seed == NULL || x == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "character_seed/get_char_seed_x_more_left");
  }
  
  int cod_err = get_img_obj_x_more_left(char_seed->obj_img, x);
  
  return cod_err;
}

int get_char_seed_x_more_right(CharSeed *char_seed, int *x){
  
  if(char_seed == NULL || x == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "character_seed/get_char_seed_x_more_right");
  }
  
  int cod_err = get_img_obj_x_more_right(char_seed->obj_img, x);
  
  return cod_err;
}

int get_char_seed_y_more_up(CharSeed *char_seed, int *y){
  
  if(char_seed == NULL || y == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "character_seed/get_char_seed_y_more_up");
  }
  
  int cod_err = get_img_obj_y_more_up(char_seed->obj_img, y);
  
  return cod_err;

}

int get_char_seed_y_more_down(CharSeed *char_seed, int *y){
  
  if(char_seed == NULL || y == NULL){
    return *print_msg(ERR_PTR_NULL, 
		    "character_seed/get_char_seed_y_more_down");
  }
  
  int cod_err = get_img_obj_y_more_down(char_seed->obj_img, y);
  
  return cod_err;
}



int set_my_word(CharSeed *charSeed, void *my_word){
  
  if(charSeed != NULL)
    charSeed->ptr_word_of_char = my_word;
  
  return INF_NOT_ERR;
}

int free_char_seed(CharSeed **charSeed){
  
  if(charSeed != NULL){
    
    if(*charSeed != NULL){
      
      if((*charSeed)->obj_img != NULL)
	freeObjDaImg(&((*charSeed)->obj_img));
      
      if((*charSeed)->ann_output != NULL)
	free((*charSeed)->ann_output);
      
      if((*charSeed)->context_probability != NULL)
	free((*charSeed)->context_probability);
      
      (*charSeed)->char_vector = NULL;
      (*charSeed)->ptr_word_of_char = NULL;
      
      free(*charSeed);
      
      *charSeed = NULL;
    }
  }
  
  return INF_NOT_ERR;
}
