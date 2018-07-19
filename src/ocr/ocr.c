#include "ocr.h"

OCRConfig* create_init_ocr_config(int resolution,
				  int is_contextual,
				  int is_filter_contours,
				  int is_filter_inv_obj,
				  char *path_ann){

  OCRConfig *ocr_config = (OCRConfig *) malloc(sizeof(OCRConfig));
  
  ocr_config->obj_img_resolution = resolution;
  ocr_config->is_to_use_statistical_context = is_contextual;
  ocr_config->is_to_filter_contours = is_filter_contours;
  ocr_config->is_to_filter_invalid_obj = is_filter_inv_obj;
  ocr_config->max_dist_between_contours = STAND_MAX_DIST_BETWEEN_CONTOURS;

  ocr_config->max_size_invalid_obj = STAND_MAX_SIZE_INVALID_OBJ;
  ocr_config->max_distance_char_word = STAND_MAX_DIST_CHAR_WORD;
  
  ocr_config->path_ann = path_ann;
  ocr_config->ann_base = create_ann_base_from_path(path_ann);
  
  int is_valid = 0;
  is_ocr_config_valid(ocr_config, &is_valid);
  
  if(!is_valid	){
    
    print_msg(ERR_PARAM_INV, "ocr/create_ocr_config");
    
    return NULL;
  }
  
  return ocr_config;
  
}

int set_ocr_config_params(OCRConfig *ocr_config, 
			  int max_dist_between_contours, 
			  int max_dist_char_word, 
			  int max_size_inv_obj){
			    
  if(ocr_config == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "ocr/set_ocr_config_params");
  
  ocr_config->max_dist_between_contours = max_dist_between_contours;
  ocr_config->max_size_invalid_obj = max_size_inv_obj;
  ocr_config->max_distance_char_word = max_dist_char_word;
  
  int is_valid = 0;
  is_ocr_config_valid(ocr_config, &is_valid);
  
  if(!is_valid){
    return *print_msg(ERR_PARAM_INV, 
		      "ocr/set_ocr_config_params");
  }
  
  return INF_NOT_ERR;
}

int is_ocr_config_valid(OCRConfig *ocr_config, int *result){
  
  if(ocr_config == NULL){
    return *print_msg(ERR_PTR_NULL, "ocr/create_ocr_config");
  }
  
  int is_valid = TRUE;
  
  is_valid = ocr_config->obj_img_resolution       <= 0 ? FALSE : is_valid;
  is_valid = ocr_config->max_dist_between_contours < 0 ? FALSE : is_valid;
  is_valid = ocr_config->max_size_invalid_obj          < 0 ? FALSE : is_valid;
  is_valid = ocr_config->max_distance_char_word        < 0 ? FALSE : is_valid;
  
  is_valid = ocr_config->path_ann == NULL ? FALSE : is_valid;
  
  *result = is_valid;
  
  return INF_NOT_ERR;
}

Image* ocr_pre_process_img(OCRConfig *ocr_config, Image *img){
  
  if(img == NULL){
    print_msg(ERR_GENERIC, "ocr/ocr_pre_process_img");
  
    return NULL;
  }
  
  //int *dim = get_img_dimensions(img);
  //int x = dim[0];
 // int y = dim[1];
  
  filter_redundant_contours(img, 0);
  
  filter_invalid_contours(img, 3);
  
  return img;
}

ListGeneric* init_ocr_recognition(OCRConfig *ocr_config,
				  char *path_image){
  
  Image *img = create_init_img(path_image, GRAYSCALE);
  
  if(img == NULL){
    print_msg(ERR_GENERIC, "ocr/init_ocr_recognition");
  
    return NULL;
  }
  
  int cod_err = INF_NOT_ERR;
 // int max_dist_between_contours = ocr_config->max_dist_between_contours;
  //int max_size_inv_obj = ocr_config->max_size_invalid_obj;
  
  
  cod_err = create_and_set_list_img_contours(img); 
  
  if(cod_err != INF_NOT_ERR){
    print_msg(ERR_GENERIC, "ocr/init_ocr_recognition");
  
    return NULL;
  }
  
  img = ocr_pre_process_img(ocr_config, img);
  
  cod_err = create_and_set_list_img_lines(img);
  
  find_and_merge_accents(img);
  
  ListGeneric *list_lines = ocr_create_lines(ocr_config, img);
  
  ocr_ann_recognized(ocr_config, list_lines);
  
  cod_err = ocr_create_words(ocr_config, list_lines);
  
  return list_lines;
}

