//Alunos: Adryan Gabriel Borges Rocha, Kauan Olivera Dalat

/******************************************************************************

Objetivo
Desenvolver um sistema para gerenciamento de uma biblioteca, utilizando registros (structs), vetores e funções modulares em linguagem C.



O sistema deve permitir o cadastro e gerenciamento de livros, usuários e empréstimos.

Estruturas de Dados (Structs)
O sistema deve conter pelo menos três structs principais:

Livro

int idLivro

char titulo[100]

char autor[100]

int anoPublicacao

int disponivel (1 = disponível, 0 = emprestado)

Usuário

int idUsuario

char nome[100]

char email[100]

int ativo (1 = ativo, 0 = inativo)

Empréstimo

int idEmprestimo

int idUsuario

int idLivro

char dataEmprestimo[11] // formato: "dd/mm/aaaa"

char dataDevolucao[11] // vazio se ainda não devolvido

int ativo (1 = em andamento, 0 = concluído)

Funcionalidades obrigatórias
O sistema deve exibir um menu principal com as seguintes opções:

1. Gerenciamento de Livros
Adicionar novo livro

Buscar livro por título ou autor

Listar todos os livros

Listar apenas livros disponíveis

Atualizar informações de um livro (ex: título, autor, ano)

Remover livro do acervo (opcional, apenas se não estiver emprestado)

2. Gerenciamento de Usuários
Cadastrar novo usuário

Buscar usuário por nome

Listar todos os usuários cadastrados

Inativar usuário (ex: se não pode mais pegar livros emprestados)

3. Gerenciamento de Empréstimos
Registrar novo empréstimo (vinculando um usuário a um livro disponível)

Registrar devolução de um livro

Listar todos os empréstimos ativos

Listar histórico de empréstimos (ativos e concluídos)

Mostrar todos os livros emprestados por um usuário específico

4. Relatórios (para consolidar raciocínio lógico)
Quantidade total de livros cadastrados

Quantidade de livros disponíveis e emprestados

Usuário com mais empréstimos ativos

Livro mais emprestado (extra, para quem quiser desafio)

5. Sair do sistema
Requisitos técnicos
Utilizar registros (structs) e vetores para armazenar dados (sem uso de arquivos).

Cada conjunto de dados (livros, usuários, empréstimos) deve ser armazenado em um vetor de structs.

Criar funções separadas para cada operação principal.

Utilizar IDs automáticos para livros, usuários e empréstimos (ex: incrementando um contador global).

Implementar validações básicas, como:

Impedir empréstimo de livro indisponível

Impedir empréstimo para usuário inativo

Impedir devolução de livro não emprestado

Desafio opcional (ponto extra)
Persistência em arquivo texto:

Salvar e carregar dados de livros, usuários e empréstimos ao iniciar/encerrar o programa.

Menu em submódulos:

Criar menus separados para “Livros”, “Usuários” e “Empréstimos”, melhorando a organização.

Busca parcial:

Permitir buscar livros e usuários por partes do nome (uso de strstr()).

Data automática:

Gerar automaticamente a data do empréstimo usando a biblioteca <time.h>.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// --- Estruturas de Dados (Structs) ---
struct Livro{
    int idLivro;
    char titulo[100];
    char autor[100];
    int anoPub;
    int status; // 1 = disponível, 0 = emprestado
};

struct Usuario{
    int idUsuario;
    char nome[100];
    char email[100];
    int ativo; // 1 = ativo, 0 = inativo
};

struct Emprestimo{
    int idEmprestimo;
    int idUsuario;
    int idLivro;
    char dataEmprestimo[11];// formato xx/xx/xxxx
    char dataDevolucao[11];// vazio se ainda não devolvido (ou uma data)
    int ativo; // 1 = em andamento, 0 = concluído
};

// --- Constantes para o tamanho dos vetores ---
#define MAX_LIVROS 5
#define MAX_USUARIOS 5
#define MAX_EMPRESTIMOS 5

// --- Variáveis Globais de Acervo e Contagem/ID ---
struct Livro L[MAX_LIVROS];
struct Usuario U[MAX_USUARIOS];
struct Emprestimo E[MAX_EMPRESTIMOS];

int totalLivros = 0; // Quantidade atual de livros cadastrados
int proximoIdLivro = 1; // Próximo ID a ser atribuído

int totalUsuarios = 0; // Quantidade atual de usuários cadastrados
int proximoIdUsuario = 1; // Próximo ID a ser atribuído

int contadorEmprestimos = 0; // Quantidade atual de empréstimos
int proximoIdEmprestimo = 1; // Próximo ID a ser atribuído


// --- Protótipos das Funções (Adicionando o novo RegistrarDevolucaoLivroCompleto) ---
void MostrarInformacoes();
void MostrarInformacoes2();
void MostrarInformacoes3();
void MostrarInformacoes4();
void MostrarInformacoes5(); // ADICIONADA
void AdicionarLivro(); // MODIFICADA
void BuscarLivro();
void ListarLivro();
void ListarLivrosDisponiveis();
void AtualizarInformacoes();
void CadastrarUsuario(); // MODIFICADA
void BuscarUsuarioPorNome();
void ListarTodosUsuariosCadastrados();
void InativarUsuario();
void RegistrarEmprestimo(); // MODIFICADA
void ListarTodosEmprestimosAtivo();
void RegistrarDevolucaoLivro(); // Corrigida para usar ID de empréstimo/livro e status
void ListarHistoricoEmprestimos();
void MostrarLivrosEmprestadosPorUsuario();
void QuantidadeLivros(); // ADICIONADA
void LDisponiveisEmprestados(); // ADICIONADA
void UsMaisEmpretimos(); // ADICIONADA
void LMaisEmprestado(); // ADICIONADA (Para onde o código foi movido)
void Relatorios(); // Incluída a função para o menu de relatórios
void LimparBuffer();

void LimparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c!= EOF){

    }
}

void MostrarInformacoes(){
    printf("============ Sistema de Biblioteca ============\n");
    printf("1- Livros\n2- Usuário\n3- Empréstimo\n4- Relatório\n0- Sair\n"); // Nome corrigido
    printf("* Digite um número correspondente a cada ação realizada.\n");
    printf("===============================================\n");
}
void MostrarInformacoes2(){
    printf("============ Gerenciamento de Livros ============\n"); // Nome corrigido
    printf("1- Adicionar Livro\n2- Buscar Livro (por título ou autor)\n3- Listar Todos os Livros\n4- Listar Livros Disponíveis\n5- Atualizar Informações de Livro\n0- Voltar\n"); // Opções ajustadas/removidas
    printf("* Digite um número correspondente a cada ação realizada.\n");
    printf("===============================================\n");
}
void MostrarInformacoes3(){
    printf("============ Gerenciamento de Usuário ============\n");
    printf("1- Cadastrar Usuário\n2- Buscar Usuário por Nome\n3- Listar Todos os Usuários Cadastrados\n4- Inativar Usuário\n0- Voltar\n");
    printf("* Digite um número correspondente a cada ação realizada.\n");
    printf("==================================================\n");
}
void MostrarInformacoes4(){
    printf("============ Gerenciamento de Empréstimo ============\n");
    printf("1- Registrar Novo Empréstimo\n2- Registrar Devolução de um Livro\n3- Listar Todos os Empréstimos Ativos\n4- Listar Histórico de Empréstimos\n5- Mostrar Todos os Livros Emprestados por um Usuário Específico\n0- Voltar\n");
    printf("* Digite um número correspondente a cada ação realizada.\n");
    printf("=====================================================\n");
}
void MostrarInformacoes5(){
    printf("\n===== MENU DE RELATÓRIOS =====\n");
    printf("1- Quantidade total de livros cadastrados\n");
    printf("2- Quantidade de livros disponíveis e emprestados\n3- Usuário com mais empréstimos ativos\n4- Livro mais emprestado\n0- Voltar\n");
    printf("* Digite um número correspondente a cada ação realizada.\n");
    printf("=====================================================\n");
}


void AdicionarLivro(){
    if (totalLivros >= MAX_LIVROS) {
        printf("\nERRO: Limite máximo de %d livros atingido.\n", MAX_LIVROS);
        return;
    }
    
    int i = totalLivros; // Posição para o novo livro
    
    printf("\n============ Adicionar Novo Livro (Livro #%d) ============\n", proximoIdLivro);

    // Entrada do Título
    printf("Título: ");
    fgets(L[i].titulo, sizeof(L[i].titulo), stdin);
    L[i].titulo[strcspn(L[i].titulo, "\n")] = 0;

    // Verificação de Título Único (simples, não obrigatória pelo requisito, mas boa prática)
    for(int j=0; j<totalLivros; j++){
        if(strcmp(L[i].titulo, L[j].titulo)==0){
            printf("ERRO: Título '%s' já cadastrado. Não é possível adicionar.\n", L[i].titulo);
            // Limpa a entrada do struct, embora o buffer do stdin já tenha sido limpo
            L[i].idLivro = 0; 
            L[i].titulo[0] = '\0';
            return;
        }
    }

    // Entrada do Autor
    printf("Autor: ");
    fgets(L[i].autor, sizeof(L[i].autor), stdin);
    L[i].autor[strcspn(L[i].autor, "\n")] = 0;

    // Entrada do Ano
    printf("Ano publicado: ");
    if (scanf("%d", &L[i].anoPub) != 1) {
        LimparBuffer(); // Limpa se for entrada inválida (não numérica)
        printf("ERRO: Ano de publicação inválido. Cadastro cancelado.\n");
        L[i].idLivro = 0;
        L[i].titulo[0] = '\0';
        return;
    }
    LimparBuffer();

    // Definição de status padrão
    L[i].status = 1; // Novo livro é sempre DISPONÍVEL (1)
    
    // Atribuição de ID automático
    L[i].idLivro = proximoIdLivro;
    
    // Atualização de contadores globais
    totalLivros++;
    proximoIdLivro++;
    
    printf("\nLivro '%s' cadastrado com sucesso! ID: %d\n", L[i].titulo, L[i].idLivro);
    printf("========================================================\n");
}

void BuscarLivro(){
    char termoBusca[100];
    int opcao;
    int encontrado = 0;

    printf("\nDigite 1 para pesquisar por **título** ou 2 para pesquisar por **autor**: ");
    if (scanf("%d", &opcao) != 1) {
        LimparBuffer();
        printf("Opção inválida.\n");
        return;
    }
    LimparBuffer();

    if(opcao != 1 && opcao != 2) {
        printf("Opção inválida. Voltando ao menu.\n");
        return;
    }

    printf("Digite o termo de busca: ");
    fgets(termoBusca, sizeof(termoBusca), stdin);
    termoBusca[strcspn(termoBusca, "\n")] = 0;

    printf("\n--- RESULTADOS DA BUSCA ---\n");
    for(int i=0; i<totalLivros; i++){ // Usa totalLivros
        // Usa strstr para busca parcial (Desafio Opcional)
        if((opcao == 1 && strstr(L[i].titulo, termoBusca) != NULL) || 
           (opcao == 2 && strstr(L[i].autor, termoBusca) != NULL)){
            
            encontrado = 1;
            printf("=======================\n");
            printf("[ID Livro: %d]\n", L[i].idLivro);
            printf("[Titulo: %s]\n", L[i].titulo);
            printf("[Autor: %s]\n", L[i].autor);
            printf("[Ano publicado: %d]\n", L[i].anoPub);
            printf("[Status: %s]\n", L[i].status == 1 ? "Disponível" : "Emprestado");
        }
    }
    if (!encontrado) {
        printf("Nenhum livro encontrado com o termo de busca.\n");
    }
    printf("---------------------------\n");
}


void ListarLivro(){
    if (totalLivros == 0) {
        printf("\nNenhum livro cadastrado no acervo.\n");
        return;
    }
    printf("\n--- LISTA COMPLETA DE LIVROS (%d no total) ---\n", totalLivros);
    for(int i=0; i<totalLivros; i++){
        printf("=======================\n");
        printf("[ID Livro: %d]\n", L[i].idLivro);
        printf("[Titulo: %s]\n", L[i].titulo);
        printf("[Autor: %s]\n", L[i].autor);
        printf("[Ano publicado: %d]\n", L[i].anoPub);
        printf("[Status: %s]\n", L[i].status == 1 ? "Disponível" : "Emprestado");
    }
    printf("---------------------------\n");
}

void ListarLivrosDisponiveis(){
    int disponiveis = 0;
    printf("\n--- LIVROS DISPONÍVEIS PARA EMPRÉSTIMO ---\n");
    for(int i=0; i<totalLivros; i++){
        if(L[i].status == 1){
            printf("=======================\n");
            printf("[ID Livro: %d]\n", L[i].idLivro);
            printf("[Titulo: %s]\n", L[i].titulo);
            printf("[Autor: %s]\n", L[i].autor);
            printf("[Ano publicado: %d]\n", L[i].anoPub);
            disponiveis++;
        }
    }
    if (disponiveis == 0) {
        printf("Nenhum livro disponível no momento.\n");
    }
    printf("------------------------------------------\n");
}

void AtualizarInformacoes() {
    int idBusca;
    int livroEncontrado = 0;    
    
    printf("\nDigite o ID do livro que deseja atualizar: ");
    if (scanf("%d", &idBusca) != 1) {
        LimparBuffer();
        printf("Entrada inválida.\n");
        return;
    }
    LimparBuffer();

    for (int i = 0; i < totalLivros; i++) {
        if (L[i].idLivro == idBusca) {
            livroEncontrado = 1;
            
            printf("\n--- ATUALIZANDO INFORMAÇÕES DO LIVRO ID %d ---\n", idBusca);
            
            // Novo Título
            printf("Novo título (atual: %s): ", L[i].titulo);
            fgets(L[i].titulo, sizeof(L[i].titulo), stdin);
            L[i].titulo[strcspn(L[i].titulo, "\n")] = 0;
            
            // Novo Autor
            printf("Novo autor (atual: %s): ", L[i].autor);
            fgets(L[i].autor, sizeof(L[i].autor), stdin);
            L[i].autor[strcspn(L[i].autor, "\n")] = 0;
            
            // Novo Ano
            printf("Novo ano publicado (atual: %d): ", L[i].anoPub);
            if (scanf("%d", &L[i].anoPub) != 1) {
                LimparBuffer();
                printf("\nERRO: Ano de publicação inválido. A atualização foi parcialmente concluída.\n");
                return;
            }
            LimparBuffer();
            
            printf("\nInformações do livro ID %d atualizadas com sucesso!\n", idBusca);
            break;    
        }
    }

    if (!livroEncontrado) {
        printf("\nLivro com o ID %d não encontrado.\n", idBusca);
    }
}


/**
 * Cadastra um único novo usuário no vetor, com ID automático.
 */
