#include "matrix.h"

Matrix* criaEstrutraMatriz(){
    
    Matrix *mMatriz = (Matrix*) malloc(sizeof(Matrix));
    
    if(mMatriz == NULL)
        print_msg(ERR_MEMORY,"criaEstrutraMatriz");

    return mMatriz;
}

int inicializaMatriz(Matrix **mMatriz, int linhas, int colunas){
    
    if((*mMatriz) == NULL){
        print_msg(ERR_PTR_NULL,"inicializaMatriz");
        return ERR_PTR_NULL;
    }
    
    if(linhas <=0 || colunas <= 0){
         print_msg(ERR_VAR_INV,"inicializaMatriz");
        return ERR_VAR_INV;
    }
    
    (*mMatriz)->linhas = linhas;
    (*mMatriz)->colunas = colunas;
    (*mMatriz)->matrix = (int*) malloc(sizeof(int)*linhas*colunas);
    
    return INF_NOT_ERR;
}

int getNumLinhas(Matrix **mMatriz){
    
    if((*mMatriz) == NULL){
        print_msg(ERR_PTR_NULL,"getNumLinhas");
        return ERR_PTR_NULL;
    }
    
    return (*mMatriz)->linhas;
}

int getNumColunas(Matrix **mMatriz){
    
    if((*mMatriz) == NULL){
        print_msg(ERR_PTR_NULL,"getNumColunas");
        return ERR_PTR_NULL;
    }
    
    return (*mMatriz)->colunas;
}

int* getConteudoDaMatriz(Matrix **mMatriz){
    
    if((*mMatriz) == NULL){
        print_msg(ERR_PTR_NULL,"getConteudoDaMatriz");
        return NULL;
    }
    
    return (*mMatriz)->matrix;
}

int setElementoDaMatrizInteiro(Matrix **mMatriz, int l, int c, int valor){
    
    if((*mMatriz) == NULL){
        print_msg(ERR_PTR_NULL,"setElementoDaMatriz");
        return ERR_PTR_NULL;
    }
    
    int posicao = (l * (*mMatriz)->colunas) + c;
    
    if((*mMatriz)->matrix == NULL || posicao >= ((*mMatriz)->linhas*(*mMatriz)->colunas)){
        print_msg(ERR_POS_INV,"setElementoDaMatriz");
        return ERR_POS_INV;
    }
    
    (*mMatriz)->matrix[posicao] = valor;
    
    return INF_NOT_ERR;
}

void printMatriz(Matrix *matrix){
    
    int row, col;
    for(row = 0; row < matrix->linhas; row++ ) {
        
        printf("\n");
        int* ptr =  (matrix->matrix + (row * matrix->colunas));
        
        for( col = 0; col < matrix->colunas; col++ ) {
            if(ptr[col] > 0)
                printf("%d",1);
            else
                printf("%d",0);
        }
    }
    
    printf("\n");
}

void printMatrizTexto(char *matrix, int rows, int cols){
    
    int i, j;
    for(i = 0; i < rows; i++ ) {
        
        printf("\n");
        char* ptr =  matrix + (i * cols);
        
        for( j = 0; j < cols; j++ ) {
            if(ptr[j] != '0')
                printf("1");
            else
                printf("0");
        }
    }
    
    printf("\n");
}

char* toStringMatriz(Matrix *matrix){
    
  if(matrix == NULL){
      print_msg(ERR_PTR_NULL, "estruturaMatriz.c/toStringMatriz");
      return NULL;
  }
  
  int rows = matrix->linhas;
  int cols = matrix->colunas;
  
  int* fMat = matrix->matrix;
  char *string = malloc((rows*cols) + 1);

  int i;
  for(i = 0; i < rows*cols; i++ ) 
      string[i] = fMat[i] > 0 ? '1' : '0';
  
  string[i] = '\0';
  
  
  return string;
}

char* to_string_matrix_transladed_to_origin(Matrix *matrix){
  
      if(matrix == NULL){
        print_msg(ERR_PTR_NULL, "estruturaMatriz.c/toStringMatriz");
        return NULL;
    }
   

    
  int cod = transladaEstruturaMatrizParaOrigem(matrix);
  
  if(cod != INF_NOT_ERR){
    print_big_msg(ERR_GENERIC, 
		"estruturaMatriz.c/to_string_matrix_transladed_to_origin", 
		"transladaEstruturaMatrizParaOrigem");
  
  return NULL;
  }
  
  char *mat_dados = toStringMatriz(matrix);
  
  return mat_dados;
  
}

