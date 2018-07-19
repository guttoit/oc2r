#include "post_img_processing.h"

int create_and_set_list_img_contours(Image *img){
  
  if(img == NULL)
      return *print_msg(ERR_PTR_NULL, 
			"create_and_set_list_img_contours/");
  
  int *dims = get_img_dimensions(img);
  
  int err = INF_NOT_ERR;
  
  
  if(dims[0] > 1500 || dims[1] > 1500){
    
    float width_ori = 794;
    float height_ori = 1123;
    
    float diff_w = width_ori/dims[0];
    float diff_h = height_ori/dims[1];
    
    int new_width = dims[0] * diff_w;
    int new_height = dims[1] * diff_h;
    
   // printf("new_w = %d , new_height = %d", new_width, new_height);
    
   // resizeImageEAtualiza(img, new_width, new_height);
    
    err = smoothImageUsingSmoothing(img, CV_BLUR, 3, 3);

    //show_dados_img(imgDidCanny, "DEPOIS_GAUSSIAN");
    
    err = doCanny(img, 100, 250, 3);
    
    //doThreshold(img, 155, 255, CV_THRESH_BINARY_INV);
        
  }else{
      
    err = smoothImageUsingSmoothing(img, CV_BLUR, 3, 3);
    
    err = doCanny(img, 150, 250, 3);
    
    //doThreshold(img, 155, 255, CV_THRESH_BINARY_INV);

  }
  
  if(err != INF_NOT_ERR)
      return *print_msg(ERR_PTR_NULL,
			"create_and_set_list_img_contours/");
  
  
  ListGeneric *contours = find_create_img_contours(img);
  
  err = set_img_contour_list(img, contours);
  
  return err;
  
}

