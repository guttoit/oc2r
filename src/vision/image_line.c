#include "image_line.h"

int calc_avr_bigger_distance_between_objs(ImgLine *img_line);


ImgLine* create_init_img_line(void *image){
  
  ImgLine *img_line = (ImgLine *) malloc(sizeof(ImgLine));
  
  if(img_line == NULL){
    print_msg(ERR_MEMORY, "image_line/create_init_img_line");
    return NULL;
  }
  
  img_line->image = image;
  
  img_line->avr_distance_between_objs = 0;
  img_line->avr_width_line_objs = 0;
  img_line->avr_hight_line_objs = 0;
  img_line->avr_area_line_objs = 0;
  
  img_line->smaller_dist_between_objs = 0;
  img_line->smaller_width_line_obj = 0;
  img_line->smaller_hight_line_obj = 0;
  img_line->smaller_area_line_obj = 0;
  img_line->bigger_dist_between_objs = 0;
  img_line->bigger_width_line_obj = 0;
  img_line->bigger_hight_line_obj = 0;
  img_line->bigger_area_line_obj = 0;
  
  img_line->x_more_left = 0;
  img_line->x_more_right = 0;
  img_line->y_more_up = 0;
  img_line->y_more_down = 0;
  img_line->y_line_mean = 0;
  img_line->x_line_mean = 0;
  
  img_line->img_line_contours = create_init_generic_list();
  
  if(img_line->img_line_contours == NULL){
    print_big_msg(ERR_GENERIC, 
		  "image_line/create_init_img_line", 
		  "img_line->img_line_contours == NULL");
    return NULL;
  }
  
  return img_line;
}

int add_contour_to_img_line(ImgLine *img_line, Contour *contour){
  
  if(img_line == NULL || contour == NULL){
    return *print_msg(ERR_MEMORY, 
		      "image_line/add_contour_to_img_line");
  }
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = addObjGenericoParaLista(img_line->img_line_contours, 
				    (void*)contour, 
				    TYPE_OBJ_CONTOUR, 
				    (int (*)(void**)) &free_contour);
  
  
  if(cod_err != INF_NOT_ERR){
    return *print_big_msg(ERR_MEMORY, 
			"image_line/add_contour_to_img_line", 
			"addObjGenericoParaLista");
  }
  
  cod_err = updates_img_line_after_add_contour(img_line, contour);
  
  return cod_err;
}

int updates_img_line_after_add_contour(ImgLine *img_line, Contour *contour){
  
  if(img_line == NULL || contour == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "img_line/updates_img_line_after_add_contour");
  
    
  int cod_err = INF_NOT_ERR;
  
  int n_objs = 0;
  
  cod_err = getNumObjDaLista(img_line->img_line_contours, &n_objs);
  
  
  if(cod_err != INF_NOT_ERR){
    return *print_msg(cod_err,
		    "img_line/updates_img_line_after_add_contour");
    
  }
  
  int x_left  = 0; int y_up   = 0;
  int x_right = 0; int y_down = 0;
  
  get_contour_x_more_left (contour, &x_left );
  get_contour_x_more_right(contour, &x_right);
  
  get_contour_y_more_up   (contour,  &y_up  );
  get_contour_y_more_down (contour,  &y_down);
  

  if(n_objs == 1){
      img_line->x_more_left = x_left;
      img_line->x_more_right = x_right;
      img_line->y_more_up = y_up;
      img_line->y_more_down = y_down;
      
  }else{
     
    if(img_line->x_more_left > x_left)
      img_line->x_more_left = x_left;
  
    if(img_line->x_more_right < x_right)
      img_line->x_more_right = x_right;
    
    if(img_line->y_more_up > y_up)
      img_line->y_more_up = y_up;
    
    if(img_line->y_more_down < y_down)
      img_line->y_more_down = y_down;
     
  }
    
  img_line->x_line_mean = (img_line->x_more_right + img_line->x_more_left) / 2;
  img_line->y_line_mean = (img_line->y_more_down + img_line->y_more_up) / 2;
  

  return INF_NOT_ERR;
}

