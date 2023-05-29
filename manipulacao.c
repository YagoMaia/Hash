#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int num = 0;
    FILE *file;
    file = fopen("teste.txt", "r");
    // fprintf(file, "Algo depois do hello world."); //Vai limpar o arquivo pra adicionar o que está no fprintf
    
    if(file == NULL){
        printf("Não existe tal arquivo");
        getchar();
        exit(0);
    }
    
    char frase[100], palavras[100],*token;

    // Lendo strings completas
    //while(fgets(frase, 100, file) != NULL){
    //    printf("%s", frase);
    //}

    // Lendo palavras da string -> Pensar numa maneira de separar as palavras
    while(fgets(frase, 100, file) != NULL){
        strcpy(frase, palavras);
        for(int i = 0; palavras[i] != '\n'; i++){
            printf("%c", palavras[i]);
            if(palavras[i] == ' ') printf("\n");
        }
        token = strtok(frase, " ");
        printf("\n");
        printf("%s\n", token);
        num++;
    }
    fclose(file);
    printf("Nessa arquivo ha %d palavras\n", num);
    return 0;
}