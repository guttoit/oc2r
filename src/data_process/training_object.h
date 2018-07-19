#ifndef TRAINING_OBJECT_H
#define TRAINING_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include "../util/util_ocr.h"
#include "../vision/image_object.h"
#include "../data_structure/matrix.h"
#include "../util/util_io_string.h"
#include "../util/util_macros.h"

typedef struct _training_obj{
  
  ImgObject *obj_img;
  
  int idx_output_desired;
  
  char *output_desired;
  
}TrainingObj;

TrainingObj* create_training_obj();

int init_training_obj(TrainingObj *obj, 
		      ImgObject *obj_img, 
		      int idx_output_desired);

TrainingObj* create_init_training_obj(ImgObject *obj_img, 
				      int idx_output_desired);

int set_img_obj_from_training_obj(TrainingObj *obj, 
				ImgObject *obj_img);

int set_index_output_desired(TrainingObj *obj, 
			     int index);

int set_output_desired(TrainingObj *obj, char *output);

char* get_output_desired(TrainingObj *obj);

ImgObject* get_img_obj_from_training_obj(TrainingObj *obj);

Matrix* get_mat_img_obj_from_training_obj(TrainingObj *obj, 
					  int *resolution);

char *create_img_obj_mat_from_training_obj(TrainingObj *obj, 
					   int *resolution);

char *create_img_obj_mat_human_view_from_training_obj(TrainingObj *obj, 
						      int *resolution);

int free_training_obj(TrainingObj **obj);
#endif