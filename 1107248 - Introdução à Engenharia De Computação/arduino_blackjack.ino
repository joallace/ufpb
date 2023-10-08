/* BlackJack.
 *
 * Código adaptado. Original feito por : Roger D. Linhart  linhartr@gmail.com
 *
 * Rules: Dealer bate até atingir a pontuação 17. Splitting e Doubling Down não estão contidos na regra deste blackjack.
 *
 * Notas: símbolos especiais, como os naipes e o número 10, além das animações, foram feitas por Roger D. Linhart.
 *
 * LCD Display 20x4.
 * LCD RS pin to digital pin 8.
 * LCD Enable pin to digital pin 9.
 * LCD D4 pin to digital pin 4.
 * LCD D5 pin to digital pin 5.
 * LCD D6 pin to digital pin 6.
 * LCD D7 pin to digital pin 7.
 * Keypad feito a partir de uma matriz de botões, usando voltage dividers. E enviando sinais análogicos para A0.
 * Código dos botões.
 * None   - 0.
 * Select(Selecionar) - 1.
 * Left(Esquerda)   - 2.
 * Up(Cima)     - 3.
 * Down(Baixo)  - 5.
 * Right(Direita)  - 4.
 */
//Inicializando a Pitches.
#include "BuzzerMusic.h"

void victory(){
  float notasP[] = {_C5, _R, _C5, _R, _C5, _R, _C5, _R, _GS4, _R, _AS4, _R, _C5, _R, _AS4, _C5};
  float tempoP[] = {0.5, 0.1, 0.5, 0.1, 0.5, 0.1, 1, 0.1, 1, 0.1, 1, 0.25, 0.5, 0.35, 0.25, 1};
  int qntdP = sizeof(notasP)/sizeof(notasP[0]);

  music(notasP, tempoP, qntdP, 160);
}

void buttonSound(){
  float notasP[] = {_C8};
  float tempoP[] = {0.25};
  int qntdP = sizeof(notasP)/sizeof(notasP[0]);

  float notasB[] = {_C6};
  float tempoB[] = {0.25};
  int qntdB = sizeof(notasB)/sizeof(notasB[0]);

  music2(notasP, tempoP, qntdP, notasB, tempoB, qntdB, 160);
}

