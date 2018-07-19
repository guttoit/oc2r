#ifndef CHARACTER_SEED_H
#define CHARACTER_SEED_H

#include <stdio.h>
#include <stdlib.h>
#include "../vision/image_object.h"
#include "character.h"
#include "../util/util_ocr.h"
#include "../util/util_fann.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"


typedef struct _character_seed{
    
    ImgObject *obj_img;
    void *ptr_word_of_char;
    
    int size_ann_out;
    float *ann_output;
    float *context_probability;
    
    char *char_vector;
    
    char best_char_out_context;
    char best_char_in_context;
    
}CharSeed;


CharSeed* create_init_char_seed(ImgObject *obj_img, 
				float *ann_out, 
				int size_ann_out);

int compare_x_relative_position_char_seeds(CharSeed *char_s_1, 
					   CharSeed *char_s_2,
					   int *result);

int compare_y_relative_position_char_seeds(CharSeed *char_s_1, 
					   CharSeed *char_s_2,
					   int *result);

ImgObject* get_obj_img_from_char_seed(CharSeed *charSeed);

Character* get_best_character_out_context(CharSeed *charSeed);

Character* get_best_character_in_context(CharSeed *charSeed);

int get_best_character_text_out_context(CharSeed *charSeed, 
					char *the_char);

int get_best_character_text_in_context(CharSeed *charSeed, 
				       char *the_char);

int get_index_best_value_ann_output(CharSeed *charSeed, int *index);

int get_char_seed_best_probability(CharSeed *charSeed, float *value);

int get_char_seed_x_more_left(CharSeed *char_seed, int *x);

int get_char_seed_x_more_right(CharSeed *char_seed, int *x);

int get_char_seed_y_more_up(CharSeed *char_seed, int *y);

int get_char_seed_y_more_down(CharSeed *char_seed, int *y);

int set_my_word(CharSeed *charSeed, void *my_word);

int free_char_seed(CharSeed **charSeed);

#endif
