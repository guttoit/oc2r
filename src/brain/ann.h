#ifndef ANN_H
#define ANN_H

#include <stdio.h>
#include <stdlib.h>
#include <fann.h>
#include <fann_train.h>
#include "ann_base.h"
#include "ann_train.h"
#include "ann_test.h"
#include "../util/util_train.h"
#include "../util/util_fann.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _ann_base AnnBase;

AnnBase* create_ann();

AnnBase* create_ann_from_path(char *path_ann);

AnnBase* create_init_ann(unsigned int n_layers, unsigned int *layers);

int config_train_ann(AnnBase *ann_base,
		     int algorithm_train,
		     int func_activation,
		     int func_act_output_layer,
		     int func_stop_train,
		     unsigned int n_epochs, 
		     unsigned int n_epochs_print_output,
		     float learn_rate,
		     float err_desired);


int train_save_ann(AnnBase *ann_base, 
		   char *p_data_train, 
		   char *name_ann);

AnnTestResult* do_test_ann(char *p_ann, char *p_data_test);


int set_fann_config(AnnBase *ann_base);

int set_algorithm_train(AnnBase *ann_base, int algorithm);

int set_func_activation(AnnBase *ann_base, int type_func);

int set_func_stop_train(AnnBase *ann_base, int type_func);

int set_err_desired(AnnBase *ann_base, float err_desired);

int set_learn_rate(AnnBase *ann_base, float learn_rate);

int get_num_outputs(AnnBase *ann_base, int *n_output);

int verify_validity_params(AnnBase *ann_base);

int is_algortihm_train_valid(int type_algorithm);

int is_func_activation_valid(int type_func);

int free_ann(AnnBase **ann_base);


#endif