/*

ListGeneric *ocr_pre_process_objs(ListGeneric *objs_img){
  
  ListGeneric *lines = create_init_generic_list();
  
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = sort_generic_list(objs_img, &compare_y_objs_position);
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err, 
		  "ocr/ocr_create_lines", 
		  "sort_generic_list");
    return NULL;
  }
  
  int char_from_line = FALSE;
  int is_create_new_line = TRUE;
  
  ListGeneric *line = NULL;
  
  int (*ptr_free_line)(void**) = (int (*)(void**)) &freeObjDaImg;
  
  void *obj_info_actual = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(objs_img);
  
  int y_down_line = 0;
  int y_up_line = 0;
  int y_mean_line = 0;
  
  int y_down_obj = 0;
  int y_up_obj = 0;
  
  int type_obj = 0;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
      
    if(obj_info_actual != NULL){
      
      get_list_obj_type(obj_actual, &type_obj);
      
      if(type_obj == TYPE_OBJ_IMG){
      
	ImgObject *img_obj = (ImgObject*)obj_info_actual;
	
	if(is_create_new_line){
	  line = create_init_generic_list();
	  char_from_line = TRUE;
	  
	  y_down_line = 0;
	  y_up_line = 0;
	  y_mean_line = 0;
	
	  
	}
	
	else{
	  cod_err = is_img_obj_from_line(y_mean_line, 
					 y_down_line, 
					 y_up_line, 
					 img_obj, 
					 &char_from_line);
	}
	
	if(char_from_line){
	  
	  addObjGenericoParaLista(line, 
				  img_obj, 
				  TYPE_OBJ_IMG, 
				  (int (*)(void**)) &freeObjDaImg);
	  
	  get_img_obj_y_more_down(img_obj, &y_down_obj);
	  get_img_obj_y_more_up(img_obj, &y_up_obj);
	  
	  if(line->numObjs <= 1){
	    y_down_line = y_down_obj;
	  
	    y_up_line = y_up_obj;
	    
	  }

	  y_down_line = y_down_line < y_down_obj ? y_down_obj : y_down_line;
	  y_up_line = y_up_line > y_up_obj ? y_up_obj: y_up_line;
	  
	  y_mean_line = (y_down_line + y_up_line) / 2;
	  
	  
	  is_create_new_line = FALSE;
	  
	}else{
	  
	  addObjGenericoParaLista(lines, 
				  line, 
			   TYPE_LIST_GENERIC, 
			   (int(*)(void**))&freeListaSemDep);
	  
	  line = NULL;
	  
	  is_create_new_line = TRUE;
	  
	  obj_actual = obj_actual->antObjeto;
	  
	
	}
	
      }
    }
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  int is_line_empty = 0;
  is_list_line_objs_empty(line, &is_line_empty);
  
  //Add last line
  if(is_line_empty);
    addObjGenericoParaLista(lines, 
			    line, 
			    OBJETO_TIPO_LINHA, 
			    ptr_free_line);
    
  
  return lines;
  
}
*/

int ocr_ann_recognized_line_objs(OCRConfig *ocr_config, Line *line){
  
  if(line == NULL || ocr_config == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "ocr/ocr_ann_recognized_line_objs");
  }
  
  int cod_err = INF_NOT_ERR;
  
  ListGeneric *line_objs = line->line_objs_img;
  
  if(line_objs == NULL){
    return *print_big_msg(ERR_GENERIC, 
			  "ocr/ocr_ann_recognized_line_objs", 
			  "line_objs == NULL");
  }
  
  ObjList *obj_actual = get_initial_list_obj(line_objs);
  
  void *obj_info_actual = NULL;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
    
    if(obj_info_actual != NULL){
      
      ImgObject *obj_img_actual = (ImgObject*) obj_info_actual;
      
      CharSeed *char_seed = NULL;
      
      char_seed = ocr_ann_obj_img_recognized(obj_img_actual,
					     ocr_config);      

      cod_err = add_char_seed_to_line(line, char_seed);
      
      
      if(cod_err != INF_NOT_ERR){
	return *print_big_msg(ERR_GENERIC, 
			      "ocr/ocr_ann_recognized_line_objs", 
			      "add_char_seed_to_line returned a error");
      }
      
      
    }else{
      print_big_msg(WAR_GENERIC, 
		    "ocr/ocr_ann_recognized_line_objs", 
		    "obj_info_actual != NULL");
    }
    
    
    obj_actual = obj_actual->proxObjeto;
  
    
  }
  
  return INF_NOT_ERR;
}


