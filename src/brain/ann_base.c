#include "ann_base.h"

AnnBase* create_ann_base (){
  
  AnnBase *ann_base = (AnnBase*) malloc(sizeof(AnnBase));
  
  if(ann_base == NULL)
    print_msg(ERR_MEMORY, "ann_base/create_ann_base");
  
  return ann_base;
}

AnnBase *create_ann_base_from_path(char *path_ann){
  
  if(path_ann == NULL){
    print_msg(ERR_PTR_NULL, "ann_base/create_ann_base_from_path");
    return NULL;
  }
  
  AnnBase *ann_base = create_ann_base();
  struct fann *f_ann = fann_create_from_file(path_ann);
  
  if(ann_base == NULL){
    print_msg(ERR_GENERIC, "ann_base/create_ann_base_from_path");
    return NULL;
  }
  
  if(f_ann == NULL){
    print_big_msg(ERR_GENERIC, 
		  "ann_base/create_ann_base_from_path", 
		  "f_ann");
    
    free_ann_base(&ann_base);
    
    return NULL;
  }
  
  int ANY_ONE_NEURON = 2;
  int ANY_HIDDEN_LAYER = 2;
  int layers = fann_get_num_layers(f_ann);
  ann_base->n_layers = layers;
  
  
  ann_base->neurons_layers = malloc(sizeof(unsigned int) * layers);
  fann_get_layer_array(f_ann, ann_base->neurons_layers);
  
  ann_base->type_func_stop_train = fann_get_train_stop_function(f_ann);
  ann_base->type_algorithm_train = fann_get_training_algorithm(f_ann);
  ann_base->type_func_activation = fann_get_activation_function(f_ann, 
								ANY_ONE_NEURON, 
								ANY_HIDDEN_LAYER);
  
  ann_base->n_epochs = 0;
  ann_base->n_epochs_print = 0;
  ann_base->learning_rate = 0;
  ann_base->err_desired = 0;
  
  ann_base->f_ann = (void *) f_ann;
    
  return ann_base;
}


AnnBase *create_init_ann_base(unsigned int n_layers, 
			      unsigned int *layers){
				    
  
  AnnBase *ann_base = (AnnBase*) malloc(sizeof(AnnBase));
  
  if(ann_base == NULL || layers == NULL){
    print_msg(ERR_MEMORY, "ann_base/create_ann_base");
    return NULL;
  }
  
  ann_base->n_layers = n_layers;
  ann_base->neurons_layers = layers;
  
  struct fann *f_ann = fann_create_standard_array(n_layers,
						  layers);
  
  ann_base->f_ann = (void *) f_ann;
  
  return ann_base;
}

int config_train_ann_base(AnnBase *ann_base,
			  int algorithm_train,
			  int func_activation,
			  int func_act_output_layer,
			  int func_stop_train,
			  unsigned int n_epochs, 
			  unsigned int n_epochs_print_output,
			  float learn_rate,
			  float err_desired){
		       
  
  ann_base->type_algorithm_train = algorithm_train;
  ann_base->type_func_activation = func_activation;
  ann_base->type_func_act_output_layer = func_act_output_layer;
  ann_base->type_func_stop_train = func_stop_train;
  
  ann_base->n_epochs = n_epochs;
  ann_base->n_epochs_print = n_epochs_print_output;
  ann_base->learning_rate = learn_rate;
  ann_base->err_desired = err_desired;
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = verify_validity_params_base(ann_base);
  cod_err = set_fann_config_base(ann_base);
  
  if(cod_err != INF_NOT_ERR){
    
    print_msg(cod_err, "ann_base/create_init_ann_base");
    
    free_ann_base(&ann_base);
    
    return cod_err;
  }
  
  return cod_err;
}


int set_fann_config_base(AnnBase *ann_base){
  
  //int cod_err = INF_NOT_ERR;
  
  if(ann_base == NULL)
    return *print_msg(ERR_PTR_NULL, "ann_base/set_fann_config_base");
  
  if(ann_base->f_ann == NULL){
    
    ann_base->f_ann = (void*) fann_create_standard_array(ann_base->n_layers,
							 ann_base->neurons_layers);
  }
    
    
  fann_set_training_algorithm((struct fann*) ann_base->f_ann, 
			      ann_base->type_algorithm_train);
  
  fann_set_activation_function_hidden((struct fann*) ann_base->f_ann,
				      ann_base->type_func_activation);
  
  fann_set_activation_function_output((struct fann*) ann_base->f_ann, 
				      ann_base->type_func_act_output_layer);
  
  fann_set_train_stop_function((struct fann*) ann_base->f_ann,
			      ann_base->type_func_stop_train);
  
  fann_set_learning_rate((struct fann*) ann_base->f_ann,
			 ann_base->learning_rate);
  
  return INF_NOT_ERR;
  
}


int set_algorithm_train_base(AnnBase *ann_base, int algorithm){
  
  if(ann_base == NULL || !is_algortihm_train_valid_base(algorithm))
    return *print_msg(ERR_GENERIC, "ann_base/set_algorithm_train");
  
  if(ann_base->f_ann == NULL)
    return *print_msg(ERR_GENERIC, "ann_base/set_algorithm_train");
  
  ann_base->type_algorithm_train = algorithm;
  
  fann_set_training_algorithm((struct fann*) ann_base->f_ann, 
			      ann_base->type_algorithm_train);
  
  return INF_NOT_ERR;
}