void CadastrarUsuario(){
    if (totalUsuarios >= MAX_USUARIOS) {
        printf("\nERRO: Limite máximo de %d usuários atingido.\n", MAX_USUARIOS);
        return;
    }

    int i = totalUsuarios;
    
    printf("\n============ Cadastrar Novo Usuário (Usuário #%d) ============\n", proximoIdUsuario);

    // Nome
    printf("Nome: ");
    fgets(U[i].nome, sizeof(U[i].nome), stdin);
    U[i].nome[strcspn(U[i].nome, "\n")] = 0;
    
    // Email
    printf("Email: ");
    fgets(U[i].email, sizeof(U[i].email), stdin);
    U[i].email[strcspn(U[i].email, "\n")] = 0;
    
    // Atividade (padrão 1, mas permitindo a opção)
    U[i].ativo = 1; // Novo usuário é sempre ATIVO por padrão
    printf("Usuário cadastrado como Ativo (1).\n");
    
    // Atribuição de ID automático
    U[i].idUsuario = proximoIdUsuario;
    
    // Atualização de contadores globais
    totalUsuarios++;
    proximoIdUsuario++;
    
    printf("\nUsuário '%s' cadastrado com sucesso! ID: %d\n", U[i].nome, U[i].idUsuario);
    printf("==============================================================\n");
}