char* to_string_matrix_transladed_to_center(Matrix *matrix){
  
  if(matrix == NULL){
    print_msg(ERR_PTR_NULL, "estruturaMatriz.c/toStringMatriz");
    return NULL;
  }
    
  int cod = transladaMatrizParaCentro(matrix);
    
  
  if(cod != INF_NOT_ERR){
    print_big_msg(ERR_GENERIC, 
		  "estruturaMatriz.c/to_string_matrix_transladed_to_center", 
		  "transladaMatrizParaCentro");
    
    return NULL;
  }
  
  
  return toStringMatriz(matrix);
  
}

char* to_string_matrix_human_view(Matrix *matrix){
    
    if(matrix == NULL){
      print_msg(ERR_PTR_NULL, "matrix.c/to_string_matrix_human_view");
      return NULL;
    }
    
    char *str_mat = toStringMatriz(matrix);
    
    int rows = matrix->linhas;
    int cols = matrix->colunas;
    
    int NUMBER_BAR_N = rows - 1;
    int SIZE_BAR_0 = 1;
    int size_new_string = (rows*cols) + NUMBER_BAR_N + SIZE_BAR_0;
    
    char *new_str= malloc(size_new_string);
    
    int i, j = 0;
    
    for(i = 0; i < rows*cols; i++ ){ 
	new_str[j] = str_mat[i];
	j++;
	
	if((i+1) % cols == 0 && (i + 1) != rows*cols){
	  new_str[j] = '\n';
	  j++;
	}
	
    }
    
    new_str[j] = '\0';
    
    free(str_mat);
    
    return new_str;
}

int calc_center_x_pondered(Matrix *matrix, int *center_x){
  
  if(matrix == NULL){
    return *print_msg(ERR_PTR_NULL, "matrix.c/calc_center_x_pondered");
    
  }
    
  int rows = matrix->linhas;
  int cols = matrix->colunas;
  
  int* fMat = matrix->matrix;

  int sum_x = 0;
  int count_p_valid = 0;
  
  int i, j;
  for(i = 0; i < rows; i++ ){
    
    fMat = matrix->matrix + i*cols; 
    
    for(j = 0; j < cols; j++ ){
      
      if(fMat[j] > 0){
	sum_x += j;
	count_p_valid++;
      }
    }
  }
     
  float med = ((float)sum_x) / count_p_valid;
  
  med = round(med);
  
  *center_x = (int) med;
  
  return INF_NOT_ERR;
}

int* calculaDeslocamentos(Matrix *matrix){
  
  int xMesq = matrix->colunas;
  int yMbaixo = matrix->linhas;

  int row = 0;
  int col = 0;
  
  int have_pixel_line = 0;
    
  for(row = 0; row < matrix->linhas; row++){
    
    int deslocamento = row * matrix->colunas;
    int* ptr = matrix->matrix + deslocamento;
    
    for(col = 0; col < matrix->colunas; col++){
      
      if(ptr[col] > 0){
	
	xMesq = xMesq > col ? col : xMesq;
	
	yMbaixo = yMbaixo < row ? row : yMbaixo; // Lembrar que o eixo da image comeca do canto esquerdo superior
					      //Então, quanto mais a cima a linha estiver, menor será o y.

	//have_pixel_line = 1;
	
      }
       
       /*if(have_pixel_line && yMbaixo < row){
	 yMbaixo = row;
	 have_pixel_line = 0;
       }*/
    }
    
  }

  int *deslocamento = (int*)malloc(2*sizeof(int));
  
  deslocamento[0] = xMesq;
  deslocamento[1] = yMbaixo;
  
 
  
  return deslocamento;
}

/*char *transladaMatrizParaOrigem(char *dados, int rows, int cols, int *deslocamentos){
    
  if(dados == NULL){
      print_msg(ERR_PTR_NULL, "estruturaMatriz.c/transladaMatrizParaOrigem");
      return NULL;
  }
  
  int B_ZERO = 1;
  int tamDados = rows * cols + B_ZERO;
  
  if((rows * cols) != (strlen(dados))){
      print_msg(ERR_GENERIC, "estruturaMatriz.c/transladaMatrizParaOrigem");
      return NULL;
  }

  char *newDados = malloc(tamDados);
  
  int deslocarCol = deslocamentos[0];
  int deslocarLinha = deslocamentos[1];
  
  char *tempDados = NULL;
  char *tempNewDados = newDados;
  
  int deslocarNewDados, difEsq;
  int i, j;

  deslocarLinha = rows - deslocarLinha;
  
  for(i = 0; i < rows; i++ ) {
      
      tempDados =  dados + (i * cols);
      
      deslocarNewDados = (i - deslocarLinha) < 0 ? (rows - deslocarLinha + i) : (i - deslocarLinha);

      newDados = tempNewDados + (deslocarNewDados * cols);
      
      for( j = 0; j < cols; j++ ) {
	  
	  difEsq = j - deslocarCol;
	  
	  if(difEsq < 0)
	      newDados[cols - deslocarCol + j] = tempDados[j];

	  else
	      newDados[difEsq] = tempDados[j];
	  
      }
      
  }
  
  newDados = tempNewDados;
  
  newDados[rows * cols] = '\0';
  
  newDados = tempNewDados;
  
  tempDados = NULL;
  
  //free(dados);
  
  return newDados;
    
}*/

