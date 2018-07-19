#ifndef UTIL_MACROS_H
#define UTIL_MACROS_H

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <fann.h>

//Marcros genéricos e de configuracao

#define TRUE 1
#define FALSE 0

//Macros used in the comparison funcion
#define OBJ_1_IS_MAJOR 1
#define OBJ_2_IS_MAJOR 2
#define OBJ_1_AND_2_ARE_EQUAL 0

#define OBJ_1_IS_LEFT_UP_OBJ_2 1
#define OBJ_1_IS_LEFT_DOWN_OBJ_2 2
#define OBJ_1_IS_RIGHT_UP_OBJ_2 3
#define OBJ_1_IS_RIGHT_DOWN_OBJ_2 4
#define OBJ_1_IS_SAME_PLACE_OBJ_2 5

//Types of data structure objects
#define OBJETO_TIPO_LETRA 1
#define OBJETO_TIPO_PALAVRA 2
#define TYPE_LIST_GENERIC 3
#define TYPE_OBJ_OF_LIST 4
#define TYPE_OBJ_IMG 5
#define TYPE_OBJ_IMG_LINE 6
#define OBJETO_TIPO_ACENTO 7
#define OBJETO_TIPO_PONTUACAO 8
#define OBJETO_TIPO_LINHA 9
#define OBJETO_TIPO_TEXTO 10
#define TYPE_OBJ_CONTOUR 11
#define OBJETO_TIPO_TREINO 12
#define OBJETO_TIPO_IMG_TREINO 13
#define OBJETO_TIPO_CONJ_TREINO 14
#define TYPE_OBJ_CHAR_VIRTUAL 15
#define TYPE_OBJ_CHAR_SEED 16
#define TYPE_OBJ_WORD_SEED 17
#define TYPE_OBJ_NEURAL 18

#define CHAR_TYPE_LETTER_LOW 1
#define CHAR_TYPE_LETTER_UP 2
#define CHAR_TYPE_NUMERIC 3
#define CHAR_TYPE_SYMBOL 4

//Tipos de dados de image
#define T_OPENCV_IPL_IMG 2	//tipo de image da opencv

//Canais de cores
#define GRAYSCALE CV_LOAD_IMAGE_GRAYSCALE
#define COLORSCALE CV_LOAD_IMAGE_COLOR

//Conversoes de canais de cores
#define RGB_TO_GRAY CV_RGB2GRAY
#define GRAY_TO_RGB CV_GRAY2RGB


//Standard paths and names for the data save
#define PATH_DATA_SET ".data/"

#define ANN_DATA_INPUT_SUFIX "_ann_in" 
#define ANN_DATA_HUMAN_SUFIX "_human_format" 
#define ANN_DATA_HUMAN_SAVE_PATH "./data/ann_data_human_view/" 
#define ANN_DATA_TRAIN_SAVE_PATH "./data/ann_data_train/"

#define ANN_SAVE_PATH "./data/anns/"

//Type algorithms of train ANN
#define TRAIN_INCREMENTAL FANN_TRAIN_INCREMENTAL 

//Type func activation ANN
#define SIGMOID_SYMETRIC FANN_SIGMOID_SYMMETRIC

#define SIGMOID FANN_SIGMOID

//Methods to finalize the train
#define STOP_FUNC_MSE FANN_STOPFUNC_MSE	
#define STOP_FUNC_BIT_FAIL FANN_STOPFUNC_BIT	

//Define macros utilizado para professar a estrutura matrix
#define FORMATO_VETOR 1
#define FORMATO_MATRIZ 0
#define TIPO_MATRIZ_BIN 1
#define TIPO_MATRIZ_INT 2

#define RESOLUCAO_PADRAO 50

//Parametros para a funcao canny
#define DEFAULT_LOW_TRASH_CANNY 20
#define DEFAULT_HIGHT_TRASH_CANNY 200
#define DEFAULT_APERTURE_CANNY 3
#define DEFAULT_APERTURE_SMOOTH 3


//Macros utilizados para a criacao de kernels de convolucao
#define ROWS_KERNEL_PADRAO 3
#define COLS_KERNEL_PADRAO 3
#define TYPE_KERNEL_ELIPSE 1
#define TYPE_KERNEL_CROSS 2
#define TYPE_KERNEL_RECT 3


//É a quantidade de pixel mínima que deve existir entre contornos vizinhos 
//para que eles não sejam considerados um só contorno.
#define MESCLA_CONTOURS_DIST_MIN 3


#endif