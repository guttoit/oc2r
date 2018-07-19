#ifndef CONTOUR_H
#define CONTOUR_H

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core_c.h>
#include "../util/util_cv.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _contour{
    
    int x_more_left;
    int x_more_right;
    
    /**
     * Remember that how much larger the y value, 
     * more down it will be positioned. And, how much
     * lower the y value, more up it will be positioned.
     */
    int y_more_down;

    int y_more_up; 
    
    int x_mean_value;
    int y_mean_value;
    
    int width;
    int height;
    
    void *cv_contour;
    
}Contour;


Contour* create_contour(void *cv_contour);

void* get_contour_data(Contour *contour);

int calc_and_set_contour_measure(Contour *contour);

int get_contour_x_more_left(Contour *contour, int *x);

int get_contour_x_more_right(Contour *contour, int *x);

int get_contour_y_more_up(Contour *contour, int *y);

int get_contour_y_more_down(Contour *contour, int *y);

int calc_contour_area(Contour *contour);

int is_contour_convex(Contour *contour);

int is_contour_data_null(Contour *contour);

int is_contour_1_all_left_contour_2(Contour *contour_1, 
				    Contour *contour_2, 
				    int *result);

int is_contour_1_all_right_contour_2(Contour *contour_1, 
				     Contour *contour_2, 
				     int *result);

int is_contour_1_inside_left_contour_2(Contour *contour_1, 
				       Contour *contour_2, 
				       int *result);

int is_contour_1_inside_right_contour_2(Contour *contour_1, 
					Contour *contour_2, 
					int *result);

int is_contours_same_place(Contour *contour_1, 
			   Contour *contour_2, 
			   int lim_dist, 
			   int *result);

int is_contours_same_x_place(Contour *contour_1, 
			     Contour *contour_2, 
			     int *result);

int is_contour_an_accent(Contour *contour_1, 
		         Contour *contour_2, 
			 int *result);

int compare_x_relative_position_contours(Contour *contour_1, 
					 Contour *contour_2,
					 int *result);

int y_diff_contour_1_to_contour_2(Contour *contour_1, 
				  Contour *contour_2, 
				  int *result);
/**
 * Do compare the relation between contour_1 and contour_2 using 
 * the y_axis value.
 * 
 */
int compare_y_relative_position_contours(Contour *contour_1, 
					 Contour *contour_2,
					 int *result);

int calc_dist_x_contours(Contour *contour_1, Contour *contour_2, int *result);

int free_contour(Contour **mContorno);

#endif
