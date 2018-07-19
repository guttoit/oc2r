#include "ann_test.h"

AnnTestResult* create_init_ann_test(char *p_ann, char *p_data_test){
  
  if(p_data_test == NULL){
    print_msg(ERR_PTR_NULL, "ann_test/create_init_ann_test");
    return NULL;
  }
  
  AnnTestResult *ann_test = (AnnTest*) malloc(sizeof(AnnTest));
  
  if(ann_test == NULL){
    print_msg(ERR_MEMORY, "ann_test/create_init_ann_test");
    return NULL;
  }
  
  struct fann_train_data *f_data = fann_read_train_from_file(p_data_test);
  
  ann_test->fann_data = (void*) f_data;
  
  ann_test->length_input = fann_length_train_data(f_data);
  
  ann_test->output_real = (float**) malloc(ann_test->length_input * sizeof(float));
  
  int i;
  for(i = 0; i < ann_test->length_input; i++)
    ann_test->output_real[i] = NULL;
  
  struct fann *f_ann = fann_create_from_file(p_ann);
  

  for(i = 0; i < ann_test->length_input; i++)
    ann_test->output_real[i] = ann_run(f_ann, (float*)f_data->input[i]);
  
  
  fann_destroy(f_ann);
  
  return ann_test;
  
  
}

int free_ann_test_result(AnnTestResult **ann_test){
  
  if(ann_test != NULL){
    
    if(*ann_test != NULL){
      
      if((*ann_test)->fann_data != NULL)
	fann_destroy_train((struct fann_train_data*)(*ann_test)->fann_data);
      
      if((*ann_test)->p_data_test != NULL)
	free((*ann_test)->p_data_test);
	
      if((*ann_test)->output_real != NULL){
	
	int i;
	for(i = 0; i < ann_test->length_input; i++){
	  if(ann_test->output_real[i] != NULL)
	    free(ann_test->output_real[i]);
	}
      }
      
      free(*ann_test);
      
      *ann_test = NULL;
    }
  }
  
  return INF_NOT_ERR;

}