#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definição da estrutura da tarefa
typedef struct Task {
    char id[50];
    int priority;
    struct Task *next;
} Task;

// Função para criar uma nova tarefa
Task* new_task(char id[], int priority) {
    Task *newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strcpy(newTask->id, id);
    newTask->priority = priority;
    newTask->next = NULL;
    return newTask;
}

// Função para inserir uma nova tarefa na lista
Task* insert_task(Task *head, Task *newTask) {
    if (head == NULL || newTask->priority > head->priority) {
        newTask->next = head;
        return newTask;
    }
    Task *current = head;
    while (current->next != NULL && current->next->priority >= newTask->priority) {
        current = current->next;
    }
    newTask->next = current->next;
    current->next = newTask;
    return head;
}

// Função para listar tarefas de uma determinada prioridade ou superior
void list_tasks(Task *head, int priority) {
    Task *current = head;
    while (current != NULL) {
        if (current->priority >= priority) {
            printf("Task: %s, Priority: %d\n", current->id, current->priority);
        }
        current = current->next;
    }
}

// Função para completar uma tarefa
Task* complete_task(Task *head, char id[]) {
    Task *current = head;
    Task *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("TAREFA INEXISTENTE\n");
    return head;
}

// Função para liberar a memória alocada para as tarefas
void free_tasks(Task *head) {
    Task *current = head;
    while (current != NULL) {
        Task *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Task *head = NULL;

    // Exemplo de uso
    head = insert_task(head, new_task("tarefa1", 2));
    head = insert_task(head, new_task("tarefa2", 5));
    head = insert_task(head, new_task("tarefa3", 3));

    printf("Lista de tarefas com prioridade maior ou igual a 3:\n");
    list_tasks(head, 3);

    printf("\nCompletando a tarefa 'tarefa2':\n");
    head = complete_task(head, "tarefa2");

    printf("\nLista de tarefas com prioridade maior ou igual a 3 após completar a 'tarefa2':\n");
    list_tasks(head, 3);

    // Liberando memória alocada
    free_tasks(head);

    return 0;
}
