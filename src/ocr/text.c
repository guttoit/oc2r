#include "text.h"

Text* create_init_text(){
  
  Text *text = create_text();
  
  init_text(text);
  
  return text;
}

Text* create_text(){
  
  Text *text = (Text*) malloc(sizeof(Text));
  
  if(text == NULL)
    print_msg(ERR_MEMORY,"text/create_text");
  
  return text;
}

int init_text(Text *text){
  
  if(text == NULL){
    return *print_msg(ERR_PTR_NULL,"text/init_text");
  }
  
  text->text_lines = create_init_generic_list();
  text->text_objs = create_init_generic_list();
  text->text_out_out_context = NULL;
  text->text_out_in_context = NULL;
  
  if(text->text_lines == NULL)
    return *print_big_msg(ERR_GENERIC, 
			  "text/init_text", 
			  "text_lines");
  
  return INF_NOT_ERR;
}

int sort_text_lines_up_to_down(Text *text){
  
  if(text == NULL){
    return *print_msg(ERR_PTR_NULL,
		      "text/sort_text_lines_up_to_down");
  }
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = sort_generic_list(text->text_lines, 
			      &compare_position_lines_in_text);
  
  
  return cod_err;
}

int compare_position_lines_in_text(ObjList *obj_1, 
				   ObjList *obj_2,
				   int *result){

  
  if(obj_1 == NULL || obj_2 == NULL || result == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "text/compare_position_lines_in_text");
  
  int type_obj_1 = 0, type_obj_2 = 0;
  get_list_obj_type(obj_1, &type_obj_1);
  get_list_obj_type(obj_2, &type_obj_2);  
  
  if(type_obj_1 != OBJETO_TIPO_LINHA || type_obj_2 != type_obj_1)
    return *print_msg(ERR_GENERIC, 
		     "text/compare_position_lines_in_text");
    
  
  Line *line_1 = (Line*) obj_1->objetoInformacao;
  Line *line_2 = (Line*) obj_2->objetoInformacao;
  
  if(line_1->img_line->y_line_mean < line_2->img_line->y_line_mean)
    *result = OBJ_2_IS_MAJOR;
  
  else if(line_1->img_line->y_line_mean > line_2->img_line->y_line_mean)
    *result = OBJ_1_IS_MAJOR;
  else
    *result = OBJ_1_AND_2_ARE_EQUAL;
  
  
  return INF_NOT_ERR;
  
}

int set_text_lines(Text *text, ListGeneric *lines){
  
  if(text == NULL)
    return *print_msg(ERR_PTR_NULL,"text/set_text_lines");
  
  if(lines == NULL)
    print_msg(WAR_SET_PTR_NULL,"text/set_text_lines");
  
  text->text_lines = lines;
  
  return INF_NOT_ERR;
  
}

ListGeneric* get_text_lines(Text *text){
  
  if(text == NULL){
    print_msg(ERR_PTR_NULL,"text/get_text_lines");
    return NULL;
  }
  
  return text->text_lines;
  
}

ListGeneric* get_text_objs(Text *text){
  
  if(text == NULL){
    print_msg(ERR_PTR_NULL,"text/get_text_objs");
    return NULL;
  }
  
  return text->text_objs;
  
}

char *get_text_out_out_context(Text *text){
  
  if(text == NULL){
    print_msg(ERR_PTR_NULL,"text/get_text_out_out_context");
    return NULL;
  }
  
  if(text->text_out_out_context == NULL){
    char *text_out = NULL;
    
    text_out = generate_text_out_context(text);
    text->text_out_out_context = text_out;
  }
  
  return text->text_out_out_context;
  
}

