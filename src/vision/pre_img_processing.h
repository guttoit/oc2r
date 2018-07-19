#ifndef PRE_IMG_PROCESSING_H
#define PRE_IMG_PROCESSING_H

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core_c.h>
#include <stdio.h>
#include "image.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

/**
 * Converte a escala de cor de uma image.
 */ 
Image* convertScaleColorImage(Image *imgIn, int typeConversion);


/**
 * Retorna o histograma da image.
 */
void* getHistogram(Image *imgIn, int flagAcumulaHistograma);

/**
 * Equaliza uma image por meio da análise do seu histograma. 
 */
Image* equalizeImageUsingHistogram(Image *imgIn);

/**
 * Suaviza uma image por meio da técnica de Smoothing 
 */ 
int smoothImageUsingSmoothing(Image *imgIn, int smoothType, 
				    int widthMascara, int heigthMascara);

/**
 * Realiza uma operação de threshold na image.
 */
Image* doAdaptiveThreshold(Image *imgIn, double max_value, 
				   int adaptive_method, int threshold_type, 
				   int block_size, double param1);

int doThreshold(Image* imgIn, 
		double treshould, 
		double max_value, 
		int threshold_type);

/**
 * Realiza a operação canny, que faz um destaque dos contornos dos objetos de uma image.
 */
int doCanny(Image *imgIn,  double lowThresh, double highThresh, int aperture);

#endif
