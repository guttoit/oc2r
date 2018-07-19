#include "line.h"

Line* create_init_line(){
  
  int cod_err = INF_NOT_ERR;
  
  Line *line = create_line();
  
  cod_err = init_line(line);
  
  if(cod_err != INF_NOT_ERR){
    print_msg(cod_err, "line/create_init_line");
    return NULL;
  }
  
  return line;
}

Line* create_line(){
    
  Line *line = (Line*) malloc(sizeof(Line));
  
  if(line == NULL)
      print_msg(ERR_MEMORY,"line/create_line");
      
  return line;
}


int init_line(Line *line){
    
  if(line == NULL)
    return *print_msg(ERR_PTR_NULL,"line/init_line");

  line->line_text_out_context = NULL;
  line->line_text_in_context = NULL;
  line->line_chars_seed = NULL;
  line->line_objs_img = NULL;
  line->line_words = NULL;
  
  return INF_NOT_ERR;
}

int add_obj_img_to_line(Line *line, ImgObject *obj){
  
  if(line == NULL || obj == NULL)
    return *print_msg(ERR_PTR_NULL, "line/add_obj_img_to_line");

  int cod_err = INF_NOT_ERR;

  int (*ptr)(void**) = (int (*)(void**)) &freeObjDaImg;
  
  cod_err = addObjGenericoParaLista(line->line_objs_img,
				    (void*)obj, 
				    TYPE_OBJ_IMG, 
				    ptr);

  if(cod_err != INF_NOT_ERR)
    return *print_big_msg(ERR_GENERIC, 
			  "line/add_obj_img_to_line", 
			  "addObjGenericoParaLista");
  
  return cod_err;
  
}

int add_char_seed_to_line(Line *line, CharSeed *obj){
  
  if(line == NULL || obj == NULL)
    return *print_msg(ERR_PTR_NULL, "line/add_char_seed_to_line");

  if(line->line_chars_seed == NULL)
    line->line_chars_seed = create_init_generic_list();
  
  int cod_err = INF_NOT_ERR;

  int (*ptr)(void**) = (int (*)(void**)) &free_char_seed;
  
  
  
  cod_err = addObjGenericoParaLista(line->line_chars_seed,
				    (void*)obj, 
				    TYPE_OBJ_CHAR_SEED, 
				    ptr);

  if(cod_err != INF_NOT_ERR)
    return *print_big_msg(ERR_GENERIC, 
			  "line/add_char_seed_to_line", 
			  "addObjGenericoParaLista");
  
  return cod_err;
}

int add_word_seed(Line *line, WordSeed *word_seed){
  
  if(line == NULL || word_seed == NULL)
    return *print_msg(ERR_PTR_NULL,"line/add_word_seed");
  
  int (*ptr)(void**) = (int (*)(void**)) &free_word_seed_and_objs;
  
  if(line->line_words == NULL)
    line->line_words = create_init_generic_list();
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = addObjGenericoParaLista(line->line_words,
				    (void*)word_seed, 
				    TYPE_OBJ_WORD_SEED, 
				    ptr);
  	  
  if(cod_err != INF_NOT_ERR)
    return *print_big_msg(ERR_GENERIC,
			  "line/add_word_seed", 
			  "addObjGenericoParaLista");
  
  return cod_err;
}

int sort_left_to_rigth_list_line_chars_seed(Line *line){
  
  if(line == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "line/sort_left_to_rigth_list_line_chars_seed");
    
  if(line->line_chars_seed == NULL)
    return *print_big_msg(ERR_GENERIC,
			  "line/sort_left_to_rigth_list_line_chars_seed",
			  "line_chars_seed");
  
  
  int cod_err = sort_generic_list(line->line_chars_seed, 
				  &compare_position_objs_in_line);
  
  return cod_err;
  
}

int sort_left_to_rigth_list_line_words(Line *line){
  
  if(line == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "line/sort_left_to_rigth_list_line_words");
    
  if(line->line_words == NULL)
    return *print_big_msg(ERR_GENERIC,
			  "line/sort_left_to_rigth_list_line_words",
			  "line_words");
  
  
  int cod_err = sort_generic_list(line->line_words, 
				  &compare_position_objs_in_line);
  
  return cod_err;
  
}

