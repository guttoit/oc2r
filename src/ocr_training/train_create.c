#include "train_create.h"

TrainingSet* create_dataset_from_imgs(char *p_conf, int *data_resolution ){
  
  TrainingSet *training_set = create_init_training_set(data_resolution, p_conf);
  
  if(training_set == NULL){
    print_msg(ERR_GENERIC, 
				  "train_create.c/create_dataset_from_imgs");
    return NULL;
  }
  
  int err = INF_NOT_ERR;
  
  FileConfig *f_conf = training_set->file_config_train;
  
  int n_imgs = 0;
  
  err = get_num_imgs(f_conf,&n_imgs);
  
  if(err != INF_NOT_ERR){
    print_msg(err, "train_create.c/create_dataset_from_imgs");
    return NULL;
  }
  
  int idx_output_desired = 0;
  
  int i;
  for(i = 0; i < n_imgs; i++){
    
    char *path_img = get_path_image(f_conf, i);
    char *val = get_val_des(f_conf, i);
 
    err = get_index_output_desired(val, &idx_output_desired);
    
    if(err != INF_NOT_ERR){
      print_msg(err, "train_create.c/create_dataset_from_imgs");
      return NULL;
    }
     
    Image *img = create_init_img(path_img, GRAYSCALE);
    
    err = create_and_set_list_img_contours(img);
    
    if(err != INF_NOT_ERR){
      print_msg(err, "train_create.c/create_dataset_from_imgs");
      return NULL;
    }
    
    err = filter_redundant_contours(img, 3);

    err = filter_invalid_contours(img, 2);
    
    err = create_and_set_list_img_lines(img);
  
    printf("n contours before merge accents = %d\n", img->contours->numObjs);
    
    find_and_merge_accents(img);
    
    printf("n contours after merge accents = %d\n", img->contours->numObjs);
    
    if(err != INF_NOT_ERR){
      print_msg(err, "train_create.c/create_dataset_from_imgs");
      return NULL;
    }
    
    TrainingImg *training_img = create_init_training_img(img, idx_output_desired);
    
    err = training_img_processing(training_img);
    
    if(err != INF_NOT_ERR){
      print_msg(err, "train_create.c/create_dataset_from_imgs");
      return NULL;
    }
    
    err = add_training_img(training_set, training_img);
    
    if(err != INF_NOT_ERR){
      print_msg(err, "train_create.c/create_dataset_from_imgs");
      return NULL;
    }
    
    
  }
  
  
  return training_set;
}

int training_img_processing(TrainingImg *training_img){
  
  if(training_img == NULL)
    return *print_msg(ERR_PTR_NULL, 
				  "train_create.c/training_img_processing");
  
  Image *img = get_img_of_training_img(training_img);
  
  if(img == NULL)
    return *print_msg(ERR_OBJ_NULL_LIST, 
				  "train_create.c/training_img_processing");
  
  ListGeneric *objsImg = create_list_of_img_objs(img);
  
  if(objsImg == NULL)
    return *print_msg(ERR_OBJ_NULL_LIST, 
				  "train_create.c/training_img_processing");
  
  int err = INF_NOT_ERR;
  
  int index_output_desired = 0;
  err = get_index_training_img_output(training_img, &index_output_desired);
  
  if(err != INF_NOT_ERR){
    return *print_msg(err, 
				  "train_create.c/training_img_processing");
  }
  
  ObjList *objLista = get_initial_list_obj(objsImg);
  
  
  while(objLista != NULL){
      
    ImgObject *objImgAux = (ImgObject*) get_obj_Info(objLista);
    
    if(objImgAux == NULL)
      print_msg(WAR_GENERIC, 
				  "train_create.c/training_img_processing");
    else{
      TrainingObj *training_object = create_init_training_obj(objImgAux, 
							      index_output_desired);
      
      err = add_training_obj(training_img, training_object);
      
      if(err != INF_NOT_ERR)
	print_msg(err, 
				  "train_create.c/training_img_processing");
      
    }
    
    objLista = objLista->proxObjeto;
  }
  
  
  
  return INF_NOT_ERR;
}


TrainingSet* create_and_save_dataset_from_imgs(char *file_conf, 
					      char *file_out, 
					      int *data_resolution){
  
  TrainingSet *training_set = create_dataset_from_imgs(file_conf, data_resolution);
  
  int cod_err = INF_NOT_ERR;
  
  char *ann_file_input = NULL;
  char *human_view_file_out = NULL;
  
  append_data(&human_view_file_out, ANN_DATA_HUMAN_SAVE_PATH);
  append_data(&human_view_file_out, file_out);
  append_data(&human_view_file_out, ANN_DATA_HUMAN_SUFIX);
  
  append_data(&ann_file_input, ANN_DATA_TRAIN_SAVE_PATH);
  append_data(&ann_file_input, file_out);
  
  cod_err = delete_file((const char*)ann_file_input);
  cod_err = delete_file((const char*)human_view_file_out);
  
  if(cod_err != INF_NOT_ERR){
    print_msg(cod_err, "train_create/create_and_save_dataset_from_imgs");
    
    print_msg(WAR_GENERIC, "Nao foi possivel salvar dados do training_set de treinamento");
    
    return NULL;
  }
  
  save_training_set_data(training_set, human_view_file_out, data_resolution);
  save_training_set_ann_input_data(training_set, ann_file_input, data_resolution);
  
  return training_set;
  
}


