#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VICENTE DOS SANTOS SILVA && VICTOR SAMUEL DOS SANTOS

typedef struct no
{
    char nome[64];
    float nota;
    int matricula;
    float frequencia;
    char turma[8];
    struct no *proximo;
} No;

typedef struct
{
    No *inicio;
    No *fim;
} Lista;

Lista *cria_lista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    if (lista == NULL)
    {
        printf("\nMemoria insuficiente!\n");
        exit(1);
    }

    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

void verificarAluno(Lista *lista, int mat, int *verif)
{
    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->matricula != mat)
        {
            continue;
        }

        if (node->matricula == mat)
        {
            *verif = 0;
        }
    }
}

void insereAluno(Lista *lista, int mat, char name[], float note, float freq, char class[])
{
    if (lista == NULL)
        return;

    No *novo = (No *)malloc(sizeof(No));

    if (lista->inicio == NULL)
    {
        lista->fim = novo;
    }

    if (novo)
    {
        strcpy(novo->nome, name);
        novo->nota = note;
        novo->matricula = mat;
        novo->frequencia = freq;
        strcpy(novo->turma, class);

        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    else
    {
        printf("Erro ao alocar memória!!");
        exit(1);
    }
}

void destroi_lista(Lista *lista)
{

    if (lista == NULL)
        return;

    if (lista->inicio == NULL)
        return;

    No *node;

    while (lista->inicio != NULL)
    {
        node = lista->inicio;
        lista->inicio = node->proximo;
        free(node);
    }

    free(lista);
}

void imprime(Lista *lista)
{

    if (lista == NULL)
    {

        printf("lista nao criada!\n");
        return;
    }

    if (lista->inicio == NULL)
    {
        printf("lista vazia!\n");
        return;
    }

    No *novo;

    for (novo = lista->inicio; novo != NULL; novo = novo->proximo)
    {
        printf("\nNome: %s\n", novo->nome);
        printf("Nota: %.2f\n", novo->nota);
        printf("Matricula: %d\n", novo->matricula);
        printf("Frequencia: %.2f\n", novo->frequencia);
        printf("Turma: %s\n", novo->turma);

        if (novo->proximo == NULL)
        {
            printf("\nExibicao completa!\n");
        }
        else
        {
            printf("\n");
        }
    }
}

int remove_lista(Lista *lista, int mat)
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 0;

    No *before, *after;

    for (after = lista->inicio; after != NULL; before = after, after = after->proximo)
    {
        if (after->matricula == mat)
        {
            if (lista->inicio == lista->fim)
            {
                lista->inicio = NULL;
                lista->fim = NULL;
            }

            else
            {
                if (after == lista->inicio)
                {
                    lista->inicio = after->proximo;
                }

                else if (after == lista->fim)
                {
                    lista->fim = before;
                    before->proximo = NULL;
                }

                else
                {
                    before->proximo = after->proximo;
                }
            }

            return 1;
        }
    }

    return 0;
}

int ordenaNome(Lista *lista)
{
    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 3;

    if (lista->inicio == lista->fim)
    {
        return 2;
    }

    No *aux = (No *)malloc(sizeof(No));
    No *pi, *pj;

    for (pi = lista->inicio; pi != NULL; pi = pi->proximo)
    {
        for (pj = lista->inicio; pj != NULL; pj = pj->proximo)
        {
            if (strcmp(pi->nome, pj->nome) < 0)
            {
                strcpy(aux->nome, pj->nome);
                strcpy(pj->nome, pi->nome);
                strcpy(pi->nome, aux->nome);

                aux->matricula = pj->matricula;
                pj->matricula = pi->matricula;
                pi->matricula = aux->matricula;

                aux->frequencia = pj->frequencia;
                pj->frequencia = pi->frequencia;
                pi->frequencia = aux->frequencia;

                aux->nota = pj->nota;
                pj->nota = pi->nota;
                pi->nota = aux->nota;

                strcpy(aux->turma, pj->turma);
                strcpy(pj->turma, pi->turma);
                strcpy(pi->turma, aux->turma);
            }
        }
    }
    free(aux);
    return 1;
}

int mostrar_por_nota(Lista *lista)
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 4;

    if (lista->inicio == lista->fim)
    {
        return 2;
    }

    float menor_val = 999.0, maior_val = 0.0;
    float tmp_nota;
    char tmp_turm[8], tmp_nome[64];

    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->nota > maior_val)
        {
            maior_val = node->nota;
        }
        if (node->nota < menor_val)
        {
            menor_val = node->nota;
        }
    }

    if (menor_val == maior_val)
    {
        return 3;
    }

    printf("Alunos com a maior nota:\n");

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->nota == maior_val)
        {
            printf("\nNome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %s\n", node->turma);
        }
    }
    printf("\nAlunos com a menor nota:\n");

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (node->nota == menor_val)
        {
            printf("\nNome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %s\n", node->turma);
        }
    }

    return 1;
}

int pesquisar_por_nome(Lista *lista, char name[])
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 0;

    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {

        if (strcmp(node->nome, name) == 0)
        {
            printf("\nAluno encontrado!\n\n");
            printf("Nome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %s\n\n", node->turma);
            system("pause");

            return 1;
        }
    }
    return 0;
}

