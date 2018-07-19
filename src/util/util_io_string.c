#include "util_io_string.h"

TextFile* create_text_file(char *path_file){
  
  int err_cod = INF_NOT_ERR;
  
  int n_lines = 0;
  err_cod = get_num_lines(path_file, &n_lines);
  
  if(err_cod != INF_NOT_ERR){
    print_msg(err_cod, "util_io_string/create_text_file");
    return NULL;
  }
  
  FILE *file = fopen(path_file, "r");
  
  if(file == NULL){
    print_msg(ERR_IO, "util_io_string/create_text_file");
    return NULL;
  }
  
  LineText **linesText = (LineText**) malloc(n_lines * sizeof(LineText));
  char *l_current = NULL;
  
  int i;
  for(i = 0; i < n_lines; i++){
    
    l_current = get_current_line(file);
    
    linesText[i] = create_line_text((const char*) l_current);
    
    if(linesText[i] == NULL){
      
      print_msg(ERR_GENERIC, "util_io_string/create_text_file");
      
      fclose(file);
      //Free memory to linesText
      while(i >= 0)
	freeLineText(&(linesText[i--]));

      return NULL;
    }
    
  }
  
  TextFile *text_file = (TextFile*) malloc(sizeof(TextFile));
  
  text_file->path_file = NULL;
  append_data(&(text_file->path_file), path_file);
  
  text_file->n_lines = n_lines;
  text_file->vect_lines = linesText;
  
  fclose(file);
  
  return text_file;
  
}

LineText *create_line_text(const char *line){
  
  
  int cod_err = INF_NOT_ERR;

  char *tr_line = trim_line(line);

  int n_cols = 0;
  
  cod_err = get_n_cols_in_line(tr_line, &n_cols);
  
  if(cod_err != INF_NOT_ERR){
    print_msg(cod_err, "util_io_string/create_line_text");
    return NULL;
  }
  
  char **mat_line = (char**) malloc(n_cols);
  
  char *colun = NULL;
  int size_colun = 0;
  int i;
  
  for(i = 0; i < n_cols; i++){
    
    colun = get_column(tr_line, i);
    
    if(colun != NULL){
      
      size_colun = strlen(colun);
      
      *(mat_line + i) = (char *) alloc_str(size_colun);
      
      strcpy(*(mat_line + i), colun);
    
    }else{
      print_msg(ERR_GENERIC, "util_io_string/create_line_text");
      return NULL;
    }
  }
  
  LineText *line_text = (LineText*) malloc(sizeof(LineText));
  
  if(line_text == NULL){
    print_msg(ERR_MEMORY, "util_io_string/create_line_text");
    return NULL;
  }
  
  line_text->line = mat_line;
  line_text->n_cols = n_cols;
  
  return line_text;
    
}

/**
 * Alloc memory to a string of length "len_srt" + 1.
 * 
 * where 1 is equivalent to '\0'
 */
char* alloc_str(int len_str){
  
  char *str = malloc(len_str + 1);
  
  return str;
}

char* alloc_str_size_src(const char *src){
  
  if(src == NULL){
    print_msg(ERR_PTR_NULL, "util_io_string/alloc_str");
    return NULL;
  }
  
  char *str = malloc(strlen(src) + 1);
  
  return str;
}

/**
 * Trim white spaces on a string. The trim is make to remove blank spaces
 * in excess. For example: 
 * 
 * const char *line = "  This    is a example   ";
 * 
 * After the trim, the following string is returned:
 * 
 * char *line_trim = "This is a example";
 */
