#include "util_svm.h"

char *geraDadosMatTreinoSvm(Matrix *mat_dados, int index){
    
    if(mat_dados == NULL ){
        print_msg(ERR_PTR_NULL, "util_fann.c/geraDadosMatTreinoFann");
        return NULL;
    }
    
    int tam_matriz = mat_dados->colunas * mat_dados->linhas;
    
    char *d_mat = to_string_matrix_transladed_to_origin(mat_dados);
    
    int NUM_0 = 0;
    int NUM_TOTAL_0 = 0;
    
    //Pega o numero de 0's pois cada 0 será substituido por -1
    n_char_occurrence(d_mat, '0', &NUM_0); 
    
    
    NUM_TOTAL_0 += NUM_0;
    
    int BARRA_N = 1;
    int BARRA_ZERO = 1;
    
    
    
    //Deve haver um espaço entre cada elemento da matrix, totalizando
    // tam_matriz - 1 já que não precisa de espaço para o ultimo elemento
    
    
    
								
    
    char *dado_Final = NULL;//malloc(tamDadosObjeto);
    
   // if(dado_Final == NULL){
      //  print_msg(ERR_GENERIC, "util_fann.c/geraDadosMatTreinoFann");
    //    return NULL;
    //}
    
    char int_temp[100];
    
    int i, j;
    int count = 0;
    
    sprintf(int_temp, "%d", index);
    
    append_data(&dado_Final, int_temp);
    
    for(i = 0; i < mat_dados->linhas; i++){
      
      char *ptr_d_mat = d_mat + i*mat_dados->colunas;
      
      for(j = 0; j < mat_dados->colunas; j++){

	count++;
	
	if(*ptr_d_mat == '0'){
	  
	  sprintf(int_temp, " %d:%s", count,"-1");
	  
	  append_data(&dado_Final, int_temp);
	  
	}else if(*ptr_d_mat == '1'){
	  sprintf(int_temp, " %d:%s", count,"1");
	  append_data(&dado_Final, int_temp);
	  
	}else{
	
	  print_msg(ERR_GENERIC, "geraDadosMatTreinoFann/util_fann.c");
	  return NULL;
	}
	
	
	ptr_d_mat++;
      }
    }
    
    //*dado_Final = '\0';

    return dado_Final;
}

float* create_svm_input(Matrix *mat_dados){
  
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

float* copy_svm_output(float *fann_output, int size_out){
  
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



/*int main(int argc, char **argv)
{
	FILE *input, *output;
	int i;
	// parse options
	for(i=1;i<argc;i++)
	{
		if(argv[i][0] != '-') break;
		++i;
		switch(argv[i-1][1])
		{
			case 'b':
				predict_probability = atoi(argv[i]);
				break;
			case 'q':
				info = &print_null;
				i--;
				break;
			default:
				fprintf(stderr,"Unknown option: -%c\n", argv[i-1][1]);
				exit_with_help();
		}
	}

	if(i>=argc-2)
		exit_with_help();

	input = fopen(argv[i],"r");
	if(input == NULL)
	{
		fprintf(stderr,"can't open input file %s\n",argv[i]);
		exit(1);
	}

	output = fopen(argv[i+2],"w");
	if(output == NULL)
	{
		fprintf(stderr,"can't open output file %s\n",argv[i+2]);
		exit(1);
	}

	if((model=svm_load_model(argv[i+1]))==0)
	{
		fprintf(stderr,"can't open model file %s\n",argv[i+1]);
		exit(1);
	}

	x = (struct svm_node *) malloc(max_nr_attr*sizeof(struct svm_node));
	if(predict_probability)
	{
		if(svm_check_probability_model(model)==0)
		{
			fprintf(stderr,"Model does not support probabiliy estimates\n");
			exit(1);
		}
	}
	else
	{
		if(svm_check_probability_model(model)!=0)
			info("Model supports probability estimates, but disabled in prediction.\n");
	}

	predict(input,output);
	svm_free_and_destroy_model(&model);
	free(x);
	free(line);
	fclose(input);
	fclose(output);
	return 0;
}
*/