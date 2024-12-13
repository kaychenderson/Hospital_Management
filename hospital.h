#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

// Estruturas
typedef struct Paciente {
    int id;
    char nome[MAX_NAME];
    int idade;
    char endereco[MAX_NAME];
    char telefone[MAX_NAME];
    struct Paciente *prox;
} Paciente;

typedef struct Medico {
    int id;
    char nome[MAX_NAME];
    char especialidade[MAX_NAME];
    struct Medico *prox;
} Medico;

typedef struct Consulta {
    int idPaciente;
    int idMedico;
    int gravidade; // 1 a 5 (5 é mais grave)
    char data[MAX_NAME];
    struct Consulta *prox;
} Consulta;

typedef struct FilaPrioridade {
    Consulta *inicio;
} FilaPrioridade;

// Funções de gerenciamento
Paciente* cadastrarPaciente(Paciente **lista, int id, const char *nome, int idade, const char *endereco, const char *telefone);
Medico* cadastrarMedico(Medico **lista, int id, const char *nome, const char *especialidade);
Consulta* agendarConsulta(FilaPrioridade *fila, int idPaciente, int idMedico, int gravidade, const char *data);

// Funções de busca
Paciente* buscarPacientePorID(Paciente *lista, int id);
Medico* buscarMedicoPorID(Medico *lista, int id);

// Funções utilitárias
void listarPacientes(Paciente *lista);
void listarMedicos(Medico *lista);
void listarConsultas(FilaPrioridade *fila);
void excluirPaciente(Paciente **lista, int id);
void excluirMedico(Medico **lista, int id);
void excluirConsulta(FilaPrioridade *fila, int idPaciente, int idMedico);
void gerarRelatorio(Paciente *lista, Medico *listaMedicos, FilaPrioridade *fila);

// Funções para Salvar e Carregar os dados
void salvarDados(Paciente *pacientes, Medico *medicos, FilaPrioridade *fila);
void carregarDados(Paciente **pacientes, Medico **medicos, FilaPrioridade *fila);

#endif
