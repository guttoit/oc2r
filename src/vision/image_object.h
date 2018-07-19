#ifndef IMAGE_OBJECT_H
#define IMAGE_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include "img_processing.h"
#include "../util/util_cv.h"
#include "image.h"
#include "contour.h"
#include "../data_structure/matrix.h"
#include "../msg_handling/msg_handling.h"
#include "../util/util_macros.h"

typedef struct _img_object{
    
    int x_more_left;
    int x_more_right;
    int y_more_down;
    int y_more_up;
    
    int x_mean_value;
    int y_mean_value;
    
    /**
     * Contour que representa este objDaImagem.
     */
    Contour *contour;
    
    /**
     * Image que representa um "pedaço da image principal" correspondente
     * ao contour desse objetoDaImagem.
     */
    Image *imgDoObj;
    
    /**
     * Para uso interno. Armazena, temporariamente, a matrix criada a partir
     * da image binaria do objeto, da uma resolution x.
     */
    Matrix *matDadosObj;
    
    
}ImgObject;

/**
 * Cria objeto da image a partir de um contour.
 * Durante a criacao, as principais caracteristicas
 * do objeto sao calculadas a partir do contour 
 * e adicionas ao objeto.
 */
ImgObject* criaObjDaImg(Image *img, Contour *contour);

ImgObject* criaObjDaImgSimples();

int inicializaObjDaImg(ImgObject *obj);

int calc_set_img_obj_contour_measure(ImgObject *imageObject);

int setAtributosDePosicaoDoObjetoDaImagem(ImgObject *obj, 
					  int x_more_left, int x_more_right, 
					  int y_more_down, int y_more_up);

Matrix* getMatObjDaImg(ImgObject *objImg, int tipo_de_dados, int *resolution);

Matrix *criaMatObjDaImg(ImgObject *objImg, int tipo_de_dados, int *resolution);

int setContorno(ImgObject *obj, Contour *contour);

int setImgDoObj(ImgObject *obj, Image *contour);

Image* getImgDoObj(ImgObject *obj);

Contour* getContornoDoObjDaimg(ImgObject *mObjetoDaImagem);

int get_img_obj_x_more_left(ImgObject *obj, int *x);

int get_img_obj_x_more_right(ImgObject *obj, int *x);

int get_img_obj_y_more_up(ImgObject *obj, int *y);

int get_img_obj_y_more_down(ImgObject *obj, int *y);

int get_relative_obj1_obj2_position(ImgObject *obj_1, 
				    ImgObject *obj_2,
				    int *result);

int compare_x_relative_position_img_objs(ImgObject *obj_1, 
					 ImgObject *obj_2,
					 int *result);

int is_objs_same_place(ImgObject *obj_1, ImgObject *obj_2, int lim_dist);

int calc_dist_x_objs_img(ImgObject *obj_1, ImgObject *obj_2, int *result);

int calcule_area_obj(ImgObject *obj);

void printInformacaoObjetoDaImagem(ImgObject *mObjeto);

void* getFuncLiberaObjImg();

int freeObjDaImg(ImgObject **obj);

#endif
