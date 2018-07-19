#include "image_object.h"

ImgObject* criaObjDaImg(Image *img, Contour *contour){
  
  if(contour == NULL){
    print_msg(ERR_OBJ_NULL_LIST,"objDaImagem/criaObjDaImg");
    return NULL;
  }
  
  ImgObject *objeto = (ImgObject*) malloc(sizeof(ImgObject));
  
  int err = INF_NOT_ERR;
  
  inicializaObjDaImg(objeto);
  
  err = setContorno(objeto, contour);
  
  if(err != INF_NOT_ERR){
    print_msg(err,"criaObjDaImg");
    freeObjDaImg(&objeto);
    
    return NULL;
  }
  
  Image *imgDoObj = get_img_slice_of_corresponding_contour(img, contour);
  
  if(imgDoObj == NULL){
    print_msg(ERR_OBJ_NULL_LIST,"objDaImagem/criaObjDaImg");
    return NULL;
  }
  
  objeto->imgDoObj = imgDoObj;
  
  err = calc_set_img_obj_contour_measure(objeto);
  
  if(err != INF_NOT_ERR){
    print_msg(err,"criaObjDaImg");
    freeObjDaImg(&objeto);
    
    return NULL;
  }
  
  return objeto;
  
}

ImgObject* criaObjDaImgSimples(){
  
  ImgObject *objeto = (ImgObject*) malloc(sizeof(ImgObject));
  
  int err = INF_NOT_ERR;
  
  err = inicializaObjDaImg(objeto);
  
  if(err != INF_NOT_ERR){
    print_msg(err,"criaObjDaImgSimples");
    freeObjDaImg(&objeto);
    
    return NULL;
  }
  
  return objeto;
}

int inicializaObjDaImg(ImgObject *obj){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,
			      "objDaImg.c/inicializaObjetoDaImagem");
        return ERR_PTR_NULL;
    }
    
    obj->x_mean_value = 0;
    obj->y_mean_value = 0;
    obj->x_more_left = 0;
    obj->x_more_right = 0;
    obj->y_more_down = 0;
    obj->y_more_up = 0;
    obj->contour = NULL;
    obj->imgDoObj = NULL;
    obj->matDadosObj = NULL;
    
    return INF_NOT_ERR;
}

int calc_set_img_obj_contour_measure(ImgObject *imageObject){
  
  if(imageObject == NULL){
    print_msg(ERR_PTR_NULL, "calc_set_img_obj_contour_measure.");
    return ERR_PTR_NULL;
  }
  
  Contour *contour = getContornoDoObjDaimg(imageObject);
  
  int err1, err2, err3, err4;
  
  err1 = get_contour_x_more_left(contour, &(imageObject->x_more_left));
  err2 = get_contour_x_more_right(contour, &(imageObject->x_more_right));
  err3 = get_contour_y_more_down(contour, &(imageObject->y_more_down));
  err4 = get_contour_y_more_up(contour, &(imageObject->y_more_up));
  
  if(err1 != INF_NOT_ERR || err2 != INF_NOT_ERR || err3 != INF_NOT_ERR || 
					     err4 != INF_NOT_ERR)
  {
    
    print_msg(ERR_GENERIC, "calc_set_img_obj_contour_measure.");
    return ERR_GENERIC;
  
    
  }
    
  imageObject->x_mean_value = (imageObject->x_more_left + imageObject->x_more_right) / 2;
  imageObject->y_mean_value = (imageObject->y_more_down + imageObject->y_more_up) / 2;
  
  return INF_NOT_ERR;
}


int setImgDoObj(ImgObject *obj, Image *imgDoObj){
  
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL,
				  "objDaImagem.c/setImgDoObj.");
    
  
  if(imgDoObj == NULL)
    print_msg(WAR_GENERIC,"objDaImagem.c/setImgDoObj.");
  
  obj->imgDoObj = imgDoObj;
  
  return INF_NOT_ERR;
  
}

Image* getImgDoObj(ImgObject *obj){
  
  if(obj == NULL){
    print_msg(ERR_PTR_NULL,
				  "objDaImagem.c/getImgDoObj.");
    return NULL;
  }
  
  return obj->imgDoObj;
}