int create_and_set_list_img_lines(Image *img){
  
  ListGeneric *contours = get_img_contours_list(img);
  
  if(contours == NULL)
    return *print_msg(ERR_GENERIC, 
		      "post_img_processing/create_and_set_list_img_lines");
  
  
  int cod_err = INF_NOT_ERR;
   
  cod_err = sort_generic_list(contours, &compare_img_contours_y_position);
  
  if(cod_err != INF_NOT_ERR)
    return *print_big_msg(ERR_GENERIC, 
			  "post_img_processing/create_and_set_list_img_lines", 
			  "sort_generic_list");
    
  
  int contour_from_line = FALSE;
  int is_create_new_line = TRUE;
  
  ImgLine *line = NULL;
  
  ListGeneric *lines = create_init_generic_list();
  
  int (*ptr_free_line)(void**) = (int (*)(void**)) &free_img_line_and_objs;
  
  void *obj_info_actual = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(contours);
  
  int type_obj = 0;
  
  while(obj_actual != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
      
    if(obj_info_actual != NULL){
      
      get_list_obj_type(obj_actual, &type_obj);
      
      if(type_obj == TYPE_OBJ_CONTOUR){
      
	Contour *contour = (Contour*) obj_info_actual;
	
	 
	if(is_create_new_line){
	  line = create_init_img_line(img);
	  contour_from_line = TRUE;
	}
	
	else{
	  cod_err = is_contour_from_img_line(line, 
					     contour, 
					     &contour_from_line);
	}
	
	if(contour_from_line){
	  add_contour_to_img_line(line, contour);
	  
	  is_create_new_line = FALSE;
	  
	}else{
	  
	  addObjGenericoParaLista(lines, 
				  line, 
				  TYPE_OBJ_IMG_LINE, 
				  ptr_free_line);
	  
	  calc_objs_img_line_measures(line);
	  
	  line = NULL;
	  
	  is_create_new_line = TRUE;
	  
	  obj_actual = obj_actual->antObjeto;
	  
	
	}
	
      }
    }
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  int is_line_empty = 0;
  is_img_line_empty(line, &is_line_empty);
  
  //Add last line
  if(!is_line_empty && line != NULL)
    addObjGenericoParaLista(lines, 
			    line, 
			    TYPE_OBJ_IMG_LINE, 
			    ptr_free_line);
    

  set_img_lines_list(img, lines);
  
  return INF_NOT_ERR;
  
}


ListGeneric* create_list_of_img_objs(Image *imgIn){

    ListGeneric *contours = get_img_contours_list(imgIn);
    
    if(imgIn == NULL || contours == NULL){
      print_msg(ERR_GENERIC, 
		"createDataStructFromImageContours/ if-inicial");
      return NULL;
    }
    
    if(isDadosImagemNull(imgIn) != FALSE){
      print_msg(ERR_GENERIC, 
		"createDataStructFromImageContours");
        return NULL;
    }
    
    ListGeneric *list = create_init_generic_list();
    
    ObjList *obj = get_initial_list_obj(contours);
    
    while(obj != NULL){
        
      Contour *c = (Contour*) get_obj_Info(obj);
      
      ImgObject *imageObject = criaObjDaImg(imgIn , c);
      
      if(imageObject == NULL){
	print_msg(ERR_GENERIC, "createDataStructFromImageContours");
	return list;
      }

      int (*ptr)(void**) = NULL;
      ptr = (int (*)(void**)) &freeObjDaImg;
      
      addObjGenericoParaLista(list, (void*) imageObject, TYPE_OBJ_IMG, ptr);

      obj = obj->proxObjeto;
        
    }
    
    return list;
}

int filter_redundant_contours(Image *img, int desvio_padrao){
  
  if((isDadosImagemNull(img)) != FALSE)
    return *print_msg(ERR_PTR_NULL, 
		      "post_img_processing.c/filter_redundant_contours");
    
  ListGeneric *contours = get_img_contours_list(img);
  
  if(contours == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "post_img_processing.c/filter_redundant_contours");
  
  ObjList *objAtual = get_initial_list_obj(contours);
  ObjList *objNext = objAtual;
  ObjList *objToRemove = NULL;
  
  void *objInfoAtual = NULL;
  void *objInfoNext = NULL;
  
  Contour *contAtual = NULL;
  Contour *contNext = NULL;
  
  int err_cod = INF_NOT_ERR;
  int is_inside_left = FALSE;
  int is_inside = FALSE;
  int pos_insert_contour = 0;
  
  printf("Number of contours before redundant filter = %d\n", contours->numObjs);
  
  while(objAtual != NULL){
    
    objInfoAtual = get_obj_Info(objAtual);
    
    if(objInfoAtual != NULL){
      contAtual = (Contour*) objInfoAtual;
      
      objNext = objAtual->proxObjeto;
      
      while(objNext != NULL){
	
	objInfoNext = get_obj_Info(objNext);
    
	if(objInfoNext != NULL){
	  
	  contNext = (Contour*) objInfoNext;
	  
	  is_contours_same_place(contAtual, contNext, 
				desvio_padrao, &is_inside);
	  
	  if(is_inside){
	    
	    is_contour_1_inside_left_contour_2(contAtual, 
					       contNext, 
					       &is_inside_left);
	    
	    if(is_inside_left)
	      pos_insert_contour = CONTOUR_INSERT_END;
	    
	    else
	      pos_insert_contour = CONTOUR_INSERT_START;
	    
	    err_cod = merge_second_contour_in_first(contAtual->cv_contour, 
						    contNext->cv_contour, 
						    pos_insert_contour);
	    
	    if(err_cod != INF_NOT_ERR)
	      return *print_msg(err_cod, 
				"post_img_processing.c/filtraContornosRedundantes");
	    
	    
	    
	    calc_and_set_contour_measure(contAtual);
	    
	    objToRemove = objNext;
	    
	    objNext = objNext->proxObjeto;
	    
	    
	    err_cod = free_contour(&contNext);
	    err_cod = removeObjDaLista(contours, objToRemove);
	      
	  }else
	    objNext = objNext->proxObjeto;
	  
	
	}else
	  return *print_msg(ERR_GENERIC, 
			    "post_img_processing.c/filtraContornosRedundantes");
      
      }
    
    
    }else
      return *print_msg(ERR_GENERIC, 
			"post_img_processing.c/filtraContornosRedundantes");
      
    objAtual = objAtual->proxObjeto;
  }
  
  printf("Number of contours after redundant filter = %d\n", contours->numObjs);
  
  return INF_NOT_ERR;
}

int find_and_merge_accents_in_line(ImgLine *img_line){
  
  ListGeneric *line_contours = get_img_line_contours_list(img_line);
  
  if(line_contours == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "post_img_processing.c/find_and_merge_accents_in_line");
    
  
  int cod = INF_NOT_ERR;
  
  //int have_accent = FALSE;
  int is_an_accent = FALSE;
  int is_inside_left = FALSE;
  int pos_insert_contour = 0;
  int diff_contours = 0;
  
  sort_generic_list(line_contours, &compare_x_position_objs_in_img_line);
  
  ObjList *obj_actual = get_initial_list_obj(line_contours);
  ObjList *obj_next   = obj_actual->proxObjeto;
  ObjList *obj_to_remove = NULL;
  
  void *obj_info_actual = NULL;
  void *obj_info_prox   = NULL;
  
  while(obj_next != NULL){
    
    obj_info_actual = get_obj_Info(obj_actual);
    obj_info_prox   = get_obj_Info(obj_next);
    
    if(obj_info_actual != NULL && obj_info_prox != NULL){
      
      Contour *contour_actual = (Contour*) obj_info_actual;
      Contour *contour_prox   = (Contour*) obj_info_prox;
      
      cod = y_diff_contour_1_to_contour_2(contour_actual, 
					  contour_prox, 
					  &diff_contours);
      
      if(cod != INF_NOT_ERR)
	return *print_big_msg(ERR_GENERIC, 
			    "post_img_processing.c/find_and_merge_accents_in_line", 
			    "y_diff_contour_1_to_contour_2");
	

      cod = is_contour_an_accent(contour_actual, 
				 contour_prox, 
				  &is_an_accent);
      
      
      if(cod != INF_NOT_ERR)
	return *print_big_msg(ERR_GENERIC, 
			    "post_img_processing.c/find_and_merge_accents_in_line", 
			    "is_contours_same_x_place");

      is_an_accent = TRUE;
      
      if(diff_contours >= 0 && is_an_accent){
	
	is_contour_1_inside_left_contour_2(contour_actual, 
					   contour_prox, 
					   &is_inside_left);
	    
	if(is_inside_left)
	  pos_insert_contour = CONTOUR_INSERT_END;
	
	else
	  pos_insert_contour = CONTOUR_INSERT_START;
	
	cod = merge_second_contour_in_first(contour_actual->cv_contour, 
					    contour_prox->cv_contour, 
					    pos_insert_contour);
	
	
	calc_and_set_contour_measure(contour_actual);
	
	obj_to_remove = obj_next;
	
	obj_actual = obj_next->proxObjeto;
	obj_next = obj_actual != NULL ? obj_actual->proxObjeto : obj_actual;
	
	cod = free_contour(&contour_prox);
	cod = removeObjDaLista(line_contours, obj_to_remove);
      
	
      }else{
	obj_actual = obj_next;
	obj_next = obj_actual != NULL ? obj_actual->proxObjeto : obj_actual;
      }
      
      
    }else{
      return *print_big_msg(ERR_GENERIC, 
			    "post_img_processing.c/find_and_merge_accents_in_line", 
			    "obj_info_actual == NULL || obj_info_prox == NULL");
    }
    
    
  }
  
  calc_objs_img_line_measures(img_line);
  
  return INF_NOT_ERR;
}

int update_img_contours_list_by_img_lines(Image *img){
  
  ListGeneric *img_lines = get_img_lines_list(img);
  
  if(img_lines == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "post_img_processing.c/update_img_contours_list_by_img_lines");
  
  int (*ptr_free_contour)(void**) = (int (*) (void**)) &free_contour;
  
  ListGeneric *new_contours = create_init_generic_list();
  ListGeneric *contours_line = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(img_lines);
  ObjList *obj_actual_line = NULL;
  
  void *obj_info_line = NULL;
  void *obj_info_contour = NULL;
  ImgLine *img_line = NULL;
  
  while(obj_actual != NULL){
    
    obj_info_line = get_obj_Info(obj_actual);
    
    if(obj_info_line != NULL){
      
      img_line = (ImgLine*) obj_info_line;
      
      contours_line = get_img_line_contours_list(img_line);
      
      obj_actual_line = get_initial_list_obj(contours_line);
      
      while(obj_actual_line != NULL){
	
	obj_info_contour = get_obj_Info(obj_actual_line);
	
	if(obj_info_contour != NULL){
      
	  Contour *contour_act = (Contour*) obj_info_contour;
	  
	  addObjGenericoParaLista(new_contours, (void*)contour_act, 
				  TYPE_OBJ_CONTOUR, ptr_free_contour);
	  
	}
	
	obj_actual_line = obj_actual_line->proxObjeto;
      }
    }
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  freeListaSemDep(&(img->contours));
  
  set_img_contour_list(img, new_contours);
  
  return INF_NOT_ERR;
}

int find_and_merge_accents(Image *img){
  
  ListGeneric *img_lines = get_img_lines_list(img);
  
  if(img_lines == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "post_img_processing.c/find_and_merge_accents");
  
  ObjList *obj_actual = get_initial_list_obj(img_lines);
  
  void *obj_info= NULL;
  
  ImgLine *img_line = NULL;
  
  int cod = INF_NOT_ERR;
  
  while(obj_actual != NULL){
    
    obj_info = get_obj_Info(obj_actual);
    
    if(obj_info != NULL){
      
      img_line = (ImgLine*) obj_info;
      
      cod = find_and_merge_accents_in_line(img_line);
      
      if(cod != INF_NOT_ERR)
	print_big_msg(WAR_GENERIC, 
		      "post_img_processing.c/find_and_merge_accents", 
		      "find_and_merge_accents_in_line");
      
      
    }else
      return *print_big_msg(ERR_GENERIC, 
			    "post_img_processing.c/find_and_merge_accents", 
			    "obj_info == NULL");
      
    obj_actual = obj_actual->proxObjeto;
  
  }
  
  cod = update_img_contours_list_by_img_lines(img);
  
  return cod;
}

int filter_invalid_contours(Image *img, int tam_min){
  
  if((isDadosImagemNull(img)) != FALSE)
    return *print_msg(ERR_PTR_NULL, 
			  "post_img_processing.c/filter_invalid_contours");
    
  ListGeneric *contours = get_img_contours_list(img);
  
  if(contours == NULL)
    return *print_msg(ERR_PTR_NULL, 
			  "post_img_processing.c/filter_invalid_contours");
  
  ObjList *objAtual = get_initial_list_obj(contours);
  
  ObjList *objToRemove = NULL;
  
  void *objInfoAtual = NULL;
  
  Contour *contAtual = NULL;
  
  int contour_area = 0;
  
  int err_cod = INF_NOT_ERR;
  
  printf("Number of contours before object invalid filter = %d\n", contours->numObjs);
  
  while(objAtual != NULL){
    
    objInfoAtual = get_obj_Info(objAtual);
    
    if(objInfoAtual != NULL){
      contAtual = (Contour*) objInfoAtual;
      
      contour_area = contAtual->width * contAtual->height;
      
      if(contour_area <= tam_min*tam_min){
	
	objToRemove = objAtual;
	objAtual = objAtual->proxObjeto;
	
	free_contour(&contAtual);
	
	err_cod = removeObjDaLista(contours, objToRemove);
	
	if(err_cod != INF_NOT_ERR)
	  return *print_msg(err_cod, "post_img_processing.c/filter_invalid_contours");
	
      }else
	objAtual = objAtual->proxObjeto;
      
    }else
      return *print_msg(ERR_GENERIC, "post_img_processing.c/filter_invalid_contours");
      
  
  }
  
  printf("Number of contours after object invalid filter = %d\n", contours->numObjs);
  
  return INF_NOT_ERR;
  
}


ListGeneric* create_list_line_objs(ImgLine *img_line){
  
  ListGeneric *line_contours = get_img_line_contours_list(img_line);
  
  ListGeneric *obj_line_list = create_init_generic_list();
  
  if(line_contours == NULL || obj_line_list == NULL){
    print_big_msg(ERR_GENERIC, 
		  "post_img_processing/create_list_line_objs", 
		  "line_contours == NULL");
    
    return NULL;
  }
  
  
  ObjList *obj_actual = get_initial_list_obj(line_contours);
  
  void *obj_info = NULL;
  int type_obj = 0;
  
  
  while(obj_actual != NULL){
    
    obj_info = get_obj_Info(obj_actual);
    get_list_obj_type(obj_actual, &type_obj);
    
    if(obj_info != NULL && type_obj == TYPE_OBJ_CONTOUR){
      
      Contour *contour = (Contour*) obj_info;
      
      ImgObject *imageObject = criaObjDaImg((Image*)img_line->image, 
					    contour);
      
      
      if(imageObject == NULL){
	print_big_msg(ERR_GENERIC, 
		      "post_img_processing/create_list_line_objs", 
		      "imageObject == NULL");
	return NULL;
      }

      int (*ptr)(void**) = NULL;
      ptr = (int (*)(void**)) &freeObjDaImg;
      
      addObjGenericoParaLista(obj_line_list, 
			      (void*) imageObject, 
			      TYPE_OBJ_IMG, ptr);

      
    
      
    }else{
      print_big_msg(WAR_GENERIC, 
		    "post_img_processing/create_list_line_objs", 
		    "obj_info != NULL && type_obj == TYPE_OBJ_CONTOUR");
    }
  
    obj_actual = obj_actual->proxObjeto;
    
  }
  
  return obj_line_list;
  
}