int sort_left_to_rigth_list_img_line_objs(ImgLine *img_line){
  
  if(img_line == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "image_line/sort_left_to_rigth_list_img_line_objs");
    
  if(img_line->img_line_contours == NULL)
    return *print_big_msg(ERR_GENERIC,
			  "image_line/sort_left_to_rigth_list_img_line_objs",
			  "img_line_contours");
  
  
  int cod_err = sort_generic_list(img_line->img_line_contours, 
				  &compare_x_position_objs_in_img_line);
  
  return cod_err;
}

int compare_x_position_objs_in_img_line(ObjList *obj_1,
				      ObjList *obj_2,
				      int *result){
					
  int cod_err = INF_NOT_ERR;
  
  if(obj_1 == NULL || obj_2 == NULL || result == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "image_line/compare_x_position_objs_in_img_line");
  
  int type_obj_1 = 0, type_obj_2 = 0;
  get_list_obj_type(obj_1, &type_obj_1);
  get_list_obj_type(obj_2, &type_obj_2);
  
  if(type_obj_1 != type_obj_2){
       
    return *print_big_msg(ERR_GENERIC,
		      "image_line/compare_x_position_objs_in_img_line", 
		      "type_obj_1 != type_obj_2");
  }
  
  if(type_obj_1 == TYPE_OBJ_CONTOUR){
    
    Contour *img_contour_1 = (Contour*)obj_1->objetoInformacao;
    Contour *img_contour_2 = (Contour*)obj_2->objetoInformacao;
    
    cod_err = compare_x_relative_position_contours(img_contour_1, 
						   img_contour_2, 
						   result);
  
    
  }else
   return *print_big_msg(ERR_GENERIC, 
			"image_line/compare_x_position_objs_in_img_line", 
			"type_obj_1 != TYPE_OBJ_CONTOUR");  
      
  return cod_err; 

}

int calc_objs_img_line_measures(ImgLine *img_line){
					
  int cod_err = INF_NOT_ERR;
  
  if(img_line == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "image_line/calc_objs_img_line_measures");
    
  
  if(img_line->img_line_contours == NULL)
    return *print_msg(ERR_GENERIC,
		      "image_line/calc_objs_img_line_measures");
    
  cod_err = sort_left_to_rigth_list_img_line_objs(img_line);
  
  if(cod_err != INF_NOT_ERR)
    return *print_big_msg(cod_err,
		      "image_line/calc_objs_img_line_measures",
		      "sort_left_to_rigth_list_img_line_objs");
  
  int x_left = 0, x_right = 0, y_up = 0, y_down = 0; 
  int hight_act = 0, width_act = 0, area_act = 0, dist_act = 0;
  
  int sum_area = 0, sum_hight = 0, sum_width = 0, sum_dist = 0;
  
  ObjList *obj_actual = get_initial_list_obj(img_line->img_line_contours);
  
  void *obj_info_act = NULL;
  Contour *contour_img_act = NULL;
  Contour *contour_img_ant = NULL;
  

  while(obj_actual != NULL){
    
    obj_info_act = obj_actual->objetoInformacao;
    
    if(obj_info_act != NULL){
      
      contour_img_act = (Contour *) obj_info_act;
      
      area_act = calc_contour_area(contour_img_act);
      
      
      get_contour_x_more_left(contour_img_act, &x_left);
      get_contour_x_more_right(contour_img_act, &x_right);
      get_contour_y_more_up(contour_img_act, &y_up);
      get_contour_y_more_down(contour_img_act, &y_down);
      
      width_act = x_right - x_left;
      hight_act = y_down - y_up;
      
      sum_area += area_act;
      sum_hight += hight_act;
      sum_width += width_act;
      
      if(contour_img_ant != NULL){
	
	cod_err = calc_dist_x_contours(contour_img_ant, 
				       contour_img_act, 
				       &dist_act);
	
	if(cod_err != INF_NOT_ERR)
	  return *print_big_msg(cod_err, 
				"image_line/calc_objs_img_line_measures", 
				"calc_dist_x_contours");
	
	sum_dist += dist_act;
      }
      
      if(obj_actual == get_initial_list_obj(img_line->img_line_contours)){
	
	if(contour_img_ant != NULL){
	  img_line->smaller_dist_between_objs = dist_act;
	  img_line->bigger_dist_between_objs  = dist_act;
	}
	
	img_line->bigger_area_line_obj 	 = area_act;
	img_line->smaller_area_line_obj  = area_act;

	img_line->bigger_hight_line_obj  = hight_act;
	img_line->bigger_width_line_obj  = width_act;
	
	img_line->smaller_hight_line_obj = hight_act;
	img_line->smaller_width_line_obj = width_act;
	

      }else{
	
	if(contour_img_ant != NULL){
	  
	  if(img_line->smaller_dist_between_objs > dist_act)
	    img_line->smaller_dist_between_objs = dist_act;
	
	  if(img_line->bigger_dist_between_objs < dist_act)
	    img_line->bigger_dist_between_objs = dist_act;
	  
	}
	
	if(img_line->bigger_area_line_obj < area_act)
	  img_line->bigger_area_line_obj = area_act;
	
	if(img_line->smaller_area_line_obj > area_act)
	  img_line->smaller_area_line_obj = area_act;

	
	if(img_line->bigger_hight_line_obj  < hight_act)
	  img_line->bigger_hight_line_obj = hight_act;
	
	if(img_line->bigger_width_line_obj < width_act)
	  img_line->bigger_width_line_obj = width_act;
	
	if(img_line->smaller_hight_line_obj > hight_act)
	  img_line->smaller_hight_line_obj = hight_act;
	
	if(img_line->smaller_width_line_obj > width_act)
	  img_line->smaller_width_line_obj = width_act;
	
      }

    }

    contour_img_ant = contour_img_act;
    
    obj_actual = obj_actual->proxObjeto;
    
  }
  
  int n_objs = 0;
  getNumObjDaLista(img_line->img_line_contours, &n_objs);
  
  img_line->avr_area_line_objs = sum_area / n_objs ;
  img_line->avr_distance_between_objs = sum_dist / n_objs;
  img_line->avr_hight_line_objs = sum_hight / n_objs;
  img_line->avr_width_line_objs = sum_width / n_objs;
  
  calc_avr_bigger_distance_between_objs(img_line);
  
  return cod_err; 

}

