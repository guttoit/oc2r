#include "img_processing.h"

ListGeneric* find_create_img_contours(Image *imgIn){
  
  if(imgIn == NULL){
    
    print_msg(ERR_PTR_NULL, "find_create_img_contours");
    
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) != FALSE){
    
    print_msg(ERR_OBJ_NULL_LIST, "find_create_img_contours");
    
    return NULL;
  }
  
  IplImage *ipl_imgIn = (IplImage*) get_process_img_data(imgIn);
  
  int nCanais = 0;
  getNCanaisImg(imgIn, &nCanais);
  
  if(nCanais == 3 ){
    
    cvCvtColor(ipl_imgIn, ipl_imgIn, CV_RGB2GRAY);
    
  }else if(nCanais != 1){
    print_msg(ERR_VAR_INV, "img_processing.c/find_create_img_contours");
    
    return NULL;
  }
  
  int err = INF_NOT_ERR;
  
  CvMemStorage* storage = cvCreateMemStorage(0);
  CvSeq* contours = NULL;
  
  cvFindContours(ipl_imgIn, storage, 
		 &contours, sizeof(CvContour),
		 CV_RETR_TREE, 
		 CV_CHAIN_APPROX_SIMPLE, 
		 cvPoint(0,0) );
  
  
  ListGeneric *lista = create_init_generic_list();
    
  if(lista == NULL){
    print_msg(ERR_GENERIC, "img_processing/find_create_img_contours");
    return NULL;
  }
  
  CvSeq *contoursAux = contours;
  
  while(contoursAux != NULL){
    
    Contour *c = create_contour(contoursAux);
        
    ObjList *objLista = criaObjLista();
    
    int (*ptr) (void**) = (int (*) (void**)) &free_contour;
    
    err = initObjLista(objLista, 
		      (void*)c, 
		      TYPE_OBJ_CONTOUR, 
		      ptr);
    
    
    if(err != INF_NOT_ERR)
      print_msg(err, "img_processing.c/find_create_img_contours");
    
    else{
      addObjParaLista(lista, objLista);
    
    }
    
    contoursAux = contoursAux->h_next;
  }
  
  //printf("Numero de contornos na lista da image %s e %d\n", imgIn->path, lista->numObjs);
  
  return lista;
}

Image* resizeImage(Image *imgIn, int newSizeWidth, int newSizeHeight){
  
  if(imgIn == NULL){
    print_msg(ERR_PTR_NULL, "resizeImage");
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) == TRUE){
    print_msg(ERR_OBJ_NULL_LIST, "resizeImage");
    return NULL;
  }
  
  CvSize newSize = cvSize(newSizeWidth, newSizeHeight);
  
  IplImage *imgInAux = (IplImage*) get_process_img_data(imgIn);
  
  IplImage *imgOut = cvCreateImage(newSize, imgInAux->depth, imgInAux->nChannels);
  
  cvResize(imgInAux, imgOut, CV_INTER_CUBIC);
  
  Image *imgModificada = criaImagem();
  
  int err = setDadosImgProcess(imgModificada, imgOut);
 
  if(err != INF_NOT_ERR){
    print_msg(ERR_GENERIC, "resizeImage");
    return NULL;
  }
  
  return imgModificada;
  
}

int resizeImageEAtualiza(Image *imgIn, int newSizeWidth, int newSizeHeight){
  
   if(imgIn == NULL)
    return *print_msg(ERR_PTR_NULL, "resizeImageEAtualiza");
    
  if(isDadosImagemNull(imgIn) != FALSE)
    return *print_msg(ERR_OBJ_NULL_LIST, "resizeImageEAtualiza");
  
  CvSize newSize = cvSize(newSizeWidth, newSizeHeight);
  
  IplImage *imgInAux = (IplImage*) get_process_img_data(imgIn);
  
  IplImage *imgOut = cvCreateImage(newSize, imgInAux->depth, imgInAux->nChannels);
  
  cvResize(imgInAux, imgOut, CV_INTER_CUBIC);
  
  int err = setDadosImgProcess(imgIn, imgOut);
  
  if(err != INF_NOT_ERR)
    return *print_msg(err, "resizeImageEAtualiza");
  
  return INF_NOT_ERR;
  
}

