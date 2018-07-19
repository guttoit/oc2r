#include "word_seed.h"


//Funcion declaration
int update_word_seed_one_char(WordSeed *, CharSeed *);


WordSeed* create_init_word_seed(int dist_char_word){
  
  WordSeed *word_seed = (WordSeed*) malloc(sizeof(WordSeed));
  
  if(word_seed == NULL){
    print_big_msg(ERR_MEMORY, 
		  "word_seed/create_init_word_seed", 
		  "word_seed");
    
    return NULL;
  }
  
  word_seed->charsSeed = create_init_generic_list();
  
  if(word_seed->charsSeed == NULL){
    print_big_msg(ERR_GENERIC, 
		  "word_seed/create_init_word_seed", 
		  "word_seed->charsSeed");
    
    return NULL;
  }
  
  
  word_seed->word_most_probable_on_ann = NULL;
  word_seed->word_most_probable_on_context = NULL;
  word_seed->word_x_mean = 0;
  word_seed->word_y_mean = 0;
  word_seed->x_more_left = 0;
  word_seed->x_more_right = 0;
  word_seed->y_more_up = 0;
  word_seed->y_more_down = 0;
  word_seed->dist_char_word = dist_char_word;
  
  word_seed->word_text_out_context = NULL;
  word_seed->word_text_in_context = NULL;
  
  return word_seed;
}

int add_char_seed_to_word(WordSeed *word_seed, CharSeed *char_seed){
  
  if(word_seed == NULL || char_seed == NULL){
    return *print_msg(ERR_PTR_NULL, "word_seed/add_char_seed_to_word");
    
  }
  
  int (*ptr) (void **) = (int (*) (void**)) &free_char_seed;
  
  int cod_err = addObjGenericoParaLista(word_seed->charsSeed, 
					(void*) char_seed, 
					TYPE_OBJ_CHAR_SEED,
					ptr );
  
  if(cod_err != INF_NOT_ERR)
    return *print_big_msg(cod_err, 
			  "word_seed/add_char_seed_to_word", 
			  "addObjGenericoParaLista");
  

  cod_err = set_my_word(char_seed, (void*) word_seed);
 
  cod_err = update_word_seed_one_char(word_seed, char_seed);
  
  return cod_err;
  
}

int compare_x_relative_position_words_seed(WordSeed *word_1, 
					   WordSeed *word_2,
					   int *result){
				      
  if(word_1 == NULL || word_2 == NULL)
    return *print_big_msg(ERR_GENERIC, 
			  "word_seed/compare_x_position_words_seed", 
			  "word_1, word_2");
    
  
  int x_left_1  = 0;
  int x_left_2  = 0;
  
  x_left_1 = word_1->x_more_left;
  x_left_2 = word_2->x_more_left;  
  
  if(x_left_1 < x_left_2)  
    *result = OBJ_2_IS_MAJOR;
  
  else if(x_left_1 > x_left_2)
    *result = OBJ_1_IS_MAJOR;
  
  else
    *result = OBJ_1_AND_2_ARE_EQUAL;
   
  
  return INF_NOT_ERR;
}

int compare_y_relative_position_words_seed(WordSeed *word_1, 
					   WordSeed *word_2,
					   int *result){
				    
  if(word_1 == NULL || word_2 == NULL)
    return *print_big_msg(ERR_GENERIC, 
			  "word_seed/compare_y_position_words_seed", 
			  "word_1, word_2");
  
  int y_up_1   = 0;
  int y_up_2   = 0;	  

  y_up_1 = word_1->y_more_up; 
  y_up_2 = word_2->y_more_up;
  
  
  if(y_up_1 < y_up_2)  
    *result = OBJ_2_IS_MAJOR;
  
  else if(y_up_1 > y_up_2)
    *result = OBJ_1_IS_MAJOR;
  
  else
    *result = OBJ_1_AND_2_ARE_EQUAL;
   
  
  return INF_NOT_ERR;
}

