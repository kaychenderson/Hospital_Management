#include "hospital.h"

int main() {
    Paciente *pacientes = NULL;
    Medico *medicos = NULL;
    FilaPrioridade fila = {NULL};

    carregarDados(&pacientes, &medicos, &fila);

    int opcao;

    do {
        printf("\nSistema de Gerenciamento Hospitalar\n");
        printf("1. Cadastrar Paciente\n");
        printf("2. Cadastrar Médico\n");
        printf("3. Agendar Consulta\n");
        printf("4. Listar Pacientes\n");
        printf("5. Listar Médicos\n");
        printf("6. Listar Consultas\n");
        printf("7. Excluir Paciente\n");
        printf("8. Excluir Médico\n");
        printf("9. Excluir Consulta\n");
        printf("10. Gerar Relatório\n");
        printf("11. Salvar e Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int id, idade;
                char nome[MAX_NAME], endereco[MAX_NAME], telefone[MAX_NAME];
                printf("ID do Paciente: ");
                scanf("%d", &id);
                printf("Nome: ");
                scanf(" %[^\n]s", nome);
                printf("Idade: ");
                scanf("%d", &idade);
                printf("Endereço: ");
                scanf(" %[^\n]s", endereco);
                printf("Telefone: ");
                scanf(" %[^\n]s", telefone);
                cadastrarPaciente(&pacientes, id, nome, idade, endereco, telefone);
                break;
            }
            case 2: {
                int id;
                char nome[MAX_NAME], especialidade[MAX_NAME];
                printf("ID do Médico: ");
                scanf("%d", &id);
                printf("Nome: ");
                scanf(" %[^\n]s", nome);
                printf("Especialidade: ");
                scanf(" %[^\n]s", especialidade);
                cadastrarMedico(&medicos, id, nome, especialidade);
                break;
            }
            case 3: {
                int idPaciente, idMedico, gravidade;
                char data[MAX_NAME];
                printf("ID do Paciente: ");
                scanf("%d", &idPaciente);
                printf("ID do Médico: ");
                scanf("%d", &idMedico);
                printf("Gravidade (1 a 5): ");
                scanf("%d", &gravidade);
                printf("Data (dd/mm/aaaa): ");
                scanf(" %[^\n]s", data);
                agendarConsulta(&fila, idPaciente, idMedico, gravidade, data);
                break;
            }
            case 4:
                listarPacientes(pacientes);
                break;
            case 5:
                listarMedicos(medicos);
                break;
            case 6:
                listarConsultas(&fila);
                break;
            case 7: {
                int idPaciente;
                printf("ID do Paciente: ");
                scanf("%d", &idPaciente);
                excluirPaciente(&pacientes, idPaciente);
                break;
            }
            case 8: {
                int idMedico;
                printf("ID do Médico: ");
                scanf("%d", &idMedico);
                excluirMedico(&medicos, idMedico);
                break;
            }
            case 9: {
                int idPaciente, idMedico;
                printf("ID do Paciente: ");
                scanf("%d", &idPaciente);
                printf("ID do Médico: ");
                scanf("%d", &idMedico);
                excluirConsulta(&fila, idPaciente, idMedico);
                break;
            }
            case 10:
                gerarRelatorio(pacientes, medicos, &fila);
                break;
            case 11:
                salvarDados(pacientes, medicos, &fila);
                printf("Dados salvos. Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 11);

    return 0;
}