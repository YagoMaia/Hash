#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_1 46
#define TAM_2 100
#define TABELA 80000
#define prepos 45
#define max_tam_prep 8

typedef struct dados
{
    char *palavra;
    unsigned int cont;
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

unsigned int MAD(int hash)
{
    unsigned int multiplica = 8;
    unsigned int soma = 11;
    unsigned int divisor_primo = 6761;
    return (((multiplica * hash + soma) % divisor_primo) % TABELA);
}

void analise_tabela(Dados tabela[], unsigned int posicao, char *palavra_texto)
{
    if (palavra_texto != NULL)
    {
        if (tabela[posicao].cont == 0)
        {
            tabela[posicao].palavra = malloc(TAM_1);
            strcpy(tabela[posicao].palavra, palavra_texto);
            tabela[posicao].cont = 1;
        }
        else
            tabela[posicao].cont++;
    }
}

int analise_prep(char *palavra)
{
    char matriz_prep[prepos][max_tam_prep] = {"pelo", "ao", "pro", "do", "no", "pela", "a", "pra", "da", "na", "pelos", "aos", "pros", "dos", "nos", "pelas", "as", "pras", "das", "nas", "num", "numa", "numas", "nele", "neles", "nelas", "nelas", "neste", "nisto", "nesse", "nesses", "nisso", "aquele", "aquela", "daquilo", "daquele", "naquele", "naquilo", "de"};
    if (palavra != NULL)
    {
        for (int i = 0; i < prepos; i++)
        {
            if (strcmp(palavra, matriz_prep[i]) == 0)
            {
                
                return 1;
            }
        }
    }
    return 0;
}

void maiscula_minuscula(char *palavra)
{
    char *maiscula = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};  //{ABCDEFGHiJKLMNOPQRSTUVWXYZ}
    char *minuscula = {"abcdefghijklmnopqrstuvwxyz"}; //{abcdefghijklmnopqrstuvwxyz}
    if (palavra != NULL)
    {
        for (unsigned int i = 0; i < strlen(palavra); i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (palavra[i] == maiscula[j])
                {
                    palavra[i] = minuscula[j];
                }
            }
        }
    }
}

unsigned int leitor_linhas(char texto[TAM_2], FILE *arquivo, Dados tabela_hash[TABELA])
{
    char *sub_string;
    char black_list[TAM_1] = "  ,.!?\n\r#@-_+=/;*:1234567890()''^~\"";
    unsigned int numero_palavras = 0;
    unsigned int pos_tabela;
    while (fgets(texto, TAM_2, arquivo) != NULL)
    {
        sub_string = strtok(texto, black_list); // Primeira palavra da linha
        maiscula_minuscula(sub_string);         // Convertendo todas as letras da primeira palavra da frase em minusculo
        while (sub_string != NULL)
        {
            maiscula_minuscula(sub_string); // Convertendo as demais palavras da linha
            if (analise_prep(sub_string) == 1)
            {
                sub_string = strtok(NULL, black_list);
                maiscula_minuscula(sub_string);
            }
            if (sub_string != NULL)
            {
                pos_tabela = MAD(hashcode(sub_string));
                analise_tabela(tabela_hash, pos_tabela, sub_string);
                sub_string = strtok(NULL, black_list);
                numero_palavras++;
            }
        }
    }
    return numero_palavras;
}

void conteudo_tabela(Dados tabela[])
{
    for (unsigned int i = 0; i < TABELA; i++)
    {
        if (tabela[i].cont != 0)
        {
            printf("Palavra: %s // Vezes %d\n", tabela[i].palavra, tabela[i].cont);
        }
    }
}

void acessar_palavra(Dados tabela[], char *palavra_desejada)
{
    if(tabela[MAD(hashcode(palavra_desejada))].cont > 0){
        //printf("Posicao da tabela hash: %d\n"), MAD(hashcode(palavra_desejada));
        printf("Palavra: %s\n", tabela[MAD(hashcode(palavra_desejada))].palavra);
        printf("Quantidade: %d\n", tabela[MAD(hashcode(palavra_desejada))].cont);
    }
    else printf("Não existe tal palavra na tabela Hash\n");
}

int main(void)
{
    Dados tabela_hash[TABELA];
    for (unsigned int i = 0; i < TABELA; i++)
    {
        tabela_hash[i].cont = 0;
    }
    unsigned int num = 0;
    FILE *file;
    // file = fopen("brascubas.txt", "r");
    file = fopen("D:\\Engenharia de Sistemas\\2º Período\\AEDS 2\\Hash\\brascubas.txt", "r");

    if (file == NULL)
    {
        printf("Não existe tal arquivo");
        getchar();
        exit(0);
    }

    char frase[TAM_2];

    num = leitor_linhas(frase, file, tabela_hash);
    fclose(file);
    //conteudo_tabela(tabela_hash);
    acessar_palavra(tabela_hash, "toda");
    printf("Nessa arquivo ha %d palavras\n", num);
    return 0;
}
