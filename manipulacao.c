#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_1 30
#define TAM_2 100
#define fim_palavras 12

int leitor_linhas(char texto[TAM_2], FILE *arquivo, char separadas[TAM_1])
{
    char black_list[fim_palavras] = {' ', '\n', '.', ',', '/', '-', ';', '?', '!', '*', ':', '"'};
    int k, numero_palavras;
    k = numero_palavras = 0;
    while (fgets(texto, TAM_2, arquivo) != NULL)
    {
        for (unsigned int i = 0; i < strlen(texto); i++, k++)
        {   
            for (int cases = 0; cases < fim_palavras; cases++)
            {
                if(texto[i] != black_list[cases]){
                    separadas[k] = texto[i];
                }
                else if (texto[i] == black_list[cases])
                {
                    if(k!= 0) numero_palavras++; //Gambiarra 
                    separadas[k] = '\0'; 
                    //printf("Valor do k: %d ", k);
                    //puts(separadas);
                    k = -1;
                }
            }
            
        }
       // printf("Fim da linha\n");
    }
    return numero_palavras;
}

int main(void)
{
    int num = 0;
    FILE *file;
    file = fopen("brascubas.txt", "r");
    // fprintf(file, "Algo depois do hello world."); //Vai limpar o arquivo pra adicionar o que está no fprintf

    if (file == NULL)
    {
        printf("Não existe tal arquivo");
        getchar();
        exit(0);
    }

    char frase[TAM_2], palavra[TAM_1];

    num = leitor_linhas(frase, file, palavra);
    fclose(file);
    printf("Nessa arquivo ha %d palavras\n", num);
    return 0;
}