int setAtributosDePosicaoDoObjetoDaImagem(ImgObject *obj, 
					  int x_more_left, int x_more_right, 
					  int y_more_down, int y_more_up){
  
  if(obj == NULL){  
    print_msg(ERR_PTR_NULL, "setAtributosDePosicaoDoObjetoDaImagem.");
    return ERR_PTR_NULL;
  }
  
  obj->x_more_left = x_more_left;
  obj->x_more_right = x_more_right;
  obj->y_more_up = y_more_up;
  obj->y_more_down = y_more_down;
  
  return INF_NOT_ERR;
  
}

int setContorno(ImgObject *obj, Contour *contour){
  
  if(obj == NULL)
    return *print_msg(ERR_PTR_NULL, "setContorno.");
  
  obj->contour = contour;
  
  return INF_NOT_ERR;
}

Matrix* getMatObjDaImg(ImgObject *objImg, int tipo_de_dados, int *resolution){
  
  if(objImg == NULL || resolution == NULL){
    print_msg(ERR_PTR_NULL, "objDaImg.c/getMatObjDaImg");
    return NULL;
  }
  
  Matrix *matObj = objImg->matDadosObj;
  
  if(matObj != NULL){
    
    if(matObj->linhas == resolution[0] && matObj->colunas == resolution[1])
      return matObj;
  
    else{
      return criaMatObjDaImg(objImg, tipo_de_dados, resolution);
    }
  
    
  }else
    return criaMatObjDaImg(objImg, tipo_de_dados, resolution);
  
  
}

Matrix *criaMatObjDaImg(ImgObject *objImg, int tipo_de_dados, int *resolution){
  
  if(objImg == NULL || resolution == NULL){
    print_msg(ERR_PTR_NULL, "objDaImg.c/criaDadosObjDaImg");
    return NULL;
  }
  
  if(isDadosImagemNull(objImg->imgDoObj) != FALSE){
    print_msg(ERR_PTR_NULL, "objDaImg.c/criaDadosObjDaImg");
    return NULL;
  }
  
  int err = INF_NOT_ERR;
  
  if (tipo_de_dados == TIPO_MATRIZ_BIN){
    
    int rows = resolution[0];
    int cols = resolution[1];
    
    Matrix *matrix = criaEstrutraMatriz();
    err = inicializaMatriz(&matrix, rows, cols);
    
    if(err != INF_NOT_ERR){
      print_msg(err, "objDaImg.c/criaMatObjDaImg");
      
      return NULL;
    }
    
    Image *img_obj = getImgDoObj(objImg);
    
    err = resizeImageEAtualiza(img_obj, 
				  rows, 
				  cols);
    
    IplImage *ipl_img_obj = (IplImage*) get_process_img_data(img_obj);
    
    if(ipl_img_obj == NULL){
      print_msg(ERR_PTR_NULL, 
				    "objDaImg.c/criaDadosObjDaImg");
      
      return NULL;
    }

    if(ipl_img_obj->depth != IPL_DEPTH_8U){
      print_msg(ERR_GENERIC, 
				    "objDaImg.c/criaDadosObjDaImg");
  
      return NULL;
    } 
    
    
    int i, j;
    
    for(i = 0; i < rows;  i++ ){
	
      uchar* ptr = (uchar*) (ipl_img_obj->imageData + (i * ipl_img_obj->widthStep));
      int *ptr_mat = matrix->matrix + i*cols;
      
      for( j = 0; j < cols; j++ ){
	*(ptr_mat + j) = (int) *(ptr + j);
      }
    }
    
    objImg->matDadosObj = matrix;
    
    
    return objImg->matDadosObj;
      
  }

  print_msg(ERR_GENERIC, "objDaImg.c/criaDadosObjDaImg");
  
  return NULL;
  
}

Contour* getContornoDoObjDaimg(ImgObject *obj){
   
  if(obj == NULL){
        print_msg(ERR_PTR_NULL,"getContornoDoObjDaimg");
        return NULL;
    }
    
    return obj->contour;    
}

int get_img_obj_x_more_left(ImgObject *obj, int *x){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,"get_img_obj_x_more_left");
        return ERR_PTR_NULL;
    }
    
    *x = obj->x_more_left;
    
    return INF_NOT_ERR; 
}

int get_img_obj_x_more_right(ImgObject *obj, int *x){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,"get_img_obj_x_more_right");
        return ERR_PTR_NULL;
    }
    
    *x = obj->x_more_right;
    
    return INF_NOT_ERR;
}

