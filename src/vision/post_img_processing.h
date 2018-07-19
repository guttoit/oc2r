#ifndef POST_IMG_PROCESSING_H
#define POST_IMG_PROCESSING_H

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core_c.h>
#include <stdio.h>
#include <stdlib.h>
#include "pre_img_processing.h"
#include "img_processing.h"
#include "../util/util_cv.h"
#include "image.h"
#include "image_line.h"
#include "../data_structure/list_generic.h"
#include "image_object.h"
#include "contour.h"
#include "../util/util_macros.h"


int create_and_set_list_img_contours(Image *img);

int create_and_set_list_img_lines(Image *img);

int filter_redundant_contours(Image *img, 
			      int desvio_padrao);

int filter_invalid_contours(Image *img, int tam_min);

int find_and_merge_accents_in_line(ImgLine *img_line);

int find_and_merge_accents(Image *img);

ListGeneric* create_list_line_objs(ImgLine *img_line);

ListGeneric* create_list_of_img_objs(Image *imgIn);


#endif

