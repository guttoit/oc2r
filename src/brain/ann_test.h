#ifndef ANN_TEST_H
#define ANN_TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <fann.h>
#include "ann_run.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _ann_test_result{
  
  char *p_data_test;
  
  void *fann_data;
  
  int length_input;
  
  float **output_real;
  
}AnnTestResult;

AnnTestResult* create_init_ann_test(char *p_ann, char *p_data_test);



int free_ann_test_result(AnnTestResult **ann_test);

#endif