#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int num = 0;
    FILE *file;
    file = fopen("brascubas.txt", "r");
    // fprintf(file, "Algo depois do hello world."); //Vai limpar o arquivo pra adicionar o que está no fprintf
    
    if(file == NULL){
        printf("Não existe tal arquivo");
        getchar();
        exit(0);
    }
    
    char frase[100];

    // Lendo strings completas
    //while(fgets(frase, 100, file) != NULL){
    //    printf("%s", frase);
    //}

    // Lendo palavras da string -> Pensar numa maneira de separar as palavras
    while(fgets(frase, 100, file) != NULL){
        for(int i = 0; i < strlen(frase); i++){
            if(frase[i] == ' ' || frase[i] == '\n'){
                if(frase[i] != '\n') num++;
            }
        }
        //printf("%s", frase);
    }
    fclose(file);
    printf("Nessa arquivo ha %d palavras\n", num);
    return 0;
}