void BuscarUsuarioPorNome(){
    char nomeBusca[100];
    int encontrado = 0;

    printf("\nNome do Usuário para busca (parcial ou completo): ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    printf("\n--- RESULTADOS DA BUSCA ---\n");
    for(int i=0; i<totalUsuarios; i++){
        // Busca parcial com strstr
        if(strstr(U[i].nome, nomeBusca) != NULL){
            encontrado = 1;
            printf("=======================\n");
            printf("ID: %d\n", U[i].idUsuario);
            printf("Nome: %s\n", U[i].nome);
            printf("Email: %s\n", U[i].email);
            printf("Status: %s\n", U[i].ativo == 1 ? "Ativo" : "Inativo");
        }
    }
    if (!encontrado) {
        printf("Nenhum usuário encontrado com o nome de busca.\n");
    }
    printf("---------------------------\n");
}

void ListarTodosUsuariosCadastrados(){
    if (totalUsuarios == 0) {
        printf("\nNenhum usuário cadastrado.\n");
        return;
    }
    printf("\n--- LISTA COMPLETA DE USUÁRIOS (%d no total) ---\n", totalUsuarios);
    for(int i=0; i<totalUsuarios; i++){
        printf("=======================\n");
        printf("ID: %d\n", U[i].idUsuario);
        printf("Nome: %s\n", U[i].nome);
        printf("Email: %s\n", U[i].email);
        printf("Status: %s\n", U[i].ativo == 1 ? "Ativo" : "Inativo");
    }
    printf("---------------------------\n");
}

void InativarUsuario(){
    int idBusca;
    int encontrado = 0;

    printf("\nDigite o ID do Usuário para inativar: ");
    if (scanf("%d", &idBusca) != 1) {
        LimparBuffer();
        printf("Entrada inválida.\n");
        return;
    }
    LimparBuffer();

    for(int i=0; i<totalUsuarios; i++){
        if(U[i].idUsuario == idBusca){
            encontrado = 1;
            if(U[i].ativo == 0){
                printf("Erro - Usuário '%s' (ID: %d) já está inativo.\n", U[i].nome, idBusca);
                return;
            } else {
                U[i].ativo = 0;
                printf("Usuário '%s' (ID: %d) inativado com sucesso.\n", U[i].nome, idBusca);
                return;
            }
        }
    }
    if (!encontrado) {
        printf("Erro - Usuário com ID %d não encontrado.\n", idBusca);
    }
}


void RegistrarEmprestimo(){
    if (contadorEmprestimos >= MAX_EMPRESTIMOS) {
        printf("\nERRO: Limite máximo de %d empréstimos atingido.\n", MAX_EMPRESTIMOS);
        return;
    }

    int idUsuarioBusca, idLivroBusca;
    int posLivro = -1;
    int posUser = -1;

    printf("\nDigite o ID do Usuário: ");
    if (scanf("%d", &idUsuarioBusca) != 1) {
        LimparBuffer();
        printf("Entrada inválida.\n");
        return;
    }
    LimparBuffer();
    
    // 1. Validar Usuário
    for(int i = 0; i < totalUsuarios; i++){
        if(U[i].idUsuario == idUsuarioBusca){
            posUser = i;
            if(U[i].ativo == 0){
                printf("ERRO: Usuário ID %d inativo. Não pode realizar empréstimo.\n", idUsuarioBusca);
                return;
            }
            break;
        }
    }
    if (posUser == -1) {
        printf("ERRO: Usuário ID %d não encontrado.\n", idUsuarioBusca);
        return;
    }

    printf("Digite o ID do Livro: ");
    if (scanf("%d", &idLivroBusca) != 1) {
        LimparBuffer();
        printf("Entrada inválida.\n");
        return;
    }
    LimparBuffer();

    // 2. Validar Livro
    for(int i = 0; i < totalLivros; i++){
        if(L[i].idLivro == idLivroBusca){
            posLivro = i;
            if(L[i].status == 0){
                printf("ERRO: Livro ID %d indisponível para empréstimo.\n", idLivroBusca);
                return;
            }
            break;
        }
    }
    if (posLivro == -1) {
        printf("ERRO: Livro ID %d não encontrado.\n", idLivroBusca);
        return;
    }

    // 3. Registrar o Empréstimo
    int i = contadorEmprestimos;
    E[i].idEmprestimo = proximoIdEmprestimo;
    E[i].idUsuario = idUsuarioBusca;
    E[i].idLivro = idLivroBusca;

    // Geração de Data Automática (<time.h> - Desafio Opcional)
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);    
    strftime(E[i].dataEmprestimo, sizeof(E[i].dataEmprestimo), "%d/%m/%Y", tm);
    
    strcpy(E[i].dataDevolucao, ""); // Data de devolução vazia
    E[i].ativo = 1; // Empréstimo ativo
    
    // 4. Atualizar o status do Livro
    L[posLivro].status = 0; // Marcar como emprestado

    printf("\nEmpréstimo registrado com sucesso!\n");
    printf("ID do Empréstimo: %d\n", E[i].idEmprestimo);
    printf("Livro '%s' para Usuário '%s'.\n", L[posLivro].titulo, U[posUser].nome);
    printf("Data: %s\n", E[i].dataEmprestimo);

    // 5. Atualizar contadores
    contadorEmprestimos++;
    proximoIdEmprestimo++;
}


