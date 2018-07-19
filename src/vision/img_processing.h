#ifndef IMG_PROCESSING_H
#define IMG_PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include "pre_img_processing.h"
#include "image.h"
#include "contour.h"
#include "../data_structure/list_generic.h"
#include "../data_structure/object_list.h"
#include "../data_structure/matrix.h"
#include "../util/util_cv.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

/**
 * Retorna uma lista onde cada objeto corresponde a um contour
 * encontrado na image passada como parametro. O procedimento usa
 * a funcao cvFindContours da opencv para encontrar os contornos.
 */
ListGeneric* find_create_img_contours(Image *imgIn);

/**
 * Faz uma copia da image passada como parametro e a redimensiona
 * nao alterando a image original.A nova image e retornada. 
 */
Image* resizeImage(Image *imgIn, int newSizeWidth, int newSizeHeight);

int resizeImageEAtualiza(Image *imgIn, int newSizeWidth, int newSizeHeight);
/**
 * Cria uma copia da image do parametro, faz a erosao da nova image
 * utilizando o kernel passado e, então, retorna a image erodida.
 * Ex de kernel.: int k[2] = {3, 3}; int k[2] = {5, 5}
 * O type_kernel representa o formato do kernel, podendo ser em formato de cruz
 * retangular ou elipcal. 
 */
Image* erodeImage(Image *imgIn, int *kernel , int type_kernel);

/**
 * Cria uma copia da image do parametro, e faz a dilatacao de tal image
 * utilizando o kernel passado e, então, retorna a image dilatada.
 */
Image* dilatImage(Image *imgIn, int *kernel , int type_kernel);

/**
 * Retorna uma image correspondente a um pedaço da image passada
 * por parametro. Tal image e criada utilizando a posicao do contour
 * passado por parametro.
 */
Image* get_img_slice_of_corresponding_contour(Image *imgIn, Contour *contour);

#endif
