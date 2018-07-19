#include "util_cv.h"

void* load_dados_image(char *pathImage, int canais_cor){
  
  if(pathImage == NULL){
    print_msg(ERR_PTR_NULL, 
				  "pre_img_processing.c/load_dados_image");
    return NULL;
  }
  
  if(canais_cor != GRAYSCALE && canais_cor != COLORSCALE){
    print_msg(ERR_COLOR_INV, 
				  "util_cv.c/load_dados_image");
    return NULL;
  }
  
  
  IplImage *ipl_img = cvLoadImage(pathImage, canais_cor);

  
  return ipl_img;
}

void* clone_dados_img(void *img_to_clone){
  
  if(img_to_clone == NULL){
    print_msg(ERR_PTR_NULL, 
				  "util_cv.c/clone_dados_img");
  
    return NULL;
  }
  
  IplImage *img_clone = cvCloneImage(((IplImage*)img_to_clone));
  
  return img_clone;
}

int get_nCanais_dados_img(void *img, int *canais){
  
  if(img == NULL)
    return *print_msg(ERR_PTR_NULL, 
				  "util_cv.c/get_nCanais");
  
  *canais = ((IplImage*)img)->nChannels;
  
  return INF_NOT_ERR;
}

void show_dados_img(void *img, char *name_window){
  
  if(img != NULL){
    
    if(name_window == NULL)
      name_window = "Image";
    
    
    //cvNamedWindow(name_window, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(name_window, 2);
    cvShowImage(name_window, (IplImage*)img);
    
    cvWaitKey(0);
    
  }else
    print_msg(ERR_PTR_NULL, 
				  "util_cv.c/show_dados_img");
 
}


void show_dados_contour(void *img, void *cv_contour){
  
  if(img == NULL || cv_contour == NULL)
    print_msg(ERR_PTR_NULL, 
				  "util_cv.c/show_dados_contour");
  else{
    CvScalar sc1 = cvScalarAll(155);
    CvScalar sc2 = cvScalarAll(255);
    
    IplImage* gray_img = (IplImage*)img;
    IplImage* color_img = NULL;//cvCloneImage(gray_img);
    
    color_img = cvCreateImage(cvGetSize(gray_img), IPL_DEPTH_8U, 1);
    
    //CvMat *color_mat_hdr = cvCreateMatHeader(gray_img->height,gray_img->width*3,IPL_DEPTH_8U );
    //IplImage color_img_hdr;
    //cvReshape(gray_img, color_mat_hdr, 3, 0);
    //color_img = cvGetImage(&color_mat_hdr, &color_img_hdr);
    
    cvDrawContours(color_img, ((CvSeq*)cv_contour) ,sc1, sc2, CV_FILLED, 2, 8 , cvPoint(0,0));
    
    cvNamedWindow("drawContour", 1);
    cvShowImage("drawContour", color_img);
    cvWaitKey(0);
    
    cvReleaseImage(&color_img);
    //show_dados_img(img->img_to_process, "drawContour");
  
  }

  
}

int save_img(char *pathName, void *image){
  
  if(image == NULL || pathName == NULL)
    return *print_msg(ERR_PTR_NULL, "util_cv.c/save_img");
  
  
  cvSaveImage(pathName, ((IplImage*)image), 0);
  
  return INF_NOT_ERR;
}

