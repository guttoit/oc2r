#include "training_set.h"

TrainingSet* create_init_training_set(int *output_data_resolution, 
				      char *path_config_train){
  
  TrainingSet *training_set = create_training_set();
  
  int err = INF_NOT_ERR;
  
  err = init_training_set(training_set, path_config_train, output_data_resolution);
  
  if(err != INF_NOT_ERR){
    
    if(training_set != NULL)
      free_training_set(&training_set);
    
    print_msg(err, "training_set/create_init_training_set");
    return NULL;
  }
  
  return training_set;
  
}

TrainingSet* create_training_set(){
  
  TrainingSet *training_set = (TrainingSet*) malloc(sizeof(TrainingSet));
  
  if(training_set == NULL){
    print_msg(ERR_MEMORY, "training_set/create_training_set");
    return NULL;
  }
  
  return training_set;
  
}

int init_training_set(TrainingSet *training_set, char *path_config_train, int *output_data_resolution){
  
  if(training_set == NULL)
   return  *print_msg(ERR_MEMORY, "training_set/init_training_set");
  
  training_set->output_data_resolution = output_data_resolution;
  
  if(path_config_train != NULL)
    training_set->file_config_train = criaEinicializaFileConfig(path_config_train);
  
  if(path_config_train == NULL)
    training_set->file_config_train = NULL;
  
  
  training_set->training_imgs = create_init_generic_list();
  
  
  return INF_NOT_ERR;
  
}

int add_training_img(TrainingSet *training_set, TrainingImg *training_img){
  
  if(training_set == NULL || training_img == NULL)
    return *print_msg(ERR_PTR_NULL, "training_set/add_training_img");
  
  int err = INF_NOT_ERR;
  
  int (*ptr)(void**) = (int (*)(void**)) &free_training_img;
  
  err = addObjGenericoParaLista(training_set->training_imgs, 
				   (void*)training_img, 
				   OBJETO_TIPO_IMG_TREINO,
				   ptr);
  
  if(err != INF_NOT_ERR)
    return *print_msg(err, "training_set/add_training_img");
 
  return INF_NOT_ERR;
}

int set_file_config_training(TrainingSet *training_set, 
			    FileConfig *file_config_train){
  
  if(training_set == NULL)
    return *print_msg(ERR_PTR_NULL,"training_set/set_file_config_training");
  
  if(file_config_train == NULL)
    print_msg(WAR_GENERIC, "training_set/set_file_config_training");
  
  training_set->file_config_train = file_config_train;
  
  return INF_NOT_ERR;
}

int set_training_imgs(TrainingSet *training_set, ListGeneric *training_imgs){
  
  if(training_set == NULL)
    return *print_msg(ERR_PTR_NULL, "training_set/set_training_imgs");
  
  if(training_imgs == NULL)
    print_msg(WAR_GENERIC, "training_set/set_training_imgs");
  
  training_set->training_imgs = training_imgs;
  
  return INF_NOT_ERR;
}

int set_data_resolution(TrainingSet *training_set, int *output_data_resolution){
  
  if(training_set == NULL)
    return *print_msg(ERR_PTR_NULL, "training_set/set_data_resolution");
  
  if(output_data_resolution == NULL)
    print_msg(WAR_GENERIC, "training_set/set_data_resolution");
    
  training_set->output_data_resolution = output_data_resolution;
  
  return INF_NOT_ERR;
}

int get_n_training_imgs(TrainingSet *training_set, int *num){
  
  if(training_set == NULL || num == NULL)
    return *print_msg(ERR_PTR_NULL, 
				  "training_set/get_n_training_imgs");
  
  
  int err = getNumObjDaLista(training_set->training_imgs, num);
  
  return err;
}

int get_n_total_training_objs(TrainingSet *training_set, int *num){
  
  if(training_set == NULL || num == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "training_set/get_n_total_training_objs");
    
  ObjList *objListaImg = get_initial_list_obj(training_set->training_imgs);
  
  if(objListaImg == NULL)
    return *print_msg(ERR_GENERIC, 
		      "training_set/get_n_total_training_objs");
  
  TrainingImg *training_img = NULL;
  void *objInfo = NULL;
  int total = 0;
  int total_atual = 0;
  
  while(objListaImg != NULL){
    
    objInfo = get_obj_Info(objListaImg);
    
    if(objInfo != NULL){
      
      training_img = (TrainingImg*) objInfo;
      
      getNumObjDaLista(get_training_objs(training_img), 
		       &total_atual);
      
      total += total_atual;
      
    }else{
      return *print_msg(ERR_GENERIC, 
			"training_set/get_n_total_training_objs");
    }
    
    objListaImg = objListaImg->proxObjeto;
    
  }
  
  *num = total;
  
  return INF_NOT_ERR;
}

ListGeneric* get_training_imgs(TrainingSet *training_set){
  
  if(training_set == NULL){
    print_msg(ERR_PTR_NULL, 
	      "training_set/get_training_imgs");
  
    return NULL;
  }
  
  return training_set->training_imgs;

}


int free_training_set(TrainingSet **training_set){
  
  int err = INF_NOT_ERR;
  
  if(training_set != NULL){
    
    if((*training_set) != NULL){
      
      if((*training_set)->training_imgs != NULL){
	err = freeListaEDep(&((*training_set)->training_imgs));
	
	if(err != INF_NOT_ERR)
	  print_msg(err, "training_set/free_training_set");
	
	print_msg(INF_NOT_ERR, "freeListaEDep has success");
      }
    
      if((*training_set)->file_config_train != NULL){
	err = freeFileConfig(&((*training_set)->file_config_train));
	
	if(err != INF_NOT_ERR)
	  print_msg(err, "training_set/free_training_set");
	
	print_msg(INF_NOT_ERR, "freeFileConfig has success");
      }
      
      free((*training_set));
  
      (*training_set) = NULL;
    }
    
  }
  
  return INF_NOT_ERR;
  
}


