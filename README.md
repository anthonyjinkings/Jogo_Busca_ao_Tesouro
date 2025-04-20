
# 💎 Jogo da Mineração de Diamantes

Este é um jogo de mineração de diamantes em C++ para 2 a 4 jogadores, onde cada jogador tenta encontrar diamantes escondidos em uma mina, evitando armadilhas e utilizando ferramentas estratégicas como drones, radar de mina e dicas. O objetivo é acumular o maior número de **quilates (pontos)** até o fim da partida.

---

## 🎮 Como Jogar

- O jogo é jogado em uma matriz **6x6** representando a mina.
- Cada célula contém um **diamante 💎**, uma **armadilha 🧨**, uma **dica 💰** ou o **vilão 😈**.
- Os jogadores se revezam escolhendo posições para minerar.
- O número de rodadas varia conforme a quantidade de jogadores:
  - 2 jogadores → 18 rodadas cada
  - 3 jogadores → 12 rodadas cada
  - 4 jogadores → 9 rodadas cada

---

## 🧠 Recursos do Jogo

- **Radar de Mina**: revela dinamites próximas.
- **Drone**: escaneia parte da matriz.
- **Dica**: revela se há algo suspeito por perto (uso único por jogador).
- **Vilão**: visível o tempo todo. O jogador pode enfrentá-lo quando quiser. Ele possui entre 1 e 100 quilates. Se o jogador vencer, ganha 40 quilates; se perder, perde 40.

---

## 🏆 Ranking Final

- Ao final do jogo, o ranking dos jogadores é exibido, mostrando quem acumulou mais quilates.

---

## 🛠️ Tecnologias Utilizadas

- Linguagem: **C++**
- Interface: **Console (CLI)**
- Emojis e lógica: Para maior imersão e desafio

---

## 👨‍💻 Desenvolvedor

Desenvolvido por **Anthony Jinkings da Mata**, estudante de Ciência da Computação.
