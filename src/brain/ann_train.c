#include "ann_train.h"

int _EPOCHS_BETWEEN_REPORT = 10;

int train_save_ann_train(AnnBase *ann_base, char *path_data, char *name_ann){
    
  if(path_data == NULL || ann_base == NULL )
    return *print_msg(ERR_PTR_NULL, "ann_train/train_ann");
  
  
  struct fann_train_data *data = fann_read_train_from_file(path_data);
  
  if(data == NULL)
    return *print_msg(ERR_IO, "ann_train/train_ann");
  
  fann_scale_train_data(data, 0, 1);
  
  fann_shuffle_train_data(data);
  
  set_fann_config_base(ann_base);
  
  struct fann *ann = (struct fann *) ann_base->f_ann;
  
  printf("\ntrain_alg = %d\n\
	    act_func = %d\n\
	    act_func = %d\n", fann_get_training_algorithm(ann),
			      fann_get_activation_function(ann, 2, 2),
			      fann_get_activation_function(ann, 2, 2));
  
  
  fann_train_on_data(ann, data, ann_base->n_epochs, 
		     _EPOCHS_BETWEEN_REPORT, ann_base->err_desired);
  
  save_ann_train(ann, name_ann);
  
  return 0;
}

int save_ann_train(void *g_ann, char *name_ann){
  
  if(g_ann == NULL || name_ann == NULL)
    return *print_msg(ERR_PTR_NULL, "ann_train/save_ann");
  
  char *path = NULL;
  
  append_data(&path, ANN_SAVE_PATH);
  append_data(&path, name_ann);
  
  fann_save(g_ann, name_ann);
  
  return INF_NOT_ERR;
}

int  set_epochs_between_reports_train(int n_epochs_reports){
  
  if(n_epochs_reports < 1)
    n_epochs_reports = 1;
  
  _EPOCHS_BETWEEN_REPORT = n_epochs_reports;
  
  return INF_NOT_ERR;
}
