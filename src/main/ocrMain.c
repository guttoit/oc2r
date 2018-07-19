#include <stdio.h>
#include <stdlib.h>

#include "../ocr/ocr.h"
#include "../ocr/text.h"

void print_help(){
  
  char ax[] = "***********************";
  
  printf("\n* \t \t %s%s \n*\
\t\t \t         Welcome to OC2R \n*\n*\
\t      [OpenSource Contextual Optical Character Recognation] \n*\n* \
\t\t	     \n* \
\n\n\
Usage: ./ocrMain [path_image.[jpg][png]] [path_ann] [width_obj_img]\
		 [width_inv_obj] [dist_bet_contours] [dist_char_word] \n\n", ax, ax);
  
}

void show_lines(void *cv_image, ListGeneric *lines){
  
  int i = 0;
  
  ObjList *obj_list_line = get_initial_list_obj(lines);
  ObjList *obj_list_char = NULL;
  
  while(obj_list_line != NULL){
    
    Line *line = (Line*) get_obj_Info(obj_list_line);
      
    obj_list_char = get_initial_list_obj(line->line_chars_seed);
    
    printf("line %d\n", i++);

    while(obj_list_char != NULL){
      
      CharSeed *char_seed = (CharSeed *)obj_list_char->objetoInformacao;
      
      show_dados_contour(cv_image, 
			char_seed->obj_img->contour->cv_contour ); 
      
      obj_list_char = obj_list_char->proxObjeto;
      
    }
    
    obj_list_line = obj_list_line->proxObjeto;
  }
  
}

void show_word(void *cv_image, WordSeed *word_seed){
  

  ObjList *obj_list = get_initial_list_obj(word_seed->charsSeed);

  
  while(obj_list != NULL){
    
    CharSeed *char_seed= (CharSeed*) get_obj_Info(obj_list);
      
    show_dados_contour(cv_image, 
		      char_seed->obj_img->contour->cv_contour ); 
      

    obj_list = obj_list->proxObjeto;
  }
  
}

void print_text(ListGeneric *list_lines){
  
  char *word_line_text = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(list_lines);
  
  while(obj_actual != NULL){
    
    Line *line = (Line*) get_obj_Info(obj_actual);
    
    ObjList *obj_word = line->line_words->objInicial;
    
    while(obj_word != NULL){
      
      WordSeed *word_seed = (WordSeed*) obj_word->objetoInformacao;
      
      word_line_text = get_word_seed_text_out_context(word_seed);
      
      printf("%s ", word_line_text);
     
      
      obj_word = obj_word->proxObjeto;
      
    }
    
    printf("\n");
    
    
    obj_actual = obj_actual->proxObjeto;
    
  }
  
}


int main(int argc, char** argv){
  
  char *path_ann= NULL;
  char *path_image = NULL;
  int *resolution = (int*)malloc(sizeof(int) *2);
  resolution[0] = 50;
  resolution[1] = 50;
  
  if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
  {
    print_help();
    return 0;
  }
  
  path_image = argv[1];
  path_ann= argv[2];
    
  
  resolution[0] = atoi(argv[3]);
  resolution[1] = resolution[0];
  
  
  
  OCRConfig *ocr_config = create_init_ocr_config(resolution[0], FALSE, 
						 TRUE, TRUE, path_ann);
  
  int dist_contours = argv[5] != NULL ? atoi(argv[5]) : 
					STAND_MAX_DIST_BETWEEN_CONTOURS;
  
  int dist_char_word = argv[6] != NULL ? atoi(argv[6]) : 
					STAND_MAX_DIST_CHAR_WORD;
					
  int max_size_inv_obj = argv[4] != NULL ? atoi(argv[4]) : 
					  STAND_MAX_SIZE_INVALID_OBJ;
  
  set_ocr_config_params(ocr_config, dist_contours, 
			dist_char_word,max_size_inv_obj );
  
  ListGeneric *list_lines = init_ocr_recognition(ocr_config, path_image);
  
  
  print_text(list_lines);
  
  void *image = load_dados_image(path_image, 1);
  
  //show_lines(image, list_lines);
  
  char *un_text_line_act = NULL;
  char *text_line_act = NULL;
  
  char *word_line_text = NULL;
  
  ObjList *obj_actual = get_initial_list_obj(list_lines);
  
  int i = 0 ;
  int j = 0;
  float *prob = NULL;
  int n_word_chars = 0;
  
  while(obj_actual != NULL){
    
    Line *line = (Line*) get_obj_Info(obj_actual);
    
    ObjList *obj_word = line->line_words->objInicial;
    
    printf("Line %d ------------------\n", i);
    
    while(obj_word != NULL){
      
      WordSeed *word_seed = (WordSeed*) obj_word->objetoInformacao;
      
      show_word(image, word_seed);
      
      word_line_text = get_word_seed_text_out_context(word_seed);
      
      getNumObjDaLista(word_seed->charsSeed, &n_word_chars);
      
      prob = get_word_seed_chars_probability(word_seed);
      
      printf("%d - %s :", j, word_line_text);
      
      for(n_word_chars; n_word_chars > 0; n_word_chars--)
	printf(" %f", prob[n_word_chars - 1]);
      
      printf("\n");
      
      obj_word = obj_word->proxObjeto;
      
      j++;
    }
    
    
    //un_text_line_act = get_line_text_out_context_unedited(line);
    
    //text_line_act = get_line_text_out_context(line);
    
    //printf("Line %d = \n%s \n", i, un_text_line_act);
    
    obj_actual = obj_actual->proxObjeto;
    
    i++;
  }
  
  //free_ocr_config(&ocr_config);
  freeListaEDep(&list_lines);
  
  return 0;
  
}
