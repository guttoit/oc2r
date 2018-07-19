#ifndef WORD_SEED_H
#define WORD_SEED_H

#include <stdlib.h>
#include <stdio.h>
#include "word.h"
#include "character_seed.h"
#include "../vision/image_object.h"
#include "../data_structure/list_generic.h"
#include "../data_structure/object_list.h"
#include "../util/util_io_string.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"


typedef struct _word_seed{
  
  ListGeneric *charsSeed;
  
  Word *word_most_probable_on_ann;
  Word *word_most_probable_on_context;
  
  int word_x_mean;
  int word_y_mean;
  
  int x_more_right;
  int x_more_left;
  
  int y_more_up;
  int y_more_down;
  
  //Maximum x-axis distance between a character and a word thats  
  //defines if this character can do or not part of the word. 
  int dist_char_word;
  
  char *word_text_out_context;
  char *word_text_in_context;
  
}WordSeed;

WordSeed* create_init_word_seed(int dist_char_word );

int add_char_seed_to_word(WordSeed *word_seed, 
			  CharSeed *char_seed);

int compare_x_relative_position_words_seed(WordSeed *word_1, 
					   WordSeed *word_2,
					   int *result);

int compare_y_relative_position_words_seed(WordSeed *word_1, 
					   WordSeed *word_2,
					   int *result);

int update_word_seed(WordSeed *word_seed);

int get_word_seed_x_more_left(WordSeed *word_seed, int *x);

int get_word_seed_x_more_right(WordSeed *word_seed,  int *x);

int get_word_seed_y_more_up(WordSeed *word_seed, int *y);

int get_word_seed_y_more_down(WordSeed *word_seed, int *y);

int get_word_seed_x_mean(WordSeed *word_seed, int *x_mean);

int get_word_seed_y_mean(WordSeed *word_seed, int *y_mean);

int is_word_seed_empty(WordSeed *word_seed, int *result);

float* get_word_seed_chars_probability(WordSeed *word_seed);

char* get_word_seed_text_out_context(WordSeed *word_seed);

char* get_word_seed_text_in_context(WordSeed *word_seed);

char* generate_word_seed_text(WordSeed *word, 
			      int is_to_use_context);

int free_word_seed_and_objs(WordSeed **word_seed);

int free_word_seed_only(WordSeed **word_seed);



#endif