int ocr_ann_recognized(OCRConfig *ocr_config, ListGeneric *lines){
  
  if(lines == NULL){
    return *print_msg(ERR_PTR_NULL, "ocr/ocr_ann_recognized");
  }
  
  int cod_err = INF_NOT_ERR;
  
  ObjList *obj_actual = get_initial_list_obj(lines);
  
  void *obj_info_actual = NULL;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
    
    if(obj_info_actual != NULL){
      
      Line *line_actual = (Line*) obj_info_actual;
      
      cod_err = ocr_ann_recognized_line_objs(ocr_config, line_actual);
      
      
      if(cod_err != INF_NOT_ERR){
	return *print_big_msg(ERR_GENERIC, 
			      "ocr/ocr_ann_recognized", 
			      "ocr_ann_recognized_line_objs returned a error");
      }
      
    }else{
      return *print_big_msg(ERR_GENERIC, 
			    "ocr/ocr_ann_recognized", 
			    "obj_info_actual == NULL");
    }
      
    obj_actual = obj_actual->proxObjeto;
    
  }
  
  return INF_NOT_ERR;
}


CharSeed* ocr_ann_obj_img_recognized(ImgObject *obj_img, 
				     OCRConfig *ocr_config){
  
  if(obj_img == NULL || ocr_config == NULL){
    print_msg(ERR_PTR_NULL, "ocr/ocr_ann_obj_img_recognized");
    return NULL;
  }
  
  AnnBase *ann_base = ocr_config->ann_base;
  
  int obj_res = ocr_config->obj_img_resolution;
  
  int obj_resolution[2] = {obj_res, obj_res};
  
  Matrix *matrix = getMatObjDaImg(obj_img, 
				  TIPO_MATRIZ_BIN, 
				  obj_resolution);
  
  float *ann_input = create_fann_input(matrix);
  
  float *ann_output = ann_run(ann_base->f_ann, ann_input);
  
  
  if(ann_output == NULL){
    print_big_msg(ERR_GENERIC, 
		  "ocr/ocr_ann_obj_img_recognized", 
		  "ann_output");
    return NULL;
  }
  
  
  int n_outs = 0;
  get_num_outputs(ann_base, &n_outs);
  
  CharSeed *char_seed = create_init_char_seed(obj_img, 
					      ann_output,
					      n_outs);
  
  
  return char_seed;
}

int compare_y_objs_position(ObjList *obj_1, 
			    ObjList *obj_2,
			    int *result){

  
  if(obj_1 == NULL || obj_2 == NULL || result == NULL){
    return *print_msg(ERR_PTR_NULL, 
		    "ocr/compare_y_objs_position");
  }
  
  int type_obj_1 = 0, type_obj_2 = 0;
  
  get_list_obj_type(obj_1, &type_obj_1);
  get_list_obj_type(obj_2, &type_obj_2);
  
  int y_up_1 = 0; 
  int y_up_2 = 0;
  
  if(type_obj_1 == TYPE_OBJ_IMG && type_obj_2 == type_obj_1){
    
    ImgObject *img_obj_1 = (ImgObject*) obj_1->objetoInformacao;
    ImgObject *img_obj_2 = (ImgObject*) obj_2->objetoInformacao;
    
    get_img_obj_y_more_up(img_obj_1, &y_up_1);
    get_img_obj_y_more_up(img_obj_2, &y_up_2);
    
  }
  
  else if(type_obj_1 == TYPE_OBJ_CHAR_SEED && type_obj_2 == type_obj_1){
    
    CharSeed *char_seed_1 = (CharSeed*) obj_1->objetoInformacao;
    CharSeed *char_seed_2 = (CharSeed*) obj_2->objetoInformacao;
    
    get_char_seed_y_more_up  (char_seed_1, &y_up_1  );
    get_char_seed_y_more_up  (char_seed_2, &y_up_2  );
    
  }else{
    return *print_big_msg(ERR_GENERIC, 
			  "ocr/compare_y_objs_position", 
			  "type_obj_1 != TYPE_OBJ_CHAR_SEED");
  }
  
  
  if(y_up_1 == y_up_2)
    *result = OBJ_1_AND_2_ARE_EQUAL;
  
  else if(y_up_1 > y_up_2 )
    *result = OBJ_1_IS_MAJOR;
  
  else
    *result = OBJ_2_IS_MAJOR;
  
  
  return INF_NOT_ERR;
}