char* trim_line(const char *line){
  
  if(line == NULL){
    print_msg(ERR_PTR_NULL, "util_io_string/trim_line");
    return NULL;
  }
  
  char const *str_actual = line;
  
  char *line_trim = alloc_str(strlen(line));
  char *init_line_trim = line_trim;
  
  //jump the white spaces initials
  while(*str_actual == ' ' && *str_actual != '\0')
    str_actual++;
  
  while(*str_actual != '\0'){
    
    if(*str_actual != ' '){
      
      *line_trim = *str_actual;
      line_trim++; str_actual++;
      
    }else{
      
      while(*str_actual == ' ' && *str_actual != '\0')
	str_actual++;
      
      if(*str_actual != '\0'){
	*line_trim = ' ';
	line_trim++;
      }
    }
  }
  
  if(*line_trim != '\0')
    *(line_trim + 1) = '\0';
  
  line_trim = init_line_trim;
  
  return line_trim;
}

int get_n_cols_in_line(const char *line, int *cols){
  
  char *str_actual = trim_line(line);
  
  if(str_actual == NULL)
    return *print_msg(ERR_PTR_NULL, "util_io_string/get_n_cols_in_line");
  
  int n_cols = 1;

  while (*str_actual != '\0'){
    
    if(*str_actual == ' ')
      n_cols++;
    
    str_actual++;
  }
  
  *cols = n_cols;
  
  return INF_NOT_ERR;
}

char *get_line_at(char *path_file, int index_line){
  
  if(path_file == NULL){
    print_msg(ERR_PTR_NULL, "util_io_string/get_line_at");
    return NULL;
  }
  
  FILE *file = fopen(path_file, "r");
  
  if(file == NULL){
    print_msg(ERR_IO, "util_io_string/get_line_at");
    return NULL;
  }
  
  int count = 0;
  
  char c = ' ';
  
  while(count < index_line && c != '\0' && !feof(file)){
    
    c = fgetc(file);
    
    if(c == '\n')
      count++;
      
  }
  
  if(count != index_line){
    print_msg(ERR_GENERIC, "util_io_string/get_line_at");
    return NULL;
  }
  
  char *line = get_current_line(file);
  
  fclose(file);
  
  return line;
}

char* get_current_line(FILE *file){
    
    int tamBuff = UTIL_STR_SIZE_BUFFER;
    
    char *buff = malloc(UTIL_STR_SIZE_BUFFER);
    char *line = NULL;
    
    if(buff == NULL){
      print_msg(ERR_MEMORY, "util_io_string/get_current_line");
      return NULL;
    }
    
    char c = fgetc(file);
    
    if(c == EOF){

        //print_msg(WAR_END_FILE, "util_io_string.c/get_current_line");
        free(buff);
        
        return NULL;
    }
    
    int pos = 0;

    while(c != '\n' && c != EOF && c != '\0'){
        
       *(buff + pos) = c;
        
        c = fgetc(file);
        
        pos++;
        
        if(pos >= tamBuff){
            
            tamBuff += UTIL_STR_SIZE_BUFFER;
            
            line = realloc(buff, tamBuff);
            
            if(line == NULL){
                print_msg(ERR_MEMORY, "io.c/get_current_line");
                return NULL;
            }
            
            buff = line;    
        }
            
    }
    
    if(pos >= tamBuff){
        line = realloc(buff, tamBuff++);
    
        if(line == NULL){
            print_msg(ERR_MEMORY, "io.c/get_current_line");
            return NULL;
        }
        
        buff = line;
    }
    
    *(buff + pos) = '\0';
    
    
    return buff;
}

int get_num_lines(char *path_file, int *n_lines){
    
    FILE *file = fopen(path_file, "r");
    
    if(file == NULL)
        return *print_msg(ERR_IO, "io.c/get_num_lines");
       
    int num_lines = 1;
    char c = '\0';
    
    while(!feof(file)){
        
        c =  fgetc(file);
        num_lines = c == '\n' ? num_lines + 1 : num_lines;
        
    }
    
    *n_lines = num_lines;
    
    fclose(file);
    
    return INF_NOT_ERR;
}

