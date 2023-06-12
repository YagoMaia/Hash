#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define tam 80000

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

typedef struct bloco
{
    char *palavra;
    int quantidade;
} bloco;

void inseretabela(char *palavra, bloco tabela[])
{

    unsigned int codigo;
    codigo = hashcode(palavra);
    codigo = codigo % 12467;

    if (tabela[codigo].quantidade == 0)
    {
        tabela[codigo].palavra = malloc(25);
        strcpy(tabela[codigo].palavra, palavra);
        tabela[codigo].quantidade++;
    }
    else
        tabela[codigo].quantidade++;
    return;
}

int comparapalavra(char *sub, int cont)
{

    char prep[60][8] = {"pelo", "ao", "pro", "do", "no", "pela",
                        "a", "ante", "entre", "para", "per", "perante", "por", "sem", "sob",
                        "sobre", "dum", "desta", "pra", "da", "na", "pelos", "aos", "pros",
                        "dos", "nos", "pelas", "as", "pras", "das", "nas", "num", "numa",
                        "numas", "nele", "neles", "nelas", "neste", "nisto",
                        "nesse", "nesses", "nisso", "aquele", "aquela", "daquilo",
                        "daquele", "naquele", "naquilo", "de", "ate", "essa", "aquilo"};
    int verificador = 0;
    int linha = 0;

    for (linha; linha < 60; linha++)
    {
        if (strcmp(prep[linha], sub) == 0)
            verificador++;
    }
    if (verificador == 0)
        cont++;
    return cont;
}

int main()
{

    int verificador = 0, cont = 0;
    int palavradiferente = 0, x;
    unsigned int posicao = 0;
    bloco tabela[tam];
    char frase[tam];
    char *sub;
    FILE *arquivo;

    arquivo = fopen("brascubas.txt", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado\n");
        return 0;
    }
    while (fgets(frase, tam, arquivo) != NULL)
    {
        sub = strtok(frase, "  ,.!?\n\r#@-_+=/;*:1234567890()''^~\"");
        while (sub != NULL)
        {
            // puts(sub);
            verificador = cont;
            cont = comparapalavra(sub, cont);
            if (verificador != cont)
                inseretabela(sub, tabela);
            sub = strtok(NULL, "  ,.!?\n\r#@-_+=/;*:1234567890()''^~\"");
        }
    }
    fclose(arquivo);

    for (int vezes = 0; vezes < tam; vezes++)
    {
        if (tabela[vezes].quantidade != 0)
            palavradiferente++;
        if (tabela[vezes].quantidade != 0)
        {
            printf("A palavra %s apareceu %d vezes\n", tabela[vezes], tabela[vezes].quantidade);
        }
    }
    printf("O texto tem %d palavras diferentes\n", palavradiferente);

    return 0;
}