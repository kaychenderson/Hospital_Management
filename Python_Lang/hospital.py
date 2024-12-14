class Paciente:
    def __init__(self, id, nome, idade, endereco, telefone):
        self.id = id
        self.nome = nome
        self.idade = idade
        self.endereco = endereco
        self.telefone = telefone
        self.prox = None

class Medico:
    def __init__(self, id, nome, especialidade):
        self.id = id
        self.nome = nome
        self.especialidade = especialidade
        self.prox = None

class Consulta:
    def __init__(self, idPaciente, idMedico, gravidade, data):
        self.idPaciente = idPaciente
        self.idMedico = idMedico
        self.gravidade = gravidade
        self.data = data
        self.prox = None

class FilaPrioridade:
    def __init__(self):
        self.inicio = None

    def agendar_consulta(self, idPaciente, idMedico, gravidade, data):
        nova = Consulta(idPaciente, idMedico, gravidade, data)
        if not self.inicio or self.inicio.gravidade < gravidade:
            nova.prox = self.inicio
            self.inicio = nova
        else:
            atual = self.inicio
            while atual.prox and atual.prox.gravidade >= gravidade:
                atual = atual.prox
            nova.prox = atual.prox
            atual.prox = nova
        return nova

class Hospital:
    def __init__(self):
        self.pacientes = None
        self.medicos = None
        self.fila = FilaPrioridade()

    def cadastrar_paciente(self, id, nome, idade, endereco, telefone):
        novo = Paciente(id, nome, idade, endereco, telefone)
        novo.prox = self.pacientes
        self.pacientes = novo
        return novo

    def cadastrar_medico(self, id, nome, especialidade):
        novo = Medico(id, nome, especialidade)
        novo.prox = self.medicos
        self.medicos = novo
        return novo

    def buscar_paciente_por_id(self, id):
        atual = self.pacientes
        while atual:
            if atual.id == id:
                return atual
            atual = atual.prox
        return None

    def buscar_medico_por_id(self, id):
        atual = self.medicos
        while atual:
            if atual.id == id:
                return atual
            atual = atual.prox
        return None

    def listar_pacientes(self):
        print("Lista de Pacientes:")
        atual = self.pacientes
        while atual:
            print(f"ID: {atual.id}, Nome: {atual.nome}, Idade: {atual.idade}, Endereço: {atual.endereco}, Telefone: {atual.telefone}")
            atual = atual.prox

    def listar_medicos(self):
        print("Lista de Médicos:")
        atual = self.medicos
        while atual:
            print(f"ID: {atual.id}, Nome: {atual.nome}, Especialidade: {atual.especialidade}")
            atual = atual.prox

    def listar_consultas(self):
        print("Lista de Consultas:")
        atual = self.fila.inicio
        while atual:
            print(f"Paciente ID: {atual.idPaciente}, Médico ID: {atual.idMedico}, Gravidade: {atual.gravidade}, Data: {atual.data}")
            atual = atual.prox

    def excluir_paciente(self, id):
        atual = self.pacientes
        anterior = None
        while atual:
            if atual.id == id:
                if anterior:
                    anterior.prox = atual.prox
                else:
                    self.pacientes = atual.prox
                print(f"Paciente ID {id} excluído com sucesso.")
                return
            anterior = atual
            atual = atual.prox
        print(f"Paciente ID {id} não encontrado.")

    def excluir_medico(self, id):
        atual = self.medicos
        anterior = None
        while atual:
            if atual.id == id:
                if anterior:
                    anterior.prox = atual.prox
                else:
                    self.medicos = atual.prox
                print(f"Médico ID {id} excluído com sucesso.")
                return
            anterior = atual
            atual = atual.prox
        print(f"Médico ID {id} não encontrado.")

    def excluir_consulta(self, idPaciente, idMedico):
        atual = self.fila.inicio
        anterior = None
        while atual:
            if atual.idPaciente == idPaciente and atual.idMedico == idMedico:
                if anterior:
                    anterior.prox = atual.prox
                else:
                    self.fila.inicio = atual.prox
                print(f"Consulta do Paciente ID {idPaciente} com Médico ID {idMedico} excluída com sucesso.")
                return
            anterior = atual
            atual = atual.prox
        print(f"Consulta não encontrada para o Paciente ID {idPaciente} e Médico ID {idMedico}.")

    def gerar_relatorio(self):
        with open('relatorio.txt', 'w') as fp:
            fp.write("Relatório de Pacientes:\n")
            paciente = self.pacientes
            while paciente:
                fp.write(f"ID: {paciente.id}, Nome: {paciente.nome}, Idade: {paciente.idade}, Endereço: {paciente.endereco}, Telefone: {paciente.telefone}\n")
                paciente = paciente.prox

            fp.write("\nRelatório de Médicos:\n")
            medico = self.medicos
            while medico:
                fp.write(f"ID: {medico.id}, Nome: {medico.nome}, Especialidade: {medico.especialidade}\n")
                medico = medico.prox

            fp.write("\nRelatório de Consultas:\n")
            consulta = self.fila.inicio
            while consulta:
                fp.write(f"Paciente ID: {consulta.idPaciente}, Médico ID: {consulta.idMedico}, Gravidade: {consulta.gravidade}, Data: {consulta.data}\n")
                consulta = consulta.prox

        print("Relatório gerado com sucesso em 'relatorio.txt'.")

# Função principal para o menu
def main():
    hospital = Hospital()

    while True:
        print("\nSistema de Gerenciamento Hospitalar")
        print("1. Cadastrar Paciente")
        print("2. Cadastrar Médico")
        print("3. Agendar Consulta")
        print("4. Listar Pacientes")
        print("5. Listar Médicos")
        print("6. Listar Consultas")
        print("7. Excluir Paciente")
        print("8. Excluir Médico")
        print("9. Excluir Consulta")
        print("10. Gerar Relatório")
        print("11. Sair")
        opcao = int(input("Escolha uma opção: "))

        if opcao == 1:
            id = int(input("ID do Paciente: "))
            nome = input("Nome: ")
            idade = int(input("Idade: "))
            endereco = input("Endereço: ")
            telefone = input("Telefone: ")
            hospital.cadastrar_paciente(id, nome, idade, endereco, telefone)
        elif opcao == 2:
            id = int(input("ID do Médico: "))
            nome = input("Nome: ")
            especialidade = input("Especialidade: ")
            hospital.cadastrar_medico(id, nome, especialidade)
        elif opcao == 3:
            idPaciente = int(input("ID do Paciente: "))
            idMedico = int(input("ID do Médico: "))
            gravidade = int(input("Gravidade (1 a 5): "))
            data = input("Data (dd/mm/aaaa): ")
            hospital.fila.agendar_consulta(idPaciente, idMedico, gravidade, data)
        elif opcao == 4:
            hospital.listar_pacientes()
        elif opcao == 5:
            hospital.listar_medicos()
        elif opcao == 6:
            hospital.listar_consultas()
        elif opcao == 7:
            id = int(input("ID do Paciente: "))
            hospital.excluir_paciente(id)
        elif opcao == 8:
            id = int(input("ID do Médico: "))
            hospital.excluir_medico(id)
        elif opcao == 9:
            idPaciente = int(input("ID do Paciente: "))
            idMedico = int(input("ID do Médico: "))
            hospital.excluir_consulta(idPaciente, idMedico)
        elif opcao == 10:
            hospital.gerar_relatorio()
        elif opcao == 11:
            print("Saindo...")
            break
        else:
            print("Opção inválida. Tente novamente.")

if __name__ == "__main__":
    main()
