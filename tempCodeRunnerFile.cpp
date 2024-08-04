#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale>
#include <codecvt>
#define ANSI_COLOR_CYN      "\e[0;36m" // Cor ciano
#define ANSI_COLOR_RED      "\e[0;31m" // Cor vermelha
#define ANSI_COLOR_YEL      "\e[0;33m" // Cor amarela
#define ANSI_COLOR_RESET    "\e[0m"    // Resetar cor

using namespace std;

void imprimirmatriz(const string matriz[6][6]) {
    cout << ANSI_COLOR_CYN << "+-----+-----+-----+-----+-----+" << ANSI_COLOR_RESET << endl;
    for (int l = 0; l < 6; l++) {
        cout << ANSI_COLOR_CYN << "| " << ANSI_COLOR_RESET;
        for (int c = 0; c < 6; c++) {
            cout << setw(3) << matriz[l][c] << ANSI_COLOR_CYN << " | " << ANSI_COLOR_RESET;
        }
        cout << endl << ANSI_COLOR_CYN << "+-----+-----+-----+-----+-----+" << ANSI_COLOR_RESET << endl;
    }
}

void exibirranking(const int pontuacao[], const string nomes[], int num_jog) {
    cout << ANSI_COLOR_CYN << "Ranking atual:" << ANSI_COLOR_RESET << endl;
    for (int i = 0; i < num_jog; i++) {
        cout << ANSI_COLOR_RED << "Jogador " << i + 1 << " (" << nomes[i] << "): " << pontuacao[i] << " quilates" << ANSI_COLOR_RESET << endl;
    }
}

void drone(string matriz[6][6], const string matriz_oculta[6][6], int linha, int coluna) {
    for (int l = max(0, linha - 1); l <= min(6 - 1, linha + 1); l++) {
        for (int c = max(0, coluna - 1); c <= min(6 - 1, coluna + 1); c++) {
            matriz[l][c] = matriz_oculta[l][c];
        }
    }
}

void radardemina(string matriz[6][6], const string matriz_oculta[6][6], int linha, int coluna, int& pontos) {
    bool encontroudinamite = false;
    for (int l = max(0, linha - 1); l <= min(6 - 1, linha + 1); l++) {
        for (int c = max(0, coluna - 1); c <= min(6 - 1, coluna + 1); c++) {
            matriz[l][c] = matriz_oculta[l][c];
            if (matriz_oculta[l][c] == "🧨") {
                encontroudinamite = true;
            }
        }
    }
    if (encontroudinamite) {
        pontos += 15;
        cout << ANSI_COLOR_YEL << "Você encontrou dinamite! Ganhou 15 quilates!" << ANSI_COLOR_RESET << endl;
    } else {
        pontos -= 15;
        cout << ANSI_COLOR_YEL << "Que azar! Nenhum dinamite por aqui, por causa disso menos 15 quilates na conta." << ANSI_COLOR_RESET << endl;
    }
}

