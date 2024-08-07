#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#define ANSI_COLOR_CYN      "\e[0;36m" // Cor ciano
#define ANSI_COLOR_RED      "\e[0;31m" // Cor vermelha
#define ANSI_COLOR_YEL      "\e[0;33m" // Cor amarela
#define ANSI_COLOR_RESET    "\e[0m"    // Resetar cor

using namespace std;

bool usou_drone[4] = {false}; //aqui determina se o jogador usou ou não o drone.
bool usou_radar[4] = {false};
bool usou_dica[4] = {false};
//const não permite modificações na variável ao decorrer do código.

void imprimirmatriz(const string matriz[6][6], const int pontuacao[], const string nomes[], int num_jog) { //aqui vai imprimir a matriz com laterais e imprimir o ranking ao lado da matriz.
    // Imprime a matriz
    cout << ANSI_COLOR_CYN << "+-----+-----+-----+-----+-----+" << ANSI_COLOR_RESET << "               " << ANSI_COLOR_CYN << "Ranking" << ANSI_COLOR_RESET << endl;
    for (int l = 0; l < 6; l++) {
        cout << ANSI_COLOR_CYN << "| " << ANSI_COLOR_RESET;
        for (int c = 0; c < 6; c++) {
            cout << setw(3) << matriz[l][c] << ANSI_COLOR_CYN << " | " << ANSI_COLOR_RESET;
        }
        cout << "              "; // Espaço para o ranking
        // Imprime o ranking ao lado da matriz
        for (int i = 0; i < num_jog; i++) {
            if (i == l) {
                cout << ANSI_COLOR_RED << "Jogador " << i + 1 << ": " << pontuacao[i] << " quilates" << ANSI_COLOR_RESET << "            ";
            } else {
                cout << "                    ";
            }
        }
        cout << endl << ANSI_COLOR_CYN << "+-----+-----+-----+-----+-----+" << ANSI_COLOR_RESET << "            " << ANSI_COLOR_RESET;
        for (int i = 0; i < num_jog; i++) {
            if (l == i) {
                cout << "----------";
            } else {
                cout << "                    ";
            }
        }
        cout << endl;
    }

}


void exibirranking(const int pontuacao[], const string nomes[], int num_jog) { //aqui imprime o ranking a cada rodada.
    cout << ANSI_COLOR_CYN << "Ranking atual:" << ANSI_COLOR_RESET << endl;
    for (int i = 0; i < num_jog; i++) {
        cout << ANSI_COLOR_RED << "Jogador " << i + 1 << " (" << nomes[i] << "): " << pontuacao[i] << " quilates" << ANSI_COLOR_RESET << endl;
    }
}

void drone(string matriz[6][6], const string matriz_oculta[6][6], int linha, int coluna, int jogadoratual) { //aqui é a função do uso do drone.
    int dronerevelado = 0; //aqui inicializei a posição máxima que o drone pode mostrar.
    if (usou_drone[jogadoratual]) { //aqui é: se o bool for true ele vai mostrar esse cout, se for false vai mostrar o else.
        cout << "Você já usou o drone! Tente novamente." << endl;
        return;
    } else {
        for (int l = max(0, linha - 1); l <= min(6 - 1, linha + 1) && dronerevelado < 1; l++) { //o max serve para limitar que o acesso
        //seja no minimo 0 e o min determina que 6-1, ou seja, que acesse no maximo a posição 5 da matriz.
        for (int c = max(0, coluna - 1); c <= min(6 - 1, coluna + 1) && dronerevelado < 1; l++) { // define que linha e coluna nunca serão menores que 0 e maiores que 5.
            matriz[l][c] = matriz_oculta[l][c]; //aqui é pra mostrar os emoji da oculta na matriz visível.
            dronerevelado++; //continuação da limitação.
            usou_drone[jogadoratual] = true; //coloca true depois do uso.
        }
    }
}
    } //o radar de mina é para determinar se há dinamite proxima da posição que voce selecionou, se tiver ganha 15 quilates, se não, perde 15.
