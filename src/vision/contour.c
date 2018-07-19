#include "contour.h"


Contour* create_contour(void *c_contour){
  
  if(c_contour == NULL){
    print_msg(ERR_OBJ_NULL_LIST,"contour.c/create_contour");
    return NULL;
  }
  
  Contour *contour = (Contour*) malloc(sizeof(Contour));
    
  int err = INF_NOT_ERR;
  
  contour->cv_contour = c_contour;
  
  err = calc_and_set_contour_measure(contour);
  
  if(err != INF_NOT_ERR){
    print_msg(err,"contour.c/create_contour");
    free_contour(&contour);
    
    return NULL;
  }
  
  return contour;
}

void* get_contour_data(Contour *contour){
  
  if(contour == NULL){
    print_msg(ERR_PTR_NULL, "contour.c/get_contour_data.");
    return NULL;
  }
  
  return contour->cv_contour;
    
}

int calc_and_set_contour_measure(Contour *contour){
  
  if(contour == NULL)
    return *print_msg(ERR_PTR_NULL, "contour.c\
				  /calc_and_set_contour_measure.");
  
  if(contour->cv_contour == NULL)
    return *print_msg(ERR_PTR_NULL, "contour.c\
				  /calc_and_set_contour_measure.");
  
  CvSeq *cv_contour = (CvSeq*) (contour->cv_contour);
  
  CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, cv_contour, 0);
  
  contour->x_more_left = p->x; contour->x_more_right = p->x; contour->y_more_down = p->y; 
  contour->y_more_up = p->y; contour->x_mean_value = 0; contour->y_mean_value = 0;
  
  int i;
  
  for(i = 1; i < cv_contour->total; i++ ) {
    
    p = CV_GET_SEQ_ELEM( CvPoint, cv_contour, i);
    
    contour->x_more_left = p->x < contour->x_more_left ? p->x : contour->x_more_left;
    contour->x_more_right = p->x > contour->x_more_right ? p->x : contour->x_more_right;
    
    contour->y_more_down = p->y > contour->y_more_down ? p->y : contour->y_more_down;
    contour->y_more_up = p->y < contour->y_more_up ? p->y : contour->y_more_up;
  }
  
  
  contour->x_mean_value = (contour->x_more_left + contour->x_more_right) / 2;
  contour->y_mean_value = (contour->y_more_down + contour->y_more_up) / 2;
  
  contour->width = contour->x_more_right - contour->x_more_left;
  contour->height = contour->y_more_down - contour->y_more_up;
  
  return INF_NOT_ERR;
}

int get_contour_x_more_left(Contour *contour, int *x){
  
  if(contour == NULL){
    print_msg(ERR_PTR_NULL,"contour.c/get_img_obj_x_more_left");
    return ERR_PTR_NULL;
  }
    
    *x = contour->x_more_left;
    
    return INF_NOT_ERR; 
}

int get_contour_x_more_right(Contour *contour, int *x){
  
  if(contour == NULL){
    print_msg(ERR_PTR_NULL,"contour.c/get_img_obj_x_more_right");
    return ERR_PTR_NULL;
  }
    
  *x = contour->x_more_right;
  
  return INF_NOT_ERR;
}

int get_contour_y_more_up(Contour *contour, int *y){
  
  if(contour == NULL){
    print_msg(ERR_PTR_NULL,"contour.c/get_img_obj_y_more_up");
    return ERR_PTR_NULL;
  }
    
  *y = contour->y_more_up;
  
  return INF_NOT_ERR;
}

int get_contour_y_more_down(Contour *contour, int *y){
  
  if(contour == NULL){
    print_msg(ERR_PTR_NULL,"contour.c/get_img_obj_y_more_down");
    return ERR_PTR_NULL;
  }
    
  *y = contour->y_more_down;
  
  return INF_NOT_ERR;
}

