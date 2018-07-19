#include "util_fann.h"

char *geraDadosMatTreinoFann(Matrix *mat_dados, char *saida_des){
    
    if(mat_dados == NULL || saida_des == NULL){
        print_msg(ERR_PTR_NULL, "util_fann.c/geraDadosMatTreinoFann");
        return NULL;
    }
    
    int tam_matriz = mat_dados->colunas * mat_dados->linhas;
    
    char *d_mat = toStringMatriz(mat_dados);
    
    int NUM_0 = 0;
    int NUM_TOTAL_0 = 0;
    
    //Pega o numero de 0's pois cada 0 será substituido por -1
    n_char_occurrence(d_mat, '0', &NUM_0); 
    n_char_occurrence(saida_des, '0', &NUM_TOTAL_0); 
    
    NUM_TOTAL_0 += NUM_0;
    
    int BARRA_N = 1;
    int BARRA_ZERO = 1;
    
    int len_saida_des = strlen(saida_des);
    
    //Deve haver um espaço entre cada elemento da matrix, totalizando
    // tam_matriz - 1 já que não precisa de espaço para o ultimo elemento
    int NUM_ESPACOS = tam_matriz - 1 + len_saida_des - 1;
    
    
								
    int tamDadosObjeto = tam_matriz + NUM_ESPACOS + NUM_TOTAL_0 
						  + BARRA_N 
						  + BARRA_ZERO 
						  + len_saida_des;
    
    char *dado_Final = malloc(tamDadosObjeto);
    
    if(dado_Final == NULL){
        print_msg(ERR_GENERIC, "util_fann.c/geraDadosMatTreinoFann");
        return NULL;
    }
    
    char *aux_fin= dado_Final;
    
    int i, j;
    
    for(i = 0; i < mat_dados->linhas; i++){
      
      char *ptr_d_mat = d_mat + i*mat_dados->colunas;
      
      for(j = 0; j < mat_dados->colunas; j++){
	
	if(*ptr_d_mat == '0'){
	  *aux_fin = '-';
	  aux_fin++;
	  *aux_fin = '1';
	  aux_fin++;
	  
	}else if(*ptr_d_mat == '1'){
	  *aux_fin = '1';
	  aux_fin++;
	  
	}else{
	
	  print_msg(ERR_GENERIC, "geraDadosMatTreinoFann/util_fann.c");
	  return NULL;
	}
	
	//Evita colocar espaco depois do ultimo caracter
	if((i + j) != (mat_dados->linhas + mat_dados->colunas -2)){
	  *aux_fin = ' ';
	  aux_fin++;
	}
	
	ptr_d_mat++;
      }
    }
    
    //Append nova linha + os dados referente ao valor de output desejada
    *aux_fin = '\n';
    aux_fin++;
    
    char *temp_des = saida_des;
    while(*temp_des != '\0'){
      
      if(*temp_des == '0'){
	*aux_fin = '-';
	aux_fin++;
	*aux_fin = '1';
	aux_fin++;
	
      }else if(*temp_des == '1'){
	  *aux_fin = '1';
	  aux_fin++;
	  
      }else{
	
	  print_msg(ERR_GENERIC, "geraDadosMatTreinoFann/util_fann.c");
	  return NULL;
	}
      
      //Evita colocar espaço depois do ultimo elemento
      if(*(temp_des +1) != '\0' ){
	*aux_fin = ' ';
	aux_fin++;
      }
      
      temp_des++;
    }
    
    *aux_fin = '\0';

    return dado_Final;
}

float* create_fann_input(Matrix *mat_dados){
  
  if(mat_dados == NULL){
    print_msg(ERR_PTR_NULL, "util_fann.c/create_fann_input");
    return NULL;
  }
  
  if(mat_dados->matrix == NULL){
    print_msg(ERR_PTR_NULL, "util_fann.c/create_fann_input");
    return NULL;
  }
    
  int tam_matriz = mat_dados->colunas * mat_dados->linhas;
  
  float *output = (float*) malloc(sizeof(float) * tam_matriz);
  
  if(output == NULL){
    print_msg(ERR_MEMORY, "util_fann.c/create_fann_input");
    return NULL;
  }
  
  int i;
  for(i = 0 ; i < tam_matriz; i++){
    output[i] = (float) mat_dados->matrix[i] <= 0 ? -1 : 1 ;
  }
  
  return output;

}

float* copy_fann_output(float *fann_output, int size_out){
  
  if(fann_output == NULL || size_out <= 0){
    print_msg(ERR_GENERIC, "util_fann/copy_fann_output");
  
    return NULL;
  }
  
  float *output_copy = (float*) malloc(size_out * sizeof(float));
  
  int i;
  for(i = 0; i < size_out; i++)
    output_copy[i] = fann_output[i];
  
  return output_copy;
  
}

