#ifndef ANN_TRAIN_H
#define ANN_TRAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <fann.h>
#include <fann_train.h>
#include "ann_base.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

int train_save_ann_train(AnnBase *ann_base, char *path_data, char *name_ann);

int save_ann_train(void *g_ann, char *name_ann);

int  set_epochs_between_reports_train(int n_epochs_reports);

#endif