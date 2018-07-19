#include "util_ocr.h"

char *__vetor = "\0";
char **VETOR_REF = &__vetor;

int get_index_output_desired(char *valReferencia, int *index){
  
  if(valReferencia == NULL || index == NULL)
    return *print_msg(ERR_PTR_NULL, "util_ocr.c/get_index_output_desired");
  
  char *vetor = getVetorReferencia();
  
  int i;
  for(i = 0 ; i < TAM_VETOR_SAIDA; i++)
    if(*valReferencia == *(vetor + i)){
      *index = i;
      
      return INF_NOT_ERR;
    }
    
    return ERR_VAR_INV;
}

int getCharSaidaDesejada(int index_output_desired, char *valSaidaDes){
  
  char *vetor = getVetorReferencia();
  
  *valSaidaDes = vetor[index_output_desired];
  
  return INF_NOT_ERR;
}

char* getVetorReferencia(){
  
  int BAR_ZERO = 1;
  if(*__vetor == '\0'){
    
    __vetor = malloc(TAM_VETOR_SAIDA + BAR_ZERO);
    
    int i;
    for(i = 0; i < TAM_VETOR_SAIDA ; i++){
      __vetor[i] = (char) i + LIM_INF_ASCII;
    }
    
    __vetor[i] = '\0';
    
  }
  
  return __vetor;
  
}

char *getVetorSaidaDesejada(int index_output_desired){
  
  
  if(index_output_desired >= TAM_VETOR_SAIDA){
    print_msg(ERR_GENERIC, 
			  "getVetorSaida");
    return NULL;
  }
  
  int BARRA_ZERO = 1;
  
  char *saidaDesejada = (char*) malloc(TAM_VETOR_SAIDA + BARRA_ZERO);
  
  int i;
  for(i = 0; i < TAM_VETOR_SAIDA; i++)
    saidaDesejada[i] = index_output_desired == i ? '1' : '0';
  
  saidaDesejada[i] = '\0';
    
  return saidaDesejada;
}

int get_size_vect_out(int *size){
  
  *size = TAM_VETOR_SAIDA;
  
  return INF_NOT_ERR;
}