void radardemina(string matriz[6][6], const string matriz_oculta[6][6], bool matriz_acessada[6][6], int linha, int coluna, int& pontos, int jogadoratual) { //int& permite modificar a variável diretamente.
    int radar_revelado = 0; //para limitar o número de posições reveladas.
    bool encontroudinamite = false; //bool usado para determinar se encontrou dinamite ou não.

    if (usou_radar[jogadoratual]) {
        cout << "Você já usou o Radar de mina!" << endl;
        return;
    } else {
            for (int l = max(0, linha - 1); l <= min(6 - 1, linha + 1) && radar_revelado < 1; l++) {
        for (int c = max(0, coluna - 1); c <= min(6 - 1, coluna + 1) && radar_revelado < 1; c++) {
            if (!matriz_acessada[l][c] && matriz_oculta[l][c] == "🧨") { //determina que, se tal posição já não foi acessada e se a matriz oculta
            //tem um dinamite, vai mudar o bool pra true nos 3 bool.
                encontroudinamite = true;
                matriz_acessada[l][c] = true;
                usou_radar[jogadoratual] = true;
            }
            matriz[l][c] = matriz_oculta[l][c]; //muda o emoji da visivel pro emoji que está na oculta.
            usou_radar[jogadoratual] = true;
        }
    }

    if (encontroudinamite) { //se o bool for true, acontece esse if, se for false, acontece o else.
        pontos += 15;
        cout << ANSI_COLOR_YEL << "Você encontrou dinamite! Ganhou 15 quilates!" << ANSI_COLOR_RESET << endl;
    } else {
        pontos -= 15;
        cout << ANSI_COLOR_YEL << "Que azar! Nenhum dinamite por aqui, por causa disso menos 15 quilates na conta." << ANSI_COLOR_RESET << endl;
    }
    }

}

//a função dica diz se tem armadilhas, diamantes ou bonus proximos da posição selecionada.
void dica(const string matriz_oculta[6][6], bool matriz_acessada[6][6], int linha, int coluna, int jogadoratual) { //diz se tem armadilhas, diamantes ou bonus proximos
    bool encontrou_armadilha = false;
    bool encontrou_dica = false;
    if (usou_dica[jogadoratual]) {
        cout << "Você já usou dica! Tente novamente." << endl;
        return;
    } else {
            for (int l = max(0, linha - 3); l <= min(6 - 1, linha + 3); l++) { //delimita acessar no minimo posição 0 e no máximo posição 5 de até 3 células próximas do que selecionou.
        for (int c = max(0, coluna - 3); c <= min(6 - 1, coluna + 3); c++) {
            int distancia = (linha - l) + (coluna - c); //faz o calculo da distancia entre dois pontos, tornando em numero absoluto para ter sempre um resultado positivo.
            if (distancia <= 3 && !matriz_acessada[l][c]) { //verifica se a distancia é menor ou igual a 3 e se já não foi acessada.
                if (distancia <= 2) {
                    if (matriz_oculta[l][c] == "🧨") {
                        encontrou_armadilha = true;
                    }
                    if (matriz_oculta[l][c] == "💰") {
                        encontrou_dica = true;
                    }
                }
            }
            usou_dica[jogadoratual] = true;
        }
    }

    if (encontrou_armadilha) {
        cout << "Há uma armadilha nas proximidades!" << endl;
    } else if (encontrou_dica) {
        cout << "Há um saco de diamantes nas proximidades!" << endl;
    } else {
        cout << "Nada encontrado nas proximidades!" << endl;
    }
    }
}