int update_word_seed(WordSeed *word_seed){
  
  if(word_seed == NULL)
    return *print_msg(ERR_PTR_NULL, "word_seed/update_word_seed");
  
  int cod_err = INF_NOT_ERR;
  
  ObjList *obj_actual = get_initial_list_obj(word_seed->charsSeed);
  
  void *obj_info_actual = get_obj_Info(obj_actual);
  
  CharSeed *char_seed_actual = NULL;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
    
    if(obj_info_actual != NULL){
      
      char_seed_actual = (CharSeed*) obj_info_actual;
      
      cod_err = update_word_seed_one_char(word_seed, 
					  char_seed_actual);
      
      if(cod_err != INF_NOT_ERR){
	print_big_msg(cod_err, 
		      "word_seed/update_word_seed", 
		      "update_word_seed");
      }
      
    
    }else{
	print_big_msg(ERR_GENERIC, 
		      "word_seed/update_word_seed", 
		      "obj_info_actual == NULL");
    }
      
    obj_actual = obj_actual->proxObjeto;  
    
  }
  
  
  return INF_NOT_ERR;
  
}

int update_word_seed_one_char(WordSeed *word_seed, CharSeed *char_seed){
  
  if(word_seed == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "word_seed/update_word_seed_one_char");
    
  
  ImgObject *obj_img = get_obj_img_from_char_seed(char_seed);
  
  if(obj_img == NULL)
    return *print_big_msg(ERR_GENERIC, 
			  "word_seed/update_word_seed_one_char",
			  "obj_img");
    
  int n_objs = 0;
  getNumObjDaLista(word_seed->charsSeed, &n_objs);
  
  int x_left_obj_img  = 0; int y_up_obj_img = 0;
  int x_rigth_obj_img = 0; int y_down_obj_img = 0;
  
  get_img_obj_x_more_left(obj_img, &x_left_obj_img);
  get_img_obj_x_more_right(obj_img, &x_rigth_obj_img);
  get_img_obj_y_more_up(obj_img, &y_up_obj_img);
  get_img_obj_y_more_down(obj_img, &y_down_obj_img);
  
  if(n_objs == 1){
    
    word_seed->x_more_left = x_left_obj_img;
  
    word_seed->x_more_right = x_rigth_obj_img;
    
    //Remember that when y is more up, the lower its value will be.
    word_seed->y_more_up = y_up_obj_img;
    
    //Remember that when y is more down, the greater its value will be. 
    word_seed->y_more_down = y_down_obj_img;

  }else{
    
    word_seed->x_more_left = word_seed->x_more_left > x_left_obj_img ? 
						      x_left_obj_img :
						      word_seed->x_more_left;
    
    word_seed->x_more_right = word_seed->x_more_right < x_rigth_obj_img ? 
						      x_rigth_obj_img :
						      word_seed->x_more_right;
    
    //Remember that when y is more up, the lower its value will be.
    word_seed->y_more_up = word_seed->y_more_up > y_up_obj_img ? 
						  y_up_obj_img : 
						  word_seed->y_more_up;
    
    //Remember that when y is more down, the greater its value will be. 
    word_seed->y_more_down = word_seed->y_more_down < y_down_obj_img ? 
						      y_down_obj_img : 
						      word_seed->y_more_down;	
    
  }
  
  
  word_seed->word_x_mean = ( word_seed->x_more_right + 
			     word_seed->x_more_left    ) / 2;
  
  word_seed->word_y_mean = ( word_seed->y_more_down + 
			     word_seed->y_more_up    ) / 2;

  return INF_NOT_ERR;

}

int get_word_seed_x_more_left(WordSeed *word_seed, 
			      int *x){
				
  
  if(word_seed == NULL || x == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "word_seed/get_word_seed_x_more_left");
    
  *x = word_seed->x_more_left;
  
  return INF_NOT_ERR;
}

