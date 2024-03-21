#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRIORIDADE 5
#define MIN_PRIORIDADE 0

typedef struct Tarefa {
    char id[100];
    int prioridade;
    time_t dataCriacao;
    struct Tarefa *proximo;
} Tarefa;

// Array de listas para tarefas, uma para cada nível de prioridade
Tarefa *listasTarefas[MAX_PRIORIDADE + 1] = {NULL};

void adicionarTarefa(int prioridade, char *id) {
    if (prioridade < MIN_PRIORIDADE || prioridade > MAX_PRIORIDADE) {
        printf("Prioridade inválida. Deve ser entre %d e %d.\n", MIN_PRIORIDADE, MAX_PRIORIDADE);
        return;
    }

    // Criar nova tarefa
    Tarefa *novaTarefa = (Tarefa *)malloc(sizeof(Tarefa));
    strcpy(novaTarefa->id, id);
    novaTarefa->prioridade = prioridade;
    novaTarefa->dataCriacao = time(NULL);
    novaTarefa->proximo = NULL;

    // Adicionar tarefa na lista correspondente
    if (listasTarefas[prioridade] == NULL) {
        listasTarefas[prioridade] = novaTarefa;
    } else {
        // Adiciona no início para simplicidade
        novaTarefa->proximo = listasTarefas[prioridade];
        listasTarefas[prioridade] = novaTarefa;
    }

    printf("Tarefa '%s' adicionada com prioridade %d.\n", id, prioridade);
}

void listarTarefas(int prioridadeMinima) {
    for (int i = MAX_PRIORIDADE; i >= prioridadeMinima; i--) {
        Tarefa *atual = listasTarefas[i];
        printf("Prioridade %d:\n", i);
        while (atual != NULL) {
            printf("\tID: %s, Data de Criação: %ld\n", atual->id, atual->dataCriacao);
            atual = atual->proximo;
        }
    }
}

void completarTarefa(char *id) {
    Tarefa *tarefaAnterior = NULL;
    int encontrou = 0;

    for (int i = 0; i <= MAX_PRIORIDADE; i++) {
        Tarefa *atual = listasTarefas[i];
        while (atual != NULL) {
            if (strcmp(atual->id, id) == 0) {
                encontrou = 1;
                if (tarefaAnterior == NULL) {
                    // Tarefa está no início da lista
                    listasTarefas[i] = atual->proximo;
                } else {
                    tarefaAnterior->proximo = atual->proximo;
                }
                free(atual);
                printf("Tarefa '%s' completada e removida.\n", id);
                break;
            }
            tarefaAnterior = atual;
            atual = atual->proximo;
        }
        if (encontrou) break;
    }

    if (!encontrou) {
        printf("TAREFA INEXISTENTE.\n");
    }
}

int main() {
    char comando[50];
    char idTarefa[100];
    int prioridade;

    while (1) {
        printf("Digite um comando (new, list, complete) ou 'sair' para terminar: ");
        scanf("%s", comando);

        if (strcmp(comando, "sair") == 0) {
            break;
        } else if (strcmp(comando, "new") == 0) {
            printf("Digite a prioridade e o ID da nova tarefa: ");
            scanf("%d %s", &prioridade, idTarefa);
            adicionarTarefa(prioridade, idTarefa);
        } else if (strcmp(comando, "list") == 0) {
            printf("Digite a prioridade mínima para listar: ");
            scanf("%d", &prioridade);
            listarTarefas(prioridade);
        } else if (strcmp(comando, "complete") == 0) {
            printf("Digite o ID da tarefa a ser completada: ");
            scanf("%s", idTarefa);
            completarTarefa(idTarefa);
        } else {
            printf("Comando desconhecido.\n");
        }
    }

    return 0;
}
