#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_1 46
#define TAM_2 100
#define TABELA 80000
#define fim_palavras 12

int leitor_linhas(char texto[TAM_2], FILE *arquivo)
{
    char *sub_string;
    char black_list[TAM_1] = " ,.!?\n\r#@-_+=/;*:1234567890";
    char matriz_prep[10][30] = {{"de"}, {"das"}, {"o"}, {"dos"},{"os"},{"as"},{"em"}};
    //matriz_palavras[quantidade_palavras -> Seria o tamanho da listas hash][tamanho_maior_palavra -> 46 letras -> TAM_1];
    int numero_palavras;
    numero_palavras = 0;
    while (fgets(texto, TAM_2, arquivo) != NULL)
    {
        sub_string = strtok(texto, black_list);
        while(sub_string != NULL){
            puts(sub_string);
            for(int i = 0; i < 10; i++){
              if(strcmp(sub_string, matriz_prep[i]) == 0){
                numero_palavras--;
                }
            }
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
    file = fopen("teste.txt", "r");

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