void RegistrarDevolucaoLivro(){
    int idEmprestimo;
    int emprestimoEncontrado = 0;
    
    printf("\nDigite o ID do Empréstimo a ser devolvido: ");
    if (scanf("%d", &idEmprestimo) != 1) {
        LimparBuffer();
        printf("Entrada inválida.\n");
        return;
    }
    LimparBuffer();

    for(int i = 0; i < contadorEmprestimos; i++){
        if(E[i].idEmprestimo == idEmprestimo){
            emprestimoEncontrado = 1;
            if(E[i].ativo == 0){
                printf("Erro - Este empréstimo (ID %d) já foi concluído.\n", idEmprestimo);
                return;
            }
            
            // 1. Concluir o Empréstimo
            E[i].ativo = 0; 
            
            // Gerar data de devolução automática (Opcional, mas útil)
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);    
            strftime(E[i].dataDevolucao, sizeof(E[i].dataDevolucao), "%d/%m/%Y", tm);

            // 2. Marcar Livro como Disponível
            for(int j = 0; j < totalLivros; j++){
                if(L[j].idLivro == E[i].idLivro){
                    L[j].status = 1;    
                    printf("\nEmpréstimo ID %d devolvido com sucesso. Livro '%s' agora está disponível.\n", 
                               idEmprestimo, L[j].titulo);
                    return; // Sai da função após o sucesso
                }
            }
            printf("\nAVISO: Empréstimo concluído, mas o Livro ID %d associado não foi encontrado no acervo.\n", E[i].idLivro);
            return;
        }
    }
    if (!emprestimoEncontrado) {
        printf("\nErro - Empréstimo ID %d não encontrado.\n", idEmprestimo);
    }
}


