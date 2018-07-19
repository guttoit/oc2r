#include "ann.h"

AnnBase* create_ann(){
  
  return create_ann_base();
}

AnnBase *create_ann_from_path(char *path_ann){
  
  return create_ann_base_from_path(path_ann);
    
}

AnnBase *create_init_ann(unsigned int n_layers, 
			 unsigned int *layers){
				    
  return create_init_ann_base(n_layers, layers);
  
}

int config_train_ann(AnnBase *ann_base,  int algorithm_train,
		     int func_activation,int func_act_output_layer,
		     int func_stop_train, unsigned int n_epochs, 
		     unsigned int n_epochs_print_output,
		     float learn_rate,   float err_desired)
{
		       
  
  int err_cod =  config_train_ann_base(ann_base, 
				       algorithm_train, 
				       func_activation,
				       func_act_output_layer,
				       func_stop_train,
				       n_epochs,
				       n_epochs_print_output,
				       learn_rate,
				       err_desired);
  
  return err_cod;
  
}

int train_save_ann(AnnBase *ann_base, 
		   char *p_data_train, 
		   char *name_ann)
{
  
  return train_save_ann_train(ann_base, p_data_train, name_ann);

  
}


AnnTestResult* do_test_ann(char *p_ann, char *p_data_test){
  
  
  return NULL;
  
}

int set_fann_config(AnnBase *ann_base){
  
  return set_fann_config_base(ann_base);
  
}


int set_algorithm_train(AnnBase *ann_base, int algorithm){
  
  return set_algorithm_train_base(ann_base, algorithm);
  
}

int set_func_activation(AnnBase *ann_base, int type_func){
  
  return set_func_activation_base(ann_base, type_func);
}

int set_func_stop_train(AnnBase *ann_base, int type_func){
  
  return set_func_stop_train_base(ann_base, type_func);
}

int set_err_desired(AnnBase *ann_base, float err_desired){
  
  return set_err_desired_base(ann_base, err_desired);
}

int set_learn_rate(AnnBase *ann_base, float learn_rate){
 
  return set_learn_rate_base(ann_base, learn_rate);
}

int get_num_outputs(AnnBase *ann_base, int *n_output){
  
  return get_num_outputs_base(ann_base, n_output);
}

int verify_validity_params(AnnBase *ann_base){
  
  return verify_validity_params_base(ann_base);
}

int is_algortihm_train_valid(int type_algorithm){
  
  return is_algortihm_train_valid_base(type_algorithm);
}

int is_func_activation_valid(int type_func){
  
  return is_func_activation_valid_base(type_func);
}

int is_func_stop_train_valid(int type_func){
  
  return is_func_stop_train_valid_base(type_func);
}

int free_ann(AnnBase **ann_base){
  
  return free_ann_base(ann_base);
  
}