int compare_position_objs_in_line(ObjList *obj_1,
				  ObjList *obj_2,
				  int *result){
  
  int cod_err = INF_NOT_ERR;
  
  if(obj_1 == NULL || obj_2 == NULL || result == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "line/compare_position_objs_in_line");
  
  int type_obj_1 = 0, type_obj_2 = 0;
  
  get_list_obj_type(obj_1, &type_obj_1);
  get_list_obj_type(obj_2, &type_obj_2);
  
  if(type_obj_1 != type_obj_2){
       
    return *print_big_msg(ERR_GENERIC,
		      "line/compare_position_objs_in_line", 
		      "type_obj_1, type_obj_2");
  }
  
  if(type_obj_1 == TYPE_OBJ_CHAR_SEED){
    
    CharSeed *char_1 = (CharSeed*)obj_1->objetoInformacao;
    CharSeed *char_2 = (CharSeed*)obj_2->objetoInformacao;
    
    cod_err = compare_x_relative_position_char_seeds(char_1, 
						     char_2, 
						     result);
  }
  
  else if(type_obj_1 == TYPE_OBJ_WORD_SEED){
    
    WordSeed *word_1 = (WordSeed*) obj_1->objetoInformacao;
    WordSeed *word_2 = (WordSeed*) obj_2->objetoInformacao;
    
    cod_err = compare_x_relative_position_words_seed(word_1, 
						     word_2, 
						     result);
    
  }
  
  if(cod_err != INF_NOT_ERR)
    print_big_msg(cod_err, 
		  "line/compare_position_objs_in_line", 
		  "compare_x_relative_position");
    
      
  return cod_err; 
  
}

int is_line_empty(Line *line, int *result){
  
  if(line == NULL || result == NULL){
    return *print_big_msg(ERR_PTR_NULL, 
			  "line/is_line_empty", 
			  "line");
  }
  
  int n_chars = 0, n_objs_img = 0;
  
  int cod_0 = getNumObjDaLista(line->line_chars_seed, &n_chars);
  int cod_1 = getNumObjDaLista(line->line_objs_img, &n_objs_img);
  
  if(cod_0 == INF_NOT_ERR && cod_1 == INF_NOT_ERR)
    *result = n_chars + n_objs_img > 0 ? FALSE : TRUE;
  
  else
    print_big_msg(ERR_GENERIC, 
		  "line/is_line_empty", 
		  "getNumObjDaLista");
  
    
  return cod_0 != INF_NOT_ERR ? cod_0 : cod_1;
}

int is_list_line_objs_empty(Line *line, int *result){
  
  if(line == NULL || result == NULL){
    return *print_big_msg(ERR_PTR_NULL, 
			  "line/is_list_line_objs_empty", 
			  "line");
  }
  
  int n_objs_img = 0;
  
  int cod_1 = getNumObjDaLista(line->line_objs_img, &n_objs_img);
  
  if(cod_1 == INF_NOT_ERR)
    *result = n_objs_img > 0 ? FALSE : TRUE;
  
  else
    print_big_msg(ERR_GENERIC, 
		  "line/is_list_line_objs_empty", 
		  "getNumObjDaLista");
  
    
  return cod_1;
}

int is_list_line_words_seed_empty(Line *line, int *result){
  
  if(line == NULL || result == NULL){
    return *print_big_msg(ERR_PTR_NULL, 
			  "line/is_list_line_words_seed_empty", 
			  "line");
  }
  
  int n_words = 0;
  
  int cod_1 = getNumObjDaLista(line->line_words, &n_words);
  
  if(cod_1 == INF_NOT_ERR)
    *result = n_words > 0 ? FALSE : TRUE;
  
  else
    print_big_msg(ERR_GENERIC, 
		  "line/is_list_line_words_seed_empty", 
		  "getNumObjDaLista");
  
    
  return cod_1;
}

int set_max_dist_char_word(Line *line, int max_dist){
  
  if(line == NULL){
    return *print_big_msg(ERR_PTR_NULL, 
			  "line/set_max_dist_char_word", 
			  "line");
  }
  
  line->max_dist_char_word = max_dist;
  
  return INF_NOT_ERR;
}

int set_min_dist_word_word(Line *line, int min_dist){
  
  if(line == NULL){
    return *print_big_msg(ERR_PTR_NULL, 
			  "line/set_min_dist_word_word", 
			  "line");
  }
  
  line->min_dist_word_word = min_dist;
  
  return INF_NOT_ERR;
}

