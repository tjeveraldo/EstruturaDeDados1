#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 30
#define MAX_PESSOAS 5

typedef struct p {
    char nome[TAM_NOME];
} t_p;

typedef struct f {
    t_p vetor[MAX_PESSOAS];
    int inicio;
    int fim;
    int qnt_elementos;
} t_f;

t_f criarFila() {
    t_f fila;

    fila.qnt_elementos = 0;
    fila.inicio = 0;
    fila.fim = -1;

    return fila;
}

int filaItsVazia(t_f fila) {
    return fila.qnt_elementos == 0;
}

int filaItsCheia(t_f fila) {
    return (fila.qnt_elementos == MAX_PESSOAS);
}

int inserirPessoa(t_f * fila, t_p pessoa_nova) {
    if(filaItsCheia(*fila))
        return 0;

    fila->fim = (fila->fim + 1) % MAX_PESSOAS;
    fila->vetor[fila->fim] = pessoa_nova;
    (fila->qnt_elementos)++;

    return 1;
}

t_p removerPessoa(t_f * fila) {
    t_p pessoa_remover = {""};

    if(filaItsVazia(*fila))
        return pessoa_remover;

    pessoa_remover = fila->vetor[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_PESSOAS;
    --(fila->qnt_elementos);

    return pessoa_remover;
}

void exibirFila(t_f fila) {
    int i = 0, index = 0;

    if(filaItsVazia(fila)) {
        printf(">> A fila esta vazia.\n");
        return;
    }

    printf("\nFILA: \n");
    for(i = 0, index = fila.inicio; i < fila.qnt_elementos; i++, index = (fila.inicio + i) % MAX_PESSOAS) {

        printf("%do = %s\n", i + 1, fila.vetor[index].nome);

    }

}

int entramPessoas(t_f * fila) {
    int i = 0;
    t_p nova_pessoa;

    printf("--- ENTRANDO PESSOAS NA FILA ---\n");
    for(; i < 4; i++) {
        if(filaItsCheia(*fila)) {
            printf(">> Nao ha mais espaco na fila.\n");
            return 0;
        }

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
    t_f main_fila = criarFila(); 
    entramPessoas(&main_fila); 

    saemPessoas(&main_fila); 
    entramPessoas(&main_fila); 

    return 0;
}
