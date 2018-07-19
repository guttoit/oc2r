#include "util_train.h"

FileConfig *criaEinicializaFileConfig(char *path){
  
  FileConfig *f_conf = (FileConfig*) malloc(sizeof(FileConfig));
  
  int err_cod = INF_NOT_ERR;
  
  err_cod = inicializaFileConf(f_conf, path);
  
  if(err_cod != INF_NOT_ERR){
    print_msg(err_cod, "util_train/criaFileConfig");
    
    if(f_conf != NULL)
      freeFileConfig(&f_conf);
    
    return NULL;
  }
  
  return f_conf;
}

int inicializaFileConf(FileConfig *f_conf, char *path){
  
  if(f_conf == NULL || path == NULL)
    return *print_msg(ERR_GENERIC, 
		      "util_train/inicializaFileConf");
  
  int numLines = 0;
  get_num_lines(path, &numLines);
  
  f_conf->num_images = numLines;
  
  f_conf->path_file = NULL;
  append_data(&(f_conf->path_file), path);
  
  f_conf->text_file = create_text_file(path);
  
  if(f_conf->text_file == NULL)
    return *print_msg(ERR_GENERIC, 
		      "util_train/inicializaFileConf");
    
  return INF_NOT_ERR;
}

char* get_path_image(FileConfig *f_conf, int index_img){
  
  if(f_conf == NULL){
    print_msg(ERR_PTR_NULL, "util_train/get_path_image");
    return NULL;
  }
  
  char *col = get_col_text_file(f_conf->text_file, 
				index_img, 
				_IND_PATH_IMG);
  
  if(col == NULL){
    print_msg(ERR_GENERIC, "util_train/get_path_image");
    return NULL;
  }
  
  return col;
}

char* get_val_des(FileConfig *f_conf, int num_imagem){
  
  if(f_conf == NULL){
    print_msg(ERR_PTR_NULL, "util_train/get_val_des");
    return NULL;
  }
  
  char *val = get_col_text_file(f_conf->text_file, 
				num_imagem, 
				_IND_VALUE_IMG);
  
  if(val == NULL){
    print_msg(ERR_GENERIC, "util_train/get_val_des");
    return NULL;
  }
  
  return val;
}

int get_num_imgs(FileConfig *f_conf, int *n_img){
  
  if(f_conf == NULL || n_img == NULL){
    return *print_msg(ERR_PTR_NULL, 
		      "util_train/get_num_imgs");
  }
  
  *n_img = f_conf->num_images;
  
  return INF_NOT_ERR;
  
}

int freeFileConfig(FileConfig **f_conf){
  
  int cod_err = INF_NOT_ERR;
  
  print_msg(cod_err, "free_file_config");
  
  if(f_conf != NULL){
    
    if(*f_conf != NULL){
      
      if((*f_conf)->path_file != NULL)
	free((*f_conf)->path_file);
      
      if((*f_conf)->text_file != NULL)
	freeTextFile(&((*f_conf)->text_file));
      
      free(*f_conf);
      
      *f_conf = NULL;
    }
  }
  
  return INF_NOT_ERR;
}