int get_img_obj_y_more_up(ImgObject *obj, int *y){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,"get_img_obj_y_more_up");
        return ERR_PTR_NULL;
    }
    
    *y = obj->y_more_up;
    
    return INF_NOT_ERR;
}

int get_img_obj_y_more_down(ImgObject *obj, int *y){
    
    if(obj == NULL){
        print_msg(ERR_PTR_NULL,"get_img_obj_y_more_down");
        return ERR_PTR_NULL;
    }
    
    *y = obj->y_more_down;
    
    return INF_NOT_ERR;
}

int get_relative_obj1_obj2_position(ImgObject *obj_1, 
				    ImgObject *obj_2,
				    int *result){
				  

  if(obj_1 == NULL || obj_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaImg.c/compare_position_char_seeds");
  
  
  int x1_ext_esq = obj_1->x_more_left; 
  int x2_ext_esq = obj_2->x_more_left; 
  
  int y1_menor = obj_1->y_more_up;
  int y2_menor = obj_2->y_more_up;
  
  
  if(is_objs_same_place(obj_1, obj_2, 0))
    *result = OBJ_1_IS_SAME_PLACE_OBJ_2;
  
  else{
    
    if(x1_ext_esq < x2_ext_esq)
      *result = y1_menor < y2_menor ? OBJ_1_IS_LEFT_UP_OBJ_2 : 
				      OBJ_1_IS_LEFT_DOWN_OBJ_2;
    
    
    else
      *result = y1_menor < y2_menor ? OBJ_1_IS_RIGHT_UP_OBJ_2 : 
				      OBJ_1_IS_RIGHT_DOWN_OBJ_2;
				      
  }
  
  return INF_NOT_ERR;
    
}

int compare_x_relative_position_img_objs(ImgObject *obj_1, 
					 ImgObject *obj_2,
					 int *result){
  
  int cod_err = INF_NOT_ERR;
  int res = 0;
  
  cod_err = get_relative_obj1_obj2_position(obj_1, obj_2, &res);
  
  if(cod_err != INF_NOT_ERR)
    return *print_msg(cod_err, 
		      "image_object/compare_x_relative_position_img_objs");
  
  
  if(res == OBJ_1_IS_LEFT_UP_OBJ_2 || res == OBJ_1_IS_LEFT_DOWN_OBJ_2 )
    *result = OBJ_2_IS_MAJOR;
  
  else if(res == OBJ_1_IS_RIGHT_UP_OBJ_2 || res == OBJ_1_IS_RIGHT_DOWN_OBJ_2 )
    *result = OBJ_1_IS_MAJOR;
  
  else
    *result = OBJ_1_AND_2_ARE_EQUAL;
  
  return INF_NOT_ERR;
  
}

int is_objs_same_place(ImgObject *obj_1, ImgObject *obj_2, int lim_dist){
    
    
  if(obj_1 == NULL || obj_2 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaImg.c/is_objs_same_place");
  
  int x1_ext_esq = obj_1->x_more_left - lim_dist; int x1_ext_dir = obj_1->x_more_right + lim_dist;
  int x2_ext_esq = obj_2->x_more_left; int x2_ext_dir = obj_2->x_more_right;
  int y1_maior = obj_1->y_more_down + lim_dist; int y1_menor = obj_1->y_more_up - lim_dist;
  int y2_maior = obj_2->y_more_down; int y2_menor = obj_2->y_more_up;
  
  
  int p1_obj1[2] = {x1_ext_esq, y1_maior};
  int p2_obj1[2] = {x1_ext_esq, y1_menor};
  int p3_obj1[2] = {x1_ext_dir, y1_maior};
  int p4_obj1[2] = {x1_ext_dir, y1_menor};
  
  int p1_obj2[2] = {x2_ext_esq, y2_maior};
  int p2_obj2[2] = {x2_ext_esq, y2_menor};
  int p3_obj2[2] = {x2_ext_dir, y2_maior};
  int p4_obj2[2] = {x2_ext_dir, y2_menor};
  
  
  
  int is_obj1_dentro_obj2 = is_p2_entre_p1_e_p3(p1_obj1, p1_obj2, p4_obj2) == TRUE || 
			    is_p2_entre_p1_e_p3(p2_obj1, p1_obj2, p4_obj2) == TRUE ||
			    is_p2_entre_p1_e_p3(p3_obj1, p1_obj2, p4_obj2) == TRUE ||
			    is_p2_entre_p1_e_p3(p4_obj1, p1_obj2, p4_obj2) == TRUE;

  int is_obj2_dentro_obj1 = is_p2_entre_p1_e_p3(p1_obj2, p1_obj1, p4_obj1) == TRUE || 
			    is_p2_entre_p1_e_p3(p2_obj2, p1_obj1, p4_obj1) == TRUE ||
			    is_p2_entre_p1_e_p3(p3_obj2, p1_obj1, p4_obj1) == TRUE ||
			    is_p2_entre_p1_e_p3(p4_obj2, p1_obj1, p4_obj1) == TRUE;
			    
  
  //printf("Objeto 1 esta em xesq = %d , ycima = %d, xdir = %d, ybaixo = %d\n",
	  //   x1_ext_esq, y1_maior,
	  //   x1_ext_dir, y1_menor);
      
  //printf("Objeto 2 esta em xesq = %d , ycima = %d, xdir = %d, ybaixo = %d\n",
	//     x2_ext_esq, y2_maior,
	  //   x2_ext_dir, y2_menor);
  
  return is_obj1_dentro_obj2 || is_obj2_dentro_obj1;
   
}

int calc_dist_x_objs_img(ImgObject *obj_1, ImgObject *obj_2, int *result){
  
  int cod_err = INF_NOT_ERR;
  
  cod_err = compare_x_relative_position_img_objs(obj_1, obj_2, result);
  
  if(*result != OBJ_2_IS_MAJOR || cod_err != INF_NOT_ERR)
    return *print_big_msg(ERR_GENERIC, 
			  "image_line/calc_dist_x_objs_img", 
			  "compare_x_relative_position_img_objs");
  
  int x_right_1 = 0, x_left_2 = 0;
  
  get_img_obj_x_more_right(obj_1, &x_right_1);
  get_img_obj_x_more_left (obj_2, &x_left_2 );
  
  *result = x_left_2 - x_right_1;
  
  if(*result < 0)
    return *print_big_msg(ERR_GENERIC, 
			  "image_line/calc_dist_x_objs_img", 
			  "dist < 0");
  
  return INF_NOT_ERR;
  
}

int calcule_area_obj(ImgObject *obj){
    
    int x = obj->x_more_right - obj->x_more_left;
    int y = obj->y_more_down - obj->y_more_up ;
    
    //printf("Xd = %d, Xe = %d \n Yc = %d , Yb = %d\n", obj->x_more_right, obj->x_more_left
    //                                                , obj->y_more_down, obj->y_more_up);
    
    int area = x * y;
    
    return area;
}

void printInformacaoObjetoDaImagem(ImgObject *mObjeto){
    
    
    if(mObjeto == NULL){
      print_msg(ERR_PTR_NULL,"printInformacao em ImgObject");
  }
  else{
      
      printf("\n\n -------INFORMACOES SOBRE OBJETO DA IMAGEM-------\n");
      printf("\n -- x_more_left: %d", mObjeto->x_more_left);
      printf("\n -- x_more_right: %d", mObjeto->x_more_right);
      printf("\n -- y_more_down: %d", mObjeto->y_more_down);
      printf("\n -- y_more_up: %d", mObjeto->y_more_up);
      printf("\n -- x_mean_value: %d", mObjeto->x_mean_value);
      printf("\n -- y_mean_value: %d", mObjeto->y_mean_value);

  }
}

int freeObjDaImg(ImgObject **objImg){
  
  int err_1, err_2, err_3;
  
  if(objImg != NULL){
    
    if((*objImg) != NULL){
      
      if((*objImg)->matDadosObj != NULL)
	err_1 = liberaMemoriaMatrizEDependencias(&((*objImg)->matDadosObj));

      if((*objImg)->imgDoObj != NULL)
	err_2 = liberaMemoriaImg(&((*objImg)->imgDoObj));
      
      if((*objImg)->contour != NULL)
	err_3 = free_contour((&((*objImg)->contour)));
      
      free((*objImg));
      
      (*objImg) = NULL;
      
      if(err_1 != INF_NOT_ERR || err_2 != INF_NOT_ERR || err_3 != INF_NOT_ERR)
	  print_msg(WAR_GENERIC, "freeObjDaImg/objDaImg.c");
    }
  }
  
  return INF_NOT_ERR;

}