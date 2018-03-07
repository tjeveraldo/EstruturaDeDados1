#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct contatos {
    char nome[50];
    char numero1[15];
    char numero2[15];
} t_contato;

typedef struct agenda {
    t_contato vetor_contatos[MAX];
    int indice_ultimo_contato; 
} t_agenda;




t_agenda criarAgenda() {
    t_agenda agenda;

    agenda.indice_ultimo_contato = -1;

    return agenda;
}

int getTamanho(t_agenda * agenda) {
  return agenda->indice_ultimo_contato + 1;
}

int isCheia(t_agenda * agenda) {
    return ( agenda->indice_ultimo_contato == (MAX - 1) );
}

int isVazia(t_agenda * agenda) {
    return (agenda->indice_ultimo_contato == -1);
}

t_contato * getContato(t_agenda * agenda, int indice_contato_procurado) {
  if(indice_contato_procurado > agenda->indice_ultimo_contato) {
    return 0;
  }

  return &(agenda->vetor_contatos[indice_contato_procurado]);
}

int compara(t_contato contato_vetor_agenda, t_contato contato_procurado) {
    return strcmp(contato_vetor_agenda.nome, contato_procurado.nome);
}

int getPosicaoContato(t_agenda * agenda, t_contato contato) {
    int i = 0;

    for(i = 0; i <= agenda->indice_ultimo_contato; i++)
        if(compara(agenda->vetor_contatos[i], contato) == 0)
            return i;

    return -1; 
}

int deslocaDireita(t_agenda * agenda, int indice) {
    int i = 0;

    for(i = agenda->indice_ultimo_contato + 1; i > indice; i--)
        agenda->vetor_contatos[i] = agenda->vetor_contatos[i - 1];

    return 1;
}

int inserirContatos(t_agenda * agenda, int indice_da_insercao, t_contato contato) {
    if( isCheia(agenda) || indice_da_insercao > (agenda->indice_ultimo_contato + 1) || indice_da_insercao < 0 ) {
        return 0;
    }

    deslocaDireita(agenda, indice_da_insercao);

    agenda->vetor_contatos[indice_da_insercao] = contato;

    (agenda->indice_ultimo_contato)++;

    return 1;
}

void solicitaDadosNovoContato(t_contato * contato) {
    char resposta_inserir_numero2 = 'n';

    printf("--- Novo contato ---");

    printf("\nNome: ");
    scanf("%s", contato->nome);

    printf("Numero 01: ");
    scanf("%s", contato->numero1);

    getchar(); 

    printf("Deseja inserir outro numero ('s' ou 'n')? ");
    scanf("%c", &resposta_inserir_numero2);

    if(resposta_inserir_numero2 == 's') {
        printf("Numero 02: ");
        scanf("%s", contato->numero2);
    } else {
        strcpy(contato->numero2, "---");
    }

    puts("");
}

int deslocaEsquerda(t_agenda * agenda, int indice_contato_removido) {
    int i = 0;

    for(i = 0; i < (agenda->indice_ultimo_contato); i++)
        agenda->vetor_contatos[i] = agenda->vetor_contatos[i + 1];

    return 1;
}

int removerContato(t_agenda * agenda, int indice_contato_remover) {
    if(indice_contato_remover > agenda->indice_ultimo_contato || indice_contato_remover < 0) {
        return 0;
    }

    deslocaEsquerda(agenda, indice_contato_remover);

    (agenda->indice_ultimo_contato)--;

    return 1;
}

int main() {
    t_agenda m_agenda01; 
    t_contato m_contato;
    int quant_contatos = 0;
    int i = 0;

    m_agenda01 = criarAgenda();


    printf("Informar quantos contatos deseja adicionar: ");
    scanf("%d", &quant_contatos);

    for(i = 0; i < quant_contatos; i++) {
        solicitaDadosNovoContato(&m_contato);

        inserirContatos(&m_agenda01, i, m_contato);
    }

     for(i = 0; i < getTamanho(&m_agenda01); i++) {
        printf("\n----- CONTATOS -----\n");
        printf("Nome: %s\n", getContato(&m_agenda01, i)->nome);
        printf("Telefone 1: %s\n", getContato(&m_agenda01, i)->numero1);
        printf("Telefone 2: %s\n", getContato(&m_agenda01, i)->numero2);
    }

    
    printf("\n----- REMOVA CONTATO -----\n");
    printf("Nome do contato que deseja excluir: ");
    scanf("%s", m_contato.nome);
    int posicao_contato = getPosicaoContato(&m_agenda01, m_contato);
    removerContato(&m_agenda01, posicao_contato);

 
    for(i = 0; i < getTamanho(&m_agenda01); i++) {
        printf("----- CONTATOS -----\n");
        printf("Nome: %s\n", getContato(&m_agenda01, i)->nome);
        printf("Telefone 1: %s\n", getContato(&m_agenda01, i)->numero1);
        printf("Telefone 2: %s\n", getContato(&m_agenda01, i)->numero2);
    }

 
    printf("\n----- ATUALIZAR CONTATO -----\n");
    printf("\nInforme o nome do contato: ");
 
    return 0;
}
