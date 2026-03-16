// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define NUM_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 30

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;

};

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
struct Territorio* alocarmapa();
void inicializarTerritorios(struct Territorio mapa []);
void liberarmemoria(struct Territorio *mapa);
void exibirMapa(const struct Territorio Mapa[]);
void faseDeAtaque(struct Territorio mapa[]);
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor);

// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    srand(time(NULL));

    struct Territorio *mapa = alocarmapa();

    if(mapa == NULL){
        printf("Erro ao alocar memoria\n");
        return 1;
    }
    
    inicializarTerritorios(mapa);

    int opcao;

    do{
        exibirMapa(mapa);
         
        printf("\n1 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha");
        scanf("%d", &opcao);

        switch (opcao){

            case 1:
                    faseDeAtaque(mapa);
                    break;
            case 0: printf("Saindo do jogo...\n");
                     break;
            default:
                    printf("Opcao invalida\n");
        }

    }while (opcao !=0);
     liberarmemoria(mapa);

    
    
    

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.



    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;

}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
struct Territorio* alocarmapa(){
    struct Territorio *mapa;
    mapa = (struct Territorio*) calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    
 return mapa;
}

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(struct Territorio mapa[]){

strcpy(mapa[0].nome,"America");
strcpy(mapa[0].cor,"Azul");
mapa[0].tropas = 12;

strcpy(mapa[1].nome,"Asia");
strcpy(mapa[1].cor,"Vermelho");
mapa[1].tropas = 20;

strcpy(mapa[2].nome,"Africa");
strcpy(mapa[2].cor,"Verde");
mapa[2].tropas = 8;

strcpy(mapa[3].nome,"Europa");
strcpy(mapa[3].cor,"Amarelo");
mapa[3].tropas = 15;

strcpy(mapa[4].nome,"Oceania");
strcpy(mapa[4].cor,"Roxo");
mapa[4].tropas = 6;

}







// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

void liberarMemoria(struct Territorio *mapa){
    free(mapa);
}

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

void exibirMapa(const struct Territorio mapa[]){
    printf("\n ====== ESTADO ATUAL DO MAPA ====== \n");
   
     for (int i = 0; i <NUM_TERRITORIOS; i++){
       
        printf("%d - %s | Cor: %s | Tropas: %d\n",
        i+1,
        mapa[i].nome,
        mapa[i].cor,
        mapa[i].tropas);
    }
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

 void faseDeAtaque(struct Territorio mapa[]){
    int atacante, defensor;

printf("\nEscolha o territorio atacante (1-5): ");
scanf("%d",&atacante);

printf("Escolha o territorio defensor (1-5):");
scanf("%d",&defensor);

atacante--;
defensor--;

if (atacante < 0 || atacante >= NUM_TERRITORIOS || defensor < 0 || defensor >= NUM_TERRITORIOS){
    printf("Territorio invalido\n");
    return;
}

if(atacante == defensor){
    printf ("Nao pode atacar o mesmo territorio\n");
    return;
}

simularAtaque(&mapa[atacante],&mapa[defensor]);

 }
// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
 
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor){

    int dadoAtaque = rand()%6 + 1;
    int dadoDefesa = rand()%6 + 1;

    printf("\nDado atacante: %d\n", dadoAtaque);
    printf("Dado defensor: %d\n", dadoDefesa);

    if(dadoAtaque >= dadoDefesa){

        defensor->tropas--;

        printf("O defensor perdeu uma tropa!\n");

        if(defensor->tropas <= 0){

            printf("Territorio conquistado!\n");

            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;

        }

    }
    else{

        atacante->tropas--;

        printf("O atacante perdeu uma tropa!\n");

    }

}


// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
