#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

#include "../data_structure/list_generic.h"
#include "image_line.h"
#include "contour.h"
#include "../util/util_cv.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

#define IMG_INVALID_STATISTICAL 0

typedef struct _image{
  
  int type_of_img_data;
  
  char *path;
  
  void *img_only_read;
  
  void *img_to_process; //Generic image
  
  ListGeneric *contours;
  
  ListGeneric *img_lines;
  
}Image;

/**
 * Cria uma estrutura image 
 * e carrega a image identificada pelo path_img.
 */
Image* create_init_img(char *path, int n_canais);

/**
 * Aloca espaco para a estrutura image. Bem como inicializa suas variaveis
 * com valores nulos.
 */

Image* criaImagem();

Image* criaImagemComDados(void *g_img);

/**
 * Get altura x largura
 */
int* get_img_dimensions(Image *img);

/**
 * Armazena o numero de canais da image no parametro
 * armazena_canais. Retorna um identificador de erro.
 */
int getNCanaisImg(Image *img, int *armazena_canais);

int set_img_contour_list(Image *img, ListGeneric *objs);

int set_img_lines_list(Image *img, ListGeneric *img_lines);

int setDadosImgProcess(Image *img, void *img_to_process);

int setDadosImagemOnlyRead(Image *img, void *img_only_read);

ListGeneric* get_img_lines_list(Image *img);
/**
 * Get ponteiro para image
 */
void* get_process_img_data(Image *img);

void* getDadosImgOnlyRead(Image *img);

ListGeneric* get_img_contours_list(Image *img);

int compare_img_contours_y_position(ObjList *obj_1,
				    ObjList *obj_2,
				    int *result);
/**
 * Retorna TRUE caso o ponteiro para para a estrutura
 * que armazena os dados da image for nulo. 
 */
int isDadosImagemNull(Image *img);

/**
 * Libera a estrutua image e seus componentes
 */

int liberaMemoriaImg(Image **img);

#endif