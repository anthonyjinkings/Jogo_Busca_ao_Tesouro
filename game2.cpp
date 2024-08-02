#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <locale>
#include <codecvt>
#include <windows.h>
#define ANSI_COLOR_CYN      "\e[0;36m" //cores em ANSI utilizadas 
#define ANSI_COLOR_RED     "\e[0;31m"


using namespace std;

int main() {
    system("chcp 65001");
    int num_jog, perso1, perso2, perso3, perso4, nume_jog=1, escolha;
    string perso5[5];
    string nome_jog1, nome_jog2, nome_jog3, nome_jog4, emoji[]={"🐻", "😽", "🧙‍♂", "🦸‍♂"};
    string emoji_matriz[]={"💎"};
    int escolhas[5];
    int i;
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
        string matriz[6][6];
        int l, c;
        srand(time(NULL));
        for (l=0; l<6; l++) {
            for (c=0; c<6; c++) {
                matriz[l][c] = emoji_matriz[0];
            }
        }
        for (l=0; l<6; l++) {
            for (c=0; c<6; c++) {
                cout << setw(5) << matriz[l][c];
            }
            cout << endl;
        }
    }
