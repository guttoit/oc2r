#ifndef TRAINING_IMG_H
#define TRAINING_IMG_H

#include <stdio.h>
#include <stdlib.h>
#include "training_object.h"
#include "../data_structure/object_list.h"
#include "../vision/image.h"
#include "../data_structure/list_generic.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _training_img{
  
  Image *img;
  
  ListGeneric *training_objs;
  
  int index_output_desired;
  
}TrainingImg;

TrainingImg* create_init_training_img(Image *img, 
				      int index_output_desired);

TrainingImg* create_training_img();

int init_training_img(TrainingImg *training_img, 
		      Image *img, 
		      int index_output_desired);



int set_training_img(TrainingImg *training_img, Image *img);

int set_training_objs(TrainingImg *training_img, 
		      ListGeneric *training_objs);

int add_training_obj(TrainingImg *training_img, 
		     TrainingObj *obj);

int create_and_add_training_obj(TrainingImg *training_img, 
				ImgObject *objImg,  
				int index_output_desired);

Image* get_img_of_training_img(TrainingImg *training_img);

ListGeneric* get_training_objs(TrainingImg *training_img);

int get_index_training_img_output(TrainingImg *training_img, 
				  int *index);

int free_training_img(TrainingImg **training_img);
#endif