int set_line_objs_img(Line *line, ListGeneric *list){
  
  if(line == NULL || list == NULL)
    return *print_msg(ERR_PTR_NULL,"line/set_line_objs_img");
  
  line->line_objs_img = list;
  
  return INF_NOT_ERR;
}

ListGeneric* get_line_objs_img(Line *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,"line/get_line_objs_img");
  
    return NULL;
  }
  
  return line->line_objs_img;
  
}

int set_line_words_seed(Line *line, ListGeneric *list){
  
  if(line == NULL || list == NULL)
    return *print_msg(ERR_PTR_NULL,"line/set_line_words_seed");
  
  line->line_words = list;
  
  return INF_NOT_ERR;
}

int set_line_chars_seed(Line *line, ListGeneric *list){
  
  if(line == NULL || list == NULL)
    return *print_msg(ERR_PTR_NULL,"line/set_line_chars_seed");
  
  line->line_chars_seed = list;
  
  return INF_NOT_ERR;
}

int get_max_dist_char_word(Line *line, int *dist){
  
  if(line == NULL || dist == NULL)
    return *print_msg(ERR_PTR_NULL,"line/get_max_dist_char_word");
  
  *dist = line->max_dist_char_word;
  
  return INF_NOT_ERR;
}

int get_min_dist_word_word(Line *line, int *dist){
  
  if(line == NULL || dist == NULL)
    return *print_msg(ERR_PTR_NULL,"line/get_min_dist_word_word");
  
  *dist = line->min_dist_word_word;
  
  return INF_NOT_ERR;
}

int get_n_line_objs_img(Line *line, int *n_objs){
  
  if(line == NULL || n_objs == NULL)
    return *print_msg(ERR_PTR_NULL,"line/get_n_line_objs_img");
  
  int cod = getNumObjDaLista(line->line_objs_img, n_objs);
  
  return cod;
}

int get_n_line_chars_seed(Line *line, int *n_objs){
  
  if(line == NULL || n_objs == NULL)
    return *print_msg(ERR_PTR_NULL,"line/get_n_line_chars_seed");
  
  int cod = getNumObjDaLista(line->line_chars_seed, n_objs);
  
  return cod;
}


int get_n_line_words_seed(Line *line, int *n_objs){
  
  if(line == NULL || n_objs == NULL)
    return *print_msg(ERR_PTR_NULL,"line/get_n_line_chars_seed");
  
  int cod = getNumObjDaLista(line->line_words, n_objs);
  
  return cod;
}

ListGeneric* get_line_chars_seed(Line *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,"line/get_line_chars_seed");
  
    return NULL;
  }
  
  return line->line_chars_seed;
  
}

ListGeneric* get_line_words_seed(Line *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,"line/get_line_chars_seed");
  
    return NULL;
  }
  
  return line->line_words;
  
}

char* get_line_text_out_context(Line *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,"line/get_line_text_out_context");
  
    return NULL;
  }
  
  if(line->line_text_out_context == NULL)
    line->line_text_out_context = generate_line_text(line, FALSE);
  
  return line->line_text_out_context;
  
}

char* get_line_text_in_context(Line *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,"line/get_line_text_in_context");
  
    return NULL;
  }
  
  if(line->line_text_in_context == NULL)
    line->line_text_in_context = generate_line_text(line, TRUE);
  
  return line->line_text_in_context;
  
}

char* get_line_text_out_context_unedited(Line *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,
	      "line/get_line_text_out_context_unedited");
  
    return NULL;
  }
  
  char *text = generate_line_text_unedited(line, FALSE);
  
  return text;
  
}

char* get_line_text_in_context_unedited(Line *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,
	      "line/get_line_text_out_context_unedited");
  
    return NULL;
  }
  
  char *text = generate_line_text_unedited(line, TRUE);
  
  return text;
  
}



