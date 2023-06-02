#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_1 46
#define TAM_2 100
#define TABELA 80000
#define prepos 39
#define max_tam_prep 8

typedef struct dados
{
    char *palavra;
    int cont;
} Dados;

int hashcode(char *s)
{
    int r = 0, i;
    for (i = 0; s[i] != '\0'; i++)
    {
        r = (r << 5) | (r >> 27);
        r = (int)s[i] ^ r;
    }
    return r;
}

int MAD(int hash)
{
    int multiplica = 8;
    int soma = 11;
    int divisor_primo = 6761;
    return (((multiplica * hash + soma) % divisor_primo) % TABELA);
}

void analise_tabela(Dados tabela[], int posicao, char *palavra_texto)
{
    if (posicao < 0)
        posicao = -posicao;
    if (tabela[posicao].cont == 0)
    {
        tabela[posicao].palavra = malloc(TAM_1);
        strcpy(tabela[posicao].palavra, palavra_texto);
        tabela[posicao].cont = 1;
    }
    else
        tabela[posicao].cont++;
}

int leitor_linhas(char texto[TAM_2], FILE *arquivo, Dados tabela_hash[TABELA])
{
    char *sub_string;
    char black_list[TAM_1] = " ,.!?\n\r#@-_+=/;*:1234567890";
    char matriz_prep[prepos][max_tam_prep] = {{"pelo"}, {"ao"}, {"pro"}, {"do"}, {"no"}, {"pela"}, {"a"}, {"pra"}, {"da"}, {"na"}, {"pelos"}, {"aos"}, {"pros"}, {"dos"}, {"nos"}, {"pelas"}, {"as"}, {"pras"}, {"das"}, {"nas"}, {"num"}, {"numa"}, {"numas"}, {"nele"}, {"neles"}, {"nelas"}, {"nelas"}, {"neste"}, {"nisto"}, {"nesse"}, {"nesses"}, {"nisso"}, {"aquele"}, {"aquela"}, {"daquilo"}, {"daquele"}, {"naquele"}, {"naquilo"}, {"de"}};
    int numero_palavras = 0;
    int pos_tabela;
    while (fgets(texto, TAM_2, arquivo) != NULL)
    {
        sub_string = strtok(texto, black_list);
        while (sub_string != NULL)
        {
            for (int i = 0; i < prepos; i++)
            {
                if (strcmp(sub_string, matriz_prep[i]) == 0)
                    sub_string = strtok(NULL, black_list);
            }
            if (sub_string != NULL)
            {
                puts(sub_string);
                pos_tabela = MAD(hashcode(sub_string));
                analise_tabela(tabela_hash, pos_tabela, sub_string);
                printf("Posicao tabela = %d\n", pos_tabela);
                sub_string = strtok(NULL, black_list);
                numero_palavras++;
            };
        }
    }
    return numero_palavras;
}

void conteudo_tabela(Dados tabela[])
{
    for (int i = 0; i < TABELA; i++)
    {
        if (tabela[i].cont != 0)
        {
            printf("Palavra: %s // Vezes %d\n", tabela[i].palavra, tabela[i].cont);
        }
    }
}

int main(void)
{
    Dados tabela_hash[TABELA];
    for (int i = 0; i < TABELA; i++)
    {
        tabela_hash[i].cont = 0;
    }
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

    num = leitor_linhas(frase, file, tabela_hash);
    fclose(file);
    conteudo_tabela(tabela_hash);
    printf("Nessa arquivo ha %d palavras\n", num);
    return 0;
}
