#ifndef TRAIN_CREATE_H
#define TRAIN_CREATE_H

#include <stdio.h>
#include <stdlib.h>
#include "../data_process/training_set.h"
#include "../data_process/training_img.h"
#include "../data_process/training_object.h"
#include "../vision/post_img_processing.h"
#include "../util/util_cv.h"
#include "../data_structure/list_generic.h"
#include "../data_structure/object_list.h"
#include "../vision/image_object.h"
#include "../data_structure/matrix.h"
#include "../util/util_train.h"
#include "../util/util_ocr.h"
#include "../util/util_fann.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

/**
 * Recebe o path do arquivo de treinamento que contem
 * o caminho das imagens que serao usadas para gerar os 
 * dados treinamento.
 */

TrainingSet* create_and_save_dataset_from_imgs(char *file_conf, 
					      char *file_out, 
					      int *data_resolution);

TrainingSet* create_dataset_from_imgs(char *p_conf, int *data_resolution );


int training_img_processing(TrainingImg *training_img);

int save_training_set_data(TrainingSet *training_set, char *path, int *resolution);

int save_training_set_ann_input_data(TrainingSet *training_set, char *path_data, int *resolution);

int save_training_img_data(TrainingImg *training_img, char *path, int *resolution);

int save_training_img_ann_input_data(TrainingImg *training_img, char *path_data_ann, int *resolution);

char* get_training_img_data(TrainingImg *training_img, int *resolution);



#endif