ListGeneric* ocr_create_lines(OCRConfig *ocr_config, Image *img){
  
  ListGeneric *list_img_lines = get_img_lines_list(img);
  
  if(list_img_lines == NULL || ocr_config == NULL){
    print_msg(ERR_PTR_NULL, "ocr/ocr_create_lines");
    return NULL;
  }
  
  //int cod_err = INF_NOT_ERR;
  
  Line *line = NULL;
  
  ListGeneric *lines = create_init_generic_list();
  
  int (*ptr_free_line)(void**) = (int (*)(void**)) &free_line_and_objs;
  
  void *obj_info_actual = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(list_img_lines);
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
      
    if(obj_info_actual != NULL){
      
      ListGeneric *img_objs_line = create_list_line_objs((ImgLine*) obj_info_actual);
      
      if(img_objs_line == NULL){
	print_big_msg(ERR_GENERIC, 
		      "ocr/ocr_create_lines", 
		      "img_objs_line == NULL");
	return NULL;
      }
      
      line = create_init_line();
     
      line->img_line = (ImgLine*) obj_info_actual;
     
      line->line_objs_img = img_objs_line;
      
      addObjGenericoParaLista(lines, 
			      line, 
			      OBJETO_TIPO_LINHA, 
			      ptr_free_line);
	  
      line = NULL;

    }else{
      print_big_msg(WAR_GENERIC, 
		    "ocr/ocr_create_lines", 
		    "obj_info_actual == NULL");
    }
    
    obj_actual = obj_actual->proxObjeto;
  }

  return lines;
  
}

/*ListGeneric* ocr_create_lines(OCRConfig *ocr_config, 
			      ListGeneric *chars_seed){
  
  
  if(chars_seed == NULL || ocr_config == NULL){
    print_msg(ERR_PTR_NULL, "ocr/ocr_create_lines");
    return NULL;
  }
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = sort_generic_list(chars_seed, &compare_y_objs_position);
  
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err, 
		  "ocr/ocr_create_lines", 
		  "sort_generic_list");
    return NULL;
  }
  
  int char_from_line = FALSE;
  int is_create_new_line = TRUE;
  
  Line *line = NULL;
  
  ListGeneric *lines = create_init_generic_list();
  
  int (*ptr_free_line)(void**) = (int (*)(void**)) &free_line_and_objs;
  
  void *obj_info_actual = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(chars_seed);
  
  int type_obj = 0;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
      
    if(obj_info_actual != NULL){
      
      get_list_obj_type(obj_actual, &type_obj);
      
      if(type_obj == TYPE_OBJ_CHAR_SEED){
      
	CharSeed *char_seed = (CharSeed*)obj_info_actual;
	
	if(is_create_new_line){
	  line = create_init_line();
	  char_from_line = TRUE;
	}
	
	else{
	  cod_err = is_char_seed_from_line(line, 
				       char_seed, 
				       &char_from_line);
	}
	
	if(char_from_line){
	  add_char_seed_to_line(line,(CharSeed*) obj_info_actual);
	  
	  is_create_new_line = FALSE;
	  
	}else{
	  
	  addObjGenericoParaLista(lines, 
				  line, 
			   OBJETO_TIPO_LINHA, 
			   ptr_free_line);
	  
	  line = NULL;
	  
	  is_create_new_line = TRUE;
	  
	  obj_actual = obj_actual->antObjeto;
	  
	
	}
	
      }
    }
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  int is_line_empty = 0;
  is_list_line_objs_empty(line, &is_line_empty);
  
  //Add last line
  if(!is_line_empty)
    addObjGenericoParaLista(lines, 
			    line, 
			    OBJETO_TIPO_LINHA, 
			    ptr_free_line);
    
  
  return lines;
  
}*/

