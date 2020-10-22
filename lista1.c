#include <stdio.h>
#define MAX 100
#define SUCESSO 1
#define FALHA -1
#define CHAVE_INVALIDA -1
#include <stdlib.h>

typedef struct
{
    unsigned int chave;
    unsigned int dado;
} Celula;

typedef struct
{
    Celula celulas[MAX];
    unsigned int tam;
} ListaLinear;

int criarListaVazia(ListaLinear *lls)
{

    lls->tam = 0;
    printf("**Lista criada\n");
    return (SUCESSO);
}
int criarListaVaziaL(ListaLinear *lls)
{
    int i;
    for (i = 0; (i < MAX); i++)
    {
        lls->celulas[i].chave = CHAVE_INVALIDA;
    }
    lls->tam = 0;
    printf("-----Lista criada\n");
    return (SUCESSO);
}

int criarListaChave(ListaLinear *lls, Celula celula)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        lls->celulas[i].chave = CHAVE_INVALIDA;
    }
    lls->celulas[0] = celula;
    lls->tam = 1;
    return SUCESSO;
}
void mostrarCelula(Celula celula)
{
    printf("%u", celula.chave);
    printf("       %u\n", celula.dado);
}

void mostrarLista(ListaLinear *lls)
{
    int i;
    if (lls->tam == 0)
    {
        printf("\nLista vazia \n");
    }
    else
    {
        //printf("A linear possui %u elementos \n", lls->tam);
        for (i = 0; i < lls->tam; i++)
        {
            //printf("Elemento n.: %u\n", (i + 1));
            mostrarCelula(lls->celulas[i]);
        }
    }
    printf("\nfim da lista\n");
}

int inserirInicio(ListaLinear *lls, Celula celula)
{
    int i;
    if (lls->tam == MAX)
        return FALHA;
    else
    {
        for (i = lls->tam; i > 0; i--)
        {
            lls->celulas[i] = lls->celulas[i - 1];
        }
        lls->celulas[0] = celula;
        lls->tam++;
        return SUCESSO;
    }
}

int inserirFinal(ListaLinear *lls, Celula celula)
{
    int i;
    Celula aux;
    if (lls->tam == MAX)
        return FALHA; // a lista esta cheia (overflow)
    else
    {
        lls->celulas[lls->tam] = celula; // insere no final da lista
        lls->tam++;
        return SUCESSO;
    }
}

//retorna a celula que esta na posicao desejada
// ou chave invalida se a posicao nao existe
Celula consultaListaPosicao(ListaLinear *lls, int posicao)
{
    Celula cResultado;
    if ((posicao > 0) && posicao <= lls->tam)
        cResultado = lls->celulas[posicao - 1];
    else
        cResultado.chave = CHAVE_INVALIDA;
    return cResultado;
}
int tamanhoLista(ListaLinear *lls)
{
    if (lls->tam >= 0)
        return lls->tam;
    else
        return FALHA;
}
// retorna a celula com a chave desejada
//ou chave invalida se a chave nao existe na lista
Celula consultaListaChave(ListaLinear *lls, Celula celula)
{
    int i;
    for (i = 0; i < lls->tam; i++)
        if (lls->celulas[i].chave == celula.chave)
            return lls->celulas[i];
    celula.chave = CHAVE_INVALIDA;
    return celula;
}

int main()
{

    ListaLinear *lls;
    int resultado;
    lls = (ListaLinear *)malloc(sizeof(ListaLinear));
    resultado = criarListaVaziaL(lls);
    Celula cls;
    int i;
    for (i = 0; i < 5; i++)
    {
        cls.chave = i;
        scanf("%d", &cls.dado);
        //mostrarCelula(cls);
        inserirInicio(lls, cls);
    }
    printf("Chave       Dado\n");
    mostrarLista(lls);
    Celula p;
    printf("\nposicao = %d %d", consultaListaPosicao(lls, 4), lls->celulas[4]);
    printf("\nchave = %d %d", consultaListaChave(lls, cls), lls->celulas[4].chave);
    printf("\ntamanho da lista = %d", tamanhoLista(lls));

    printf("\n inserindo no final da lista\n");
    for (i = 0; i < 5; i++)
    {
        cls.chave = i;
        scanf("%d", &cls.dado);
        //mostrarCelula(cls);
        inserirFinal(lls, cls);
    }
    printf("Chave       Dado\n");
    mostrarLista(lls);
    return 0;
}