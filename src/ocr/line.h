#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>
#include "word_seed.h"
#include "character_seed.h"
#include "../data_structure/list_generic.h"
#include "../data_structure/object_list.h"
#include "../vision/image.h"
#include "../vision/image_line.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_io_string.h"
#include "../util/util_macros.h"


typedef struct _line{
  
  ImgLine *img_line;
 
  ListGeneric *line_objs_img;
  
  ListGeneric *line_chars_seed;
  
  ListGeneric *line_words;
  
  int max_dist_char_word;
  
  int min_dist_word_word;
  
  char *line_text_out_context;
  char *line_text_in_context;
    
}Line;

Line* create_init_line();

Line* create_line();

int init_line(Line *line);

int add_obj_img_to_line(Line *line, ImgObject *obj);

int add_char_seed_to_line(Line *line, CharSeed *obj);

int add_word_seed(Line *line, WordSeed *word_seed);

int updates_line_after_add_obj(Line *line, ObjList *obj);

int sort_left_to_rigth_list_line_chars_seed(Line *line);

int sort_left_to_rigth_list_line_words(Line *line);

int compare_position_objs_in_line(ObjList *obj_1,
				  ObjList *obj_2,
				  int *result);

int is_line_empty(Line *line, int *result);

int is_list_line_objs_empty(Line *line, int *result);

int is_list_line_words_seed_empty(Line *line, int *result);

int set_max_dist_char_word(Line *line, int max_dist);

int set_min_dist_word_word(Line *line, int min_dist);

int set_line_objs_img(Line *line, ListGeneric *list);

int set_line_chars_seed(Line *line, ListGeneric *list);

int set_line_words_seed(Line *line, ListGeneric *list);

int get_n_line_objs_img(Line *line, int *n_objs);

int get_n_line_chars_seed(Line *line, int *n_objs);

int get_n_line_words_seed(Line *line, int *n_objs);

ListGeneric* get_line_objs_img(Line *line);

ListGeneric* get_line_chars_seed(Line *line);

ListGeneric* get_line_words_seed(Line *line);

char* get_line_text_out_context(Line *line);

char* get_line_text_in_context(Line *line);

char* get_line_text_out_context_unedited(Line *line);

char* get_line_text_in_context_unedited(Line *line);

char* generate_line_text(Line *line, int is_to_use_context);

char* generate_line_text_unedited(Line *line, int is_to_use_context);

int free_line_and_objs(Line **line);

int free_only_line(Line **line);

#endif