void ListarTodosEmprestimosAtivo(){
    int ativos = 0;
    printf("\n--- LISTA DE EMPRÉSTIMOS ATIVOS ---\n");

    for(int i = 0; i < contadorEmprestimos; i++){
        if (E[i].ativo == 1) { 
            ativos++;
            char tituloLivro[100] = "Livro Não Encontrado";
            char nomeUsuario[100] = "Usuário Não Encontrado";
            
            // Busca nome do Usuário
            for (int j = 0; j < totalUsuarios; j++) {
                if (E[i].idUsuario == U[j].idUsuario) {
                    strcpy(nomeUsuario, U[j].nome);
                    break;
                }
            }
            
            // Busca título do Livro
            for (int k = 0; k < totalLivros; k++) {
                if (E[i].idLivro == L[k].idLivro) {
                    strcpy(tituloLivro, L[k].titulo);
                    break;
                }
            }
            
            printf("======================================\n");
            printf("ID Empréstimo: %d\n", E[i].idEmprestimo);
            printf("Livro (ID %d): %s\n", E[i].idLivro, tituloLivro);
            printf("Emprestado para (ID %d): %s\n", E[i].idUsuario, nomeUsuario);
            printf("Data: %s\n", E[i].dataEmprestimo);
        }
    }
    if (ativos == 0) {
        printf("Nenhum empréstimo ativo no momento.\n");
    }
    printf("--------------------------------------\n");
}

void ListarHistoricoEmprestimos(){
    if (contadorEmprestimos == 0) {
        printf("\nNenhum empréstimo registrado no histórico.\n");
        return;
    }
    printf("\n--- HISTÓRICO DE EMPRÉSTIMOS (%d no total) ---\n", contadorEmprestimos);

    for(int i = 0; i < contadorEmprestimos; i++){
        char tituloLivro[100] = "Livro Não Encontrado";
        char nomeUsuario[100] = "Usuário Não Encontrado";
        
        // Busca nome do Usuário
        for (int j = 0; j < totalUsuarios; j++) {
            if (E[i].idUsuario == U[j].idUsuario) {
                strcpy(nomeUsuario, U[j].nome);
                break;
            }
        }
        
        // Busca título do Livro
        for (int k = 0; k < totalLivros; k++) {
            if (E[i].idLivro == L[k].idLivro) {
                strcpy(tituloLivro, L[k].titulo);
                break;
            }
        }
        
        printf("======================================\n");
        printf("ID Empréstimo: %d\n", E[i].idEmprestimo);
        printf("Livro (ID %d): %s\n", E[i].idLivro, tituloLivro);
        printf("Usuário (ID %d): %s\n", E[i].idUsuario, nomeUsuario);
        printf("Data de Empréstimo: %s\n", E[i].dataEmprestimo);
        printf("Status: %s\n", E[i].ativo == 1 ? "Ativo" : "Concluído");
        if (E[i].ativo == 0 && E[i].dataDevolucao[0] != '\0') {
             printf("Data de Devolução: %s\n", E[i].dataDevolucao);
        }
    }
    printf("--------------------------------------\n");
}

