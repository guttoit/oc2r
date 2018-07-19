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
Usage: ./oc2r\n\
                [path_image.[jpg][png]] [path_ann]  [width_obj_img]\n\
		[width_inv_obj] [dist_bet_contours] [dist_char_word] \n\n", ax, ax);
  
}

void print_text(ListGeneric *list_lines){
  
  printf("\n********************* The text output **********************\n\n");
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
  
  printf("\n");
}

void print_lines_statistical(ListGeneric *lines, int n_lines_to_print){
  
  ObjList *obj_actual = get_initial_list_obj(lines);
  Line *line_actual = NULL;
  int i = 0;
  while(n_lines_to_print > 0 && obj_actual != NULL){
    
    line_actual = (Line*) get_obj_Info(obj_actual);
    
    printf("\nLine %d\n", i++);
    
    print_statistical_info(line_actual->img_line);
    
    obj_actual = obj_actual->proxObjeto;
    
    n_lines_to_print--;
  }
  
  
}

char* svm_recognize(ListGeneric *list_lines){

  
  int count_word = 0;
  char temp_count[50];
  
  ObjList *obj_actual = get_initial_list_obj(list_lines);

  while(obj_actual != NULL){
    
    Line *line = (Line*) get_obj_Info(obj_actual);
    
    ObjList *obj_word = line->line_words->objInicial;

    while(obj_word != NULL){

      count_word++;
      sprintf(temp_count, "%s%d", "temp/word", count_word);
      
      WordSeed *word_seed = (WordSeed*) obj_word->objetoInformacao;
      ObjList *obj_charSeed = get_initial_list_obj(word_seed->charsSeed);
      
      char *word_actual = NULL;
      FILE *f_word_act= fopen(temp_count, "w");
  
      while(obj_charSeed != NULL){
    
	CharSeed *char_seed= (CharSeed*) get_obj_Info(obj_charSeed);
	
	int resolution[2] = {20,20};
	
	Matrix *mat_atual = getMatObjDaImg(char_seed->obj_img, TIPO_MATRIZ_BIN, resolution);
	
	char *char_actual = geraDadosMatTreinoFann(mat_atual, "0000000000000001");
	
	append_data_with_new_line(&word_actual, char_actual);
	
	obj_charSeed = obj_charSeed->proxObjeto;
      }
      
      fprintf(f_word_act, "%s", word_actual);
      
      fclose(f_word_act);
      
      obj_word = obj_word->proxObjeto;
      
    }
    
    
    obj_actual = obj_actual->proxObjeto;
    
  }

  
  return NULL;
  
}

int main(int argc, char** argv){
  
  char *path_ann= NULL;
  char *path_image = NULL;
  int *resolution = (int*)malloc(sizeof(int) *2);
  resolution[0] = 20;
  resolution[1] = 20;
  
  if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
  {
    print_help();
    return 0;
  }
  
  path_image = append_data(&path_image, argv[1]);
  path_ann= append_data(&path_ann, argv[2]);
    
  
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
  
  printf("Criei tudo\n");
  svm_recognize(list_lines);
  //print_text(list_lines);
  
  //print_lines_statistical(list_lines, 2);
  
  free_ocr_config(&ocr_config);
  freeListaEDep(&list_lines);
  
  return 0;
  
}
