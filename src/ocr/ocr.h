#ifndef OCR_H
#define OCR_H

#include <stdio.h>
#include <string.h>
#include "../vision/post_img_processing.h"
#include "../brain/ann.h"
#include "../vision/image.h"
#include "../vision/image_line.h"
#include "character_seed.h"
#include "text.h"
#include "word_seed.h"
#include "line.h"
#include "../data_structure/list_generic.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"
#include "../brain/ann.h"


#define STAND_MAX_DIST_BETWEEN_CONTOURS 0
#define STAND_MAX_SIZE_INVALID_OBJ 5
#define STAND_MAX_DIST_CHAR_WORD 6
#define STAND_MAX_VAR_Y_LINE 10
#define STAND_MAX_DIST_BETWENN_LINES 0

typedef struct _ocr_config{
  
  int obj_img_resolution;
  
  int is_to_use_statistical_context;
  int is_to_filter_contours;
  int is_to_filter_invalid_obj;
  
  int max_dist_between_contours;
  int max_size_invalid_obj;
  int max_distance_char_word;
  
  char *path_ann;
  
  AnnBase *ann_base;
  
}OCRConfig;

OCRConfig* create_init_ocr_config(int resolution,
				  int is_contextual,
				  int is_filter_contours,
				  int is_filter_inv_obj,
				  char *path_ann);

ListGeneric* init_ocr_recognition(OCRConfig *ocr_config,
				  char *path_image);


int set_ocr_config_params(OCRConfig *ocr_config, 
			  int max_dist_between_contours, 
			  int max_dist_char_word, 
			  int max_size_inv_obj);

int is_ocr_config_valid(OCRConfig *ocr_config, int *result);

int ocr_ann_recognized_line_objs(OCRConfig *ocr_config, Line *line);

int ocr_ann_recognized(OCRConfig *ocr_config, ListGeneric *lines);

CharSeed* ocr_ann_obj_img_recognized(ImgObject *obj_img, 
				     OCRConfig *ocr_config);

int compare_y_objs_position(ObjList *obj_1, 
			    ObjList *obj_2,
			    int *result);

ListGeneric* ocr_create_lines(OCRConfig *ocr_config, Image *img);


int is_char_seed_from_line(Line *line, 
			   CharSeed *char_seed, 
			   int *result);


int ocr_create_words(OCRConfig *ocr_config,
		      ListGeneric *lines);

int ocr_create_words_of_line(OCRConfig *ocr_config,
			     Line *line);

Text* ocr_text_create(OCRConfig *ocr_config, 
		       ListGeneric *lines_text);


int free_ocr_config(OCRConfig **ocr_config);

#endif