int calc_avr_bigger_distance_between_objs(ImgLine *img_line){
  
  int cod_err = INF_NOT_ERR;
  
  if(img_line == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "image_line/calc_avr_bigger_distance_between_objs");
    
  
  if(img_line->img_line_contours == NULL)
    return *print_msg(ERR_GENERIC,
		      "image_line/calc_avr_bigger_distance_between_objs");
  
  ObjList *obj_actual = get_initial_list_obj(img_line->img_line_contours);
  
  void *obj_info_act = NULL;
  Contour *contour_img_act = NULL;
  Contour *contour_img_ant = NULL;
  
  int avr_dist = img_line->avr_distance_between_objs;
  int n_objs_bigger_dist = 0;
  int sum_bigger_dist = 0;
  int dist_act = 0;
  
  while(obj_actual != NULL){
    
    obj_info_act = obj_actual->objetoInformacao;
    
    if(obj_info_act != NULL){
      
      contour_img_act = (Contour *) obj_info_act;
      
      
      if(contour_img_ant != NULL){
	
	cod_err = calc_dist_x_contours(contour_img_ant, 
				       contour_img_act, 
				       &dist_act);
	
	if(cod_err != INF_NOT_ERR)
	  return *print_big_msg(cod_err, 
				"image_line/calc_objs_img_line_measures", 
				"calc_dist_x_contours");
	
	if(dist_act > avr_dist){
	  sum_bigger_dist += dist_act;
	  n_objs_bigger_dist++;
	}
	  
      }
      
      
    }
    
    contour_img_ant = contour_img_act;
    
    obj_actual = obj_actual->proxObjeto;
  }
  
  n_objs_bigger_dist = n_objs_bigger_dist > 0 ? n_objs_bigger_dist : 1;
  
  img_line->avr_bigger_distance_between_objs = sum_bigger_dist / n_objs_bigger_dist;

  return INF_NOT_ERR;
}

int is_img_line_empty(ImgLine *img_line, int *result){
  
  if(img_line == NULL || result == NULL){
    return *print_big_msg(ERR_PTR_NULL, 
			  "image_line/is_img_line_empty", 
			  "img_line");
  }
  
  if(img_line->img_line_contours == NULL)
    return *print_big_msg(ERR_PTR_NULL, 
			  "image_line/is_img_line_empty", 
			  "img_line->img_line_contours");
  
  int cod_err = INF_NOT_ERR;
  int res = 0;
  
  cod_err = getNumObjDaLista(img_line->img_line_contours, &res);
  
  *result = res < 1 ? TRUE : FALSE;
  
  return cod_err;
  
}

