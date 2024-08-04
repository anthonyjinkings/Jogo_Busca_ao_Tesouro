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
    cout << ANSI_COLOR_CYN << "+-----+-----+-----+-----+-----+-----+" << ANSI_COLOR_RESET << endl;
    for (int l=0; l<6; l++) {
        cout << ANSI_COLOR_CYN << "| " << ANSI_COLOR_RESET;
        for (int c=0; c<6; c++) {
            cout << setw(3) << matriz[l][c] << ANSI_COLOR_CYN << " | " << ANSI_COLOR_RESET;
        }
        cout << endl << ANSI_COLOR_CYN << "+-----+-----+-----+-----+-----+-----+" << ANSI_COLOR_RESET << endl;
    }
}

void exibirranking(const int pontuacao[], const string nomes[], int num_jog) {
    cout << ANSI_COLOR_CYN << "Ranking atual:" << ANSI_COLOR_RESET << endl;
    for (int i=0; i< num_jog; i++) {
        cout << ANSI_COLOR_RED << "Jogador " << i + 1 << " (" << nomes[i] << "): " << pontuacao[i] << " quilates" << ANSI_COLOR_RESET << endl;
    }
}

int main() {
    system("chcp 65001 > nul");
    int escolhas[5];
    int i;
    float armadilhas = 0.10;
    float dicas = 0.05;
    int num_jog, perso1, perso2, perso3, perso4, nume_jog=1, escolha, quilates[6][6], totaljogadas = 36;
    string perso5[5];
    string nome_jog1, nome_jog2, nome_jog3, nome_jog4, emoji[]={"🐻", "😽", "🧙‍♂", "🦸‍♂"};
    string emoji_matriz[]={"💎"};
    string matriz[6][6];
    string emoji_trevo[]={"🍀"};
    string emoji_armadilha[]={"🧨"};
    string emoji_dica[]{"💰"};
    cout << "Quantos jogadores teremos nessa partida?" << endl;
    cin >> num_jog;
    while (num_jog < 2 || num_jog > 4) {
        cout << "Escolha inválida, escolha entre 2 e 4 jogadores." << endl;
        cin >> num_jog;
    }
    cin.get();
        for (i=0; i<num_jog; i++) {
            cout << "Nome do jogador " << i+1 << ":" << endl;
            getline (cin,perso5[i]);
        }
        cout << "Agora escolha seu personagem: " << endl;
        cout << "Urso" << emoji[0] << "  " << "Gato" << emoji[1] << "  " << "Mago" << emoji[2] << "  " << "Super-Herói" << emoji[3] << endl;
        for (i=0; i<num_jog; i++) {
            cout << "Personagem do jogador " << i+1 << endl;
            cin >> escolha;
            while (escolha < 1 || escolha > 4) {
                cout << "Escolha inválida. Tente novamente entre 1 e 4." << endl;
                cin >> escolha;
            }
            escolhas[i]= escolha;
        }
        for (i=0; i<num_jog; i++) {
            cout << ANSI_COLOR_RED << "Nome do jogador " << i + 1 << ":" << perso5[i] << endl;
            cout << ANSI_COLOR_RED << "Personagem do jogador " << i+1 << ":" << emoji[escolhas[i]-1] << endl;
        }
         //--------------------------------Parte dois adicional----------------------------------------//
        srand(time(NULL));
        int totalpontos = 6*6;
        int totalarmadilhas = armadilhas * totalpontos;
        int totalpistas = dicas * totalpontos;
        int l, c;

        for (l = 0; l<6; l++) {
            for (c = 0; c<6; c++) {
                matriz[l][c] = emoji_matriz[0];
            }
        }

        int num_armadilhas =0, num_pistas = 0;

        while (num_armadilhas < totalarmadilhas) {
            l = rand()%6;
            c = rand()%6;
            if (matriz[l][c] == emoji_matriz[0]) {
                matriz[l][c] = emoji_trevo[0];
                num_armadilhas++;
            }
        }

        while (num_pistas < totalpistas) {
            l = rand()%6;
            c = rand()%6;
            if (matriz[l][c] == emoji_matriz[0]) {
                matriz[l][c] = emoji_trevo[0];
                num_pistas++;
            }
        }

        int pontuacao[4] = {0};

        for (int jogada =0; jogada < 36; jogada++) {
            imprimirmatriz(matriz);
            exibirranking(pontuacao, perso5, num_jog);
            int jogadoratual = jogada % num_jog;
            cout << ANSI_COLOR_CYN << "Jogador " << jogadoratual + 1 << " (" << perso5[jogadoratual] << ") Escolha uma posição: " << ANSI_COLOR_RESET;
            int linha, coluna;
            cin >> linha >> coluna;

            if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6) {
                string conteudo = matriz[linha][coluna];
                if (conteudo == emoji_trevo[0]) {
                    if (rand() % 2 == 0) {
                        conteudo = emoji_armadilha[0];
                        pontuacao[jogadoratual] -= 10;
                        cout << ANSI_COLOR_RED << "O jogador " << jogadoratual + 1 << "caiu em uma bomba e perdeu 10 quilates!" << ANSI_COLOR_RESET << endl;

                    } else {
                        conteudo = emoji_dica[0];
                        pontuacao[jogadoratual] += 10;
                        cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << "encontrou um saco cheio de ouro! Mais 10 quilates pra conta." << ANSI_COLOR_RESET << endl;
                    }
                } else if (conteudo == emoji_matriz[0]) {
                    int diamantes = rand() % 10 + 1;
                    pontuacao[jogadoratual] += diamantes;
                    cout << ANSI_COLOR_YEL << "O jogador " << jogadoratual + 1 << "encontrou " << diamantes << " quilates de diamantes!" << ANSI_COLOR_RESET << endl;
                }
                matriz[linha][coluna] = emoji[escolhas[jogadoratual] - 1];
            } else {
                cout << ANSI_COLOR_RED << "Posição inválida! Tente novamente." << ANSI_COLOR_RESET << endl;
                jogada--;
            }
        }
        cout << ANSI_COLOR_YEL << "O ranking final é: " << ANSI_COLOR_RESET << endl;
        for (int i=0; i< num_jog; i++) {
        cout << ANSI_COLOR_YEL << "Jogador " << i + 1 << " (" << perso5[i] << "): " << pontuacao[i] << " quilates" << ANSI_COLOR_RESET << endl;
        }
    }