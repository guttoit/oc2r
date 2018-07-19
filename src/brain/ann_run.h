#ifndef ANN_RUN_H
#define ANN_RUN_H

#include <stdlib.h>
#include <stdio.h>
#include <fann.h>
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

float* ann_run(void *ann, float *input);

#endif