void MostrarLivrosEmprestadosPorUsuario(){
    int idUsuarioBusca;
    int idUsuarioEncontrado = -1;

    printf("\nDigite o ID do Usuário: ");
    if (scanf("%d", &idUsuarioBusca) != 1) {
        LimparBuffer();
        printf("Entrada inválida.\n");
        return;
    }
    LimparBuffer();

    // 1. Encontrar o nome do usuário pelo ID
    char nomeUsuario[100] = "N/A";
    for(int i = 0; i < totalUsuarios; i++){
        if(U[i].idUsuario == idUsuarioBusca){
            strcpy(nomeUsuario, U[i].nome);
            idUsuarioEncontrado = U[i].idUsuario;
            break;
        }
    }

    if(idUsuarioEncontrado == -1){
        printf("Usuário ID %d não encontrado.\n", idUsuarioBusca);
        return;
    }

    printf("\n--- LIVROS ATIVOS EMPRESTADOS POR %s (ID %d) ---\n", nomeUsuario, idUsuarioBusca);
    int emprestimosEncontrados = 0;
    
    // 2. Listar empréstimos ativos para este usuário
    for(int i = 0; i < contadorEmprestimos; i++){
        if(E[i].idUsuario == idUsuarioBusca && E[i].ativo == 1){
            emprestimosEncontrados++;
            // Buscar o título do livro
            for(int j = 0; j < totalLivros; j++){
                if(L[j].idLivro == E[i].idLivro){
                    printf("=======================\n");
                    printf("ID Livro: %d\n", L[j].idLivro);
                    printf("Título: %s\n", L[j].titulo);
                    printf("Data de Empréstimo: %s\n", E[i].dataEmprestimo);
                    break;
                }
            }
        }
    }
    
    if (emprestimosEncontrados == 0) {
        printf("O usuário não possui empréstimos ativos.\n");
    }
    printf("--------------------------------------------\n");
}

void QuantidadeLivros(){
    printf("\nTotal de livros cadastrados: %d\n", totalLivros);
                
}
void LDisponiveisEmprestados(){
    int disponiveis = 0, emprestados = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (L[i].status == 1) disponiveis++;
        else emprestados++;
        }    
        printf("\nLivros disponíveis: %d\n", disponiveis);
        printf("Livros emprestados: %d\n", emprestados);
    
}
void UsMaisEmpretimos(){              
    // Usuário com mais empréstimos ativos
    int contagemEmprestimos[MAX_USUARIOS] = {0};
    for (int j = 0; j < contadorEmprestimos; j++) {
        if (E[j].ativo == 1) {
            for(int i = 0; i < totalUsuarios; i++) {
                if(U[i].idUsuario == E[j].idUsuario) {
                    contagemEmprestimos[i]++;
                }
            }
        }
    }
                
    int maiorQtd = -1;
    int idxUsuario = -1;
    for (int i = 0; i < totalUsuarios; i++) {
        if (contagemEmprestimos[i] > maiorQtd) {
            maiorQtd = contagemEmprestimos[i];
            idxUsuario = i;
        }
    }

    if (idxUsuario != -1 && maiorQtd > 0) {
        printf("\nUsuário com mais empréstimos ativos: %s (ID: %d) - %d empréstimos ativos\n",
                           U[idxUsuario].nome, U[idxUsuario].idUsuario, maiorQtd);
        } else {
            printf("\nNenhum empréstimo ativo encontrado.\n");
                }
    
}

// NOVO CORPO DA FUNÇÃO PARA O RELATÓRIO DO LIVRO MAIS EMPRESTADO
void LMaisEmprestado(){
    // Livro mais emprestado (contagem TOTAL - ativos e concluídos)
    int contagemLivros[MAX_LIVROS] = {0};
    int totalEmprestimosRegistrados = 0; // Para checar se houve algum empréstimo

    for (int j = 0; j < contadorEmprestimos; j++) {
        totalEmprestimosRegistrados++;
        for(int i = 0; i < totalLivros; i++) {
            if(L[i].idLivro == E[j].idLivro) {
                contagemLivros[i]++;
                break;
            }
        }
    }
                
    int maiorQtd = -1;
    int idxLivro = -1;
    for (int i = 0; i < totalLivros; i++) {
        if (contagemLivros[i] > maiorQtd) {
            maiorQtd = contagemLivros[i];
            idxLivro = i;
        }
    }
    
    if (idxLivro != -1 && maiorQtd > 0) {
        printf("\nLivro mais emprestado: %s (ID: %d) - %d vezes.\n",
            L[idxLivro].titulo, L[idxLivro].idLivro, maiorQtd);
    } else {
        printf("\nNenhum empréstimo registrado para determinar o livro mais emprestado.\n");
    }
}

void CarregarLivros() {
    FILE *arquivo;
    arquivo = fopen("livros.dat", "rb");
    
    if (arquivo == NULL) {
        totalLivros = 0; 
        proximoIdLivro = 1;
        printf("Arquivo de livros não encontrado. Iniciando novo acervo.\n");
        return;
    }
    
    // Tenta ler a contagem
    size_t lido_qtd = fread(&totalLivros, sizeof(int), 1, arquivo);
    
    size_t lido_dados = 0;
    if (lido_qtd == 1 && totalLivros > 0) {
        // Se a contagem foi lida e é maior que zero, lê os dados.
        lido_dados = fread(L, sizeof(struct Livro), totalLivros, arquivo);
        totalLivros = (int)lido_dados; // Define a contagem real de dados lidos
    } else {
        totalLivros = 0;
    }

    fclose(arquivo);

    // ********* CORREÇÃO CHAVE: Verificar se totalLivros > 0 *********
    if (totalLivros > 0) {
        proximoIdLivro = L[totalLivros - 1].idLivro + 1;
        printf("Dados de %d Livros carregados de 'livros.dat' com sucesso!\n", totalLivros);
    } else {
        proximoIdLivro = 1;
        printf("Arquivo de livros vazio ou corrompido. Iniciando novo acervo.\n");
    }
}