int is_img_obj_from_line(int y_mean_line, 
			 int y_down_line,
			 int y_up_line,
			 ImgObject *img_obj, 
			 int *result){

  
  if(img_obj == NULL || result == NULL){
    
    return *print_msg(ERR_PTR_NULL, 
		      "ocr/is_char_seed_from_line");
    
  }
  
  int y_up_obj = 0, y_down_obj= 0;
  
  get_img_obj_y_more_down(img_obj, &y_down_obj  );
  get_img_obj_y_more_up(img_obj, &y_up_obj);
  
  int y_mean_obj = (y_up_obj + y_down_obj) / 2;
  
  
  //Char_seed is more down
  if(y_mean_obj> y_mean_line){
  
    //if y_mean_char_seed is equal or more up than y_down_line
    if(y_mean_obj<= y_down_line)
      *result = TRUE;
    else
      *result = FALSE;
    
  }else if(y_mean_obj< y_mean_line){
    
    //if y_mean_char_seed is equal or more down than y_up_line
    if(y_mean_obj >= y_up_line)
      *result = TRUE;
    else
      *result = FALSE;
  
    
  }else
    *result = TRUE;
  
  return INF_NOT_ERR;
  
}

int is_char_seed_from_word_seed(WordSeed *word_seed, 
				CharSeed *char_seed, 
				int *result){
  
  if(word_seed == NULL || char_seed == NULL){
    
    return *print_msg(ERR_PTR_NULL, 
		      "ocr/is_char_seed_from_word_seed");
  }
  
  int x_left_word = 0, x_right_word = 0;
  int x_left_char = 0, x_right_char = 0;
  
  get_word_seed_x_more_left(word_seed, &x_left_word);
  get_word_seed_x_more_right(word_seed, &x_right_word);
  
  get_char_seed_x_more_left(char_seed, &x_left_char);
  get_char_seed_x_more_right(char_seed, &x_right_char);
  
  int diff_word_char = 0;
  
  if(x_right_word <= x_left_char)
    diff_word_char = x_left_char - x_right_word;
  
  else if(x_right_char <= x_left_word)
    diff_word_char = x_left_word - x_right_char;
  
  else{
    *result = TRUE;
  
    return INF_NOT_ERR;
  }
  
  *result = diff_word_char <= word_seed->dist_char_word ? TRUE : FALSE;
  
  return INF_NOT_ERR;
    
}

int ocr_create_words(OCRConfig *ocr_config,
		      ListGeneric *lines){
  
  if(lines == NULL || ocr_config == NULL){
    return *print_msg(ERR_PTR_NULL, "ocr/ocr_create_words");
  }

  int cod_err = INF_NOT_ERR;
  
  ObjList *obj_actual = get_initial_list_obj(lines);
  void *obj_info = NULL;
  
  while(obj_actual != NULL){

    obj_info = get_obj_Info(obj_actual);
    
    if(obj_info != NULL){
      
      Line *line_actual = (Line*) obj_info;
      
      
      cod_err = ocr_create_words_of_line(ocr_config, 
					 line_actual);
      
      if(cod_err != INF_NOT_ERR)
	print_big_msg(cod_err, 
		      "ocr/ocr_create_words", 
		      "ocr_create_words_of_line");
    
      
    }else{
      
      if(cod_err != INF_NOT_ERR)
	print_big_msg(cod_err, 
		      "ocr/ocr_create_words", 
		      "obj_info == NULL");
    }
    
    obj_actual = obj_actual->proxObjeto;
    
  }
  
  return INF_NOT_ERR;
    
}


