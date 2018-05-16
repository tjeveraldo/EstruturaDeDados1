#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <windows.h> 

#define TAM_PLACA 9

typedef struct carro {
    char placa[TAM_PLACA];
} t_carro;

typedef struct no {
    t_carro carro;
    struct no * prox;
} t_no;

typedef struct fila {
    t_no * inicio;
    int quant_elementos;
    t_no * fim;
} t_fila;



t_fila * criarCabecaFila() {
    t_fila * fila = (t_fila *) malloc(sizeof(t_fila));

    if(fila) {
        fila->inicio = NULL;
        fila->quant_elementos = 0;
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

int filaItsVazia(t_fila * fila) {
    return fila->quant_elementos == 0;
}

int inserir(t_fila * fila, t_carro novo_carro) {
    t_no * novo_no = criarNo();

    if(novo_no == NULL)
        return 0;

    novo_no->carro = novo_carro;

    if(filaItsVazia(fila))
        fila->inicio = novo_no;

    else
        (fila->fim)->prox = novo_no;

    fila->fim = novo_no;
    fila->quant_elementos++;

    return 1;
}

t_carro remover(t_fila * fila) {
    t_carro carro_a_remover = {""};
    t_no * aux;

    if(filaItsVazia(fila))
        return carro_a_remover;

    carro_a_remover = (fila->inicio)->carro;

    if(fila->inicio == fila->fim)
        fila->fim = NULL;

    aux = fila->inicio; 

    fila->inicio = (fila->inicio)->prox;

    free(aux);

    --(fila->quant_elementos);

    return carro_a_remover;
}



void exibirCabecalho() {
    int i = 0;

    for(i = 0; i < 32; i++)
        printf("-");

    printf("\n");

    printf("ALUNO: JOSE EVERALDO GOMES BEZERRA FILHO\n");
    printf("DISCIPLINA: ESTRUTUA DE DADOS I\n");
    printf("PROFESSOR: WALACE BONFIM\n");


    for(i = 0; i < 32; i++)
        printf("-");

    printf("\n\n");
}

void formataPlaca(char placa[]) {
    char aux[1] = "";
    int i = strlen(placa);

    for(; i > 2; i--) {
        aux[0] = placa[i];
        placa[i + 1] = aux[0];
    }

    placa[3] = '-';
}

t_carro receberPlaca() {
    char placa[TAM_PLACA] = "";
    t_carro novo_carro = {""};

    while(1) {
        printf("Informe a placa do carro (ex.: exe0222): ");
        scanf("%s", placa);

        if(strlen(placa) < 7 || strlen(placa) > 7)
            printf("\n>> Informe uma placa com ate 7 caraceteres!\n\n");

        else
            break;

        getchar();
    }

    formataPlaca(placa);

    strcpy(novo_carro.placa, strupr(placa)); 

    return novo_carro;

    system("cls");
}

void statusTransito(t_fila * filaA, t_fila * filaB, int semafA, int semafB) {
    printf("--------------------------------------------\n");
    printf("          COMO TA O TRANSITO\n");
    printf("--------------------------------------------\n\n");

    printf(semafA == 1 ? "     Sinal A: ABERTO\n" : "     Sinal A: FECHADO\n");
    printf(semafB == 1 ? "     Sinal B: ABERTO\n" : "     Sinal B: FECHADO\n");

    printf("     Quantos carros no semaforo A: %d\n", filaA->quant_elementos);
    printf("     Quantos carros no semaforo B: %d\n", filaB->quant_elementos);

    printf("\n--------------------------------------------\n");

    system("pause");

    system("cls");
}

void trocaSemaforos(int * semafA, int * semafB) {
    int semaforo_aux = 0;

    semaforo_aux = *semafA;
    *semafA = *semafB;
    *semafB = semaforo_aux;
}

int main() {
    int opcao = 0, i = 0, semaforoA = 1, semaforoB = 0; 
    t_fila * m_filaA = criarCabecaFila();
    t_fila * m_filaB = criarCabecaFila();
    t_carro novo_carro;

    srand(time(NULL)); 

    while(1) {
        for(i = 0; i < 10; i++) {
            exibirCabecalho();

            printf("Conta de iteracoes: %d\n\n", i + 1);

            opcao = rand() % 3; 

            switch (opcao) {
                case 0:
                    printf("++ Entra carro na rua A ++\n");
                    novo_carro = receberPlaca();
                    inserir(m_filaA, novo_carro);
                    break;

                case 1:
                    printf("++ Entra carro na rua B ++\n");
                    novo_carro = receberPlaca();
                    inserir(m_filaB, novo_carro);
                    break;
            }

            if(semaforoA == 1) {
                if( ! filaItsVazia(m_filaA) ) {
                    printf("\n-------------------------------------\n");
                    printf("   Carro passa no semaforo A (VERDE)   \n");
                    printf("--------------------------------------\n\n");
                    remover(m_filaA);
                }
            }

            else if(semaforoB == 1) { 
                if( ! filaItsVazia(m_filaB) ) {
                    printf("\n-------------------------------------\n");
                    printf("   Carro passa no semaforo B (VERDE)   \n");
                    printf("--------------------------------------\n\n");
                    remover(m_filaB);
                }
            }

            statusTransito(m_filaA, m_filaB, semaforoA, semaforoB);

        }
        trocaSemaforos(&semaforoA, &semaforoB); 
    }

    return 0;
}
