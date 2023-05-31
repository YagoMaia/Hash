#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_1 30
#define TAM_2 100
#define fim_palavras 12

int leitor_linhas(char texto[TAM_2], FILE *arquivo)
{
    char *sub_string;
    char black_list[TAM_1] = " ,.!?\n#@-_+=/;*:1234567890";
    int numero_palavras;
    numero_palavras = 0;
    while (fgets(texto, TAM_2, arquivo) != NULL)
    {
        sub_string = strtok(texto, black_list);
        while(sub_string != NULL){
            //printf("%s\n", sub_string);
            sub_string = strtok(NULL, black_list);
            numero_palavras++;
        }
    }
    return numero_palavras;
}

int main(void)
{
    int num = 0;
    FILE *file;
    file = fopen("brascubas.txt", "r");

    if (file == NULL)
    {
        printf("Não existe tal arquivo");
        getchar();
        exit(0);
    }

    char frase[TAM_2];

    num = leitor_linhas(frase, file);
    fclose(file);
    printf("Nessa arquivo ha %d palavras\n", num);
    return 0;
}