int get_word_seed_x_more_right(WordSeed *word_seed, 
			       int *x){
				 

  if(word_seed == NULL || x == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "word_seed/get_word_seed_x_more_right");
    
  *x = word_seed->x_more_right;
  
  return INF_NOT_ERR;
}


int get_word_seed_y_more_up(WordSeed *word_seed, 
			      int *y){
				

  if(word_seed == NULL || y == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "word_seed/get_word_seed_y_more_up");
    
  *y = word_seed->y_more_up;
  
  return INF_NOT_ERR;
}

int get_word_seed_y_more_down(WordSeed *word_seed, 
			      int *y){
				
  if(word_seed == NULL || y == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "word_seed/get_word_seed_y_more_down");
    
  *y = word_seed->y_more_down;
  
  return INF_NOT_ERR;
  
}

int get_word_seed_x_mean(WordSeed *word_seed, 
			 int *x_mean){

  
  if(word_seed == NULL || x_mean == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "word_seed/get_word_seed_x_mean");
    
  *x_mean = word_seed->word_x_mean;
  
  return INF_NOT_ERR;
  
}

int get_word_seed_y_mean(WordSeed *word_seed, 
			 int *y_mean){
 
  if(word_seed == NULL || y_mean == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "word_seed/get_word_seed_y_mean");
    
  *y_mean = word_seed->word_y_mean;
  
  return INF_NOT_ERR;
}

int is_word_seed_empty(WordSeed *word_seed, int *result){
  
  if(word_seed == NULL || result == NULL){
    return *print_msg(ERR_PTR_NULL,
		      "word_seed/is_word_seed_empty");
  }
  
  if(word_seed->charsSeed == NULL){
    return *print_msg(ERR_GENERIC, 
		      "word_seed/is_word_seed_empty");
  }
  
  int n_objs = 0;
  
  getNumObjDaLista(word_seed->charsSeed, &n_objs);
  
  *result = n_objs == 0 ? TRUE : FALSE;
  
  return INF_NOT_ERR;
}

float* get_word_seed_chars_probability(WordSeed *word_seed){
  
  float *chars_prob = NULL;
  
  if(word_seed == NULL){
    print_msg(ERR_PTR_NULL, 
	      "word_seed/get_word_seed_chars_probability");

    return NULL;
  }
  
  if(word_seed->charsSeed == NULL){
    
    chars_prob = (float*) malloc(sizeof(float));
    
    *chars_prob = 0.0;
  }
  
  else{
    
    int n_chars = 0, i = 0;
    getNumObjDaLista(word_seed->charsSeed, &n_chars);
    
    chars_prob = (float*) malloc(sizeof(float) * n_chars);
      
    ObjList *obj_actual = get_initial_list_obj(word_seed->charsSeed);
    
    while(obj_actual != NULL && i < n_chars){
      
      CharSeed *char_seed_actual = (CharSeed*)get_obj_Info(obj_actual);
      
      get_char_seed_best_probability(char_seed_actual, &(chars_prob[i]));
      
      i++;
      
      obj_actual = obj_actual->proxObjeto;
    }
    
    if(obj_actual != NULL){
      print_big_msg(WAR_GENERIC, 
		    "word_seed/get_word_seed_chars_probability", 
		    "The number of charsSeed is more than expected");
    }
  }
  
  return chars_prob;
}

char* get_word_seed_text_out_context(WordSeed *word_seed){
				
  if(word_seed == NULL){
    print_msg(ERR_PTR_NULL, 
	      "word_seed/get_word_seed_text_out_context");
  
    return NULL;
  }
  
  if(word_seed->word_text_out_context == NULL){
    
    char *text = NULL;
    
    text = generate_word_seed_text(word_seed, FALSE);
    
    word_seed->word_text_out_context = text;
  }
  
  return word_seed->word_text_out_context;
}

char* get_word_seed_text_in_context(WordSeed *word_seed){
				
  if(word_seed == NULL){
    print_msg(ERR_PTR_NULL, 
	      "word_seed/get_word_seed_text_in_context");
  
    return NULL;
  }
  
  if(word_seed->word_text_in_context == NULL){
    
    char *text = NULL;
    
    text = generate_word_seed_text(word_seed, TRUE);
  
    word_seed->word_text_in_context = text;
  }
  
  return word_seed->word_text_in_context;
  
}

