#include "training_img.h"


TrainingImg* create_init_training_img(Image *img, 
				      int index_output_desired){
  
  TrainingImg *training_img = create_training_img();
  
  int err = INF_NOT_ERR;
  
  err = init_training_img(training_img, img, index_output_desired);
  
  if(err != INF_NOT_ERR){
     print_msg(err, "training_img.c/create_init_training_img");
  
    if(training_img != NULL)
      free_training_img(&training_img);
    
    return NULL;
  }
  
  return training_img;
}

TrainingImg* create_training_img(){
  
  TrainingImg *training_img = (TrainingImg*) malloc(sizeof(TrainingImg));
  
  if(training_img == NULL)
    print_msg(ERR_MEMORY,
	      "training_img.c/create_training_img");
    
  training_img->img = NULL;
  training_img->training_objs = NULL;
  training_img->index_output_desired = -1;
    
  return training_img;
}

int init_training_img(TrainingImg *training_img, 
		      Image *img,
		      int index_output_desired){
  
  if(training_img == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "training_img.c/init_training_img");
  
  training_img->index_output_desired = index_output_desired;
  
  if(img == NULL)
    print_msg(WAR_GENERIC,
	      "training_img.c/init_training_img");
  
  training_img->img = img;
  
  training_img->training_objs = create_init_generic_list();
  
  
  return INF_NOT_ERR;
}


int set_training_img(TrainingImg *training_img, Image *img){
  
  if(training_img == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "training_img.c/set_training_img");
  
  if(img == NULL)
    print_msg(WAR_GENERIC,
	      "training_img.c/set_training_img");

  training_img->img = img;
  
  return INF_NOT_ERR;
}

int set_training_objs(TrainingImg *training_img, 
		      ListGeneric *training_objs){
    
  if(training_img == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "training_img.c/set_training_objs");
  
  if(training_objs == NULL)
    print_msg(WAR_GENERIC,
	      "training_img.c/set_training_objs");

  training_img->training_objs = training_objs;
  
  return INF_NOT_ERR;
  
}

int add_training_obj(TrainingImg *training_img, 
		     TrainingObj *obj){
  
  if(training_img == NULL || obj == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "training_img.c/addObjTreino");
  
  if(training_img->training_objs == NULL)
    return *print_msg(ERR_GENERIC,
		      "training_img.c/addObjTreino");
  
  int err = INF_NOT_ERR;
  
  int (*ptr) (void**) = (int (*)(void**)) &free_training_obj;
  
  err = addObjGenericoParaLista(training_img->training_objs,
				   (void*)obj,
				   OBJETO_TIPO_TREINO,
				   ptr);
  
  if(err != INF_NOT_ERR)
    return *print_msg(err,"training_img.c/addObjTreino");
  
  
  return INF_NOT_ERR;
  
}

int create_and_add_training_obj(TrainingImg *training_img, 
				ImgObject *objImg, 
				int index_output_desired){
  
  if(training_img == NULL || objImg == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "training_img.c/create_and_add_training_obj");
  
  TrainingObj *training_object = create_init_training_obj(objImg, 
						      index_output_desired);
  
  
  int err = add_training_obj(training_img, training_object);
  
  if(err != INF_NOT_ERR)
    return *print_msg(err,
		      "training_img.c/create_and_add_training_obj");
  
  return err;
}

Image* get_img_of_training_img(TrainingImg *training_img){
  
  if(training_img != NULL)
    return training_img->img;
  
  print_msg(ERR_PTR_NULL,
	    "training_img.c/get_img_of_training_img");
  
  return NULL;
}

ListGeneric* get_training_objs(TrainingImg *training_img){
  
  if(training_img == NULL){
    print_msg(ERR_PTR_NULL,
	      "training_img.c/get_training_objs");
  
    return NULL;
  }
  
  return training_img->training_objs;
  
}
int get_index_training_img_output(TrainingImg *training_img, int *index){
  
   if(training_img == NULL || index == NULL)
    return *print_msg(ERR_PTR_NULL,
		      "training_img.c/get_index_output_desired");
     
  *index = training_img->index_output_desired;
  
  return INF_NOT_ERR;
}

int free_training_img(TrainingImg **training_img){
  
  print_msg(INF_NOT_ERR, "Doing free_training_img");
  
  if(training_img != NULL){
    
    if((*training_img) != NULL){
      
      if((*training_img)->training_objs != NULL)
	freeListaEDep(&((*training_img)->training_objs));
      
      if((*training_img)->img != NULL)
	liberaMemoriaImg(&((*training_img)->img));
      
      free((*training_img));
    
      (*training_img) = NULL;
    }
    
  }
  
  
  return INF_NOT_ERR;
  
  
}
