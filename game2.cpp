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

int main() {
    system("chcp 65001 > nul");
    int escolhas[4]; // Corrigido para 4 jogadores
    int i;
    float armadilhas = 0.10;
    float dicas = 0.05;
    int num_jog, escolha, totaljogadas = 36;
    string perso5[4]; // Corrigido para 4 jogadores
    string emoji[] = {"🐻", "😽", "🧙‍♂", "🦸‍♂"};
    string emoji_matriz = "💎";
    string matriz[6][6];
    string matriz_oculta[6][6]; // Matriz oculta para armadilhas e dicas
    string emoji_armadilha = "🧨";
    string emoji_dica = "💰";

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
        while (escolha < 1 || escolha > 4) {
            cout << "Escolha inválida. Tente novamente entre 1 e 4." << endl;
            cin >> escolha;
        }
        escolhas[i] = escolha;
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

    for (int jogada = 0; jogada < totaljogadas; jogada++) {
        imprimirmatriz(matriz);
        exibirranking(pontuacao, perso5, num_jog);
        cout << "Vamos jogar! Escolha uma posição (linha coluna): " << endl;
        int jogadoratual = jogada % num_jog;
        int linha, coluna;
        cin >> linha >> coluna;

        if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
            string conteudo = matriz_oculta[linha][coluna];
            if (conteudo == emoji_armadilha) {
                pontuacao[jogadoratual] -= 10;
                cout << ANSI_COLOR_RED << "O jogador " << jogadoratual + 1 << " caiu em uma bomba e perdeu 10 quilates!" << ANSI_COLOR_RESET << endl;
                matriz[linha][coluna] = emoji_armadilha; // Mostrar bomba após acesso
            } else if (conteudo == emoji_dica) {
                pontuacao[jogadoratual] += 10;
                cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << " encontrou um saco cheio de ouro! Mais 10 quilates pra conta." << ANSI_COLOR_RESET << endl;
                matriz[linha][coluna] = emoji_dica; // Mostrar dica após acesso
            } else if (conteudo == emoji_matriz) {
                int diamantes = rand() % 10 + 1;
                pontuacao[jogadoratual] += diamantes;
                cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << " encontrou " << diamantes << " quilates de diamantes!" << ANSI_COLOR_RESET << endl;
                matriz[linha][coluna] = emoji[escolhas[jogadoratual] - 1]; // Mostrar personagem após acesso
            }
        } else {
            cout << ANSI_COLOR_RED << "Posição inválida! Tente novamente." << ANSI_COLOR_RESET << endl;
            jogada--;
        }
    }

    cout << ANSI_COLOR_YEL << "O ranking final é: " << ANSI_COLOR_RESET << endl;
    int maior=0, pma=0;
    for (int i = 0; i < num_jog; i++) {
        if(pontuacao[i] > maior) {
            maior = pontuacao[i];
            pma = i + 1;
        }
        cout << ANSI_COLOR_YEL << "Jogador " << i + 1 << " (" << perso5[i] << "): " << pontuacao[i] << " quilates" << ANSI_COLOR_RESET << endl;
    }
    cout << "O Ganhador da partida foi o(a) jogador(a): " << pma << endl;

    cout << ANSI_COLOR_CYN << "Obrigado por jogar!" << ANSI_COLOR_RESET << endl;

}
