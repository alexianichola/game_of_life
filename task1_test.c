
#include "task1.h"

int main(int argc, const char*  argv[])
{  
        for(int i = 1; i < argc; i=i+2)
        {
            FILE *input_file = fopen(argv[i], "r");
            FILE *output_file = fopen(argv[i+1], "w");
    
            if(input_file == NULL || output_file == NULL) {
    
                printf("File could not open");
    
                if(input_file == NULL) {
                    fclose(output_file);

                } else if (output_file == NULL) {

                    fclose(input_file);
                }
    
                return 1;
            }

            
        
            
    int T, M, N, K, j, p;
    char **matrice, **matrice_noua, **aux;
    Node* stack=NULL;  

    fscanf(input_file, "%d %d %d %d ", &T, &N, &M, &K);
    
    matrice = (char **)malloc(N * sizeof(char *));
    if (matrice == NULL) {
        printf("Eroare la alocarea memoriei pentru matrice.\n");
        return 1;
    }
    for (i = 0; i < N; i++)
    {
        matrice[i] = (char *)malloc(M * sizeof(char));
        if (matrice[i] == NULL) {
            printf("Eroare la alocarea memoriei pentru matrice.\n");
            return 1;
        }
    }

    matrice_noua = (char **)malloc(N * sizeof(char *));
    if (matrice_noua == NULL) {
        printf("Eroare la alocarea memoriei pentru matrice.\n");
        return 1;
    }
    
    for (i = 0; i < N; i++)
    {
        matrice_noua[i] = (char *)malloc(M * sizeof(char));
        if (matrice_noua[i] == NULL) {
            printf("Eroare la alocarea memoriei pentru matrice.\n");
            return 1;
        }
    }
    //task 1

    if( T == 1 ){

    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            fscanf(input_file, " %c", &matrice[i][j]);
            fprintf(output_file, "%c", matrice[i][j]);
        }
        
        fprintf(output_file, "\n");
    }
    fprintf(output_file, "\n");

    for (p = 0; p < K; p++){  
         if(p > 0){ 
            fprintf(output_file, "\n");

        }

        reguli(matrice, matrice_noua, N, M);

        for (i = 0; i < N; i++){
            for (j = 0; j < M; j++){
                fprintf(output_file, "%c", matrice_noua[i][j]);
            } 
          
            fprintf(output_file, "\n");
        }  
        
         
        aux=matrice;
        matrice = matrice_noua;
        matrice_noua=aux;
    }
        fprintf(output_file, "\n");
    } 

    //task  2

    if ( T == 2 ){
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
        fscanf(input_file, " %c", &matrice[i][j]);
               }
        }
        
    for (p = 0; p < K; p++) {  
        

        reguli(matrice, matrice_noua, N, M);
        schimbari(matrice, matrice_noua, N, M, &stack);
      

        aux=matrice;
        matrice = matrice_noua;
        matrice_noua=aux;
      } 
        printStack(stack, output_file);
   
    } 


    


    for (i = 0; i < N; i++) {
        free(matrice[i]);      
        free(matrice_noua[i]); 
    }

    free(matrice);      
    free(matrice_noua); 
  
    deleteStack(&stack);

    fclose(input_file);
    fclose(output_file);
    }
    
}