int set_func_activation_base(AnnBase *ann_base, int type_func){
  
  if(ann_base == NULL || !is_func_activation_valid_base(type_func))
    return *print_msg(ERR_GENERIC, "ann_base/set_func_activation");
  
  if(ann_base->f_ann == NULL)
    return *print_msg(ERR_GENERIC, "ann_base/set_func_activation");
  
  ann_base->type_func_activation = type_func;
  
  fann_set_activation_function_hidden((struct fann*) ann_base->f_ann,
				      ann_base->type_func_activation);
  
  fann_set_activation_function_output((struct fann*) ann_base->f_ann, 
				      ann_base->type_func_activation);
  
  return INF_NOT_ERR;
}

int set_func_stop_train_base(AnnBase *ann_base, int type_func){
  
  if(ann_base == NULL || !is_func_stop_train_valid_base(type_func))
    return *print_msg(ERR_GENERIC, "ann_base/set_func_stop_train");
  
  if(ann_base->f_ann == NULL)
    return *print_msg(ERR_GENERIC, "ann_base/set_func_stop_train");
  
  ann_base->type_func_stop_train = type_func;
  
  fann_set_train_stop_function((struct fann*) ann_base->f_ann, 
			       ann_base->type_func_stop_train);
  
  return INF_NOT_ERR;
}

int set_err_desired_base(AnnBase *ann_base, float err_desired){
  
  
  if(ann_base == NULL || err_desired < 0)
    return *print_msg(ERR_GENERIC, "ann_base/set_err_desired");
  
  ann_base->err_desired = err_desired;
  
  return INF_NOT_ERR;
}

int set_learn_rate_base(AnnBase *ann_base, float learn_rate){
 
  if(ann_base == NULL || learn_rate <= 0 || learn_rate > 1)
    return *print_msg(ERR_GENERIC, "ann_base/set_learn_rate");
  
  if(ann_base->f_ann == NULL)
    return *print_msg(ERR_GENERIC, "ann_base/set_learn_rate");
  
  ann_base->learning_rate = learn_rate;
  
  fann_set_learning_rate((struct fann*) ann_base->f_ann,
			 ann_base->learning_rate);
  
  return INF_NOT_ERR;
}

int get_num_outputs_base(AnnBase *ann_base, int *n_output){
  
  if(ann_base == NULL)
    return *print_msg(ERR_PTR_NULL, "ann_base/get_numb_outputs");
  
  if(ann_base->neurons_layers != NULL){
    *n_output = ann_base->neurons_layers[ann_base->n_layers-1];
  
    return INF_NOT_ERR;
  }
  
  return ERR_GENERIC;
}

int verify_validity_params_base(AnnBase *ann_base){
  
  if(ann_base == NULL)
    return *print_msg(ERR_PTR_NULL, "ann_base/verify_validity_params_base");
  
  int cod = INF_NOT_ERR;
  
  cod = (ann_base->n_layers < 2 || ann_base->n_epochs < 1) ? ERR_VAR_INV : cod;
  cod = !is_algortihm_train_valid_base(ann_base->type_algorithm_train) ? ERR_VAR_INV : cod; 
  cod = !is_func_activation_valid_base(ann_base->type_func_activation) ? ERR_VAR_INV : cod; 
  cod = !is_func_stop_train_valid_base(ann_base->type_func_stop_train) ? ERR_VAR_INV : cod;
  
  cod = (ann_base->learning_rate > 1 ||
	 ann_base->learning_rate < 0) ? ERR_VAR_INV : cod;

  cod = ann_base->err_desired < 0 ? ERR_VAR_INV : cod;
  
  int i;
  for(i = 0; i < ann_base->n_layers; i++)
    cod = ann_base->neurons_layers[i] < 1 ? ERR_VAR_INV : cod;
  
  
  return cod;
}

int is_algortihm_train_valid_base(int type_algorithm){
  
  int cod = TRUE;
  
  cod = type_algorithm != TRAIN_INCREMENTAL ? FALSE : cod;
  
  return cod;
}

int is_func_activation_valid_base(int type_func){
  
  int cod = TRUE;
  
  cod = type_func != SIGMOID_SYMETRIC ? FALSE : cod;
  
  return cod;
}

int is_func_stop_train_valid_base(int type_func){
  
  int cod = TRUE;
  
  cod = (type_func != STOP_FUNC_MSE &&
	type_func != STOP_FUNC_BIT_FAIL ) ? FALSE : cod;
  
  return cod;
}

int free_ann_base(AnnBase **ann_base){
  
  if(ann_base != NULL){
    
    if(*ann_base != NULL){
      
      if((*ann_base)->neurons_layers != NULL)
	free((*ann_base)->neurons_layers);
      
      if((*ann_base)->f_ann != NULL)
	fann_destroy((*ann_base)->f_ann);
      
      free((*ann_base));
      
      *ann_base = NULL;
    }
  }
  
  return INF_NOT_ERR;
}