#ifndef TRAINING_SET_H
#define TRAINING_SET_H

#include <stdio.h>
#include <stdlib.h>
#include "../util/util_train.h"
#include "training_img.h"
#include "../data_structure/list_generic.h"
#include "../data_structure/object_list.h"
#include "../util/util_macros.h"

typedef struct _training_set_objects{
  
  FileConfig *file_config_train;
  
  ListGeneric *training_imgs;
  
  int *output_data_resolution;
  
}TrainingSet;

TrainingSet* create_init_training_set(int *output_data_resolution, 
				      char *path_config_train);

TrainingSet* create_training_set();

int init_training_set(TrainingSet *training_set, 
		      char *path_config_train, 
		      int *output_data_resolution);

int add_training_img(TrainingSet *training_set, 
		     TrainingImg *training_img);

int set_file_config_training(TrainingSet *training_set, 
			     FileConfig *file_config_train);

int set_training_imgs(TrainingSet *training_set, 
		      ListGeneric *training_imgs);

int set_data_resolution(TrainingSet *training_set, 
			int *output_data_resolution);

int get_n_training_imgs(TrainingSet *training_set, int *num);

int get_n_total_training_objs(TrainingSet *training_set, int *num);

ListGeneric* get_training_imgs(TrainingSet *training_set);

int free_training_set(TrainingSet **training_set);

#endif