int save_training_set_data(TrainingSet *training_set, char *path,int *resolution){
  
  if(training_set == NULL || path == NULL || resolution == NULL)
    return *print_msg(ERR_PTR_NULL, "util_train.c/save_training_set_data");
  
  if(resolution[0] <= 0 || resolution[1] <= 0)
    return *print_msg(ERR_PARAM_INV, "util_train.c/save_training_set_data");
  
  
  void *objInfoAtual = NULL;
  TrainingImg *imgTreinoAtual = NULL;
  
  ListGeneric *listaImgsTreino = get_training_imgs(training_set);
  
  ObjList *objListaAtual = get_initial_list_obj(listaImgsTreino);
  
  if(objListaAtual == NULL)
    printf("objListaAtual = NULL\n");
  
  printf("Saving set data train\n");
  
  int count = -1;
  
  while(objListaAtual != NULL){
    count++;
    
    if(objListaAtual->objetoInformacao == NULL)
      printf("%d objListaAtual->objetoInformacao == NULL\n",count);
    
    objInfoAtual = objListaAtual->objetoInformacao;
    
    if(objInfoAtual != NULL){
      
      imgTreinoAtual = (TrainingImg*) objInfoAtual;
      
      save_training_img_data(imgTreinoAtual, path, resolution);
      
    }else
      print_msg(WAR_GENERIC, "util_train.c/save_training_set_data");
    
    
    objListaAtual = objListaAtual->proxObjeto;
  }
  
  return INF_NOT_ERR;
  
}

int save_training_set_ann_input_data(TrainingSet *training_set, char *path_data, int *resolution){
  
  if(training_set == NULL || path_data == NULL || resolution == NULL){
    return *print_msg(ERR_PTR_NULL, "util_train.c/save_training_set_ann_input_data");
  }
  
  if(resolution[0] <= 0 || resolution[1] <= 0)
    return *print_msg(ERR_PARAM_INV, "util_train.c/save_training_set_ann_input_data");
  
  
  void *objInfoAtual = NULL;
  TrainingImg *imgTreinoAtual = NULL;
  
  ListGeneric *listaImgsTreino = get_training_imgs(training_set);
  
  ObjList *objListaAtual = get_initial_list_obj(listaImgsTreino);
  
  if(objListaAtual == NULL)
    printf("objListaAtual = NULL\n");
  
  int err_cod = INF_NOT_ERR;
  
  int total_objs_treino = 0;
  int size_out_ann = 0;
  int size_input = resolution[0] * resolution[1];
  
  err_cod = get_n_total_training_objs(training_set, &total_objs_treino);
  err_cod = get_size_vect_out(&size_out_ann);
  
  if(err_cod != INF_NOT_ERR)
    return *print_msg(err_cod, "util_train.c/save_training_set_ann_input_data");
  
  
  char *header_ann = create_fann_header(total_objs_treino, 
					size_input, 
					size_out_ann);
  
  if(header_ann == NULL)
    return *print_msg(ERR_GENERIC, "util_train.c/save_training_set_ann_input_data");
  
  append_data_in_file(header_ann , path_data);
  append_data_in_file("\n", path_data);
  
  printf("Saving ann input data train\n");
  
  int count = -1;
  
  while(objListaAtual != NULL){
    count++;
    
    if(objListaAtual->objetoInformacao == NULL)
      printf("%d objListaAtual->objetoInformacao == NULL\n",count);
    
    objInfoAtual = objListaAtual->objetoInformacao;
    
    if(objInfoAtual != NULL){
      
      imgTreinoAtual = (TrainingImg*) objInfoAtual;

      save_training_img_ann_input_data(imgTreinoAtual, path_data, resolution);
      
    }else
      print_msg(WAR_GENERIC, "util_train.c/save_training_set_ann_input_data");
    
    
    objListaAtual = objListaAtual->proxObjeto;
  }
  
  return INF_NOT_ERR;
  
}

