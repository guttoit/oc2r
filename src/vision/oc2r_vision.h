#ifndef OC2R_VISION_H
#define OC2R_VISION_H

#include "post_img_processing.h"
#include "img_processing.h"
#include "pre_img_processing.h"
#include "image_object.h"
#include "image.h"
#include "contour.h"

typedef struct _contour Contour;
typedef struct _image Image;
typedef struct _img_object ImgObject;


//#-------------------contour_funcions-------------------------#

Contour* oc2r_create_contour(void *cv_contour){
  
  return create_contour(cv_contour);
}

void* oc2r_get_contour_data(Contour *contour){
  
  return get_contour_data(contour);
}

int oc2r_calc_and_set_contour_measure(Contour *contour){
  
  return calc_and_set_contour_measure(contour);
}

int oc2r_get_contour_x_more_left(Contour *contour, int *x){
  
  return get_contour_x_more_left(contour, x);
}

int oc2r_get_contour_x_more_right(Contour *contour, int *x){
  
  return get_contour_x_more_right(contour, x);
}

int oc2r_get_contour_y_more_up(Contour *contour, int *y){
  
  return get_contour_y_more_up(contour, y);
}

int oc2r_get_contour_y_more_down(Contour *contour, int *y){
  
  return get_contour_y_more_down(contour, y);
}

int oc2r_calc_contour_area(Contour *contour){
  
  return calc_contour_area(contour);
}

int oc2r_is_contour_data_null(Contour *contour){
  
  return is_contour_data_null(contour);
}

int oc2r_is_contour_1_all_left_contour_2(Contour *contour_1, 
				    Contour *contour_2, 
				    int *result){
  
  return is_contour_1_all_left_contour_2(contour_1, 
					 contour_2, 
					 result);
}

int oc2r_is_contour_1_all_right_contour_2(Contour *contour_1, 
				     Contour *contour_2, 
				     int *result){
				       
  return is_contour_1_all_right_contour_2(contour_1, 
					  contour_2, 
					  result);
}

int oc2r_is_contour_1_inside_left_contour_2(Contour *contour_1, 
				       Contour *contour_2, 
				       int *result){
					 
  return is_contour_1_inside_left_contour_2(contour_1, 
					    contour_2, 
					    result);

}

int oc2r_is_contour_1_inside_right_contour_2(Contour *contour_1, 
					Contour *contour_2, 
					int *result){
					  
  return is_contour_1_inside_right_contour_2(contour_1, 
					     contour_2, 
					     result);
}

int oc2r_is_contours_same_place(Contour *contour_1, 
			   Contour *contour_2, 
			   int lim_dist, 
			   int *result){
			     
  return is_contours_same_place(contour_1, 
				contour_2, 
				lim_dist, 
				result);
}

int oc2r_free_contour(Contour **mContorno){
  
  return free_contour(mContorno);
}


#endif