char* generate_line_text(Line *line, int is_to_use_context){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,"line/generate_line_text");
  
    return NULL;
  }
  
  char* (*ptr) (WordSeed*) = NULL;
  
  if(is_to_use_context)
    ptr = &get_word_seed_text_in_context;
  
  else
    ptr = &get_word_seed_text_out_context;
  
  
  char *text_line = NULL;
  char *text_word_actual = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(line->line_words);
  int type_obj_actual = 0;
  
  void *obj_info = NULL;
  
  WordSeed *word_seed = NULL;
  
  while(obj_actual != NULL){
    
    get_list_obj_type(obj_actual, &type_obj_actual);
    
    obj_info = get_obj_Info(obj_actual);
    
    if(obj_info != NULL){
      
      if(type_obj_actual == TYPE_OBJ_WORD_SEED){
	
	word_seed = (WordSeed*) obj_info;
	
	text_word_actual = ptr(word_seed);
	
	if(text_word_actual == NULL){
	  print_big_msg(ERR_GENERIC,
			"line/generate_line_text_out_context",
			"text_word_actual");
	
	  return NULL;
	}
	
	if(text_line == NULL){
	  append_data(&text_line, text_word_actual);
	
	  
	}else{
	  append_data(&text_line, " ");
	  append_data(&text_line, text_word_actual);
	}
	
      }else{
	print_big_msg(WAR_GENERIC, 
		      "line/generate_line_text_out_context",
		      "type_obj_actual != WORD_SEED");
      }
    
      
    }else{
      print_big_msg(ERR_GENERIC,
		    "line/generate_line_text_out_context",
		    "obj_info");

    }
      
    obj_actual = obj_actual->proxObjeto;
    
  }
  
  return text_line;
  
}

char* generate_line_text_unedited(Line *line, int is_to_use_context){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL,
	      "line/generate_line_text_unedited");
  
    return NULL;
  }
  
  
  int (*ptr) (CharSeed* , char* ) = NULL;
  
  if(is_to_use_context)
    ptr = &get_best_character_text_in_context;
  else
    ptr = &get_best_character_text_out_context;
  
  
  int cod_err = INF_NOT_ERR;
  
  int result = 0;
  is_list_line_objs_empty(line, &result);
  
  if(result == TRUE ){
    
    char *line_empty = malloc(1);
    *line_empty = '\0';
    
    return line_empty;
  }
  
  char *text_line = NULL;

  ObjList *obj_actual = get_initial_list_obj(line->line_chars_seed);
  
  void *obj_info_actual = NULL;
  
  CharSeed *char_seed_actual = NULL;
  
  char char_actual = ' ';
  
  int type_obj = 0;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
    
    if(obj_info_actual != NULL){
      
      get_list_obj_type(obj_actual, &type_obj);
      
      if(type_obj == TYPE_OBJ_CHAR_SEED){
	
	char_seed_actual = (CharSeed*) obj_info_actual;
	
	cod_err = ptr(char_seed_actual, &char_actual);
	
	if(cod_err == INF_NOT_ERR){
	
	  if(text_line == NULL)
	    append_char_data(&text_line, char_actual);
	  
	  else{
	    append_data(&text_line, " ");
	    append_char_data(&text_line, char_actual);
	  }
	
	  
	}else{
	  print_big_msg(cod_err,
		    "line/generate_line_text_unedited",
		    "ptr");
	}
	
      }else{
	print_big_msg(WAR_GENERIC,
		    "line/generate_line_text_unedited",
		    "TYPE_OBJ != CHAR_SEED");
      }
      
    }else{
      print_big_msg(ERR_GENERIC,
		    "line/generate_line_text_unedited",
		    "obj_info_actual");
      
    }
    
    
    obj_actual = obj_actual->proxObjeto;
    
  }
  
  return text_line;
}


int free_line_and_objs(Line **line){
  
  if(line != NULL){
    
    if(*line != NULL){
      
      if((*line)->img_line != NULL)
	free_img_line_and_objs(&((*line)->img_line));
      
      if((*line)->line_objs_img != NULL)
	freeListaEDep(&((*line)->line_objs_img));
      
      if((*line)->line_chars_seed != NULL)
	freeListaEDep(&((*line)->line_chars_seed));
      
      if((*line)->line_words != NULL)
	freeListaEDep(&((*line)->line_words));
      
      if((*line)->line_text_in_context != NULL)
	free((*line)->line_text_in_context);
      
      if((*line)->line_text_out_context != NULL)
	free((*line)->line_text_out_context);
      
      free(*line);
      
      *line = NULL;
    }
  }
  
  return INF_NOT_ERR;
}

int free_only_line(Line **line){
  
  if(line != NULL){
    
    if(*line != NULL){
      
      (*line)->img_line = NULL;
      (*line)->line_objs_img = NULL;
      (*line)->line_chars_seed = NULL;
      (*line)->line_words = NULL;
      (*line)->line_text_in_context = NULL;
      (*line)->line_text_out_context = NULL;
      free(*line);
      
      *line = NULL;
    }
  }
  
  return INF_NOT_ERR;
  
}