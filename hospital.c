#include "hospital.h"

Paciente* cadastrarPaciente(Paciente **lista, int id, const char *nome, int idade, const char *endereco, const char *telefone) {
    Paciente *novo = (Paciente *)malloc(sizeof(Paciente));
    if (!novo) {
        printf("Erro ao alocar memória para paciente.\n");
        return NULL;
    }
    novo->id = id;
    strncpy(novo->nome, nome, MAX_NAME);
    novo->idade = idade;
    strncpy(novo->endereco, endereco, MAX_NAME);
    strncpy(novo->telefone, telefone, MAX_NAME);
    novo->prox = *lista;
    *lista = novo;
    return novo;
}

Medico* cadastrarMedico(Medico **lista, int id, const char *nome, const char *especialidade) {
    Medico *novo = (Medico *)malloc(sizeof(Medico));
    if (!novo) {
        printf("Erro ao alocar memória para médico.\n");
        return NULL;
    }
    novo->id = id;
    strncpy(novo->nome, nome, MAX_NAME);
    strncpy(novo->especialidade, especialidade, MAX_NAME);
    novo->prox = *lista;
    *lista = novo;
    return novo;
}

Consulta* agendarConsulta(FilaPrioridade *fila, int idPaciente, int idMedico, int gravidade, const char *data) {
    Consulta *nova = (Consulta *)malloc(sizeof(Consulta));
    if (!nova) {
        printf("Erro ao alocar memória para consulta.\n");
        return NULL;
    }
    nova->idPaciente = idPaciente;
    nova->idMedico = idMedico;
    nova->gravidade = gravidade;
    strncpy(nova->data, data, MAX_NAME);
    nova->prox = NULL;

    if (!fila->inicio || fila->inicio->gravidade < gravidade) {
        nova->prox = fila->inicio;
        fila->inicio = nova;
    } else {
        Consulta *atual = fila->inicio;
        while (atual->prox && atual->prox->gravidade >= gravidade) {
            atual = atual->prox;
        }
        nova->prox = atual->prox;
        atual->prox = nova;
    }

    return nova;
}

Paciente* buscarPacientePorID(Paciente *lista, int id) {
    while (lista) {
        if (lista->id == id) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

Medico* buscarMedicoPorID(Medico *lista, int id) {
    while (lista) {
        if (lista->id == id) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

void listarPacientes(Paciente *lista) {
    printf("Lista de Pacientes:\n");
    while (lista) {
        printf("ID: %d, Nome: %s, Idade: %d, Endereço: %s, Telefone: %s\n", lista->id, lista->nome, lista->idade, lista->endereco, lista->telefone);
        lista = lista->prox;
    }
}

void listarMedicos(Medico *lista) {
    printf("Lista de Médicos:\n");
    while (lista) {
        printf("ID: %d, Nome: %s, Especialidade: %s\n", lista->id, lista->nome, lista->especialidade);
        lista = lista->prox;
    }
}

void listarConsultas(FilaPrioridade *fila) {
    Consulta *atual = fila->inicio;
    printf("Lista de Consultas:\n");
    while (atual) {
        printf("Paciente ID: %d, Médico ID: %d, Gravidade: %d, Data: %s\n", atual->idPaciente, atual->idMedico, atual->gravidade, atual->data);
        atual = atual->prox;
    }
}

void excluirPaciente(Paciente **lista, int id) {
    Paciente *atual = *lista;
    Paciente *anterior = NULL;

    while (atual) {
        if (atual->id == id) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                *lista = atual->prox;
            }
            free(atual);
            printf("Paciente ID %d excluído com sucesso.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Paciente ID %d não encontrado.\n", id);
}

void excluirMedico(Medico **lista, int id) {
    Medico *atual = *lista;
    Medico *anterior = NULL;

    while (atual) {
        if (atual->id == id) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                *lista = atual->prox;
            }
            free(atual);
            printf("Médico ID %d excluído com sucesso.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Médico ID %d não encontrado.\n", id);
}

void excluirConsulta(FilaPrioridade *fila, int idPaciente, int idMedico) {
    Consulta *atual = fila->inicio;
    Consulta *anterior = NULL;

    while (atual) {
        if (atual->idPaciente == idPaciente && atual->idMedico == idMedico) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                fila->inicio = atual->prox;
            }
            free(atual);
            printf("Consulta do Paciente ID %d com Médico ID %d excluída com sucesso.\n", idPaciente, idMedico);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Consulta não encontrada para o Paciente ID %d e Médico ID %d.\n", idPaciente, idMedico);
}

void gerarRelatorio(Paciente *listaPacientes, Medico *listaMedicos, FilaPrioridade *fila) {
    FILE *fp = fopen("relatorio.txt", "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo de relatório.\n");
        return;
    }

    // Relatório de Pacientes
    fprintf(fp, "Relatório de Pacientes:\n");
    Paciente *paciente = listaPacientes;
    while (paciente) {
        fprintf(fp, "ID: %d, Nome: %s, Idade: %d, Endereço: %s, Telefone: %s\n", paciente->id, paciente->nome, paciente->idade, paciente->endereco, paciente->telefone);
        paciente = paciente->prox;
    }

    // Relatório de Médicos
    fprintf(fp, "\nRelatório de Médicos:\n");
    Medico *medico = listaMedicos;
    while (medico) {
        fprintf(fp, "ID: %d, Nome: %s, Especialidade: %s\n", medico->id, medico->nome, medico->especialidade);
        medico = medico->prox;
    }

    // Relatório de Consultas
    fprintf(fp, "\nRelatório de Consultas:\n");
    Consulta *consulta = fila->inicio;
    while (consulta) {
        fprintf(fp, "Paciente ID: %d, Médico ID: %d, Gravidade: %d, Data: %s\n", consulta->idPaciente, consulta->idMedico, consulta->gravidade, consulta->data);
        consulta = consulta->prox;
    }

    fclose(fp);
    printf("Relatório gerado com sucesso em 'relatorio.txt'.\n");
}

void salvarDados(Paciente *pacientes, Medico *medicos, FilaPrioridade *fila) {
    FILE *fp;

    fp = fopen("pacientes.txt", "w");
    while (pacientes) {
        fprintf(fp, "%d %s %d %s %s\n", pacientes->id, pacientes->nome, pacientes->idade, pacientes->endereco, pacientes->telefone);
        pacientes = pacientes->prox;
    }
    fclose(fp);

    fp = fopen("medicos.txt", "w");
    while (medicos) {
        fprintf(fp, "%d %s %s\n", medicos->id, medicos->nome, medicos->especialidade);
        medicos = medicos->prox;
    }
    fclose(fp);
}

void carregarDados(Paciente **pacientes, Medico **medicos, FilaPrioridade *fila) {
    FILE *fp;
    int id, idade;
    char nome[MAX_NAME], endereco[MAX_NAME], telefone[MAX_NAME], especialidade[MAX_NAME];

    fp = fopen("pacientes.txt", "r");
    if (fp) {
        while (fscanf(fp, "%d %[^\n] %d %[^\n] %[^\n]\n", &id, nome, &idade, endereco, telefone) != EOF) {
            cadastrarPaciente(pacientes, id, nome, idade, endereco, telefone);
        }
        fclose(fp);
    }

    fp = fopen("medicos.txt", "r");
    if (fp) {
        while (fscanf(fp, "%d %[^\n] %[^\n]\n", &id, nome, especialidade) != EOF) {
            cadastrarMedico(medicos, id, nome, especialidade);
        }
        fclose(fp);
    }
}
