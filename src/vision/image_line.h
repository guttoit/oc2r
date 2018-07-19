#ifndef IMAGE_LINE_H
#define IMAGE_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include "contour.h"
#include "../data_structure/list_generic.h"
#include "../data_structure/object_list.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _img_line{
    
  int avr_distance_between_objs;
  int avr_bigger_distance_between_objs;
  
  int avr_width_line_objs;
  int avr_hight_line_objs;
  int avr_area_line_objs;
  
  int smaller_dist_between_objs;
  int bigger_dist_between_objs;
  int smaller_width_line_obj;
  int bigger_width_line_obj;
  int smaller_hight_line_obj;
  int bigger_hight_line_obj;
  int smaller_area_line_obj;
  int bigger_area_line_obj;
  
  int x_more_left;
  int x_more_right;
  int y_more_up;
  int y_more_down;
  
  int x_line_mean;
  int y_line_mean;
 
  //point to Image of line,  
  void *image;
  
  ListGeneric *img_line_contours;

}ImgLine;

ImgLine* create_init_img_line(void *image);

int add_contour_to_img_line(ImgLine *img_line, Contour *contour);

int updates_img_line_after_add_contour(ImgLine *img_line, Contour *contour);

int sort_left_to_rigth_list_img_line_objs(ImgLine *img_line);

int compare_x_position_objs_in_img_line(ObjList *obj_1,
					ObjList *obj_2,
					int *result);

int calc_objs_img_line_measures(ImgLine *img_line);

int is_img_line_empty(ImgLine *img_line, int *result);

int is_contour_from_img_line(ImgLine *img_line, Contour *contour, int *result);

int set_mean_x_img_line(ImgLine *img_line, int x);

int set_mean_y_img_line(ImgLine *img_line, int y);

int set_line_contours_list(ImgLine *line, ListGeneric *list);

int get_n_objs_in_img_line(ImgLine *img_line, int *n_objs);

int get_mean_x_img_line(ImgLine *img_line, int *x);

int get_mean_y_img_line(ImgLine *img_line, int *y);

int get_mean_dist_between_img_line_objs(ImgLine *img_line, int *dist_mean);

int get_mean_width_img_line_objs(ImgLine *img_line, int *width_mean);

int get_mean_hight_img_line_objs(ImgLine *img_line, int *hight_mean);

int get_mean_area_img_line_objs(ImgLine *img_line, int *area_mean);


int get_smaller_width_img_line_obj(ImgLine *img_line, int *width_small);

int get_bigger_width_img_line_obj(ImgLine *img_line, int *width_big);

int get_smaller_hight_img_line_obj(ImgLine *img_line, int *hight_small);

int get_bigger_hight_img_line_obj(ImgLine *img_line, int *hight_big);

int get_smaller_area_img_line_obj(ImgLine *img_line, int *area_small);

int get_bigger_area_img_line_obj(ImgLine *img_line, int *area_big);


int get_x_left_img_line_obj(ImgLine *img_line, int *x_left);

int get_x_right_img_line_obj(ImgLine *img_line, int *x_right);

int get_y_up_img_line_obj(ImgLine *img_line, int *y_up);

int get_y_down_img_line_obj(ImgLine *img_line, int *y_down);

ListGeneric* get_img_line_contours_list(ImgLine *img_line);

void print_statistical_info(ImgLine *img_line);

int free_img_line_and_objs(ImgLine **img_line);

int free_only_img_line(ImgLine **img_line);

#endif