int is_contour_from_img_line(ImgLine *img_line, Contour *contour, int *result){
  
  if(img_line == NULL || contour == NULL || result == NULL){
    
    return *print_msg(ERR_PTR_NULL, 
		      "img_line/is_contour_from_img_line");
  }
  
  int y_mean_line = img_line->y_line_mean;
  
  int y_down_line = img_line->y_more_down;
  
  int y_up_line = img_line->y_more_up;
  
  int y_up_contour = 0, y_down_contour = 0;
  
  get_contour_y_more_up  (contour, &y_up_contour  );
  get_contour_y_more_down(contour, &y_down_contour);
  
  int y_mean_contour = (y_up_contour + y_down_contour) / 2;
  
  //Contour is more down
  if(y_mean_contour > y_mean_line){
  
    //if y_mean_contour is equal or more up than y_down_line
    if(y_mean_contour <= y_down_line)
      *result = TRUE;
    else
      *result = FALSE;
    
  }else if(y_mean_contour < y_mean_line){
    
    //if y_mean_contour is equal or more down than y_up_line
    if(y_mean_contour >= y_up_line)
      *result = TRUE;
    else
      *result = FALSE;
  
    
  }else
    *result = TRUE;
  
  return INF_NOT_ERR;

}
  


int set_mean_x_img_line(ImgLine *img_line, int x){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/set_mean_x_img_line");
  }
  
  img_line->x_line_mean = x;
  
  return INF_NOT_ERR;
}

int set_mean_y_img_line(ImgLine *img_line, int y){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/set_mean_y_img_line");
  }
  
  img_line->y_line_mean = y;
  
  return INF_NOT_ERR;
}

int set_line_contours_list(ImgLine *img_line, ListGeneric *list){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/set_line_contours_list");
  }
  
  img_line->img_line_contours = list;
  
  return INF_NOT_ERR;
  
}

int get_n_objs_in_img_line(ImgLine *img_line, int *n_objs){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_n_objs_in_img_line");
  }
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = getNumObjDaLista(img_line->img_line_contours, n_objs);
  
  return cod_err;
}

int get_mean_x_img_line(ImgLine *img_line, int *x){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_mean_x_img_line");
  }
  
  *x = img_line->x_line_mean;
  
  return INF_NOT_ERR;
}

int get_mean_y_img_line(ImgLine *img_line, int *y){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_mean_y_img_line");
  }
  
  *y = img_line->y_line_mean;
  
  return INF_NOT_ERR;
}

int get_mean_dist_between_img_line_objs(ImgLine *img_line, int *dist_mean){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_mean_dist_between_img_line_objs");
  }
  
  *dist_mean = img_line->avr_distance_between_objs;
  
  return INF_NOT_ERR;
}

int get_mean_width_img_line_objs(ImgLine *img_line, int *width_mean){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_mean_width_img_line_objs");
  }
  
  *width_mean = img_line->avr_width_line_objs;
  
  return INF_NOT_ERR;
}

int get_mean_hight_img_line_objs(ImgLine *img_line, int *hight_mean){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_mean_hight_img_line_objs");
  }
  
  *hight_mean = img_line->avr_hight_line_objs;
  
  return INF_NOT_ERR;
  
}

int get_mean_area_img_line_objs(ImgLine *img_line, int *area_mean){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_mean_area_img_line_objs");
  }
  
  *area_mean = img_line->avr_area_line_objs;
  
  return INF_NOT_ERR;
}

int get_smaller_width_img_line_obj(ImgLine *img_line, int *width_small){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_smaller_width_img_line_obj");
  }
  
  *width_small = img_line->smaller_width_line_obj;
  
  return INF_NOT_ERR;
}

int get_bigger_width_img_line_obj(ImgLine *img_line, int *width_big){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_bigger_width_img_line_obj");
  }
  
  *width_big = img_line->bigger_width_line_obj;
  
  return INF_NOT_ERR;
}

int get_smaller_hight_img_line_obj(ImgLine *img_line, int *hight_small){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_smaller_hight_img_line_obj");
  }
  
  *hight_small = img_line->smaller_hight_line_obj;
  
  return INF_NOT_ERR;
}