void lost(){
  float notasP[] = {_B5, _F6, _R, _F6, _F6, _R, _E6, _R, _D6, _R, _C6, _E5, _R, _E5, _C5};
  float tempoP[] = {0.5, 0.5, 0.5, 0.5, 1, 0.5, 1, 0.5, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
  int qntdP = sizeof(notasP)/sizeof(notasP[0]);

  float notasB[] = {_G4, _R, _G4, _G4, _R, _A4, _R, _B4, _R, _C5, _R, _G4, _R, _C4};
  float tempoB[] = {0.5, 1, 0.5, 1, 0.5, 1, 0.5, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
  int qntdB = sizeof(notasB)/sizeof(notasB[0]);

  music2(notasP, tempoP, qntdP, notasB, tempoB, qntdB, 220);
}

// Inicializando a LiquidCrystal.
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
const byte lcdRowMax = 4;
const byte lcdColMax = 20;

// Criação de símbolos especiais. - Roger D. Linhart -
byte heart[8] = {
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
};
byte diamond[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
};
byte spade[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
  B00000,
};
byte club[8] = {
  B01110,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
  B00000,
};
byte back1[8] = {
  B11111,
  B10110,
  B10101,
  B10110,
  B10101,
  B10110,
  B10000,
  B11111,
};
byte back2[8] = {
  B11111,
  B00001,
  B01111,
  B00101,
  B00101,
  B10101,
  B01001,
  B11111,
};
byte ten[8] = {
  B01000,
  B11000,
  B01000,
  B01010,
  B11101,
  B00101,
  B00101,
  B00010,
};

// Inicializando a biblioteca originalmente feita para o shield LCD keypad
#include <DFR_Key.h>
DFR_Key keypad;

// Direcionais.
const byte keySelect = 1;
const byte keyLeft = 2;
const byte keyUp = 3;
const byte keyDown = 5;
const byte keyRight = 4;

// Inicializa Baralho.
const byte cardIndexMax = 52;
const byte rankIndex = 0;
const byte suitIndex = 1;
byte deck[cardIndexMax][2];
byte cardIndex;

// Inicializa mão.
const byte handIndexMax = 6;
const byte dealerIndex = 0;
const byte playerIndex = 1;
byte hand[2][handIndexMax][2];
byte playerHandIndex;
byte dealerHandIndex;
boolean dealerHoleCard = true;  // Estado da distribuição de cartas.
byte handTotal[2][2];           // Necessário dois totais por player.

// Inicializa banco.
// Valor do Banco em doláres e cents.
const long bankInit = 10000;
long bank = bankInit;
const long bankMax = 100000;
const long betMin = 500;
long betMax = bank;
const long betInc = 500;

// Setup.
void setup() {
  // Inicializa serial para realizar debug.
  Serial.begin(9600);

  // Inicializa caracteres especiais.
  lcd.createChar(0, heart);
  lcd.createChar(1, diamond);
  lcd.createChar(2, spade);
  lcd.createChar(3, club);
  lcd.createChar(4, back1);
  lcd.createChar(5, back2);
  lcd.createChar(7, ten);

  // Define número de linhas e de colunas.
  lcd.begin(lcdColMax, lcdRowMax);

  // Cria baralho.
  cardIndex = 0;
  for (byte suit = 0; suit <= 3 ; suit++) {
    for (byte rank = 1; rank <= 13; rank++) {
      deck[cardIndex][rankIndex] = rank;
      deck[cardIndex++][suitIndex] = suit;
    }
  }

  // Inicialização de seed random.
  unsigned long seed=0, count=32;
  while (--count) {
    seed = (seed<<1) | (analogRead(0)&1);
  }
  randomSeed(seed);
  pinMode(BUZZER_PIN, OUTPUT);
}

// Main loop.
void loop() {
  // Display splash.
  displaySplash();

  // Ainda tem dinheiro ?
  while (bank > 0 && bank < bankMax) {
    // Sim, pegue aposta.
    betMax = bank;
    int bet = getBet();

    // Inicia nova rodada.
    dealerHandIndex = 0;
    playerHandIndex = 0;
    dealerHoleCard = true;

    // Esvazia as mãos.
    handTotal[dealerIndex][0] = 0;
    handTotal[dealerIndex][1] = 0;
    handTotal[playerIndex][0] = 0;
    handTotal[playerIndex][1] = 0;

    // Negocia mão inicial.
    dealCard(playerIndex, playerHandIndex++);
    dealCard(dealerIndex, dealerHandIndex++);
    dealCard(playerIndex, playerHandIndex++);
    dealCard(dealerIndex, dealerHandIndex++);
    displayHands();

    //Blackjack do Dealer?
    if (handTotal[dealerIndex][1] == 21) {
      // Sim, chama função Display hole card.
      displayHoleCard(true);

      // Más notícias para o jogador.
      lcd.clear();
      lcd.print("Dealer Blackjack!");

      //Blackjack do Jogador ?
      lcd.setCursor(0, 1);
      if (handTotal[playerIndex][1] == 21) {
        // Sim, Empate.
        lcd.setCursor(4, 1);
        lcd.print("Empate !");
      }
      else {
        // Não, Perdeu.
        lcd.print("Perdeu ");
        lcd.print(toCurrency(bet));
        bank -= bet;
        lost();
      }
    }

    // Blackjack do jogador ?
    else if (handTotal[playerIndex][1] == 21) {
      // Sim, chama função Display Hole Card.
      displayHoleCard(true);

      // Boas notícias para o jogador.
      lcd.clear();
      lcd.print("Jogador Blackjack!");
      lcd.setCursor(0, 1);
      lcd.print("Ganhou ");
      lcd.print(toCurrency(bet * 1.5));
      bank += bet * 1.5;
      victory();
    }

    // Jogo.
    else {
      // keyUp = Bate, keySelect = Fica.
      byte key;
      // Bate ou Fica?
      do {
        lcd.setCursor(18, 0);
        lcd.print("B");
        lcd.setCursor(18, 2);
        lcd.print("S");

        // Cima ou Baixo.
        key = getKey(false, true, false, true, true);
        buttonSound();
        if (key == keyUp) {
          // Jogador Bate.
          dealCard(playerIndex, playerHandIndex++);
          displayHands();
        }
      }
      
      // Continua até que os jogadores atinjam o limite, batam ou fiquem.
      while (playerHandIndex < handIndexMax && handTotal[playerIndex][0] < 21 && key != keySelect);
      
      // Jogador estourou ?
      if (handTotal[playerIndex][0] > 21) {
        // Sim, Más notícias para o jogador.
        displayHoleCard(true);
        lcd.clear();
        lcd.print("Jogador Estourou !");
        lcd.setCursor(0, 1);
        lcd.print("Perdeu ");
        lcd.print(toCurrency(bet));
        bank -= bet;
        lost();
      }
      else {
        // Mão do Dealer
        displayHoleCard(false);
        
        // Dealer sempre fica no 17.
        while (dealerHandIndex < handIndexMax && handTotal[dealerIndex][0] < 17 && handTotal[dealerIndex][1] < 17 ) {
          // Dealer bate.
          dealCard(dealerIndex, dealerHandIndex++);
          displayHands();
          delay(2500);
        }
        delay(1000);
        
        // Total do jogador.
        int playerTotal;
        if (handTotal[playerIndex][1] > 21) {
          playerTotal = handTotal[playerIndex][0];
        }
        else {
          playerTotal = handTotal[playerIndex][1];
        }
        
        // Total do dealer.
        int dealerTotal;
        if (handTotal[dealerIndex][1] > 21) {
          dealerTotal = handTotal[dealerIndex][0];
        }
        else {
          dealerTotal = handTotal[dealerIndex][1];
        }
        
        // Dealer estourou ?
        if (dealerTotal > 21) {
          // Sim, boas notícias para o jogador.
          lcd.clear();
          lcd.print("Dealer Estourou !");
          lcd.setCursor(0, 1);
          lcd.print("Ganhou ");
          lcd.print(toCurrency(bet));
          bank += bet;
          victory();
        }
        
        //Empate ?
        else if (dealerTotal == playerTotal) {
          // Sim, notifica empate.
          lcd.clear();
          lcd.setCursor(4, 1);
          lcd.print("Empate !");
        }
        
        // Qual a maior mão ?
        else {
          if (dealerTotal > playerTotal) {
            // Dealer ganha.
            lcd.clear();
            lcd.print("Dealer Ganha!");
            lcd.setCursor(0, 1);
            lcd.print("Perdeu ");
            lcd.print(toCurrency(bet));
            bank -= bet;
            lost();
          }
          else {
            // Jogador ganha.
            lcd.clear();
            lcd.print("Jogador Ganha!");
            lcd.setCursor(0, 1);
            lcd.print("Ganhou ");
            lcd.print(toCurrency(bet));
            bank += bet;
            victory();
          }
        }
      }
    }
    delay(2000);
  }
  
  // Tá falido ?
  if (bank <= 0) {
    // Sim, tem que sacar mais dinheiro.
    lcd.clear();
    lcd.print("Faliu !");
    displayBank(1);
    delay(4000);
    lcd.clear();
    lcd.print("Saque dinheiro aqui ");
    lcd.setCursor(0, 2);
    lcd.print("Outros ");
    lcd.print(toCurrency(bankInit));
    bank += bankInit;
    // Esperar até apertar Select.
    getKey(false, true, true, true, true);
    buttonSound();
  }
  else {
    // Quebrou o Cassino do CI.
    lcd.clear();
    displayBank(0);
    lcd.setCursor(0, 2);
    lcd.print("Selecione outra mesa");
    bank = bankInit;
    // Esperar até apertar Select.
    getKey(false, true, true, true, true);
    buttonSound();
  }
}

// Função que embaralha e distribui as cartas.
void dealCard(byte player, byte card) {
  // Alguma carta sobrando ?
  if (cardIndex >= cardIndexMax) {
    // Não,embaralha as cartas.
    lcd.clear();
    lcd.print("Embaralhando");
    byte cardTemp[2];
    for (byte cardShuffle = 0; cardShuffle < cardIndexMax ; cardShuffle++) {
      byte cardRandom = random(0,51);
      cardTemp[rankIndex] = deck[cardShuffle][rankIndex];
      cardTemp[suitIndex] = deck[cardShuffle][suitIndex];
      deck[cardShuffle][rankIndex] = deck[cardRandom][rankIndex];
      deck[cardShuffle][suitIndex] = deck[cardRandom][suitIndex];
      deck[cardRandom][rankIndex] = cardTemp[rankIndex];
      deck[cardRandom][suitIndex] = cardTemp[suitIndex];
    }
    cardIndex = 0;
    delay(2000);
    displayHands();
  }

  // Distribui as cartas.
  hand[player][card][rankIndex] = deck[cardIndex][rankIndex];
  hand[player][card][suitIndex] = deck[cardIndex++][suitIndex];

  // Atualiza a pontuação da mão.
  handTotal[player][0] += min(hand[player][card][rankIndex], 10);
  handTotal[player][1] = handTotal[player][0];
  for (byte cardCount = 0; cardCount <= card; cardCount++) {
    // Achou um ás?
    if (hand[player][cardCount][rankIndex] == 1) {
      // Sim
      handTotal[player][1] += 10;
      // Pontuação do ás vira 1.
      cardCount = card + 1;
    }
  }
  Serial.println("Player #" + String(player) + "\tCard #" + String(card) + "\tCard: " + String(hand[player][card][rankIndex]) + "-" + String(hand[player][card][suitIndex]));
}

// Exibe as mãos na tela.
void displayHands() {
  // Mostra mão do Dealer.
  lcd.clear();
  lcd.print("D:");
  displayHand(dealerIndex, dealerHandIndex);

  // Mostra a mão do jogador.
  lcd.setCursor(0, 2);
  lcd.print("J:");
  displayHand(playerIndex, playerHandIndex);
}

// Mostra mão.
void displayHand(byte displayHandIndex, byte displayHandIndexMax) {
  // Mostra as cartas.
  for (byte card = 0; card < displayHandIndexMax; card++) {
    // Dealer recebeu cartas ?
    if (displayHandIndex == dealerIndex && card == 0 && dealerHoleCard) {
      // Mostra carta virada.
      lcd.write((uint8_t)4);
      lcd.write((uint8_t)5);
    }
    else {
      // Mostra rank da carta.
      switch (hand[displayHandIndex][card][rankIndex]) {
      case 1:
        lcd.print("A");
        break;
      case 10:
        lcd.write((uint8_t)7);
        break;
      case 11:
        lcd.print("J");
        break;
      case 12:
        lcd.print("Q");
        break;
      case 13:
        lcd.print("K");
        break;
      default:
        lcd.print(hand[displayHandIndex][card][rankIndex]);
      }
      // Mostra naipe da carta.  
      lcd.write((uint8_t)hand[displayHandIndex][card][suitIndex]);
    }
  }
}

// Função que mostra cartas recebidas
void displayHoleCard(boolean pause) {
      delay(2000 * pause);
      dealerHoleCard = false;
      displayHands();
      delay(2000);
}

// Mostra a conta bancária do jogador.
// Parametro determina a coluna que foi inserida.
void displayBank(byte row) {
  lcdClearRow(row);
  lcd.print("Banco ");
  lcd.print(toCurrency(bank));
}

// Pega aposta.
int getBet() {
  // Mostra ao jogador quanto dinheiro ele tem em mãos.
  displayBank(0);
  int bet = betMin;

  // keyUp = Aumenta aposta.
  // keyDown = Diminui aposta.
  // keySelect = Confirma aposta.
  byte key;
  do {
    // Resposta do jogador.
    lcdClearRow(1);
    lcd.print("Sua aposta ? ");
    lcd.print(toCurrency(bet));

    // Pega resposta do jogador.
    key = getKey(false, true, false, false, true);
    buttonSound();
    // Aumenta a aposta caso seja menor que a aposta máxima, 50 doláres, e menor que a quantidade total no banco.
    if (key == keyUp && bet < betMax && bet < bank) {
      bet += betInc;
    }
    // Diminui aposta caso seja maior que a aposta mínima, 5 doláres.
    else if (key == keyDown && bet > betMin) {
      // Diminui aposta.
      bet -= betInc; 
    }
  }
  // Continua até que jogador confirme a aposta.
  while (key != keySelect);
  return bet;
}

// Limpa a tela por coluna.
// Seta cursor na coluna que foi apagada na tela.
void lcdClearRow(byte row) {
  if (row >= 0 && row < lcdRowMax) {  
    lcd.setCursor(0, row);
    for (int x = 0; x < lcdColMax; x++) {
      lcd.print(" ");
    }
    lcd.setCursor(0, row);
  }
}

// Pega o sinal enviado pelos botões.
// Parametros pega o sinal de todos os botões.
byte getKey(boolean maskSelect, boolean maskLeft, boolean maskUp, boolean maskDown, boolean maskRight) {
  byte key;
  do {
    key = keypad.getKey();
  }
  while (key == 0 || key == 255 || \
    (key == keySelect && maskSelect) || \
    (key == keyLeft && maskLeft) || \
    (key == keyUp && maskUp) || \
    (key == keyDown && maskDown) || \
    (key == keyRight && maskRight));

  // Delay de 0,4 de seg para detectar.
  delay(250);

  return key;
}

// Converte de long para correspondente em string.
String toCurrency(long value) {
  String dollars = String(value / 100);
  String cents = String(value % 100) + "0";
  cents = cents.substring(0,2);
  /*retorna "$" + dollars + "." + cents;*/
  return "$" + String(value / 100) + "." + String(String(value % 100) + "0").substring(0,2);
}

// Mostra splash.
void displaySplash() {
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.write((uint8_t)4);
  lcd.write((uint8_t)5);
  delay(1000);
  lcd.setCursor(7, 1);
  lcd.write((uint8_t)4);
  lcd.write((uint8_t)5);
  delay(1000);
  lcd.setCursor(3, 1);
  lcd.print("J");
  lcd.write((uint8_t)1);
  delay(1000);
  lcd.setCursor(7, 1);
  lcd.print("A");
  lcd.write((uint8_t)2);
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Blackjack!");

  // Animação.
  for (byte x = 15; x < 30; x++) {
    if (x % 2) {
      lcd.display();
    }
    else {
      lcd.noDisplay();
    }
    delay(pow(31 - x, 2) + 200);
  }
  delay(1000);
}