int main() {
    system("chcp 65001 > nul");
    int escolhas[4]; // Corrigido para 4 jogadores
    int i;
    float armadilhas = 0.10;
    float dicas = 0.05;
    int num_jog, escolha, totaljogadas = 36;
    string perso5[4]; // Corrigido para 4 jogadores
    string emoji[] = {"🐻", "😽", "🧙‍♂", "🦸‍♂"};
    string emoji_matriz = {"💎"};
    string matriz[6][6];
    string matriz_oculta[6][6]; // Matriz oculta para armadilhas e dicas
    string emoji_armadilha = {"🧨"};
    string emoji_dica = {"💰"};
    string emoji_1lugar = {"🏅"};
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
    srand(time(NULL));
    int totalpontos = 6 * 6;
    int totalarmadilhas = armadilhas * totalpontos;
    int totalpistas = dicas * totalpontos;
    int l, c;

    // Inicializar a matriz com emojis de diamante
    for (l = 0; l < 6; l++) {
        for (c = 0; c < 6; c++) {
            matriz[l][c] = emoji_matriz;
            matriz_oculta[l][c] = emoji_matriz; // Inicializar matriz oculta com diamantes
        }
    }

    // Adicionar armadilhas e dicas à matriz oculta
    int num_armadilhas = 0, num_dicas = 0;

    while (num_armadilhas < totalarmadilhas || num_dicas < totalpistas) {
        l = rand() % 6;
        c = rand() % 6;
        if (matriz_oculta[l][c] == emoji_matriz) {
            if (num_armadilhas < totalarmadilhas && (rand() % (totalarmadilhas + totalpistas)) < totalarmadilhas) {
                matriz_oculta[l][c] = emoji_armadilha; // Adiciona uma bomba na matriz oculta
                num_armadilhas++;
            } else if (num_dicas < totalpistas) {
                matriz_oculta[l][c] = emoji_dica; // Adiciona uma dica na matriz oculta
                num_dicas++;
            }
        }
    }

    int pontuacao[4] = {0};
    int jogadas = 0; // Contador de jogadas válidas

    while (jogadas < totaljogadas) {
        int jogadoratual = jogadas % num_jog;
        cout << "Rodada: " << jogadas << " " << "Jogador: " << perso5[jogadoratual] << endl;
        imprimirmatriz(matriz);
        exibirranking(pontuacao, perso5, num_jog);
        cout << "Vamos jogar! Escolha uma opção: " << endl << "1. Jogar" << endl << "2. Usar drone" << endl << "3. Usar Radar" << endl;
        int escolha;
        cin >> escolha;
        if (escolha == 1) {
            cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição (linha coluna): " << ANSI_COLOR_RESET;
            int linha, coluna;
            cin >> linha >> coluna;

            if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
                if (matriz_acessada[linha][coluna]) {
                    cout << ANSI_COLOR_RED << "Essa posição já foi acessada. Escolha outra posição." << ANSI_COLOR_RESET << endl;
                    continue; // Voltar a jogada para o mesmo jogador
                }
                string conteudo = matriz_oculta[linha][coluna];
                if (conteudo == emoji_armadilha) {
                    pontuacao[jogadoratual] -= 10;
                    cout << ANSI_COLOR_RED << "O jogador " << jogadoratual + 1 << " caiu em uma bomba e perdeu 10 quilates!" << ANSI_COLOR_RESET << endl;
                    matriz[linha][coluna] = emoji_armadilha; // Mostrar bomba após acesso
                } else if (conteudo == emoji_dica) {
                    pontuacao[jogadoratual] += 10;
                    cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << " encontrou um saco cheio de diamantes! Mais 10 quilates pra conta." << ANSI_COLOR_RESET << endl;
                    matriz[linha][coluna] = emoji_dica; // Mostrar dica após acesso
                } else if (conteudo == emoji_matriz) {
                    int diamantes = rand() % 10 + 1;
                    pontuacao[jogadoratual] += diamantes;
                    cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << " encontrou " << diamantes << " quilates de diamantes!" << ANSI_COLOR_RESET << endl;
                    matriz[linha][coluna] = emoji[escolhas[jogadoratual] - 1]; // Mostrar personagem após acesso
                }
                matriz_acessada[linha][coluna] = true; // Marcar posição como acessada
                jogadas++; // Incrementar apenas se o jogador realmente jogou
            } else {
                cout << ANSI_COLOR_RED << "Posição inválida! Tente novamente." << ANSI_COLOR_RESET << endl;
            }
        } else if (escolha == 2) {
            cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição (linha e coluna): " << ANSI_COLOR_RESET;
            int linha, coluna;
            cin >> linha >> coluna;
            if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
                drone(matriz, matriz_oculta, linha, coluna);
            } else {
                cout << ANSI_COLOR_RED << "Posição inválida. Tente novamente." << ANSI_COLOR_RESET << endl;
                continue;
            }
        } else if (escolha == 3) {
            cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição (linha e coluna): " << ANSI_COLOR_RESET;
            int linha, coluna;
            cin >> linha >> coluna;
            if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
                radademina(matriz, matriz_oculta, linha, coluna, pontuacao[jogadoratual]);
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