char* generate_text_out_context(Text *text){
  
  if(text == NULL){
    print_msg(ERR_PTR_NULL,"text/generate_text_out_context");
    return NULL;
  }
  
  if(text->text_lines == NULL){
    print_msg(ERR_PTR_NULL,"text/generate_text_out_context");
    return NULL;
  }
  
  int n_lines = 0;
  getNumObjDaLista(text->text_lines, &n_lines);
  
  ObjList *obj_actual = get_initial_list_obj(text->text_lines);
  void *obj_info = NULL;
  
  Line *line = NULL;
  
  char *line_text_actual;
  char *line_text_final;
  
  while(obj_actual != NULL){
    
    obj_info = get_obj_Info(obj_actual);
    
    if(obj_info != NULL){
      
      line = (Line*) obj_info;
      
      line_text_actual = get_line_text_out_context(line);
      
      if(line_text_final == NULL){
	
	append_data(&line_text_final, (const char*)line_text_actual);
      
	
      }else{
	
	append_data(&line_text_final, " ");
	append_data(&line_text_final, (const char*)line_text_actual);
      
	
      }
      
      if(line_text_final == NULL){
	print_big_msg(ERR_GENERIC,
		      "text/generate_text_out_context", 
		      "append_data");
	return NULL;
      }
    
      
    }else{
      print_big_msg(ERR_GENERIC,
		    "text/generate_text_out_context", 
		    "obj_info");
      return NULL;
    }
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  return line_text_final;

}

char* get_text_out_in_context(Text *text){
  
  if(text == NULL){
    print_msg(ERR_PTR_NULL,"text/get_text_out_in_context");
    return NULL;
  }
  
  if(text->text_out_in_context == NULL){
    char *text_out = NULL;
    
    text_out = generate_text_in_context(text);
    text->text_out_in_context = text_out;
  }
  
  return text->text_out_in_context;
}

char* generate_text_in_context(Text *text){
  
  if(text == NULL){
    print_msg(ERR_PTR_NULL,"text/generate_text_in_context");
    return NULL;
  }
  
  if(text->text_lines == NULL){
    print_msg(ERR_PTR_NULL,"text/generate_text_in_context");
    return NULL;
  }
  
  int n_lines = 0;
  getNumObjDaLista(text->text_lines, &n_lines);
  
  ObjList *obj_actual = get_initial_list_obj(text->text_lines);
  void *obj_info = NULL;
  
  Line *line = NULL;
  
  char *line_text_actual;
  char *line_text_final;
  
  while(obj_actual != NULL){
    
    obj_info = get_obj_Info(obj_actual);
    
    if(obj_info != NULL){
      
      line = (Line*) obj_info;
      
      line_text_actual = get_line_text_in_context(line);
      
      if(line_text_final == NULL){
	
	append_data(&line_text_final, (const char*)line_text_actual);
      
	
      }else{
	
	append_data(&line_text_final, " ");
	append_data(&line_text_final, (const char*)line_text_actual);
      
	
      }
      
      if(line_text_final == NULL){
	print_big_msg(ERR_GENERIC,
		      "text/generate_text_in_context", 
		      "append_data");
	return NULL;
      }
    
      
    }else{
      print_big_msg(ERR_GENERIC,
		    "text/generate_text_in_context", 
		    "obj_info");
      return NULL;
    }
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  return line_text_final;
  
}

int free_text_and_objs(Text **text){
  
  if(text != NULL){
    
    if(*text != NULL){
      
      if((*text)->text_lines != NULL)
	freeListaEDep(&(*text)->text_lines);
      
      if((*text)->text_out_out_context != NULL)
	free((*text)->text_out_out_context);
      
      if((*text)->text_out_in_context != NULL)
	free((*text)->text_out_in_context);
      
      free(*text);
      
      *text = NULL;
    }
  }
  
  return INF_NOT_ERR;
  
}

int free_text_only(Text **text){
  
  if(text != NULL){
    
    if(*text != NULL){
      
      (*text)->text_lines = NULL;
      (*text)->text_out_out_context = NULL;
      (*text)->text_out_in_context = NULL;
      
      free(*text);
      
      *text = NULL;
    }
  }
  
  return INF_NOT_ERR;
  
}