char* get_column(const char *line, int num_col){
    
  
  int dist = 0;
  int cod_err = INF_NOT_ERR;
    
  cod_err = get_dist_col_to_begin_line(line,num_col, &dist);
  
  if(cod_err != INF_NOT_ERR){
    print_msg(cod_err, "util_io_string/get_column");
    return NULL;
  }
  
  const char *ini_col = line + dist;
  char *colun = alloc_str(strlen(line));
  
  int i = 0;
  while(*(ini_col + i) != ' ' && *(ini_col + i) != '\0'){
    
    *(colun + i) = *(ini_col + i);
    i++;
  }
  
  *(colun + i) = '\0';
  
  return colun;
  
}

int get_dist_col_to_begin_line(const char *line, 
			       int ind_col, 
			       int *dist){
  
  if(line == NULL || dist == NULL)
    return *print_msg(ERR_PTR_NULL, 
		      "util_io_string/get_dist_col_to_begin_line");

  if(ind_col < 0)
    return *print_msg(ERR_VAR_INV, 
		      "util_io_string/get_dist_col_to_begin_line");
  
    
  int i = 0;
  int col_actual = 0;
  
  while(col_actual < ind_col && *(line+i) != '\0'){
    
    if(*(line + i) == ' ')
      col_actual++;
    
    i++;
  }
  
  *dist = i;
  
  return INF_NOT_ERR;
}

char* get_col_text_file(TextFile *text_file, 
			int ind_line, 
			int ind_col){

  LineText *l_text = get_line_text_file(text_file, ind_line);
  
  if(l_text == NULL){
    print_msg(ERR_GENERIC, "util_io_string/get_col_text_file");
    return NULL;
  }
  
  char *col = get_col_line_text(l_text, ind_col);
  
  return col;
}

LineText* get_line_text_file(TextFile *text_file, int ind_line){
  
  if(text_file == NULL){
    print_msg(ERR_PTR_NULL, "util_io_string/get_line_text_file");
    return NULL;
  }
  
  if(text_file->vect_lines == NULL){
    print_msg(ERR_GENERIC, "util_io_string/get_line_text_file");
    return NULL;
  }
  
  return text_file->vect_lines[ind_line];
  
}


char* get_col_line_text(LineText *line_text, int ind_col){
  
  if(line_text == NULL){
    print_msg(ERR_PTR_NULL, "util_io_string/get_col_line_text");
    return NULL;
  }
  
  if(line_text->line == NULL){
    print_msg(ERR_GENERIC, "util_io_string/get_col_line_text");
    return NULL;
  }
  
  if(ind_col < 0 || line_text->n_cols < ind_col){
    print_msg(ERR_VAR_INV, "util_io_string/get_col_line_text");
    return NULL;
  }
  
  return line_text->line[ind_col];
}

char* get_data_file(char *path_file){
    
  FILE *file = NULL;
  char *line = NULL;
  char *data = NULL;
  
  if(path_file == NULL){
      print_msg(ERR_PTR_NULL, "get_data_file/util_io_string.c");
      return NULL;
  }
  
  file = fopen(path_file, "r");
  
  if(file == NULL){
      print_msg(ERR_IO, "get_data_file/util_io_string.c");
      return NULL;
  }
  
  line = get_current_line(file);

  while(line != NULL){
    
    append_data_with_new_line(&data, line);
    
    line = get_current_line(file);
  }
  
  fclose(file);
  
  return data;
}

char* append_data(char **dest, const char *source){
    
  if(source == NULL || dest == NULL){
      print_msg(ERR_PTR_NULL, "append_data/util_io_string.c");
      return NULL;
  }
  
  int len_dest = 0;
  int len_source = strlen(source);
  
  char *temp = NULL;
  
  if(*dest == NULL){
      *dest = alloc_str(len_source);
      
      sprintf(*dest,"%s", source);
  }
  
  else{
      
      len_dest = strlen(*dest);
  
      temp = realloc(*dest, len_source + len_dest + 1);
  
      if(temp == NULL){
	  print_msg(ERR_MEMORY, "append_data/util_io_string.c");
	  return NULL;
      }
      
      *dest = temp;
  
      strcat(*dest, source);
  }
  
  return *dest;
}

