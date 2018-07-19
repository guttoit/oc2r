#ifndef UTIL_CV_H
#define UTIL_CV_H

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "util_macros.h"
#include "../msg_handling/msg_handling.h"

#define CONTOUR_INSERT_END 1
#define CONTOUR_INSERT_START 0

void* load_dados_image(char *pathImage, int canais_cor);

void* clone_dados_img(void *img_to_clone);

int get_nCanais_dados_img(void *img, int *canais);

int* get_dims_dados_img(void *img);

void show_dados_img(void *img, char *name_window);

void show_dados_contour(void *img, void *cv_contour);

int save_img(char *pathName, void *image);

int is_p2_entre_p1_e_p3(int *p2, int *p1, int *p3);

int is_y_2_near_y_1(int y_1, int y_2, 
		    int up_variance);

int is_x_2_near_x_1(int x_1, int x_2, int variance);


int merge_second_contour_in_first(void *contour1, 
				 void *contour2, 
				 int insert_index);

#endif