char* generate_word_seed_text(WordSeed *word_seed, 
			      int is_to_use_context){

  if(word_seed == NULL){
    print_msg(ERR_PTR_NULL, "word_seed/generate_word_seed_text");
    return NULL;
  }
  
  int cod_err = INF_NOT_ERR;
  int list_empty = 0;
  
  is_list_empty(word_seed->charsSeed, &list_empty);
  
  if(word_seed->charsSeed == NULL || list_empty ){
    
    char *word_seed_empty = malloc(1);
    
    if(word_seed_empty == NULL){
      print_big_msg(ERR_MEMORY, 
		    "word_seed/generate_word_seed_text",
		    "word_empty");
      
      return NULL;
    }
    
    *word_seed_empty = '\0';
    
    return word_seed_empty;
    
  }
  
  char *word_seed_text = NULL;
  
  void *obj_info = NULL;
  
  CharSeed *char_seed_actual = NULL;
  
  Character *character_actual = NULL;
  
  char char_actual_text = ' ';
  
  Character* (*ptr) (CharSeed*) = NULL;
  
  if(is_to_use_context)
    ptr = &get_best_character_in_context;
  
  else
    ptr = &get_best_character_out_context;
  
  
  ObjList *obj_actual = get_initial_list_obj(word_seed->charsSeed);
  
  while(obj_actual != NULL){
    
    
    obj_info = get_obj_Info(obj_actual);
    
    if(obj_info != NULL){
      
      char_seed_actual = (CharSeed*) obj_info;
      
      character_actual = ptr(char_seed_actual);
      
      cod_err = get_char_character(character_actual, &char_actual_text);
      
      if(cod_err != INF_NOT_ERR){
	print_big_msg(ERR_GENERIC, 
		      "word_seed/generate_word_seed_text", 
		      "get_char_character");
	
      }else{
	
	append_char_data(&word_seed_text, (const char)char_actual_text);
      
      }
      
      
    }else{
      print_big_msg(ERR_GENERIC, 
		    "word_seed/generate_word_seed_text", 
		    "obj_info == NULL");
    }
    
    
    obj_actual = obj_actual->proxObjeto;
    
  }
  
  
  return word_seed_text;
}

int free_word_seed_and_objs(WordSeed **word_seed){
  
  if(word_seed != NULL){
    
    if(*word_seed != NULL){
      
      if((*word_seed)->charsSeed != NULL)
	freeListaEDep(&((*word_seed)->charsSeed));
      
      if((*word_seed)->word_most_probable_on_ann != NULL)
	liberaMemoriaPalavraEDepencencias(&((*word_seed)->word_most_probable_on_ann));
      
      if((*word_seed)->word_most_probable_on_context != NULL)
	liberaMemoriaPalavraEDepencencias(&((*word_seed)->word_most_probable_on_context));
      
      if((*word_seed)->word_text_in_context != NULL)
	free((*word_seed)->word_text_in_context);

      if((*word_seed)->word_text_out_context != NULL)
	free((*word_seed)->word_text_out_context);
      
      free(*word_seed);
      
      *word_seed = NULL;
    }
  }
  
  return INF_NOT_ERR;
}

int free_word_seed_only(WordSeed **word_seed){
  
  if(word_seed != NULL){
    
    if(*word_seed != NULL){
      
      (*word_seed)->charsSeed = NULL;
      
      (*word_seed)->word_most_probable_on_ann = NULL;
      
      (*word_seed)->word_most_probable_on_context = NULL;
      
      (*word_seed)->word_text_in_context = NULL;

      (*word_seed)->word_text_out_context = NULL;
      
      free(*word_seed);
      
      *word_seed = NULL;
    }
  }
  
  return INF_NOT_ERR;
}

