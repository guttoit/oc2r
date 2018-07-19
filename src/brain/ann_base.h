#ifndef ANN_BASE_H
#define ANN_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <fann.h>
#include <fann_train.h>
#include "../util/util_fann.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _ann_base{
  
  void *f_ann;
  
  unsigned int n_layers;
  unsigned int *neurons_layers;
  
  int type_algorithm_train;
  int type_func_activation;
  int type_func_act_output_layer;
  int type_func_stop_train;
  
  unsigned int n_epochs;
  unsigned int n_epochs_print;
  
  float learning_rate;
  float err_desired;
  
  
}AnnBase;

AnnBase* create_ann_base();

AnnBase* create_ann_base_from_path(char *path_ann);

AnnBase* create_init_ann_base(unsigned int n_layers, 
			      unsigned int *layers);

int config_train_ann_base(AnnBase *ann_base,
		     int algorithm_train,
		     int func_activation,
		     int func_act_output_layer,
		     int func_stop_train,
		     unsigned int n_epochs, 
		     unsigned int n_epochs_print_output,
		     float learn_rate,
		     float err_desired);


int set_fann_config_base(AnnBase *ann_base);

int set_algorithm_train_base(AnnBase *ann_base, int algorithm);

int set_func_activation_base(AnnBase *ann_base, int type_func);

int set_func_stop_train_base(AnnBase *ann_base, int type_func);

int set_err_desired_base(AnnBase *ann_base, float err_desired);

int set_learn_rate_base(AnnBase *ann_base, float learn_rate);

int get_num_outputs_base(AnnBase *ann_base, int *n_output);

int verify_validity_params_base(AnnBase *ann_base);

int is_algortihm_train_valid_base(int type_algorithm);

int is_func_activation_valid_base(int type_func);

int is_func_stop_train_valid_base(int type_func);

int free_ann_base(AnnBase **ann_base);


#endif
