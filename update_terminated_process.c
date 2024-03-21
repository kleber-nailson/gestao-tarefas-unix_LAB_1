#include <stdio.h>
#include <stdbool.h>

typedef struct Processo {
    int pid;
    int tempoFim;
    struct Processo *proximo;
} Processo;

void update_terminated_process(Processo *lista, int pid, int tempoFim) {
    Processo *atual = lista;
    while (atual != NULL) {
        if (atual->pid == pid) {
            atual->tempoFim = tempoFim;
            printf("Processo %d atualizado com tempo de término %d.\n", pid, tempoFim);
            return;
        }
        atual = atual->proximo;
    }
    printf("Processo com PID %d não encontrado.\n", pid);
}