int* get_fill_layers(int n_layers, int *neurons_hidden, int size_input){
  
  if(neurons_hidden == NULL || n_layers < 1 || size_input < 1){
    print_msg(ERR_GENERIC, "util_fann/get_fill_layers");
    return NULL;
  }
  
    
  char *v_ref = getVetorReferencia();
  
  if(v_ref == NULL){
    //print_big_msg(ERR_GENERIC, "util_fann/get_fill_layers", "v_ref");
    print_msg(ERR_GENERIC, "util_fann/get_fill_layers");
    return NULL;
  }
  
  int tam_vet = strlen(v_ref);
  
  int *layers = (int*) malloc(sizeof(int) * n_layers);
  
  if(layers == NULL){
    print_msg(ERR_MEMORY, "util_fann/get_fill_layers");
    return NULL;
  }
  
  int tam_layer_1 = size_input * size_input;
  
  int j = 0;
  
  int i; 
  for(i = 0; i < n_layers; i++){
    
    if(i == 0)
      layers[i] = tam_layer_1;
    
    else if(i+1 == n_layers)
      layers[i] = tam_vet;
    
    else{
      layers[i] = neurons_hidden[j];
    
      j++;
    }
  }
  
  return layers;
}

char* create_fann_header(int n_samples, int size_sample, int size_output){
  
  if(n_samples < 1 || size_sample < 1 || size_output < 1){
    print_msg(ERR_VAR_INV, "util_fann/create_fann_header");
    return NULL;
  }
  int n_spaces = 2;
  int b_zero = 1;
  
  char *header = malloc(sizeof(n_samples) + sizeof(size_sample) + 
			sizeof(size_output) + n_spaces + b_zero);
  
  if(header == NULL){
    print_msg(ERR_MEMORY, "util_fann/create_fann_header");
    return NULL;
  }
  
  sprintf(header, "%d %d %d", n_samples, size_sample, size_output);
  
  return header;
}

int print_ann_input(float *ann_in, int n_inputs){
  
  int i;
  for(i = 0 ; i < n_inputs; i++)
    printf("%d = %f , ", i, ann_in[i]);
  
  return INF_NOT_ERR;
}

/*
char* converteDadosParaFANN(NeuralObjIn *inNeural){
    
    if(dados == NULL){
        
        print_msg(ERR_PTR_NULL, "logicaTreino.c/converteDadosParaFANN");
        return NULL;
    }
    
    printf("Entrei no converte\n");
    
    int entradas = 0; 
    int tamDado = 0;
    int saidas = 0;
    int isEntrada = 1;
    int isFirstEntrada = 1;
    int isFirstSaida = 0;
    int BARRA_ZERO = 1;
    
    int tamSaida = strlen(dados) * 3 + BARRA_ZERO ;
    
    printf("Peguei o tamanho\n");
    
    char *dadosFann = malloc(tamSaida);
    
    if(dadosFann == NULL){
        
        print_msg(ERR_MEMORY, "logicaTreino.c/converteDadosParaFANN");
        return NULL;
    }
        
    
    printf("Aloquei memoria\n");
    
    char *posInicial = dadosFann;
    
    int i = 0;
    while(*dados != '\0'){
        printf("Salvando %d\n", i++);
        
        if(*dados == '0'){
            *dadosFann = '-';
            dadosFann++;
            *dadosFann = '1';
            
        }
        else
            *dadosFann = *dados;
        
        if(*(dados + 1) != '\n' && *dados != '\n'){
            dadosFann++;
            *dadosFann = ' ';
            
            if(isEntrada && isFirstEntrada)
               tamDado++;
            
            else if(!isEntrada && isFirstSaida)
                saidas++;
        }
        
        else if(*dados == '\n'){
            
            
            if(!isFirstSaida && isFirstEntrada)
                isFirstSaida = 1;
            else
                isFirstSaida = 0;
            
            isFirstEntrada = 0;
            
            if(isEntrada)
                entradas++;
            
            isEntrada = isEntrada ? 0 : 1;
            
        }
        
        dadosFann++;
        dados++;
    }
    
    tamDado++;
    saidas++;
    
    *dadosFann = '\0';
    
    char *stringFinal = malloc(strlen(posInicial) + 1 + 3*sizeof(int));
    
    sprintf(stringFinal,"%d %d %d\n%s", entradas, tamDado, saidas, posInicial);
    
    dadosFann = NULL;
    free(posInicial);
    
    return stringFinal; 
}*/
