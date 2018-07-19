#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <stdio.h>

#include "../util/util_cv.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"
#include "../util/util_io_string.h"
#include "../util/util_ocr.h"

int generate_text( char *img_background, char *chars_to_generate, int *list_resolution, int n_resolution )
{

  int i;

  while(*chars_to_generate != '\0'){
	  
    IplImage *img_act = cvLoadImage(img_background, GRAYSCALE );
    
    int pw_arial = 5;
    int ph_arial = 10;
    
    char  *text = NULL;
    
    append_char_data(&text, *chars_to_generate);
    
    for(i = 0; i < n_resolution; i++){
      
      CvFont arial_normal = cvFontQt("Arial", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_NORMAL, 0);
      CvFont arial_italic = cvFontQt("Arial", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_ITALIC, 0);
      
      CvFont djavu_sans_normal = cvFontQt("DejaVu Sans Mono", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_NORMAL, 0);
      CvFont djavu_sans_italic = cvFontQt("DejaVu Sans Mono", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_ITALIC, 0);
      
      CvFont djavu_serif_normal = cvFontQt("DejaVu Serif", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_NORMAL, 0);
      CvFont djavu_serif_italic = cvFontQt("DejaVu Serif", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_ITALIC, 0);
      
      CvFont free_mono_normal = cvFontQt("FreeMono", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_NORMAL, 0);
      CvFont free_mono_italic = cvFontQt("FreeMono", list_resolution[i], cvScalarAll(0), CV_FONT_NORMAL, CV_STYLE_ITALIC, 0);
      
      
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial), &arial_normal);
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial+40), &arial_italic);
      
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial+80), &djavu_sans_normal);
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial+160), &djavu_sans_italic);
      
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial+240), &djavu_serif_normal);
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial+320), &djavu_serif_italic);
      
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial+400), &free_mono_normal);
      cvAddText( img_act, text, cvPoint(pw_arial, ph_arial+480), &free_mono_italic);
      
      
      pw_arial += 40;
    }
    
    char *name = NULL;
    append_data(&name, "data/new_imgs_train/");
    append_char_data(&name, *chars_to_generate);
    append_data(&name, ".png");
    
    cvSaveImage(name, img_act, 0);
    
    cvReleaseImage(&img_act);
    free(name);
    
    chars_to_generate++;
  }
    

    return 0;
}

int main(){
  
  int n_res = 8;
  int res[8] = {24, 20, 18, 16, 14, 12, 10, 8};
  
  char *vector = getVetorReferencia();
  
  generate_text("data/img_background.png", vector, res, n_res);
  
  return 0;
}