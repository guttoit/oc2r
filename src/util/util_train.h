#ifndef UTIL_TRAIN_H
#define UTIL_TRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util_io_string.h"
#include "util_ocr.h"
#include "../msg_handling/msg_handling.h"

#define _IND_PATH_IMG 0
#define _IND_VALUE_IMG 1

typedef struct _fileConfig{
  
  int num_images;      //Numero de paths de imagens
  char *path_file;     //Path para o file de configuracao
  
  TextFile *text_file;
  
}FileConfig;

FileConfig *criaEinicializaFileConfig(char *path);

int inicializaFileConf(FileConfig *f_conf, char *path);

char* get_path_image(FileConfig *f_conf, int index_img);

char* get_val_des(FileConfig *f_conf, int pos_image);

int get_num_imgs(FileConfig *f_conf, int *n_img);

int freeFileConfig(FileConfig **f_conf);
#endif