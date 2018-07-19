#include <stdio.h>
#include <stdlib.h>

#include "../ocr_training/train_create.h"
#include "../data_process/training_set.h"
#include "../brain/ann.h"


void print_help(){
  
  char ax[] = "***********************";
  
  printf("\n* \t \t %s%s \n*\
\t\t \t         Welcome to OC2R \n*\n*\
\t      [OpenSource Contextual Optical Character Recognation] \n*\n* \
\t	     Training Data Creation Module [TDCM] \n* \
\n\n\
Usage: ./treinoMain [path_config] [name_save_data] [width_obj_img]\n\n", ax, ax);
  
}

int main(int argc, char** argv){
  
  char *pathConf = "conf.txt";
  char *path_f_out = "dados.txt";
  
  int *resolution = (int*)malloc(sizeof(int) *2);
  resolution[0] = 50;
  resolution[1] = 50;
  
  if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
  {
    print_help();
    return 0;
  }
  
  pathConf = argv[1];
    
  path_f_out = argv[2];
  
  resolution[0] = atoi(argv[3]);
  resolution[1] = resolution[0];
  
  
  TrainingSet *training_set = create_and_save_dataset_from_imgs(pathConf,
							      path_f_out,
							      resolution );
  
  free_training_set(&training_set);
  
  return 0;
  
}