char* append_char_data(char **dest, const char source){
  
  if(dest == NULL){
    print_msg(ERR_PTR_NULL, "append_char_data/util_io_string.c");
    return NULL;
  }
  
  char *s_source = malloc(2);
  
  if(s_source == NULL){
    print_big_msg(ERR_MEMORY, 
		  "append_char_data/util_io_string.c",
		  "s_source");
    return NULL;
  }
  
  *s_source = source;
  *(s_source + 1) = '\0';
  
  append_data(dest, s_source);
  
  free(s_source);
  
  return *dest;
}

char* append_data_with_new_line(char **dest, const char *source){
    
  if(dest == NULL || source == NULL){
    print_msg(ERR_PTR_NULL, "util_io_string/append_data_with_new_line");
    return NULL;
  }
  
  if(*dest == NULL){
    append_data(dest, source);
    
  }else{
    
    append_data(dest, "\n");
    append_data(dest, source);
  }
  
  return *dest;
  
}

int delete_file(const char *path_file){
  
  if(path_file == NULL)
    return *print_msg(ERR_PTR_NULL, "delete_file/util_io_string.c");
  
  FILE *file = fopen(path_file, "r");
  
  if(file == NULL)
    return INF_NOT_ERR;
  

  fclose(file);
  
  int ptr_err = 0;
 
  ptr_err = remove(path_file);
    
    
  return ptr_err == 0 ? INF_NOT_ERR : ERR_IO;

}

int append_data_in_file(char *dados, char *path_file){
  
  FILE *file = fopen(path_file, "a");
  
  if(file == NULL)
    return *print_msg(ERR_IO, 
			      "append_data_in_file/util_io_string.c");
  
  int res = fprintf(file, "%s", dados);
  
  res = res < 0 ? ERR_IO : INF_NOT_ERR;
  
  fclose(file);
  
  return res;
}

int n_char_occurrence(char *dados, char c, int *armazena){
  
  if(dados == NULL || armazena == NULL)
    return *print_msg(ERR_PTR_NULL, 
			      "n_char_occurrence/util_io_string.c");
  
  int n_rep = 0;
  char *aux = dados;
  
  while(*aux != '\0'){
    
    if(*aux == c)
      n_rep++;
    
    aux++;
  }
  
  *armazena = n_rep;
  
  return INF_NOT_ERR;
}

int freeListStrings(char **strings, int nStrings){
  
  if(strings != NULL){
    
    if(*strings != NULL){
      
      char *prox_string = NULL;
      int i;
      for(i = 0; i < nStrings; i++){
	
	if(*(strings) != NULL){
	  
	  prox_string = *(strings + 1);
	  
	  free(*(strings));
	  
	  *(strings) = NULL;
	  
	  *strings = prox_string;
	   
	}else{
	  return *print_msg(ERR_GENERIC, "util_io_string/freeListStrings");
	}
      
	
      }
      
    }
    
  }
  
  return INF_NOT_ERR; 
}

int freeLineText(LineText **lineText){
  
  if(lineText != NULL){
    
    if(*lineText != NULL){
      
      if((*lineText)->line != NULL)
	freeListStrings((*lineText)->line, (*lineText)->n_cols);
      
      free(*lineText);
      
      *lineText = NULL;
    }
  }
 
 return INF_NOT_ERR;
}

int freeTextFile(TextFile **text_file){
  
  print_msg(INF_NOT_ERR, "On free_text_file");
  
  if(text_file != NULL){
    
    if(*text_file != NULL){
      
      if((*text_file)->path_file != NULL)
	free((*text_file)->path_file);
      
      if((*text_file)->vect_lines != NULL){
	
	int i;
	for(i = 0 ; i < (*text_file)->n_lines; i++)
	  freeLineText((&(*text_file)->vect_lines[i]));
	
      }
      
      free(*text_file);
      
      *text_file = NULL;
    }
  }
 
 return INF_NOT_ERR;
}