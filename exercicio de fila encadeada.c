#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 30

typedef struct pessoa {
    char nome[TAM_NOME];
} t_p;

typedef struct no {
    t_p pessoa;
    struct no * prox;
} t_no;

typedef struct fila {
    int qnt_elementos;
    t_no * inicio;
    t_no * fim;
} t_f;


t_f * criarCabeca() {
    t_f * fila = (t_f *) malloc(sizeof(t_f));

    if(fila) {
        fila->inicio = NULL;
        fila->qnt_elementos = 0;
        fila->fim = NULL;
    }

    return fila;
}

t_no * criarNo() {
    t_no * no = (t_no *) malloc((sizeof(t_no)));

    if(no)
        no->prox = NULL;

    return no;
}

int filaItsVazia(t_f fila) {
    return fila.qnt_elementos == 0;
}

int inserirPessoa(t_f * fila, t_p pessoa_nova) {
    t_no * novo = criarNo();

    if(novo == NULL)
        return 0;

    novo->pessoa = pessoa_nova;

    if(filaItsVazia(*fila))
        fila->inicio = novo;

    else
        (fila->fim)->prox = novo;

    fila->fim = novo;
    fila->qnt_elementos++;

    return 1;
}

t_p removerPessoa(t_f * fila) {
    t_p pessoa_remover = {""};
    t_no * aux;

    if(filaItsVazia(*fila))
        return pessoa_remover;

    pessoa_remover = (fila->inicio)->pessoa;

    if(fila->inicio == fila->fim)
        fila->fim = NULL;

    aux = fila->inicio;

    fila->inicio = (fila->inicio)->prox;

    free(aux);

    --(fila->qnt_elementos);

    return pessoa_remover;
}

void exibirFila(t_f fila) {
    t_no * aux = fila.inicio;
    int i = 0;

    if(filaItsVazia(fila)) {
        printf(">> A fila esta vazia.\n");
        return;
    }

    printf("\nFILA: \n");
    while(aux != NULL) {
        printf("%do = %s\n", i + 1, aux->pessoa.nome);
        aux = aux->prox;
        i++;
    }

}

int entramPessoas(t_f * fila) {
    int i = 0;
    t_p nova_pessoa;

    printf("--- ENTRANDO PESSOAS NA FILA ---\n");
    for(; i < 4; i++) {
        printf("\n%do da fila: ", i + 1);
        scanf("%s", nova_pessoa.nome);

        getchar();

        inserirPessoa(fila, nova_pessoa);

        exibirFila(*fila);
    }

    system("pause");
    system("cls");

    return 1;
}

int saemPessoas(t_f * fila) {
    int i = 0;
    t_p nova_pessoa;

    if(filaItsVazia(*fila)) {
        printf(">> Nao ha pessoas para execluir.\n");
        return 0;
    }

    printf("--- SAINDO PESSOAS DA FILA ---\n\n");
    for(; i < 3; i++) {
        printf("Pessoa que esta saindo da fila: %s\n", removerPessoa(fila).nome);

        exibirFila(*fila);
    }

    system("pause");
    system("cls");

    return 1;
}


int main() {

    t_f * main_fila = criarCabeca(); 

    entramPessoas(main_fila); 

    saemPessoas(main_fila); 

    entramPessoas(main_fila); 

    return 0;
}
