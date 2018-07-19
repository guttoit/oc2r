#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include "../data_structure/list_generic.h"
#include "line.h"
#include "../util/util_io_string.h"

typedef struct _text{
    
  // Lines of the text organized from top to bottom.
  ListGeneric *text_lines;
  
  // All objs in the text. For now, only char_seed 
  //are considered
  ListGeneric *text_objs;
  
  char *text_out_out_context;
  char *text_out_in_context;
  
}Text;

Text* create_init_text();

Text* create_text();

int init_text(Text *text);

int add_text_line(Text* text, Line *line);

int sort_text_lines_up_to_down(Text *text);

int compare_position_lines_in_text(ObjList *obj_1, 
				   ObjList *obj_2,
				   int *result);

int set_text_lines(Text *text, 
		   ListGeneric *lines);

ListGeneric* get_text_lines(Text *text);

char* get_text_out_out_context(Text *text);

char* generate_text_out_context(Text *text);

char* get_text_out_in_context(Text *text);

char* generate_text_in_context(Text *text);

int free_text_and_objs(Text **text);

int free_text_only(Text **text);

#endif
