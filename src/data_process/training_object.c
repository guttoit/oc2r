#include "training_object.h"

TrainingObj* create_training_obj(){
  
  TrainingObj *obj = (TrainingObj*) malloc(sizeof(TrainingObj));
  
  if(obj == NULL)
    print_msg(ERR_PTR_NULL,
				  "training_object/create_training_obj");
  
  return obj;
}

int init_training_obj(TrainingObj *obj, ImgObject *obj_img, int idx_output_desired){
  
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL,
				  "training_object/init_training_obj");
  
  obj->obj_img = obj_img;
    
  obj->idx_output_desired = idx_output_desired;
  
  char *vSaida = getVetorSaidaDesejada(idx_output_desired);
  
  obj->output_desired = vSaida;
  
  return INF_NOT_ERR;
    
}

TrainingObj* create_init_training_obj(ImgObject *obj_img, int idx_output_desired){
  
  TrainingObj *obj = create_training_obj();
  
  if(obj_img == NULL || obj == NULL){
    print_msg(ERR_PTR_NULL,
				  "training_object/create_init_training_obj");
    return NULL;
  }
  
  int err = init_training_obj(obj, obj_img, idx_output_desired);
  
  if(err != INF_NOT_ERR){
    
    if(obj != NULL)
      free_training_obj(&obj);
    
    return NULL;
  }
  
  return obj;
}

int set_img_obj_from_training_obj(TrainingObj *obj, ImgObject *obj_img){
  
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL,
				  "training_object/set_img_obj_from_training_obj");
    
  if(obj_img == NULL)
    print_msg(WAR_GENERIC, "training_object/set_img_obj_from_training_obj");
  
  obj->obj_img = obj_img;
  
  return INF_NOT_ERR;
}

int set_index_output_desired(TrainingObj *obj, int index){
  
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL,
				  "training_object/set_index_output_desired");
  
  obj->idx_output_desired = index;
  
  return INF_NOT_ERR;
}

int set_output_desired(TrainingObj *obj, char *output){
  
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL,
				  "training_object/set_index_output_desired");
    
  if(output == NULL)
    print_msg(WAR_GENERIC, "training_object/set_output_desired");
  
  obj->output_desired = output;
  
  return INF_NOT_ERR;
}

char* get_output_desired(TrainingObj *obj){
  
  if(obj == NULL){
    print_msg(ERR_PTR_NULL,
				  "training_object/get_output_desired");
  
    return NULL;
  }
  
  if(obj->output_desired == NULL){
    
    obj->output_desired = getVetorSaidaDesejada(obj->idx_output_desired);
    
    if(obj->output_desired == NULL){
      print_msg(ERR_GENERIC,
				  "training_object/get_output_desired");
  
      return NULL;
    }
    
  }
  
  return obj->output_desired;
}

ImgObject* get_img_obj_from_training_obj(TrainingObj *obj){
  
  if(obj == NULL){
    print_msg(ERR_PTR_NULL, "training_object/get_img_obj_from_training_obj"); 
    return NULL;
  }
  
  return obj->obj_img;
}

Matrix* get_mat_img_obj_from_training_obj(TrainingObj *obj, int *resolution){
  
  if(obj == NULL || resolution == NULL){
    print_msg(ERR_GENERIC, "training_object/get_mat_img_obj_from_training_obj"); 
    return NULL;
  }
  
  ImgObject *obj_img = get_img_obj_from_training_obj(obj);
  
  return getMatObjDaImg(obj_img, TIPO_MATRIZ_BIN, resolution);
}

char *create_img_obj_mat_from_training_obj(TrainingObj *obj, int *resolution){
  
  if(obj == NULL || resolution == NULL){
    print_msg(ERR_GENERIC, "training_object/create_img_obj_mat_from_training_obj"); 
    return NULL;
  }
  
  Matrix *matObj = get_mat_img_obj_from_training_obj(obj, resolution);
  
  if(matObj == NULL){
    print_msg(ERR_GENERIC, 
	      "training_object/create_img_obj_mat_from_training_obj"); 
    
    return NULL;
  }
  
  char *matString = to_string_matrix_transladed_to_origin(matObj);
  
  char *output_desired = get_output_desired(obj);
  
  append_data_with_new_line(&matString, output_desired);
  
  //free(matString);
  
  return matString;
}

char *create_img_obj_mat_human_view_from_training_obj(TrainingObj *obj, 
						      int *resolution){
  
  if(obj == NULL || resolution == NULL){
    print_msg(ERR_GENERIC, 
	      "training_object/create_img_obj_mat_human_view_from_training_obj");
    
    return NULL;
  }
  
  Matrix *matObj = get_mat_img_obj_from_training_obj(obj, resolution);
  
  if(matObj == NULL){
    print_msg(ERR_GENERIC, 
	      "training_object/create_img_obj_mat_human_view_from_training_obj"); 
    
    return NULL;
  }
  
  transladaEstruturaMatrizParaOrigem(matObj);
  
  char *matString = to_string_matrix_human_view(matObj);
  
  char *output_desired = get_output_desired(obj);
  
  append_data_with_new_line(&matString, output_desired);
  
  //free(matString);
  
  return matString;
}

int free_training_obj(TrainingObj **obj){
  
  if(obj != NULL){
    
    if((*obj) != NULL){
      
      if((*obj)->obj_img != NULL)
	freeObjDaImg(&((*obj)->obj_img));
   
      if((*obj)->output_desired != NULL)
	free((*obj)->output_desired);
   
      free((*obj));
      
      (*obj) = NULL;
    }
  }
  
  return INF_NOT_ERR;
  
}
