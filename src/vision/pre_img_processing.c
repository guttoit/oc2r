#include "pre_img_processing.h"

Image* convertScaleColorImage(Image *imgIn, int typeConversion){
  
  if(imgIn == NULL){
    print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/convertScaleColorImage");  
    
    return NULL;
  }
  
  if((isDadosImagemNull(imgIn)) == TRUE){
    print_msg(ERR_OBJ_NULL_LIST, 
			  "pre_img_processing.c/convertScaleColorImage");  
    
    return NULL;
  }
  
  IplImage *ipl_imgIn = (IplImage*) get_process_img_data(imgIn);
  
  CvSize size = cvGetSize(ipl_imgIn);
  
  IplImage *ipl_imgOut = cvCreateImage(size, ipl_imgIn->depth, ipl_imgIn->nChannels);
  
  switch(typeConversion){
    
    case RGB_TO_GRAY:
      cvCvtColor(ipl_imgIn, ipl_imgOut , typeConversion);
      break;
      
    default:
      break;
  }
  
  Image *imgModificada = criaImagem();
  
  setDadosImgProcess(imgModificada, ipl_imgOut);
  
  return imgModificada;
}

void* getHistogram(Image *imgIn, int flagAcumulaHistograma){
  
  if(imgIn == NULL){
    print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/getHistogram");  
    
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) == TRUE){
    print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/getHistogram");  
    
    return NULL;
  }
  
  CvHistogram *histograma = (CvHistogram*) malloc(sizeof(CvHistogram));
  
  IplImage **ipl_imgIn = (IplImage**) &(imgIn->img_to_process);
  
  cvCalcHist(ipl_imgIn, histograma, flagAcumulaHistograma, 0);
  
  return histograma;
}

Image* equalizeImageUsingHistogram(Image *imgIn){
  
  if(imgIn == NULL){
    print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/equalizeImageUsingHistogram");  
    
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) == TRUE){
    print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/equalizeImageUsingHistogram");  
    
    return NULL;
  }
  
  IplImage *ipl_imgIn = (IplImage*) get_process_img_data(imgIn);
  
  CvSize size = cvGetSize(ipl_imgIn);
  
  IplImage *ipl_imgOut = cvCreateImage(size, ipl_imgIn->depth, ipl_imgIn->nChannels);
  
  cvEqualizeHist(ipl_imgIn, ipl_imgOut);
  
  Image *imgOut = criaImagemComDados(ipl_imgOut);
  
  return imgOut;
}

int smoothImageUsingSmoothing(Image *imgIn, int smoothType, 
				    int widthMascara, int heigthMascara){
  
  if(imgIn == NULL)
    return *print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/smoothImageUsingSmoothing");  
    
  
  if(isDadosImagemNull(imgIn) != FALSE)
    return *print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/smoothImageUsingSmoothing");  
  
  IplImage *ipl_imgIn = (IplImage*) get_process_img_data(imgIn);
  
  IplImage *ipl_imgAux = cvCreateImage(cvGetSize(ipl_imgIn), 
				       ipl_imgIn->depth, 
				       ipl_imgIn->nChannels);
  
  cvSmooth(ipl_imgIn, ipl_imgAux, smoothType, widthMascara, heigthMascara, 0, 0);
  
  ipl_imgIn = NULL;
  
  setDadosImgProcess(imgIn, ipl_imgAux);
  
  return INF_NOT_ERR;
  
}

Image* doAdaptiveThreshold(Image* imgIn, double max_value, int adaptive_method,
			    int threshold_type, int block_size, double param1){
  
  if(imgIn == NULL){
    print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/doAdaptiveThreshold");  
    
    return NULL;
  }
  
  if(isDadosImagemNull(imgIn) == TRUE){
    print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/doAdaptiveThreshold");  
    
    return NULL;
  }
  
  IplImage *ipl_imgIn = (IplImage*) get_process_img_data(imgIn);
  
  CvSize size = cvGetSize(ipl_imgIn);
  
  IplImage *ipl_imgOut = cvCreateImage(size, ipl_imgIn->depth, ipl_imgIn->nChannels);
  
  cvAdaptiveThreshold(ipl_imgIn, ipl_imgOut, max_value, CV_ADAPTIVE_THRESH_MEAN_C, 
		      CV_THRESH_BINARY_INV, 3, 5);
  
  Image *imgOut = criaImagemComDados(ipl_imgOut);
  
  
  return imgOut;
}

int doThreshold(Image* imgIn, 
		    double treshould, 
		    double max_value, 
		    int threshold_type){
  
  if(imgIn == NULL)
    return *print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/doThreshold");  

  
  if(isDadosImagemNull(imgIn) != FALSE)
    return *print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/doThreshold");  
  
  IplImage *ipl_imgIn = (IplImage*) get_process_img_data(imgIn);
  
  CvSize size = cvGetSize(ipl_imgIn);
  
  IplImage *ipl_imgOut = cvCreateImage(size, ipl_imgIn->depth, ipl_imgIn->nChannels);  
  
  cvThreshold(ipl_imgIn, ipl_imgOut, treshould, max_value, 
		      threshold_type);
  
  setDadosImgProcess(imgIn, ipl_imgOut);
  
  cvReleaseImageHeader(&ipl_imgIn);
  
  return INF_NOT_ERR;
  
}

int doCanny(Image* imgIn,  double lowThresh, double highThresh, int aperture){
  
  if(imgIn == NULL)
    return *print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/doCanny");  
  
  if(isDadosImagemNull(imgIn) != FALSE)
    return *print_msg(ERR_PTR_NULL, 
			  "pre_img_processing.c/doCanny");  
  
  IplImage *ipl_imgIn = (IplImage*) get_process_img_data(imgIn);
  
  if(ipl_imgIn->nChannels != 1)
    return *print_msg(ERR_VAR_INV, 
			  "pre_img_processing.c/doCanny");  
    
  IplImage *ipl_img_out = NULL;
  
  ipl_img_out = cvCreateImage(cvGetSize(ipl_imgIn), 
				       ipl_imgIn->depth, 
				       ipl_imgIn->nChannels);
  
  //IplImage *img_clone = (IplImage*) clone_dados_img(imgIn->img_to_process);
  
  cvCanny(ipl_imgIn, ipl_img_out, lowThresh, highThresh, aperture);
  
  ipl_imgIn = NULL;
  
  setDadosImgProcess(imgIn, ipl_img_out);
  
  return INF_NOT_ERR;
  
}