#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define false 0
#define true 1

/**
 * criei este tipo para se parecer com um boolean 
 * utilizado na função com retorno int 
 * e utilizar as define false e true 
 * */

typedef int boolean;
//typedef int TIPOCHAVE;

/** 
 *  struct para armazenar os dados de um paciente
 *  chave é o dado principal do paciente (identificador do paciente)
 *  será usado para procuarar um paciente
 *  aqui pode ser criado outros dados
 *  pode inserir uma nova struct, ENDERECO por exemplo
 * */

typedef struct
{
    int chave;
    int dado; // dado e uma informacao qualquer do paciente, aqui utilizei para ordenar a lista de pacientes
              // foi utilizado para localizar onde inserir um novo paciente ordenado
              // a ordenacao pode ocorrer por outro valor: chave, nome
    char nome[40];

} PACIENTE;

/* essa struct aux contem um registro de um paciente
   e um ponteiro *prox que servirá para percorrer uma lista de pacientes
 */
typedef struct aux
{
    PACIENTE p;
    struct aux *prox;
} REGISTRO;

/* PONT é um ponteiro para o inicio da lista */
typedef REGISTRO *PONT;

typedef struct
{
    PONT inicio;
} LISTAPACIENTES;
/* Inicializa a lista atribuindo NULL para o inicio da lista, ou seja, uma lista sem elementos */
void inicializarLista(LISTAPACIENTES *lst)
{
    printf("Lista Criada!\n");
    lst->inicio = NULL;
}
/* para mostrar o tamanho da lista */
int tamanho(LISTAPACIENTES *lst)
{
    PONT end = lst->inicio;
    int tam = 0;
    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }
}
/* Para exibir a lista de pacientes: aqui por enquanto a chave, o dado e o nome do paciente */
void exibirListaPacientes(LISTAPACIENTES *lst)
{
    PONT end = lst->inicio;
    while (end != NULL)
    {
        printf("%i        %d       %s\n", end->p.chave, end->p.dado, end->p.nome);
        end = end->prox;
    }
}

PONT buscaSequencial(LISTAPACIENTES *lst, int ch)
{
    PONT pos = lst->inicio;
    while (pos != NULL)
    {
        if (pos->p.chave == ch)
            return pos;
    }
    return NULL;
}

PONT buscaSeqencialOrdenada(LISTAPACIENTES *lst, int ch)
{
    PONT pos = lst->inicio;
    while (pos != NULL && pos->p.chave == ch)
        return pos;

    return NULL;
}
/* localiza na lista de pacientes - aqui foi utilizado p.dado da struct paciente - qual posicao sera inserido o novo paciente 
*  se o dado ja existir return NULL e nao insere o novo paciente com a chave repetida
*  precisa implementar um retorno informando que aquela chave (ou paciente) ja esta cadastrado
*/
PONT buscaSequencialExc(LISTAPACIENTES *lst, int d, PONT *ant)
{
    *ant = NULL;
    PONT atual = lst->inicio;
    while ((atual != NULL) && (atual->p.dado < d))
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->p.dado == d))
        return atual;
    return NULL;
}
/* funcao que vai inserir um paciente na LISTAPACIENTES, recebe como parâmetros uma lista 
*  e um registro completo de um paciente, ou seja todos os dados dentro da struct PACIENTE 
*/
boolean inserirPacienteListaOrdenada(LISTAPACIENTES *lst, PACIENTE paciente)
{
    int ch = paciente.chave;
    int d = paciente.dado;
    PONT ant, i;
    i = buscaSequencialExc(lst, d, &ant);
    if (i != NULL)
        return false;
    i = (PONT)malloc(sizeof(REGISTRO));
    i->p = paciente;
    if (ant == NULL)
    {
        i->prox = lst->inicio;
        lst->inicio = i;
    }
    else
    {
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
}
/*apaga toda a lista  */

void reinicializarLista(LISTAPACIENTES *lst)
{
    PONT fim = lst->inicio;
    while (fim != NULL)
    {
        PONT apagar = fim;
        fim = fim->prox;
        free(apagar);
    }
    lst->inicio = NULL;
    printf("\nLISTA VAZIA\n");
}
/* exclui um paciente da lista e libera memoria
* primeiro procura na lista se o paciente existe
*/
boolean excluirPacienteLista(LISTAPACIENTES *lst, int ch)
{
    PONT ant, i;
    i = buscaSequencialExc(lst, ch, &ant);
    if (i == NULL)
        return false;
    if (ant == NULL)
        lst->inicio = i->prox;
    else
        ant->prox = i->prox;
    free(i);
}

int main()
{
    LISTAPACIENTES *lst;
    inicializarLista(lst);
    PACIENTE p;
    int i;
    for (i = 1; i <= 5; i++)
    {
        p.chave = i;
        scanf("%d", &p.dado);
        scanf("%s", &p.nome);
        inserirPacienteListaOrdenada(lst, p);
    }

    printf("\nchave      dado       paciente\n");
    exibirListaPacientes(lst);
    reinicializarLista(lst);
    exibirListaPacientes(lst);

    return 0;
}