Image* erodeImage(Image *imgIn, int *kernel , int type_kernel){
  
  if(imgIn == NULL){
    print_msg(ERR_PTR_NULL, "erodeImage");
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) == TRUE){
    print_msg(ERR_OBJ_NULL_LIST, "erodeImage");
    return NULL;
  }
  
  IplImage *ipl_imgInAux = (IplImage*) get_process_img_data(imgIn);
  
  IplImage *ipl_imgOut = cvCreateImage(cvGetSize(ipl_imgInAux), 
				       ipl_imgInAux->depth,
				       ipl_imgInAux->nChannels);
  
  IplConvKernel *cvkernel = NULL;
  
  if(kernel == NULL)
    cvkernel = cvCreateStructuringElementEx(ROWS_KERNEL_PADRAO, ROWS_KERNEL_PADRAO,
					    0, 0,type_kernel, NULL); 
  
  else
    cvkernel = cvCreateStructuringElementEx(kernel[0], kernel[1],
					    0, 0, type_kernel, NULL); 
  
  cvErode(ipl_imgInAux, ipl_imgOut, cvkernel, 1);
  
  Image *imgErodida = criaImagemComDados(ipl_imgOut);
  
  
  return imgErodida;
}

Image* dilatImage(Image *imgIn, int *kernel , int type_kernel){
  
  if(imgIn == NULL){
    print_msg(ERR_PTR_NULL, "dilatImage");
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) == TRUE){
    print_msg(ERR_OBJ_NULL_LIST, "dilatImage");
    return NULL;
  }
  
  IplImage *ipl_imgInAux = (IplImage*) get_process_img_data(imgIn);
  
  IplImage *ipl_imgOut = cvCreateImage(cvGetSize(ipl_imgInAux), 
				       ipl_imgInAux->depth,
				       ipl_imgInAux->nChannels);
  
  IplConvKernel *cvkernel = NULL;
  
  if(kernel == NULL)
    cvkernel = cvCreateStructuringElementEx(ROWS_KERNEL_PADRAO, ROWS_KERNEL_PADRAO,
					    0, 0,type_kernel, NULL); 
  
  else
    cvkernel = cvCreateStructuringElementEx(kernel[0], kernel[1],
					    0, 0, type_kernel, NULL); 
    
  
  cvDilate(ipl_imgInAux, ipl_imgOut, cvkernel, 1);
  
  Image *imgDilate = criaImagemComDados(ipl_imgOut);
  
  
  return imgDilate;
}


Image* get_img_slice_of_corresponding_contour(Image *imgIn, Contour *contour){
  
  if(imgIn == NULL || contour == NULL){
    print_msg(ERR_PTR_NULL, "get_img_slice_of_corresponding_contour");
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) == TRUE || is_contour_data_null(contour)){
    print_msg(ERR_OBJ_NULL_LIST, "get_img_slice_of_corresponding_contour");
    return NULL;
  }
  
  int err = INF_NOT_ERR;
  int nCanais = 0;
  
  err = getNCanaisImg(imgIn, &nCanais);
  
  if(nCanais > 1 || err != INF_NOT_ERR){
    print_msg(ERR_VAR_INV, 
			  "Erro na funcao get_img_slice_of_corresponding_contour. \
			  : nChannels > 1");
    return NULL; 
  }
  
  IplImage *ipl_imgIn = (IplImage*) getDadosImgOnlyRead(imgIn);
  
  //CvSeq *cvContour = (CvSeq*) get_contour_data(contour);

  int *dim = get_img_dimensions(imgIn);
  
  if(dim == NULL){
    print_msg(ERR_PTR_NULL, "get_img_slice_of_corresponding_contour");
    return NULL;
  }
  
  int rows = dim[1]; //y da image
  int cols = dim[0];// x da image
  
  rows = rows <= 0 ? 1 : rows;
  cols = cols <= 0 ? 1 : cols;
  
  CvMat*  matOriginal = cvCreateMat(rows, cols, CV_8UC1);
  
  contour->width  = contour->width  <= 0 ? 1 : contour->width;
  contour->height = contour->height <= 0 ? 1 : contour->height;
  
  CvRect boundingBox = cvRect(contour->x_more_left, contour->y_more_up, 
			      contour->width, contour->height);
  
  matOriginal = cvGetSubRect(ipl_imgIn, matOriginal, boundingBox);
  
  CvSize sizeMat = cvSize(dim[0], dim[1]);
  
  IplImage *imgResultado = cvCreateImage(sizeMat, ipl_imgIn->depth,nCanais);
  
  imgResultado = cvGetImage(matOriginal, imgResultado);
  
  Image *imgSlice = criaImagemComDados(imgResultado);
      
  //show_dados_contour(img_line->img_to_process,obj_img_actual->contour->cv_contour);
      
  //show_dados_img(imgSlice->img_to_process,"image");
  
  //doCanny(imgSlice, 155, 255, 3);
  
  doThreshold(imgSlice, 150, 255, CV_THRESH_BINARY_INV);
  
  //show_dados_img(imgSlice->img_to_process,"image");
  
  //show_dados_img(imgSlice->img_to_process, "img do contour depois do canny");
  
  return imgSlice;
  
}