void SalvarLivros() {
    FILE *arquivo;
    // Abre o arquivo "livros.dat" para escrita binária ("wb")
    arquivo = fopen("livros.dat", "wb");
                    
    if (arquivo == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo 'livros.dat' para salvar.\n");
        return;
    }
                    
// 1. Salva a contagem de livros primeiro
    fwrite(&totalLivros, sizeof(int), 1, arquivo);
                    
    // 2. Salva todo o vetor de structs de uma vez (ideal para binário)
    fwrite(L, sizeof(struct Livro), totalLivros, arquivo);
                    
    fclose(arquivo);
    printf("Dados dos Livros salvos em 'livros.dat' com sucesso!\n");
}

void CarregarUsuarios() {
    FILE *arquivo = fopen("usuarios.dat", "rb"); 
    
    if (arquivo == NULL) {
        totalUsuarios = 0;
        proximoIdUsuario = 1;
        printf("Arquivo de usuários não encontrado. Iniciando novo cadastro.\n");
        return;
    }

    // 1. Tenta ler a contagem
    size_t lido_qtd = fread(&totalUsuarios, sizeof(int), 1, arquivo);
    
    size_t lido_dados = 0;
    if (lido_qtd == 1 && totalUsuarios > 0) {
        // 2. Se a contagem foi lida e é maior que zero, lê os dados.
        lido_dados = fread(U, sizeof(struct Usuario), totalUsuarios, arquivo);
        totalUsuarios = (int)lido_dados; // Ajusta a contagem real
    } else {
        totalUsuarios = 0;
    }
    
    fclose(arquivo);

  
    if (totalUsuarios > 0) {
        // Encontra o ID mais alto para garantir que o próximoId seja único
        int maxId = 0;
        for(int i=0; i < totalUsuarios; i++) {
            if (U[i].idUsuario > maxId) {
                maxId = U[i].idUsuario;
            }
        }
        proximoIdUsuario = maxId + 1;
        printf("Dados de %d Usuários carregados de 'usuarios.dat' com sucesso!\n", totalUsuarios);
    } else {
        proximoIdUsuario = 1;
        printf("Arquivo de usuários vazio ou corrompido. Iniciando novo cadastro.\n");
    }
}
void SalvarUsuarios() {
    FILE *arquivo = fopen("usuarios.dat", "wb"); 
    if (arquivo == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo 'usuarios.dat' para salvar.\n");
        return;
    }

    // 1. Salva a quantidade
    fwrite(&totalUsuarios, sizeof(int), 1, arquivo); 
    
    // 2. Salva todo o vetor de structs de uma vez
    fwrite(U, sizeof(struct Usuario), totalUsuarios, arquivo);
    
    fclose(arquivo);
    printf("Dados dos Usuários salvos em 'usuarios.dat' com sucesso!\n");
}
void CarregarEmprestimos() {
    FILE *arquivo;
    arquivo = fopen("emprestimos.dat", "rb");
    
    if (arquivo == NULL) {
        contadorEmprestimos = 0; 
        proximoIdEmprestimo = 1;
        printf("\nℹ️ Arquivo 'emprestimos.dat' não encontrado. Iniciando novo histórico.\n");
        return;
    }
    
    // Tenta ler a contagem
    size_t lido_qtd = fread(&contadorEmprestimos, sizeof(int), 1, arquivo);
    
    size_t lido_dados = 0;
    if (lido_qtd == 1 && contadorEmprestimos > 0) {
        // Se a contagem foi lida e é maior que zero, lê os dados.
        lido_dados = fread(E, sizeof(struct Emprestimo), contadorEmprestimos, arquivo);
        contadorEmprestimos = (int)lido_dados; // Define a contagem real de dados lidos
    } else {
        contadorEmprestimos = 0;
    }
    
    fclose(arquivo);
    
    // ********* CORREÇÃO CHAVE: Verificar se contadorEmprestimos > 0 *********
    if (contadorEmprestimos > 0) {
        proximoIdEmprestimo = E[contadorEmprestimos - 1].idEmprestimo + 1;
        printf("\nDados de %d Empréstimos carregados de 'emprestimos.dat' com sucesso!\n", contadorEmprestimos);
        printf("Próximo ID de Empréstimo será: %d\n", proximoIdEmprestimo);
    } else {
        proximoIdEmprestimo = 1;
        printf("\nAVISO: Arquivo 'emprestimos.dat' não continha dados válidos. Iniciando novo histórico.\n");
    }
}

void SalvarEmprestimos() {
    FILE *arquivo;
    // Abre o arquivo 'emprestimos.dat' para escrita binária ("wb")
    arquivo = fopen("emprestimos.dat", "wb");
    
    // VERIFICAÇÃO DE ERRO
    if (arquivo == NULL) {
        printf("\nERRO: Não foi possível abrir o arquivo 'emprestimos.dat' para salvar.\n");
        return;
    }
    
    // --- 1. ESCREVE A QUANTIDADE DE ELEMENTOS ---
    size_t escritos_qtd = fwrite(&contadorEmprestimos, sizeof(int), 1, arquivo);
    
    // --- 2. ESCREVE TODO O VETOR DE STRUCTS ---
    size_t escritos_dados = fwrite(E, sizeof(struct Emprestimo), contadorEmprestimos, arquivo);
    
    // FECHA O ARQUIVO
    fclose(arquivo);
    
    // CONFIRMAÇÃO
    if (escritos_qtd == 1 && escritos_dados == contadorEmprestimos) {
        printf("\nDados de %d Empréstimos salvos em 'emprestimos.dat' com sucesso!\n", contadorEmprestimos);
    } else {
         printf("\nAVISO: Salvamento dos Empréstimos foi parcial ou falhou.\n");
    }
}

