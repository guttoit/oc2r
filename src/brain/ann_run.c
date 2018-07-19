#include "ann_run.h"

float* ann_run(void *ann, float *input){
  
  if(ann == NULL || input == NULL){
    print_msg(ERR_PTR_NULL, "ann_run/ann_run");
    return NULL;
  }
  
  struct fann *f_ann = (struct fann *) ann;
  
  float *output = (float*) fann_run(f_ann, (fann_type*)input);
  
  return output;
  
}
