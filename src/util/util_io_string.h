#ifndef UTIL_IO_STRING_H
#define UTIL_IO_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../msg_handling/msg_handling.h"

#define UTIL_STR_SIZE_BUFFER 40


typedef struct _line_text{
  
  int n_cols; //Numero de colunas de caracteres "colados"
  
  char **line;
  
}LineText;

typedef struct _text_file{
  
  char *path_file;
  int n_lines;      //Numero de linhas
  
  LineText **vect_lines;
  
}TextFile;

TextFile* create_text_file(char *path_file);

LineText *create_line_text(const char *line);

/**
 * Alloc memory to a string of length "len_srt" + 1.
 * 
 * where 1 is because to '\0'
 */
char* alloc_str(int len_str);

char* alloc_str_size_src(const char *src);

/**
 * Trim blank spaces on a string. The trim is make to remove blank spaces
 * in excess. For example: 
 * 
 * const char *line = "  This    is a example   ";
 * 
 * After the trim, the following string is returned:
 * 
 * char *line_trim = "This is a example";
 */
char* trim_line(const char *line);

/**
 * Get the numbers of words (coluns) in a line.
 * Where a word is defined how a sequence of characters 
 * with length greater than or equal to one.
 * eg.: This . is a word.
 */
int get_n_cols_in_line(const char *line, int *cols);

char *get_line_at(char *path_file, int index);

char* get_current_line(FILE *file);

int get_num_lines(char *path_file, int *n_lines);

char* get_column(const char *line, int num_col);

int get_dist_col_to_begin_line(const char *line, 
			       int ind_col, 
			       int *dist);

char* get_col_text_file(TextFile *text_file, 
			int ind_line, 
			int ind_col);

LineText* get_line_text_file(TextFile *text_file, int ind_line);


char* get_col_line_text(LineText *line_text, int ind_col);

char* get_data_file(char *path_file);

char* append_data(char **dest, const char *source);

char* append_char_data(char **dest, const char source);

char* append_data_with_new_line(char **dest, const char *source);

int append_data_in_file(char *dados, char *path_file);

int delete_file(const char *path_file);

int n_char_occurrence(char *dados, char c, int *armazena);

int freeListStrings(char **strings, int nStrings);

int freeLineText(LineText **lineText);

int freeTextFile(TextFile **text_file);

#endif