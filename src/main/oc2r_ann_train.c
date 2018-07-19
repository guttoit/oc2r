#include <stdio.h>
#include <stdlib.h>
#include "../brain/ann.h"
#include "../util/util_io_string.h"

void print_help(){
  
  char usage[] = "\n\
\
Usage: ./trainingANN\n\
                    [n_layers]\n\
                    [\"n_inputs n_hidden_1 n_hidden_2 ... n_output\"]\n\
                    [path_data_train]\n\
                    [name_ann]\n\
                    [learn_rate]\n\
                    [err_desired]\n\
                    [n_epochs]\n\n";
  
  
  printf("%s", usage);
  
}

unsigned int* create_layer_config(int n_layers, char *layer_config){
  
  unsigned int *layers = NULL;
  
  if(layer_config == NULL){
    
    layers = (unsigned int*) malloc(3 * sizeof(unsigned int));
    
    if(layers != NULL){
    
      layers[0] = 2500;
      layers[1] = 100;
      layers[2] = 94;
      
    }
    
    return layers;
  
  }
  
  char *line = trim_line(layer_config);
  
  int n_cols = 0;
  get_n_cols_in_line(line, &n_cols);
  
  if(n_layers != n_cols){
    printf("ERROR. The length layer is different to the vector of layer\n");
    return NULL;
  }
  
  layers = (unsigned int*) malloc(sizeof(unsigned int) * n_cols);
  
  if(layers == NULL)
    return NULL;
  
  char *colun_n = NULL;
  
  int i;
  for(i = 0; i < n_cols; i++){
    
    colun_n = get_column(line, i);
    
    layers[i] = (unsigned int) atoi(colun_n);
    
  }
  
  return layers;

}

int main(int argc, char** argv){
  
  char *path_data_train = NULL;
  char *name_ann= NULL;
    
  float learn_rate = 0.3;
  float err_desired = 0.01;
  
  int n_epochs = 5000;
  
  if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL 
    || argv[4] == NULL || argv[5] == NULL || argv[6] == NULL 
    || argv[7] == NULL)
  {
    
    print_help();
    return 0;
  }
  
  unsigned int n_layers = (unsigned int)atoi(argv[1]);
  
  unsigned int *layers = create_layer_config(n_layers, argv[2]);
  
  printf("\n");
  int i;
  for(i = 0; i < n_layers; i++)
    printf("l%d = %d\n", i, layers[i]);
  
  path_data_train = argv[3];
    
  name_ann = argv[4];

  learn_rate = atof(argv[5]);
  
  err_desired = atof(argv[6]);
  
  n_epochs = atoi(argv[7]);
    
  AnnBase *ann_base = create_init_ann(n_layers, layers);
  
  int err_cod = config_train_ann(ann_base, TRAIN_INCREMENTAL, 
		    SIGMOID_SYMETRIC, SIGMOID, STOP_FUNC_MSE, 
		    n_epochs, 10, learn_rate, err_desired);
  
  if(err_cod != INF_NOT_ERR)
    return 0;
  
  train_save_ann(ann_base, path_data_train, name_ann);
  
  free_ann(&ann_base);
  
  return 0;
}