int is_p2_entre_p1_e_p3(int *p2, int *p1, int *p3){
  
  if(p1 == NULL || p2 == NULL || p3 == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaimg.c/is_p2_entre_p1_e_p3");
  
  if(&(p1[1]) == NULL || &(p2[1]) == NULL || &(p3[1]) == NULL)
    return *print_msg(ERR_PTR_NULL, "objDaimg.c/is_p2_entre_p1_e_p3");
  
  
  int dif_p1_p3[2] = {p1[0] - p3[0], p1[1] - p3[1]};
  int dif_p2_p1[2] = {p2[0] - p1[0], p2[1] - p1[1]};
  int dif_p2_p3[2] = {p2[0] - p3[0], p2[1] - p3[1]};
  
  
  if(dif_p1_p3[0] > 0 || dif_p1_p3[1] > 0){ //p1 mais a direita que p3 || p1 mais acima que p3
    
    if(dif_p1_p3[0] < 0){ //p3 mais a direita que p1 e mais abaixo que p1
      
	if(dif_p2_p3[0] <= 0 && dif_p2_p1[0] >= 0) //Verifica se p2[0] esta entre p1 e p3
	  if(dif_p2_p3[1] >= 0 && dif_p2_p1[1] <= 0) //Verifica se p2[1] esta entre p1 e p3
	    return TRUE;
    
      
    }else if(dif_p1_p3[1] < 0){ //p3 mais a esquerda que p1 e mais acima que p1
      
	if(dif_p2_p3[0] >= 0 && dif_p2_p1[0] <= 0) //Verifica se p2[0] esta entre p3 e p1
	  if(dif_p2_p3[1] <= 0 && dif_p2_p1[1] >= 0) //Verifica se p2[1] esta entre p1 e p3
	    return TRUE;
    
      
    }else{ //p1 mais a direita que p3 && p1 mais acima que p3
      
      if(dif_p2_p3[0] >= 0 && dif_p2_p1[0] <= 0) //Verifica se p2[0] esta entre p3 e p1
	  if(dif_p2_p3[1] >= 0 && dif_p2_p1[1] <= 0) //Verifica se p2[1] esta entre p1 e p3
	    return TRUE;
    }
  
    
  }else{ //p3 mais a direita que p1 && p3 mais acima que p1
    
     if(dif_p2_p3[0] <= 0 && dif_p2_p1[0] >= 0) //Verifica se p2[0] esta entre p3 e p1
	  if(dif_p2_p3[1] <= 0 && dif_p2_p1[1] >= 0) //Verifica se p2[1] esta entre p1 e p3
	    return TRUE;
    
  }
  
  return FALSE;
     
  
}

int is_y_2_near_y_1(int y_1, int y_2, int variance){

  //Remenber that how much up the y, minor is y's value.
  int is_y_2_more_up_or_equal = (y_1 - y_2) >= 0;
  int result = FALSE;
  int dif = 0;
  
  if(is_y_2_more_up_or_equal)
    dif = y_1 - y_2;
   
  else
    dif = y_2 - y_1;
  
  result = dif <= variance ? TRUE : FALSE;
  
  return result;
  
}

int is_x_2_near_x_1(int x_1, int x_2, int variance){

  
  int is_x_2_more_left_or_equal = (x_1 - x_2) >= 0;
  int result = FALSE;
  int dif = 0;
  
  if(is_x_2_more_left_or_equal)
    dif = x_1 - x_2;
  
  else
    dif = x_2 - x_1;
  
  result = dif <= variance ? TRUE : FALSE;
  
  return result;
  
}


/*static int cmp_func( const void* _a, const void* _b, void* userdata )
{
    CvPoint* a = (CvPoint*)_a;
    CvPoint* b = (CvPoint*)_b;
    int y_diff = a->y - b->y;
    int x_diff = a->x - b->x;
    return y_diff ? y_diff : x_diff;
}*/


int merge_second_contour_in_first(void *contour1, 
				  void *contour2, 
				  int insert_index){
  
  if(contour1 == NULL || contour2 == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "util_cv.c/merge_second_contour_in_first");
  
  
  CvSeq *seq_contour_1 = (CvSeq*) contour1;
  CvSeq *seq_contour_2 = (CvSeq*) contour2;

  
  CvSlice slice = cvSlice(0, CV_WHOLE_SEQ_END_INDEX);
  
  int is_to_copy_data_contour = TRUE;
  
  CvSeq *seq = cvSeqSlice(seq_contour_2, slice, 
			  NULL, is_to_copy_data_contour);
  
  
  if(insert_index == CONTOUR_INSERT_END)
    insert_index = seq_contour_1->total;
  
  cvSeqInsertSlice(seq_contour_1, insert_index, seq);
  
  seq_contour_1 = NULL;
  seq_contour_2 = NULL;
  
  
  return INF_NOT_ERR;
}