char* get_training_img_data(TrainingImg *training_img, int *resolution){
  
  if(training_img == NULL || resolution == NULL){
    print_msg(ERR_PTR_NULL,"util_train.c/get_training_img_data");
    return NULL;
  }
  
  char *dadosObjTreino = NULL;
  char *dadosImgTreino = NULL;
  
  void *objInfo = NULL;
  TrainingObj *training_object = NULL;
  
  ListGeneric *training_objs = get_training_objs(training_img);
 
  ObjList *objInicial = get_initial_list_obj(training_objs);
   
  while(objInicial != NULL){
    
    if(objInicial->objetoInformacao == NULL)
      printf("objInicial->objetoInformacao == NULL \n");
    
    objInfo = get_obj_Info(objInicial);
  
    if(objInfo != NULL){
      
      training_object = (TrainingObj*) objInfo;
      
      dadosObjTreino = create_img_obj_mat_from_training_obj(training_object, resolution);
      
      if(dadosImgTreino == NULL)
	dadosImgTreino = append_data(&dadosImgTreino, dadosObjTreino);

      else
	dadosImgTreino = append_data_with_new_line(&dadosImgTreino, dadosObjTreino);
      
      if(dadosImgTreino == NULL)
	print_msg(WAR_GENERIC,"util_train.c/get_training_img_data");
      
      
    }else
      print_msg(WAR_GENERIC,"util_train.c/get_training_img_data");
    
    objInicial = objInicial->proxObjeto;
    
  }
  
  return dadosImgTreino;
  
}


int save_training_img_data(TrainingImg *training_img, char *path, int *resolution){
  
  if(training_img == NULL || path == NULL || resolution == NULL)
    return *print_msg(ERR_PTR_NULL,"train_create.c/save_training_img_data");
  
  if(resolution[0] <= 0 || resolution[1] <= 0)
    return *print_msg(ERR_PARAM_INV,"train_create.c/save_training_img_data");
  
  char *dadosObjTreino = NULL;
  
  void *objInfo = NULL;
  TrainingObj *training_object = NULL;
  
  ListGeneric *training_objs = get_training_objs(training_img);
 
  ObjList *objInicial = get_initial_list_obj(training_objs);
  
  while(objInicial != NULL){
    
    if(objInicial->objetoInformacao == NULL)
      printf("objInicial->objetoInformacao == NULL \n");
    
    objInfo = get_obj_Info(objInicial);
  
    if(objInfo != NULL){
      
      training_object = (TrainingObj*) objInfo;
      
      //dadosObjTreino = create_img_obj_mat_from_training_obj(training_object, 
	//						    resolution);
      
      dadosObjTreino = create_img_obj_mat_human_view_from_training_obj(training_object, 
								       resolution);
      
      if(dadosObjTreino != NULL){
	append_data_in_file(dadosObjTreino , path);
	append_data_in_file("\n", path);

	
	free(dadosObjTreino);

      }
      
      
    }else
      print_msg(WAR_GENERIC,"train_create.c/save_training_img_data");
    
    objInicial = objInicial->proxObjeto;
    
  }
  
  return INF_NOT_ERR;
  
}

int save_training_img_ann_input_data(TrainingImg *training_img, char *path_data_ann, int *resolution){
  
  if(training_img == NULL || path_data_ann == NULL || resolution == NULL) {
    return *print_msg(ERR_PTR_NULL, "train_create.c/criaSalvaDadosANN");
  }
  
  if(resolution[0] <= 0 || resolution[1] <= 0)
    return *print_msg(ERR_PARAM_INV,"train_create.c/criaSalvaDadosANN");
  
  char *dadosObjTreinoFANN = NULL;
  
  void *objInfo = NULL;
  TrainingObj *training_object = NULL;
  
  ListGeneric *training_objs = get_training_objs(training_img);
 
  ObjList *objInicial = get_initial_list_obj(training_objs);
  
  Matrix *mat_obj_treino = NULL;
  
  while(objInicial != NULL){
    
    if(objInicial->objetoInformacao == NULL)
      printf("objInicial->objetoInformacao == NULL \n");
    
    objInfo = get_obj_Info(objInicial);
  
    if(objInfo != NULL){
      
      training_object = (TrainingObj*) objInfo;
      
      mat_obj_treino = get_mat_img_obj_from_training_obj(training_object, resolution);
      
      dadosObjTreinoFANN = geraDadosMatTreinoFann(mat_obj_treino, 
						  get_output_desired(training_object));
      
      if(dadosObjTreinoFANN != NULL){
	
	append_data_in_file(dadosObjTreinoFANN , path_data_ann);
	append_data_in_file("\n", path_data_ann);
	
	free(dadosObjTreinoFANN);
      }
      
      
    }else
      print_msg(WAR_GENERIC,"train_create.c/criaSalvaDadosANN");
    
    objInicial = objInicial->proxObjeto;
    
  }
  
  return INF_NOT_ERR;
  
}