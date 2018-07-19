#include "image.h"

Image* create_init_img(char *path, int n_canais){
  
  Image *img = criaImagem();
  
  img->path = path;
  
  img->img_only_read = load_dados_image(path, n_canais);
  img->img_to_process= clone_dados_img(img->img_only_read);
  
  if(img->img_only_read == NULL || img->img_to_process == NULL){
    
    print_msg(ERR_GENERIC, "image/create_init_img");
    
    liberaMemoriaImg(&img);
    
    return NULL;
  }
  
  return img;
  
}

Image* criaImagem(){
  
  Image *img = (Image*) malloc(sizeof(Image));
  
  img->type_of_img_data = T_OPENCV_IPL_IMG;
  img->path = NULL;
  img->img_to_process = NULL;
  img->img_only_read = NULL;
  img->contours = NULL;
  img->img_lines = NULL;
  
  return img;
}

Image* criaImagemComDados(void *g_img){
  
  Image *img = criaImagem();
  
  img->type_of_img_data = T_OPENCV_IPL_IMG;
  img->path = NULL;
  img->img_only_read = clone_dados_img(g_img);
  
  if(img->img_only_read == NULL){
    print_msg(ERR_GENERIC, "image/criaImagemComDados");
    return NULL;
  }
  
  img->img_to_process = g_img;
  img->contours = NULL;
  
  return img;
}


int setDadosImgProcess(Image *img, void *img_to_process){
  
  if(img == NULL)
    return *print_msg(ERR_PTR_NULL, "image/setDadosImgProcess");
  
  if(img_to_process == NULL)
    print_msg(WAR_GENERIC, "image/setDadosImgProcess/param nulo");
  
  img->img_to_process = img_to_process;
  
  return INF_NOT_ERR;
}

int setDadosImagemOnlyRead(Image *img, void *img_only_read){
  
  if(img == NULL)
    return *print_msg(ERR_PTR_NULL, 
				  "image/setDadosImagemOnlyRead");
  
  if(img_only_read == NULL)
    print_msg(WAR_GENERIC, 
			  "image/setDadosImagemOnlyRead/param nulo");
  
  img->img_only_read = img_only_read;
  
  return INF_NOT_ERR;
}

void* get_process_img_data(Image *img){
  
  if(img == NULL){
    print_msg(ERR_PTR_NULL, "image/get_process_img_data");
  
    return NULL;
  }
  
  return img->img_to_process;
  
}

void* getDadosImgOnlyRead(Image *img){
  
  if(img == NULL){
    print_msg(ERR_PTR_NULL, "image/get_process_img_data");
  
    return NULL;
  }
  
  return img->img_only_read;
  
}

int isDadosImagemNull(Image *img){
  
  if(img == NULL)
    return *print_msg(ERR_PTR_NULL, "image.c/isDadosImagemNull");
  
  int l = 0;
  
  l = (img->img_to_process == NULL || img->img_only_read == NULL) ? TRUE : FALSE;
  
  return l;
  
}

int set_img_contour_list(Image *img, ListGeneric *objs){
  
  if(img == NULL)
    return *print_msg(ERR_PTR_NULL, "image.c/set_img_contour_list");
  
  if(objs == NULL)
    print_msg(WAR_GENERIC, "image.c/set_img_contour_list");
  
  img->contours = objs;
  
  return INF_NOT_ERR;
}

int set_img_lines_list(Image *img, ListGeneric *img_lines){
  
  if(img == NULL)
    return *print_msg(ERR_PTR_NULL, "image.c/set_img_lines_list");
  
  if(img_lines == NULL)
    print_big_msg(WAR_GENERIC, 
		  "image.c/set_img_lines_list", "set img_lines NULL ");
  
  img->img_lines = img_lines;
  
  return INF_NOT_ERR;
}


ListGeneric* get_img_contours_list(Image *img){
  
  if(img == NULL){
    print_msg(ERR_PTR_NULL, "image/get_img_contours_list");
    return NULL;
  }
  
  return img->contours;
}

ListGeneric* get_img_lines_list(Image *img){
  
  if(img == NULL){
    print_msg(ERR_PTR_NULL, "image.c/get_img_lines_list");
  
    return NULL;
  }
  
  return img->img_lines;
  
}

int* get_img_dimensions(Image *img){
  
  if(img == NULL){
    print_msg(ERR_PTR_NULL, "image/get_img_dimensions");
  
    return NULL;
  }
  
  if(img->img_to_process == NULL){
    print_msg(ERR_PTR_NULL, "image/get_img_dimensions");
  
    return NULL;
  }
  
  IplImage *ipl_img = (IplImage*) img->img_to_process;
  
  int *dimensoes = (int*) malloc(sizeof(int) * 2);
  
  dimensoes[0] = ipl_img->width; //x = colunas
  dimensoes[1] = ipl_img->height; //y = linhas
  
  return dimensoes;
  
}

int getNCanaisImg(Image *img, int *armazena_canais){
  
  if(img == NULL)
    return *print_msg(ERR_PTR_NULL, "image/getNCanais");
  
  if(img->img_to_process == NULL)
    return *print_msg(ERR_PTR_NULL, "image/getNCanais");
  
  *armazena_canais = ((IplImage*)img->img_to_process)->nChannels;
  
  return INF_NOT_ERR;
}	

int compare_img_contours_y_position(ObjList *obj_1,
				    ObjList *obj_2,
				    int *result){
				      

  int cod_err_1 = INF_NOT_ERR, cod_err_2 = INF_NOT_ERR;
  
  int type_obj_1 = 0, type_obj_2 = 0;
  
  cod_err_1 = get_list_obj_type(obj_1, &type_obj_1);
  cod_err_2 = get_list_obj_type(obj_2, &type_obj_2);
  
  if(cod_err_1 != INF_NOT_ERR || cod_err_2 != INF_NOT_ERR)
    return *print_msg(ERR_GENERIC, 
		      "image/compare_img_contours_y_position");
  
  if(type_obj_1 != TYPE_OBJ_CONTOUR || type_obj_2 != TYPE_OBJ_CONTOUR)
    return *print_big_msg(ERR_GENERIC, 
			  "image/compare_img_contours_y_position", 
			  "type_obj != TYPE_OBJ_CONTOUR");
  
  void *obj_info_1 = get_obj_Info(obj_1);
  void *obj_info_2 = get_obj_Info(obj_2);
  
  if(obj_info_1 == NULL || obj_info_2 == NULL)
    return *print_big_msg(ERR_GENERIC, 
			  "image/compare_img_contours_y_position", 
			  "obj == NULL");
  
  Contour *contour_1 = (Contour*) obj_info_1;
  Contour *contour_2 = (Contour*) obj_info_2;
  
  cod_err_1 = compare_y_relative_position_contours(contour_1, 
						   contour_2, 
						   result);
  
  return cod_err_1;
}

int liberaMemoriaImg(Image **img){
  
  if(img != NULL){
    
    if((*img) != NULL){
      
      if((*img)->img_only_read != NULL)
	cvReleaseImage((IplImage**)&((*img)->img_only_read));
      
      if((*img)->img_to_process != NULL)
	cvReleaseImage((IplImage**)&((*img)->img_to_process));
      
      if((*img)->img_lines != NULL)
	freeListaEDep(&((*img)->img_lines));
      
      if((*img)->contours != NULL)
	freeListaEDep(&((*img)->contours));
      
      if((*img)->path != NULL)
	free((*img)->path);
      
      free((*img));
      
      (*img) = NULL;
      
    }
  }
 
  return INF_NOT_ERR;
}
