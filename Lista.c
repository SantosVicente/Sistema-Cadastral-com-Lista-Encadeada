#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


//Tipo criado para representar um nó / elemento da lista
typedef struct _node {

    int valor; //valor inteiro armazenado no nó

    struct _node *prox; //ponteiro para o próximo nó

} Node;


//Tipo criado para representar a lista encadeada
typedef struct
{
    Node *inicio; //ponteiro para o primeiro nó da lista
    Node *fim;    //ponteiro para o último nó da lista

} Lista;


Lista* cria_lista()
{
    //cria a lista vazia
    Lista *lista= (Lista*) malloc(sizeof(Lista));
    if(lista == NULL)
    {
        printf("\nErro ao alocar memória para a lista\n");
        exit(1); //finaliza o programa retornando código de erro 1
    }

    //inicializa os elementos da lista com null indicando que ela está vazia!
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

void destroi_lista(Lista *lista)
{
     //não faz nada pois a lista nao foi criada
    if(lista == NULL) return;

    //não faz nada pois a lista esta vazia
    if(lista->inicio == NULL) return;

    //usado para acessar um nó da lista
    Node *node;

    //enquanto o inicio da lista apontar para um nó
    while(lista->inicio != NULL)
    {
        //recupera o primeiro elemento da lista
        node = lista->inicio;

        //faz com que o próximo elemento seja o primeiro elemento da lista;
        lista->inicio = node->prox;

        //remove o nodo da lista
        free(node);
    }

    //libera a memória da variável que representa a lista
    free(lista);
}

void insere_lista_inicio(Lista *lista, int valor)
{
    //cria o nodo da lista
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
    {
        printf("\nErro ao alocar memória para o nó da lista\n");
        exit(1);  //finaliza o programa retornando código de erro 1
    }

    //insere o valor no nó da lista
    node->valor = valor;

    //o proximo aponta para onde a lista aponta
    node->prox = lista->inicio;

    //caso seja o primeiro elemento a ser inserido na lista
    //ele também passa a ser o último!!!
    if(lista->inicio == NULL)
    {
        lista->fim = node;
    }

    //o inicio da lista para a apontar para o nó
    lista->inicio = node;
}

void imprime_lista(Lista *lista)
{
    //não faz nada pois a lista não foi criada
    if(lista == NULL) return;

    //não faz nada pois a lista está vazia
    if(lista->inicio == NULL)
    {
        printf("lista vazia!\n");
        return;
    }

    //usado para acessar um nó da lista
    Node *node;

    //percorre todos os nós da lista
    for(node = lista->inicio; node != NULL; node = node->prox)
    {
        //imprime o valor inteiro salvo no nó
        printf("%d", node->valor);

        //se for o ultimo elemento da lista imprime um ponto e virgula e pula uma linha
        if(node->prox == NULL)
        {
            printf(";\n");
        }
        //se não for o último elemento da lista imprime uma virgula e um espaço
        else
        {
            printf(", ");
        }
    }

}

int remove_lista(Lista *lista, int valor)
{
    //não faz nada pois a lista não foi criada
    if(lista == NULL) return 0;

    //não faz nada pois a lista está vazia
    if(lista->inicio == NULL) return 0;

    //usados para acessar um nó da lista e o seu nó anterior
    Node *prev, *pos;

    //percorre a lista procurando o valor
    for(pos = lista->inicio; pos != NULL; prev=pos, pos=pos->prox)
    {
        //se encontrar o valor em um nó da lista
        if(pos->valor == valor)
        {
            //se a lista possui apenas um nó
            if(lista->inicio == lista->fim)
            {
                //inicializa a lista como vazia
                lista->inicio = NULL;
                lista->fim = NULL;
            }
            //se a lista possuir mais de um nó
            else
            {
                //se o elemento está no início da lista
                if(pos == lista->inicio)
                {
                    //o segundo elemento passa a ser o início da lista
                    lista->inicio = pos->prox;
                }
                //se o elemento está no fim da lista
                else if(pos == lista->fim)
                {
                    lista->fim = prev; //o final da lista passa apontar para o penúltimo nó;
                    prev->prox = NULL;  //o penúltimo nodo passa a ser o último nó;
                }
                //se resta o elemento estar no meio da lista !!!
                else
                {
                    //o proximo do nó anterior passa a ser o proximo do nó encontrado;
                    prev->prox = pos->prox;
                }
            }

            //libera a memória ocupada pelo nó
            free(pos);

            //retorna 1 (true) indicando que encontrou e removeu o elemento da lista
            return 1;

        } // fim do if que encontrou o elemento

    } //fim do for

    //se chegou nesse ponto quer dizer que a lista foi inteiramente percorrida
    //e não foi encotrado o valor que queremos remover da lista (retorna 0 - false)
    return 0;


}

void insere_lista_fim(Lista *lista, int valor)
{

    //cria o nó da lista
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
    {
        printf("\nErro ao alocar memória para o nó da lista\n");
        exit(1); //finaliza o programa retornando código de erro 1
    }

    //insere o valor no nó da lista
    node->valor = valor;

    //esse nodo é o último elemento da lista, ou seja
    //não tem nenhum elemento após ele!!!!
    node->prox = NULL;

    //caso seja o primeiro elemento a ser inserido na lista
    //ele também passa a ser o último!!!
    if(lista->inicio == NULL)
    {
        lista->inicio = node; //início da lista aponta para o nó
        lista->fim  = node;
    }
    //já possui elementos
    else
    {
        //o último nó da lista passa a apontar para o novo nó
        lista->fim->prox = node;

        //o fim da lista passa a apontar para o nó
        lista->fim = node;
    }
}


int main()
{
    setlocale(LC_ALL, "");

    Lista *lista;

    lista = cria_lista();

    /*insere_lista_inicio(lista, 1);
    insere_lista_inicio(lista, 2);
    insere_lista_inicio(lista, 3);
    insere_lista_inicio(lista, 4);
    imprime_lista(lista);*/

    /*insere_lista_fim(lista, 1);
    insere_lista_fim(lista, 2);
    insere_lista_fim(lista, 3);
    insere_lista_fim(lista, 4);
    imprime_lista(lista);*/


    /*insere_lista_fim(lista, 3);
    insere_lista_fim(lista, 4);
    insere_lista_inicio(lista, 2);
    insere_lista_fim(lista, 5);
    insere_lista_inicio(lista, 1);
    insere_lista_fim(lista, 6);
    imprime_lista(lista);*/


    /*insere_lista_fim(lista, 1);
    insere_lista_fim(lista, 2);
    insere_lista_fim(lista, 2);
    insere_lista_fim(lista, 3);
    imprime_lista(lista);
    remove_lista(lista, 2);
    remove_lista(lista, 3);
    imprime_lista(lista);*/

    destroi_lista(lista);

    printf("\nFim da execução!\n");
    return 0;
}