int get_bigger_hight_img_line_obj(ImgLine *img_line, int *hight_big){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_bigger_hight_img_line_obj");
  }
  
  *hight_big = img_line->bigger_hight_line_obj;
  
  return INF_NOT_ERR;
}

int get_smaller_area_img_line_obj(ImgLine *img_line, int *area_small){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_smaller_area_img_line_obj");
  }
  
  *area_small = img_line->smaller_area_line_obj;
  
  return INF_NOT_ERR;
}

int get_bigger_area_img_line_obj(ImgLine *img_line, int *area_big){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_bigger_area_img_line_obj");
  }
  
  *area_big = img_line->bigger_area_line_obj;
  
  return INF_NOT_ERR;
}


int get_x_left_img_line_obj(ImgLine *img_line, int *x_left){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_x_left_img_line_obj");
  }
  
  *x_left = img_line->x_more_left;
  
  return INF_NOT_ERR;

}

int get_x_right_img_line_obj(ImgLine *img_line, int *x_right){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_x_right_img_line_obj");
  }
  
  *x_right = img_line->x_more_right;
  
  return INF_NOT_ERR;
}

int get_y_up_img_line_obj(ImgLine *img_line, int *y_up){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_y_up_img_line_obj");
  }
  
  *y_up = img_line->y_more_up;
  
  return INF_NOT_ERR;
}

int get_y_down_img_line_obj(ImgLine *img_line, int *y_down){
  
  if(img_line == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "image_line/get_y_down_img_line_obj");
  }
  
  *y_down = img_line->y_more_down;
  
  return INF_NOT_ERR;
  
}


ListGeneric* get_img_line_contours_list(ImgLine *img_line){
  
  if(img_line == NULL){
    print_msg(ERR_PTR_NULL, 
	      "image_line/get_line_chars_seed");
    
    return NULL;
  }
  
  return img_line->img_line_contours;
  
}

void print_statistical_info(ImgLine *img_line){
  
  printf("\n\t\t\tImgLine statistical\n");
  
  printf("- Avrs\n ");
  
  printf("\tavr_area_line_objs = %d\n", 
	 img_line->avr_area_line_objs);
  
  printf("\tavr_width_line_objs = %d , avr_hight_line_objs = %d\n", 
	 img_line->avr_width_line_objs, img_line->avr_hight_line_objs);
  
  printf("\tavr_distance_between_objs = %d , avr_bigger_distance_between_objs = %d\n ", 
	 img_line->avr_distance_between_objs, img_line->avr_bigger_distance_between_objs);
  
  printf("\n- Extreme Measures\n ");

  printf("\tsmaller_dist_between_objs = %d , bigger_dist_between_objs = %d\n", 
	img_line->smaller_dist_between_objs, img_line->bigger_dist_between_objs);
  
  printf("\tsmaller_width_line_obj = %d , bigger_width_line_obj = %d\n", 
	 img_line->smaller_width_line_obj, img_line->bigger_width_line_obj);
  
  printf("\tsmaller_hight_line_obj = %d , bigger_hight_line_obj = %d\n", 
	img_line->smaller_hight_line_obj, img_line->bigger_hight_line_obj);
  
  printf("\tsmaller_area_line_obj = %d , bigger_area_line_obj = %d\n", 
	 img_line->smaller_area_line_obj, img_line->bigger_area_line_obj);
  
  printf("\tx_more_left = %d , x_more_right = %d\n", 
	img_line->x_more_left, img_line->x_more_right);
  
  printf("\ty_more_up = %d , y_more_down = %d\n", 
	 img_line->y_more_up, img_line->y_more_down);
    
  printf("\tx_line_mean = %d , y_line_mean = %d\n", 
	 img_line->x_line_mean, img_line->y_line_mean);

  
}

int free_img_line_and_objs(ImgLine **img_line){
  
  if(img_line != NULL){
    
    if(*img_line != NULL){
      
      if((*img_line)->img_line_contours != NULL)
	freeListaEDep(&((*img_line)->img_line_contours));
      
      
      free(*img_line);
      
    }
  }
  
  return INF_NOT_ERR;
  
}

int free_only_img_line(ImgLine **img_line){
  
  if(img_line != NULL){
    
    if(*img_line != NULL){
      
      (*img_line)->img_line_contours = NULL;
    
      free(*img_line);
      
    }
  }
  
  return INF_NOT_ERR;
}