int transladaMatrizParaCentro(Matrix *matrix){
  
  if(matrix == NULL){
    return *print_msg(ERR_PTR_NULL, "estruturaMatriz.c/transladaMatrizParaCentro");
  }
  
  int rows = matrix->linhas;
  int cols = matrix->colunas;
  int y, x = 0;
  int center_x_pondered = 0;
  int center_x_mat = cols/2;
  
  int *desloc = calculaDeslocamentos(matrix);
  
  calc_center_x_pondered(matrix, &center_x_pondered);
  
  int diff_centers = center_x_mat - center_x_pondered;
  
  int x_relative = 0;
  int y_relative = desloc[1];
  
  int *new_mat = (int*) malloc(rows * cols * sizeof(int));
  int* fMat = matrix->matrix;
  int *f_new_mat = new_mat;
  
  for(y = 0; y < rows; y++ ){
    
    y_relative = y + (rows - desloc[1]) ;
    
    if(y_relative >= rows)
      fMat = NULL; 
    
    else
      fMat = matrix->matrix + y_relative*cols;
    
    f_new_mat = new_mat + y*cols;
    
    for(x = 0; x < cols; x++ ){
      
      if(diff_centers < 0)
	x_relative = x + -1*diff_centers;
      
      else
	x_relative = x - diff_centers;
      
      if(x_relative < 0 || x_relative >= cols || fMat == NULL)
	f_new_mat[x] = 0;
      else
	f_new_mat[x] = fMat[x_relative];
          
    }
  }
  
  fMat = NULL;
  f_new_mat = NULL;
  
  free(matrix->matrix);
  
  matrix->matrix = new_mat;
  
  return INF_NOT_ERR;
  
}

int transladaEstruturaMatrizParaOrigem(Matrix *matrix){
  
  if(matrix == NULL){
    return *print_msg(ERR_PTR_NULL, "estruturaMatriz.c/transladaMatrizParaCentro");
  }
  
  int rows = matrix->linhas;
  int cols = matrix->colunas;
  int y, x = 0;
  
  int *desloc = calculaDeslocamentos(matrix);;
  
  int diff_origin = 0 - desloc[0];
  
  int x_relative = 0;
  int y_relative = desloc[1];
  
  int *new_mat = (int*) malloc(rows * cols * sizeof(int));
  int* fMat = matrix->matrix;
  int *f_new_mat = new_mat;
  
  for(y = 0; y < rows; y++ ){
    
    y_relative = y + (rows - desloc[1]) ;
    
    if(y_relative >= rows)
      fMat = NULL; 
    
    else
      fMat = matrix->matrix + y_relative*cols;
    
    f_new_mat = new_mat + y*cols;
    
    for(x = 0; x < cols; x++ ){
      
      if(diff_origin < 0)
	x_relative = x + -1*diff_origin;
      
      else
	x_relative = x - diff_origin;
      
      if(x_relative < 0 || x_relative >= cols || fMat == NULL)
	f_new_mat[x] = 0;
      else
	f_new_mat[x] = fMat[x_relative];
          
    }
  }
  
  fMat = NULL;
  f_new_mat = NULL;
  
  free(matrix->matrix);
  
  matrix->matrix = new_mat;
  
  return INF_NOT_ERR;
  
}

int liberaMemoriaMatrizEDependencias(Matrix **mMatriz){
    
    if((*mMatriz) == NULL){
        print_msg(ERR_PTR_NULL,"liberaMemoriaMatrizEDependencias");
        return ERR_PTR_NULL;
    }
    
    if((*mMatriz)->matrix != NULL)
        free((*mMatriz)->matrix);
        
    free((*mMatriz));
    
    (*mMatriz) = NULL;
    
    return INF_NOT_ERR;
}