int calc_contour_area(Contour *contour){
  
   if(contour == NULL){
    print_msg(ERR_PTR_NULL,"contour.c/calc_contour_area");
    return ERR_PTR_NULL;
  }
    
  int x = contour->x_more_right - contour->x_more_left;
  int y = contour->y_more_down - contour->y_more_up;
  
  //printf("Xd = %d, Xe = %d \n Yc = %d , Yb = %d\n", contour->x_more_right, contour->x_more_left
						//  , contour->y_more_up, contour->y_more_down);
  
  int area = x * y;
    
  return area;
}

int is_contour_convex(Contour *contour){
  
  int res = 0;
  
  res = cvCheckContourConvexity((CvSeq*) contour->cv_contour);
  
  return res;
}

int is_contour_data_null(Contour *contour){
  
  if(contour == NULL)
    return *print_msg(ERR_PTR_NULL,"contour.c/is_contour_data_null");
  
  return contour->cv_contour == NULL ? TRUE : FALSE;
  
}


int is_contour_1_all_left_contour_2(Contour *contour_1, 
				    Contour *contour_2, 
				    int *result){
  
  if(contour_1 == NULL || contour_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaImg.c/is_objs_same_place");
  
  
  *result = contour_1->x_more_right <= contour_2->x_more_left;
  
  return INF_NOT_ERR;
  
}

int is_contour_1_all_right_contour_2(Contour *contour_1, 
				     Contour *contour_2, 
				     int *result){
  
  if(contour_1 == NULL || contour_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaImg.c/is_objs_same_place");
  
  
  *result = contour_1->x_more_left >= contour_2->x_more_right;
  
  return INF_NOT_ERR;
  
}

int is_contour_1_inside_left_contour_2(Contour *contour_1, 
				       Contour *contour_2, 
				       int *result){
  
  if(contour_1 == NULL || contour_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaImg.c/is_objs_same_place");
  
  
  int is_left = 0;
  int is_right = 0;
  
  is_contour_1_all_left_contour_2(contour_1, contour_2, &is_left);
  is_contour_1_all_right_contour_2(contour_1, contour_2, &is_right);
  
  if(!is_left && !is_right){
    
    *result = contour_1->x_more_left <= 
	      contour_2->x_more_left ? TRUE : FALSE;
  
    
  }else
    *result = FALSE;
  
  
  return INF_NOT_ERR;
  
}

int is_contour_1_inside_right_contour_2(Contour *contour_1, 
					Contour *contour_2, 
					int *result){
  
  if(contour_1 == NULL || contour_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaImg.c/is_objs_same_place");
  
  
  int is_left = 0;
  int is_right = 0;
  
  is_contour_1_all_left_contour_2(contour_1, contour_2, &is_left);
  is_contour_1_all_right_contour_2(contour_1, contour_2, &is_right);
  
  if(!is_left && !is_right){
    
    *result = contour_1->x_more_right >= 
	      contour_2->x_more_right ? TRUE : FALSE;
  
    
  }else
    *result = FALSE;
  
  
  return INF_NOT_ERR;
  
}

int is_contours_same_place(Contour *contour_1, 
			   Contour *contour_2, 
			   int lim_dist, 
			   int *result){
    
    
  if(contour_1 == NULL || contour_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaImg.c/is_objs_same_place");
  
  int x1_ext_esq = contour_1->x_more_left; int x1_ext_dir = contour_1->x_more_right;
  int x2_ext_esq = contour_2->x_more_left; int x2_ext_dir = contour_2->x_more_right;
  int y1_maior = contour_1->y_more_down; int y1_menor = contour_1->y_more_up;
  int y2_maior = contour_2->y_more_down; int y2_menor = contour_2->y_more_up;
  
  if(x1_ext_esq < x2_ext_esq)
    x2_ext_esq = contour_2->x_more_left - lim_dist;
    
  else
    x1_ext_esq = contour_1->x_more_left - lim_dist;
  
  if(x1_ext_dir > x2_ext_dir)
    x2_ext_dir = contour_2->x_more_right + lim_dist;
    
  else
    x1_ext_dir = contour_1->x_more_right + lim_dist;
  
  if(y1_maior > y2_maior)
    y2_maior = contour_2->y_more_down + lim_dist;
    
  else
    y1_maior = contour_1->y_more_down + lim_dist;
  
  if(y1_menor < y2_menor)
    y2_menor = contour_2->y_more_up - lim_dist;
    
  else
    y1_menor = contour_1->y_more_up - lim_dist;
  
  int p1_c1[2] = {x1_ext_esq, y1_maior};
  int p2_c1[2] = {x1_ext_esq, y1_menor};
  int p3_c1[2] = {x1_ext_dir, y1_maior};
  int p4_c1[2] = {x1_ext_dir, y1_menor};
  
  int p1_c2[2] = {x2_ext_esq, y2_maior};
  int p2_c2[2] = {x2_ext_esq, y2_menor};
  int p3_c2[2] = {x2_ext_dir, y2_maior};
  int p4_c2[2] = {x2_ext_dir, y2_menor};
  
  
  int is_c1_dentro_c2 = is_p2_entre_p1_e_p3(p1_c1, p1_c2, p4_c2) == TRUE || 
			    is_p2_entre_p1_e_p3(p2_c1, p1_c2, p4_c2) == TRUE ||
			    is_p2_entre_p1_e_p3(p3_c1, p1_c2, p4_c2) == TRUE ||
			    is_p2_entre_p1_e_p3(p4_c1, p1_c2, p4_c2) == TRUE;

  int is_c2_dentro_c1 = is_p2_entre_p1_e_p3(p1_c2, p1_c1, p4_c1) == TRUE || 
			    is_p2_entre_p1_e_p3(p2_c2, p1_c1, p4_c1) == TRUE ||
			    is_p2_entre_p1_e_p3(p3_c2, p1_c1, p4_c1) == TRUE ||
			    is_p2_entre_p1_e_p3(p4_c2, p1_c1, p4_c1) == TRUE;
			    
  *result = is_c1_dentro_c2 || is_c2_dentro_c1;
  
  return INF_NOT_ERR;
}

int is_contours_same_x_place(Contour *contour_1, 
			     Contour *contour_2, 
			     int *result){
			       
  *result = TRUE;
  
  if(contour_1->x_more_left < contour_2->x_more_left){
    
    if(contour_1->x_more_right < contour_2->x_more_left)
      *result = FALSE;
    
  }else if(contour_1->x_more_left > contour_2->x_more_left){
    
    if(contour_1->x_more_left > contour_2->x_more_right)
      *result = FALSE;
  }
  
  return INF_NOT_ERR;
}

int is_contour_an_accent(Contour *contour_1, 
		         Contour *contour_2, 
			 int *result){
			       
  *result = TRUE;
  
  if(contour_1->x_more_left < contour_2->x_more_left){
    
    if(contour_1->x_more_right < contour_2->x_more_left - (contour_1->width/2))
      *result = FALSE;
    
  }else if(contour_1->x_more_left > contour_2->x_more_left){
    
    if(contour_1->x_more_left > (contour_2->x_more_right + (contour_2->width/2)))
      *result = FALSE;
  }
  
  return INF_NOT_ERR;
}

int compare_x_relative_position_contours(Contour *contour_1, 
					 Contour *contour_2,
					 int *result){
  
  int cod_err_1 = INF_NOT_ERR, cod_err_2 = INF_NOT_ERR;
  
  int x_left_1 = 0, x_left_2 = 0;
  int x_right_1 = 0, x_right_2 = 0;
  
  cod_err_1 = get_contour_x_more_left(contour_1, &x_left_1);
  cod_err_2 = get_contour_x_more_left(contour_2, &x_left_2);
  
  if(cod_err_1 != INF_NOT_ERR || cod_err_2 != INF_NOT_ERR)
    return *print_msg(ERR_GENERIC, 
		      "contour/compare_x_relative_position_contours");
    
  
  if(x_left_1 > x_left_2)
    *result = OBJ_1_IS_MAJOR;
  
  else if(x_left_1 < x_left_2)
    *result = OBJ_2_IS_MAJOR;
  
  else{ 
    
    cod_err_1 = get_contour_x_more_right(contour_1, &x_right_1);
    cod_err_2 = get_contour_x_more_right(contour_2, &x_right_2);
    
    if(cod_err_1 != INF_NOT_ERR || cod_err_2 != INF_NOT_ERR)
      return *print_msg(ERR_GENERIC, 
			"contour/compare_x_relative_position_contours");
    
    if(x_right_1 > x_right_2)
      *result = OBJ_1_IS_MAJOR;
    
    else if(x_right_1 < x_right_2)
      *result = OBJ_2_IS_MAJOR;
    
    else
      *result = OBJ_1_AND_2_ARE_EQUAL;
  
  }
  
  
  return INF_NOT_ERR;
  
}

int y_diff_contour_1_to_contour_2(Contour *contour_1, 
				  Contour *contour_2, 
				  int *result){

  //contour_2 is up contour_1
  if(contour_2->y_more_up < contour_1->y_more_up){
  
    *result = contour_1->y_more_up - contour_2->y_more_down;
  
    
  }else if(contour_1->y_more_up < contour_2->y_more_up){
    
    *result = contour_2->y_more_up - contour_1->y_more_down;
    
  }else
    *result = -1;
  
  return INF_NOT_ERR;
}

int compare_y_relative_position_contours(Contour *contour_1, 
					 Contour *contour_2,
					 int *result){
					   
 
  int cod_err_1 = INF_NOT_ERR, cod_err_2 = INF_NOT_ERR;
  
  int y_up_1 = 0, y_up_2 = 0;
  
  cod_err_1 = get_contour_y_more_up(contour_1, &y_up_1);
  cod_err_2 = get_contour_y_more_up(contour_2, &y_up_2);
  
  if(cod_err_1 != INF_NOT_ERR || cod_err_2 != INF_NOT_ERR)
    return *print_msg(ERR_GENERIC, 
		      "contour/compare_y_relative_position_contours");
    
  
  if(y_up_1 > y_up_2)
    *result = OBJ_1_IS_MAJOR;
  
  else if(y_up_1 < y_up_2)
    *result = OBJ_2_IS_MAJOR;
  
  else
    *result = OBJ_1_AND_2_ARE_EQUAL;
  
  
  return INF_NOT_ERR;
    
}


int calc_dist_x_contours(Contour *contour_1, Contour *contour_2, int *result){
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = compare_x_relative_position_contours(contour_1, contour_2, result);
  
  if(*result == OBJ_1_IS_MAJOR || cod_err != INF_NOT_ERR)
    return *print_big_msg(ERR_GENERIC, 
			  "contour/calc_dist_x_contours", 
			  "compare_x_relative_position_contours");
  
  int x_right_1 = 0, x_left_2 = 0;
  
  get_contour_x_more_right(contour_1, &x_right_1);
  get_contour_x_more_left (contour_2, &x_left_2 );
  
  int dist = x_left_2 - x_right_1;
  
  
  //If the distance between the contours is negative, 
  //they probably belong to the same object and should 
  //be unified by the corresponding filtering
  
  *result = dist < 0 ? 0 : dist;
  
  return INF_NOT_ERR;
  
}


int free_contour(Contour **mContorno){
  
  if(mContorno != NULL){
    
    if((*mContorno) != NULL){
      
      if((*mContorno)->cv_contour != NULL)
	cvClearSeq(((CvSeq*) ((*mContorno)->cv_contour)));
    
    
      free((*mContorno));
      (*mContorno) = NULL;
      
    }
    
  }  
  
  return INF_NOT_ERR;
}