int main() {
    system("chcp 65001 > nul");
    //string command = "mode con: cols=30 lines=30";
    //system(command.c_str());
    int escolhas[4]; // pra armazenar os personagem escolhidos
    int i;
    float armadilhas = 0.10;
    float dicas = 0.05;
    int num_jog, escolha, totaljogadas = 36;
    string perso5[4]; // pra armazenar o nome dos jogadores
    string emoji[] = {"🐻", "😽", "🧙‍♂", "🦸‍♂"};
    string emoji_matriz = {"🗺️"};
    string matriz[6][6];
    string matriz_oculta[6][6];
    string emoji_armadilha = {"🧨"};
    string emoji_dica = {"💰"};
    string emoji_1lugar = {"🏅"};
    string emoji_vilao = "👹";
    string emoji_diamante = {"💎"};
    bool matriz_acessada[6][6] = {false};
    int personagens_selecionados[4] = {0};

    cout << "Quantos jogadores teremos nessa partida?" << endl;
    cin >> num_jog;
    while (num_jog < 2 || num_jog > 4) {
        cout << "Escolha inválida, escolha entre 2 e 4 jogadores." << endl;
        cin >> num_jog;
    }
    cin.get();
    for (i = 0; i < num_jog; i++) {
        cout << "Nome do jogador " << i + 1 << ":" << endl;
        getline(cin, perso5[i]);
    }
    cout << "Agora escolha seu personagem: " << endl;
    cout << "Urso" << emoji[0] << "  " << "Gato" << emoji[1] << "  " << "Mago" << emoji[2] << "  " << "Super-Herói" << emoji[3] << endl;
    for (i = 0; i < num_jog; i++) {
        cout << "Personagem do jogador " << i + 1 << endl;
        cin >> escolha;
        while (escolha < 1 || escolha > 4 || personagens_selecionados[escolha - 1] == 1) {
            if (escolha < 1 || escolha > 4) {
                cout << "Escolha inválida. Tente novamente entre 1 e 4." << endl;
            } else {
                cout << "Esse personagem já foi selecionado. Escolha outro." << endl;
            }
            cin >> escolha;
        }
        escolhas[i] = escolha;
        personagens_selecionados[escolha - 1] = 1;
    }
    for (i = 0; i < num_jog; i++) {
        cout << ANSI_COLOR_RED << "Nome do jogador " << i + 1 << ": " << perso5[i] << endl;
        cout << ANSI_COLOR_RED << "Personagem do jogador " << i + 1 << ": " << emoji[escolhas[i] - 1] << endl;
    }

    //--------------------------------Parte dois adicional----------------------------------------//
    cout << ANSI_COLOR_YEL << "Bem-vindos ao caça tesouro perdido!" << endl << "Me chamo pirata Anthony e estou aqui para te ensinar como pode me ajudar nessa caça!" << endl;
    cout << "Como pode ver temos muitos lugares para explorar, e temos muitas chances de encontrar muitos diamantes por essas terras, mas cuidado! Foi assim que me aposentei nessa caça ao tesouro..." << endl;
    cout << "Eu estava caçando e estava ficando rico com todos os diamantes que eu achava até que... me deparei com um homem que usava uma máscara e fazia propostas tentadoras... E uma delas era uma aposta, se ele vencesse uma batalha ele levava meus quilates, mas se eu ganhasse eu levava todos os seus quilates..." << endl;
    cout << "E isso me custou todos os meus quilates! E agora estou velho demais para essa aventura... Mas um jovem como você pode derrotá-lo!" << endl;
    cout << "Cuidado por onde anda, você só pode usar dicas, rada e drone uma vez, use com sabedoria, além disso, tem armadilhas espalhadas por toda a área, mas claro, tem um bonus sensacional por aí que nunca encontrei." << endl;
    cout << "É isso... Não perca tempo e me traga esse tesouro!" << ANSI_COLOR_RESET << endl;
    srand(time(NULL));
    int totalpontos = 36;
    int totalarmadilhas = armadilhas * totalpontos;
    int totalpistas = dicas * totalpontos;
    int l, c;
    int num_vilao = 0;
    int total_diamantes = 0.5 * totalpontos;
    int num_diamantes = 0;

    // aqui vai inicializar a matriz principal e a matriz oculta toda com mapa
    for (l = 0; l < 6; l++) {
        for (c = 0; c < 6; c++) {
            matriz[l][c] = emoji_matriz;
            matriz_oculta[l][c] = emoji_matriz;
        }
    }
    for (i = 0; i < total_diamantes; i++) { //aqui vai inicializar com diamantes em 50% da matriz.
        do {
            l = rand() % 6;
            c = rand() % 6;
        } while (matriz_oculta[l][c] != emoji_matriz);
        matriz_oculta[l][c] = emoji_diamante;
    }

    // aqui vai adicionar os emoji de armadilha e saco de dinheiro só na matriz oculta
    int num_armadilhas = 0, num_dicas = 0;

    while (num_armadilhas < totalarmadilhas || num_dicas < totalpistas || num_vilao < 1) {
    int l = rand() % 6; // escolhe 1 das 6 posições aleatoriamente para adicionar os emojis.
    int c = rand() % 6;
    if (matriz_oculta[l][c] == emoji_matriz) { //verifica se tal posição da matriz oculta está liberada.
        if (num_armadilhas < totalarmadilhas) {
            matriz_oculta[l][c] = emoji_armadilha; 
            num_armadilhas++;
        } else if (num_dicas < totalpistas && num_armadilhas >= totalarmadilhas) {
            matriz_oculta[l][c] = emoji_dica; 
            num_dicas++;
        } else if (num_vilao < 1) {
            matriz_oculta[l][c] = emoji_vilao; 
            matriz[l][c] = emoji_vilao; 
            num_vilao++;
        }
    }
}

    int pontuacao[4] = {0};
    int jogadas = 0; // aqui conta so as rodadas validas!!!

while (jogadas < totaljogadas) {
    int jogadoratual = jogadas % num_jog; //aqui faz o calculo do resto, exemplo: 36 jogadas % 2 jogadores, jogada 0 % 2 = jogador 0 (jogador 1), jogada 1 % 2 = jogador 1(jogador 2).
    cout << "Rodada: " << jogadas << " " << "Jogador: " << perso5[jogadoratual] << endl;
    // Dentro do loop principal
    imprimirmatriz(matriz, pontuacao, perso5, num_jog);
    cout << "Vamos jogar! Escolha uma opção: " << endl << "1. Jogar" << endl << "2. Usar drone" << endl << "3. Usar Radar" << endl << "4. Usar Dica" << endl;
    int escolha;
    cin >> escolha;
    if (escolha == 1) {
        cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição (linha coluna): " << ANSI_COLOR_RESET;
        int linha, coluna;
        cin >> linha >> coluna;

        if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
            if (matriz_acessada[linha][coluna]) {
                cout << ANSI_COLOR_RED << "Essa posição já foi acessada. Escolha outra posição." << ANSI_COLOR_RESET << endl;
                continue; // aqui nao passa a rodada nem o player!!!
            }
            string conteudo = matriz_oculta[linha][coluna];
            if (conteudo == emoji_armadilha) {
                pontuacao[jogadoratual] -= 10;
                cout << ANSI_COLOR_RED << "O jogador " << jogadoratual + 1 << " caiu em uma bomba e perdeu 10 quilates!" << ANSI_COLOR_RESET << endl;
                matriz[linha][coluna] = emoji_armadilha; // aqui serve pra mostrar os emoji da matriz oculta na matriz principal!!!
            } else if (conteudo == emoji_dica) {
                pontuacao[jogadoratual] += 10;
                cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << " encontrou um saco cheio de diamantes! Mais 10 quilates pra conta." << ANSI_COLOR_RESET << endl;
                matriz[linha][coluna] = emoji_dica; // Mostrar dica após acesso
            } else if (conteudo == emoji_diamante) {
                int diamantes = rand() % 10 + 1;
                pontuacao[jogadoratual] += diamantes;
                cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << " encontrou " << diamantes << " quilates de diamantes!" << ANSI_COLOR_RESET << endl;
                matriz[linha][coluna] = emoji_diamante; 
            } else if (conteudo == emoji_matriz) {
                matriz[linha][coluna] = emoji[escolhas[jogadoratual] - 1]; 
                cout << "Nada encontrado!" << endl;
            }
             else if (conteudo == emoji_vilao) {
                int quilates_vilao = rand() % 25 + 1; 
                int ataque_jogador = pontuacao[jogadoratual];
                if (ataque_jogador >= quilates_vilao) {
                    pontuacao[jogadoratual] += quilates_vilao;
                    cout << ANSI_COLOR_YEL << "Parabéns! Você derrotou o vilão e ganhou" << quilates_vilao << " quilates do vilao!" << ANSI_COLOR_RESET << endl;
                } else {
                    pontuacao[jogadoratual] -= quilates_vilao;
                    cout << ANSI_COLOR_RED << "Você perdeu para o vilão e o vilao roubou " << quilates_vilao << " quilates seu!" << ANSI_COLOR_RESET << endl;
                }
                matriz[linha][coluna] = emoji[escolhas[jogadoratual]-1]; 
                matriz_acessada[linha][coluna] = true; // marca as posições acessadas
                jogadas++; 
            }
            matriz_acessada[linha][coluna] = true; 
            jogadas++; 
        } else {
            cout << ANSI_COLOR_RED << "Posição inválida! Tente novamente." << ANSI_COLOR_RESET << endl;
        }
    } else if (escolha == 2) {
        cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição (linha e coluna): " << ANSI_COLOR_RESET;
        int linha, coluna;
        cin >> linha >> coluna;
        if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
            drone(matriz, matriz_oculta, linha, coluna, jogadoratual);
        } else {
            cout << ANSI_COLOR_RED << "Posição inválida. Tente novamente." << ANSI_COLOR_RESET << endl;
            continue;
        }
    } else if (escolha == 3) {
        cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição (linha e coluna): " << ANSI_COLOR_RESET;
        int linha, coluna;
        cin >> linha >> coluna;
        if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
            radardemina(matriz, matriz_oculta, matriz_acessada, linha, coluna, pontuacao[jogadoratual], jogadoratual);
        } else {
            cout << ANSI_COLOR_RED << "Posição inválida. Tente novamente." << ANSI_COLOR_RESET << endl;
            continue;
        }
    } else if (escolha == 4) {
        cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição (linha e coluna): " << ANSI_COLOR_RESET;
        int linha, coluna;
        cin >> linha >> coluna;
        if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
            dica(matriz_oculta, matriz_acessada, linha, coluna, jogadoratual);
        } else {
            cout << ANSI_COLOR_RED << "Posição inválida. Tente novamente." << ANSI_COLOR_RESET << endl;
            continue;
        }
    }
}



    cout << ANSI_COLOR_YEL << "O ranking final é: " << ANSI_COLOR_RESET << endl;
    int maior = 0, pma = 0;
    for (int i = 0; i < num_jog; i++) {
        if (pontuacao[i] > maior) {
            maior = pontuacao[i];
            pma = i + 1;
        }
        cout << ANSI_COLOR_YEL << "Jogador " << i + 1 << " (" << perso5[i] << "): " << pontuacao[i] << " quilates" << ANSI_COLOR_RESET << endl;
    }
    cout << "O Ganhador da partida foi o(a) jogador(a): " << pma << " " << "🏅" << endl;

    cout << ANSI_COLOR_CYN << "Obrigado por jogar!" << ANSI_COLOR_RESET << endl;
}