int ocr_create_words_of_line(OCRConfig *ocr_config,
			     Line *line){
  

  if(line == NULL || ocr_config == NULL){
    return *print_msg(ERR_GENERIC, "ocr/ocr_create_words_of_line");
  }
  
  ListGeneric *line_objs = get_line_chars_seed(line);
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = sort_generic_list(line_objs, &compare_position_objs_in_line);
  
  
  if(cod_err != INF_NOT_ERR){
    return *print_big_msg(cod_err, 
			  "ocr/ocr_create_words_of_line", 
			  "sort_generic_list");
  }
  
  int char_from_word = FALSE;
  int is_create_new_word = TRUE;
  
  int dist_objs = line->img_line->avr_distance_between_objs + 2;
  
  set_max_dist_char_word(line, dist_objs);
  
  
  WordSeed *word_actual = NULL;
  
  void *obj_info_actual = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(line_objs);
  
  int type_obj = 0;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
      
    if(obj_info_actual != NULL){
      
      get_list_obj_type(obj_actual, &type_obj);
      
      if(type_obj == TYPE_OBJ_CHAR_SEED){
      
	CharSeed *char_seed = (CharSeed*)obj_info_actual;
	
	if(is_create_new_word){
	  word_actual = create_init_word_seed(dist_objs);
	  char_from_word = TRUE;
	}
	
	else{
	  cod_err = is_char_seed_from_word_seed(word_actual, 
						char_seed, 
						&char_from_word);
	}
	
	if(char_from_word){
	  add_char_seed_to_word(word_actual, char_seed);
	  
	  is_create_new_word = FALSE;
	  
	}else{
	  
	  add_word_seed(line, word_actual);
	  
	  word_actual = NULL;
	  
	  is_create_new_word = TRUE;
	  
	  obj_actual = obj_actual->antObjeto;
	 
	}
	
      }
    }
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  int word_empty = 0;
  is_word_seed_empty(word_actual, &word_empty);
  
  //Add last word_seed
  if(!word_empty);
    add_word_seed(line, word_actual);
    
  
  return INF_NOT_ERR;
 
}

/*
Text* ocr_text_create(OCRConfig *ocr_config, 
		      ListGeneric *chars_seed){
  
  if(ocr_config == NULL || chars_seed == NULL){
    print_msg(ERR_PTR_NULL, "ocr/ocr_text_create");
    return NULL;
  }
  
  int cod_err = INF_NOT_ERR;
  
  ListGeneric *lines_text = NULL;
  ListGeneric *words_seed = NULL;
  
  printf("\nCriando palavras...\n");
  
  words_seed = ocr_create_words(ocr_config, 
				chars_seed);
  printf("Done.\n");
  
  printf("\nCriando linhas...\n");
  
  lines_text = ocr_create_lines(ocr_config, 
				words_seed);
  
  printf("Done.\n");
  
  Text *text = create_init_text();
  
  cod_err = set_text_lines(text, lines_text);
  
  printf("\nCriando text...\n");
  
  if(cod_err != INF_NOT_ERR){
    print_msg(cod_err, "ocr/ocr_text_create");
    return NULL;
  }
  
  cod_err = sort_text_lines_up_to_down(text);
  
  if(cod_err != INF_NOT_ERR){
    print_big_msg(cod_err, 
		  "ocr/ocr_text_create", 
		  "sort_text_lines_up_to_down");
    
    return NULL;
  }
  
  
  return text;
}
*/


int free_ocr_config(OCRConfig **ocr_config){
  
  if(ocr_config != NULL){
    
    if(*ocr_config != NULL){
      
      if((*ocr_config)->path_ann != NULL)
	free((*ocr_config)->path_ann);
      
      if((*ocr_config)->ann_base != NULL)
	free_ann(&(*ocr_config)->ann_base);
      
      free(*ocr_config);
      
      *ocr_config = NULL;
    }
  }
  
  return INF_NOT_ERR;
}

/**
 * Próximos passos são:
 * 
 * Criar uma função para processar os objetos da image.
 * 
 * Passar cada objeto da image pela rede neural. Pegar o resultado e 
 * criar um charSeed, que vai criar vários charsVirtuais. 
 * Depois de criar os vários chárSeeds, Organizar essa lista de charSeeds em linhas.
 * Depois de criar as várias linhas, organizar os characteresSeeds em palavrasSeeds.
 * 
 * Esse é o último passo para criar o text usando apenas o resultado da rede neural.
 * 
 * Depois de fazer todo esse processo acima, criar uma função que recebe uma word ou uma linha
 * e usa a estatística da presage para atualizar as estatísticas dos charSEED, e, então, poder 
 * reorganizar as palavras.
 */