int pesquisar_por_matricula(Lista *lista, int mat)
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 0;

    No *node;

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {

        if (node->matricula == mat)
        {
            printf("\nAluno encontrado!\n\n");
            printf("Nome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %s\n\n", node->turma);
            system("pause");

            return 1;
        }
    }
    return 0;
}

int pesquisar_por_turma(Lista *lista, char turma[])
{

    if (lista == NULL)
        return 0;

    if (lista->inicio == NULL)
        return 2;

    int conf = 0;

    No *node;

    if (strcmp(turma, "Turma A") != 0 && strcmp(turma, "Turma B") != 0)
    {
        return 3;
    }

    for (node = lista->inicio; node != NULL; node = node->proximo)
    {
        if (strcmp(node->turma, turma) == 0)
        {
            printf("\nNome: %s\n", node->nome);
            printf("Nota: %.2f\n", node->nota);
            printf("Matricula: %d\n", node->matricula);
            printf("Frequencia: %.2f\n", node->frequencia);
            printf("Turma: %s\n", node->turma);
            conf = 1;
        }
        if (node->proximo == NULL && conf == 1)
        {
            printf("\n");
            system("pause");
            return 1;
        }
    }

    return 4;
}

int main()
{

    int menu = 0, i = -1, aux_mat, contador = 0, bolean_nota, remove, res1, res2, verif = 0, conf_tur = 0;
    float aux_nota, aux_freq;
    char aux_name[64], aux_turma[8];
    int achei, src;

    // criando a lista
    Lista *lista = cria_lista();

    while (menu != 8)
    {

        system("cls");
        printf("\n-------------------");
        printf("\nMenu");
        printf("\n-------------------");
        printf("\n1 - Cadastrar aluno");
        printf("\n2 - Remover aluno");
        printf("\n3 - Pesquisar aluno por nome");
        printf("\n4 - Pesquisar aluno por matricula");
        printf("\n5 - Mostrar todos os alunos de uma turma");
        printf("\n6 - Ordenar toda a lista de alunos pelo nome");
        printf("\n7 - Mostrar os alunos com a maior e menor nota");
        printf("\n8 - Sair");
        printf("\nQual opcao desejas seguir? R:");
        scanf("%d", &menu);
        system("cls");

        /*Cadastrar Aluno*/

        if (menu == 1)
        {
            printf("\nCadastro do Aluno\n\n");

            setbuf(stdin, NULL);
            printf("Digite o nome do aluno: ");
            gets(aux_name);

            bolean_nota = 0;

            while (bolean_nota == 0)
            {
                printf("\nDigite a nota do aluno: ");
                scanf("%f", &aux_nota); // aqui ele deve alocar no Nó da lista

                if (aux_nota < 0 || aux_nota > 10)
                {
                    printf("\n----------------------------------------------------");
                    printf("\n NOTA INVALIDA, DIGITE NOVAMENTE");
                    printf("\n----------------------------------------------------\n");
                }
                else
                {
                    bolean_nota = 1;
                }
            }

            printf("\nDigite a frequencia (em porcentagem): ");
            scanf("%f", &aux_freq);

            for (int conf = 0; conf != 1; conf = conf)
            {
                if (aux_freq < 0 || aux_freq > 100)
                {
                    printf("\n----------------------------------------------------");
                    printf("\n VALOR INVALIDO");
                    printf("\n----------------------------------------------------\n");
                    printf("\nDigite outro valor para frequencia(entre 0 e 100) : ");
                    scanf("%f", &aux_freq);
                }
                else
                {
                    conf = 1;
                }
            }

            setbuf(stdin, NULL);
            printf("\nDigite a turma do aluno (Turma A ou Turma B): ");
            gets(aux_turma);

            res1 = strcmp(aux_turma, "Turma A");
            res2 = strcmp(aux_turma, "Turma B");

            if (res1 == 0 || res2 == 0)
            {
                conf_tur = 0;
            }
            if (res1 != 0 && res2 != 0)
            {
                conf_tur = 1;
            }

            while (conf_tur == 1)
            {
                printf("\n----------------------------------------------------");
                printf("\n TURMA INVALIDA!");
                printf("\n----------------------------------------------------\n");
                setbuf(stdin, NULL);
                printf("\nDigite a turma do aluno (Turma A ou Turma B) :");
                gets(aux_turma);

                res1 = strcmp(aux_turma, "Turma A");
                res2 = strcmp(aux_turma, "Turma B");

                if (res1 == 0 || res2 == 0)
                {
                    conf_tur = 0;
                }
                if (res1 != 0 && res2 != 0)
                {
                    conf_tur = 1;
                }
            }

            while (verif == 0)
            {
                verif = 1;
                printf("\nDigite a matricula do aluno (entre 0 e 99999): ");
                scanf("%d", &aux_mat);
                if (aux_mat > 0 && aux_mat < 99999)
                {
                    verificarAluno(lista, aux_mat, &verif);

                    if (verif == 0)
                    {
                        printf("\n----------------------------------------------------");
                        printf("\n MATRICULA INVALIDA!");
                        printf("\n----------------------------------------------------\n");
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    printf("\n-------------------------------------------------------------------------");
                    printf("\n ESSE NUMERO DE MATRICULA E INVALIDO. INSIRA A MATRICULA NOVAMENTE");
                    printf("\n-------------------------------------------------------------------------\n");
                    verif = 0;
                }
            }

            verif = 0;
            contador++;

            insereAluno(lista, aux_mat, aux_name, aux_nota, aux_freq, aux_turma);

            printf("\n\nCadastro Realizado com Sucesso!\n");
            system("pause");
        }

        if (menu == 2)
        {
            achei = 0;
            printf("\nRemover Aluno\n\n");

            printf("Digite a matricula do aluno que voce deseja excluir : ");
            scanf("%d", &remove);

            achei = remove_lista(lista, remove);

            if (achei == 1)
            {
                printf("\n\n----------------------------------------------------");
                printf("\nAluno removido com sucesso!");
                printf("\n----------------------------------------------------\n");
                contador--;
                system("pause");
            }
            if (achei = 0)
            {
                printf("\n----------------------------------------------------");
                printf("\nNao foi possivel fazer a remocao, aluno nao encontrado!");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 3)
        {
            printf("\nPesquisar Aluno por Nome\n\n");

            printf("Digite o Nome do Aluno que deseja encontrar: ");
            setbuf(stdin, NULL);
            gets(aux_name);

            src = pesquisar_por_nome(lista, aux_name);

            if (src == 0)
            {
                printf("\n----------------------------------------------------");
                printf("\nO NOME INSERIDO NAO ESTA CADASTRADO");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 4)
        {

            printf("\nPesquisar Aluno por Matricula\n\n");

            printf("Digite a Matricula do Aluno que deseja encontrar: ");
            scanf("%d", &aux_mat);

            src = pesquisar_por_matricula(lista, aux_mat);

            if (src == 0)
            {
                printf("\n----------------------------------------------------");
                printf("\nA MATRICULA INSERIDA NAO ESTA CADASTRADA");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 5)
        {

            printf("\nMostrar todos os alunos de uma turma\n\n");

            printf("Digite a Turma (Turma A ou Turma B): ");
            setbuf(stdin, NULL);
            gets(aux_turma);

            src = pesquisar_por_turma(lista, aux_turma);

            if (src == 0)
            {
                printf("\n----------------------------------------------------");
                printf("\nA LISTA NAO FOI CRIADA");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
            if (src == 2)
            {
                printf("\n----------------------------------------------------");
                printf("\nA LISTA ESTA VAZIA");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
            if (src == 3)
            {
                printf("\n----------------------------------------------------");
                printf("\nA TURMA INSERIDA NAO EXISTE");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
            if (src == 4)
            {
                printf("\n----------------------------------------------------");
                printf("\nA TURMA INSERIDA NAO POSUI ALUNOS MATRICULADOS");
                printf("\n----------------------------------------------------\n");
                system("pause");
            }
        }

        if (menu == 6)
        {
            printf("\nOrdenar toda a lista de alunos pelo nome\n");

            src = ordenaNome(lista);

            if (src == 0)
            {
                printf("----------------------------------------------------");
                printf("\nOCORREU UM ERRO AO CRIAR A LISTA");
                printf("\n----------------------------------------------------\n");
            }

            if (src == 2)
            {
                printf("----------------------------------------------------");
                printf("\nNO MOMENTO SO HA UM ALUNO CADASTRADO.\nENTAO NAO EH POSSIVEL USAR ESTA OPCAO");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 3)
            {
                printf("----------------------------------------------------");
                printf("\nA LISTA ESTA VAZIA");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 1)
            {
                imprime(lista);
            }

            system("pause");
        }

        if (menu == 7)
        {
            printf("\nMostrar os alunos com a maior e menor nota\n");

            src = mostrar_por_nota(lista);

            printf("\n");

            if (src == 0)
            {
                printf("----------------------------------------------------");
                printf("\nOCORREU UM ERRO AO CRIAR A LISTA");
                printf("\n----------------------------------------------------\n");
            }

            if (src == 2)
            {
                printf("----------------------------------------------------");
                printf("\nNO MOMENTO SO HA UM ALUNO CADASTRADO.\nENTAO NAO EH POSSIVEL USAR ESTA OPCAO");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 3)
            {
                printf("----------------------------------------------------");
                printf("\nTODOS OS ALUNOS CADASTRADOS POSSUEM A MESMA NOTA.\nLOGO NAO EH POSSIVEL CLASSIFICA-LOS");
                printf("\n----------------------------------------------------\n\n");
            }

            if (src == 4)
            {
                printf("----------------------------------------------------");
                printf("\nA LISTA ESTA VAZIA");
                printf("\n----------------------------------------------------\n\n");
            }

            system("pause");
        }
    }

    destroi_lista(lista);
    printf("\nPrograma Finalizado!\nTenha um Bom dia!");

    return 0;
}