// ******************************************************************************
// ************************** FUNÇÃO PRINCIPAL (MAIN) ***************************
// ******************************************************************************

int main()
{
    // Inicialização do estado - Zera todos os structs e contadores
    // Garante que L, U, E comecem "vazios" no sentido de dados válidos.
    memset(L, 0, sizeof(L)); 
    memset(U, 0, sizeof(U));
    memset(E, 0, sizeof(E));

    // A inicialização dos IDs e Contadores globais não é estritamente necessária após o memset, 
    // mas se tivessem começado com valores diferentes de 0, seria:
    // proximoIdLivro = 1;
    // proximoIdUsuario = 1;
    // proximoIdEmprestimo = 1;

    CarregarLivros();
    CarregarUsuarios();
    CarregarEmprestimos();
    
    int opcao = -1;
    int opcao2 = -1;
    int opcao3 = -1;
    int opcao4 = -1;
    int opcao5 = -1;
    printf("--- Sistema de Gerenciamento de Biblioteca ---\n");
    // Inicializar o gerador de números aleatórios (usado na versão antiga de AdicionarLivro)
    // srand(time(NULL)); 
    
    while (1) {
        
        MostrarInformacoes();   
        
        if (scanf("%d", &opcao) != 1) {
            LimparBuffer();
            printf("Entrada inválida. Por favor, digite um número.\n");
            continue;
        }
        LimparBuffer();

        switch (opcao) {
            
            case 1:   
                opcao2 = -1;    
                while (opcao2 != 0) {   
                    MostrarInformacoes2();
                    if (scanf("%d", &opcao2) != 1) {
                        LimparBuffer();
                        printf("Entrada inválida. Por favor, digite um número.\n");
                        continue;
                    }
                    LimparBuffer();

                    switch (opcao2) {
                        case 1:   
                            AdicionarLivro();   
                            break;
                        case 2:
                            BuscarLivro();
                            break;
                        case 3:
                            ListarLivro();
                            break;
                        case 4:
                            ListarLivrosDisponiveis();
                            break;
                        case 5:
                            AtualizarInformacoes();
                            break;
                        case 0:
                            printf("Voltando ao Menu Principal...\n");
                            break;   
                        default:
                            printf("Opção inválida.\n");
                    }
                }
                break;   

            case 2:   
                opcao3 = -1;
                while (opcao3 != 0) {
                    MostrarInformacoes3();
                    if (scanf("%d", &opcao3) != 1) {
                        LimparBuffer();
                        printf("Entrada inválida. Por favor, digite um número.\n");
                        continue;
                    }
                    LimparBuffer();
                    
                    switch (opcao3) {
                        case 1:
                            CadastrarUsuario();
                            break;
                        case 2:
                            BuscarUsuarioPorNome();
                            break;
                        case 3:
                            ListarTodosUsuariosCadastrados();
                            break;
                        case 4:
                            InativarUsuario();
                            break;
                        case 0:
                            printf("Voltando ao Menu Principal...\n");
                            break;
                        default:
                            printf("Opção inválida.\n");
                    }
                }
                break;

            case 3:   
                opcao4 = -1;    
                while (opcao4 != 0) {
                    MostrarInformacoes4();
                    if (scanf("%d", &opcao4) != 1) {
                        LimparBuffer();
                        printf("Entrada inválida. Por favor, digite um número.\n");
                        continue;
                    }
                    LimparBuffer();
                    
                    switch (opcao4) {
                        case 1:   
                            RegistrarEmprestimo();
                            break;
                        case 2:
                            RegistrarDevolucaoLivro();
                            break;
                        case 3:
                            ListarTodosEmprestimosAtivo();
                            break;
                        case 4:
                            ListarHistoricoEmprestimos();
                            break;
                        case 5:
                            MostrarLivrosEmprestadosPorUsuario();
                            break;
                        case 0:
                            printf("Voltando ao Menu Principal...\n");
                            break;
                        default:
                            printf("Opção inválida.\n");
                    }
                }
                break;
            
            case 4:
                opcao5 = -1; 
                while (opcao5 != 0) { 
                    MostrarInformacoes5();
                    if (scanf("%d", &opcao5) != 1) {
                        LimparBuffer();
                        printf("Entrada inválida. Por favor, digite um número.\n");
                        continue;
                    }
                    LimparBuffer();

                    switch (opcao5) {
                        case 1:
                        QuantidadeLivros();
                        break;
                        case 2:
                        LDisponiveisEmprestados();
                        break;
                        case 3:
                        UsMaisEmpretimos();
                        break;
                        case 4:
                        LMaisEmprestado(); // Chamada da nova função
                        break;
                        case 0:
                        printf("Voltando ao Menu Principal\n");
                        break; 
                        default:
                        printf("Opção inválida.\n");
                    }    
                }           
                break;
            
            case 0:
                
                SalvarLivros();
                SalvarUsuarios();
                SalvarEmprestimos();
                
                printf("Encerrando o sistema. Até logo!\n");
                return 0;   
                
            default:
                printf("Opção de menu principal inválida.\n");
        }
    }   
}