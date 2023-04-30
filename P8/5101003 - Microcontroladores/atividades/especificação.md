## Atividade 6: atv_6.asm
- **Tema**: Conversor A/D: medindo de 0 a 5V em uma escala de 0 a 9 e indicação em BCD
- **Objetivo**: Exercício de familiarização com o comparador do PIC.
- **Contexto**: Um valor de tensão entre 0 e 5V deve ser representado em uma escala discreta, indicando a escala de 0 a 9 em BCD, para representação em um display de 7 segmentos.

### Especificações
- NÃO é permitida a utilização do comparador;
- A tensão de entrada é de 0 a 5V;
- A conversão de tensão para a escala de 0 a 9 deve ser efetuada através do conversor A/D;
- O valor da tensão deve ser convertido para codificação BCD para ser conectado ao display de 7 segmentos;
- A indicação deve ser efetuada, em modo cíclico, com taxa de amostragem de 100ms;
- Os bits do display b3,b2,b1,b0 devem ser conectados às portas GP5,GP4,GP2,GP0, respectivamente;
- Os níveis de tensão e a escala correspondente está na descrito na tabela a seguir:

Valor da tensão (V) | Valor mostrado no display
|-|-|
V<0,5     | 0
0,5<V<1,0 | 1
1,0<V<1,5 | 2
1,5<V<2,0 | 3
2,0<V<2,5 | 4
2,5<V<3,0 | 5
3,0<V<3,5 | 6
3,5<V<4,0 | 7
4,0<V<4,5 | 8
4,5<V     | 9

<hr>

## Atividade 5: atv_5.asm
- Tema: Comparador: medindo de 0 a 3,5V em uma escala de 0 a 7 e indicação em BCD
- Objetivo: Exercício de familiarização com o comparador do PIC.
- Contexto: Um valor de tensão entre 0 e 3,5V deve ser representado em uma escala discreta, indicando a escala de 0 a 7 em BCD, para representação em um display de 7 segmentos.

### Especificações
- NÃO é permitida a utilização do conversor A/D;
- A tensão de entrada é de 0 a 3,5V;
- A conversão de tensão para a escala de 0 a 9 deve ser efetuada através do comparador;
- O valor da tensão deve ser convertido para codificação BCD para ser conectado ao display de 7 segmentos;
- A indicação deve ser efetuada, em modo cíclico e tão rápido quanto possível (limitado pela velocidade
do microcontrolador);
- Os bits do display b3,b2,b1,b0 devem ser conectados às portas GP5,GP4,GP2,GP0, respectivamente;
- Os níveis de tensão e a escala correspondente está na descrito na tabela a seguir:

Valor da tensão (V) | Valor mostrado no display
|-|-|
V<0,5     | 0
0,5<V<1,0 | 1
1,0<V<1,5 | 2
1,5<V<2,0 | 3
2,0<V<2,5 | 4
2,5<V<3,0 | 5
3,0<V<3,5 | 6
3,5<V<4,0 | 7

<hr>

## Atividade 4: atv_4.asm
- Tema: Controlador automotivo: PISCA
- Objetivo: Exercícios para gerenciamento de portas e de tempo (com TIMERs e interrupção).
- Contexto: Sistema de sinalização automotiva, controlando o "pisca-pisca" lados direito e esquerdo, quando acionados.

### Especificações
- O sistema contém um interruptor de 3 posições, para acender 2 LEDs (LED-E e LED-D):
- Quando na posição central, o LED-E e o LED-D permanecem apagados;
- Quando na posição E (esquerda), o LED-E piscará com frequência de 1 Hz;
- Quando na posição D (direita), o LED-D piscará com frequência de 1 Hz;
- O sistema contém um interruptor (liga-desliga), para piscar os dois LEDs ao mesmo tempo (função
alerta), com frequência de 1 Hz. Esse interruptor deve ter maior prioridade;
- GP0 deverá ser utilizado com o interruptor que comandará a função "alerta";
- GP1 e GP2 deverão ser utilizados para o interruptor de 3 posições;
- GP4 e GP5 deverão ser utilizados, respectivamente, para os LED-E e LED-D;
- O uso de interrupção é obrigatório.

<hr>

## Atividade 3: atv_3.asm
- Tema: Controlador de intensidade de um LED
- Objetivo: Exercícios para gerenciamento de portas e de tempo.

### Especificações
- Duas chaves serão utilizadas para configurar a intensidade LED, alterando o duty cycle, conforme tabela abaixo:

Chaves | Duty cycle
-------|-----------
00 | 5%
01 | 20%
10 | 60%
11 | 100%

- Quando houver duty cycle diferente de 100%, a frequência do sinal deve ser de 500Hz;
- GP0 deverá ser utilizado para o bit 0 da chave;
- GP1 deverá ser utilizado para o bit 1 da chave;
- GP5 deverá ser utilizado para ativar o LED
- Pelo menos um TIMER deve ser utilizado.

<hr>

## Atividade 2: atv_2.asm
- Tema: Produto de dois números em assembly
- Objetivo: Exercícios de familiarização com o conjunto de instruções do PIC.

### Especificações
- Dado dois valores em hexadecimal, armazenados nas variáveis X1 e X2 (1 byte cada), propor um
programa na linguagem assembly (PIC12F675) para efetuar o produto desses números;
- Como o resultado do produto pode ser um valor maior que FF, considera-se que os resultados devem
ser apresentados em dois bytes (variáveis R1 e R2);
- A variável R2 será utilizada como byte mais significativo e a variável R1 como byte menos significativo;
- Se o resultado do produto for menor ou igual a 00FF, a variável R2 deverá conter zero.
- Veja os exemplos:

X1 | X2 | R2 | R1
-|-|-|-
25 | 4A | 0A | B2
FA | 51 | 4F | 1A
12 | 1A | 01 | D4
0E | 0A | 00 | 8C

<hr>

## Atividade 1: atv_1.jpeg
- **Tema**: Divisão de 2 números e resultado com uma casa decimal
- **Objetivo**: Exercício com algoritmo para posterior implementação com microcontrolador.
- **Contexto**: Dados dois valores, proponha um ALGORITMO que descreva as instruções necessárias para efetuar a divisão desses números, fornecendo o resultado com precisão de uma casa decimal.


### Especificações

- Numerador (A) e denominador (B) são números inteiros, com valores entre 0 e 255 (um byte);
- Supor que o denominador (B) não será zero;
- O resultado deve ser armazenado em duas variáveis inteiras, sendo uma para armazenar a parte
inteira (X) da divisão e a outra para armazenar a parte decimal (Y), conforme alguns exemplos abaixo:

| A | B | Resultado | Arredondado | X | Y |
|---|---|-----------|-------------|---|---|
| 9 | 5 | 1,8       | 1,8         | 1 | 8 |
| 15| 4 | 3,75      | 3,8         | 3 | 8 |
| 8 | 3 | 2,66667   | 2,7         | 2 | 7 |
|241| 40| 6,025     | 6,0         | 6 | 0 |

- As regras de arredondamento devem ser utilizadas;
- O ALGORITMO deve ser escrito em Portugol (pseudocódigo escrito em português);
- Pela própria definição, o ALGORITMO deve ter uma sequência de passos descritivos, ordenados e
sem ambiguidade;
- Os passos descritivos não podem conter ações abstratas ou que impliquem na utilização de outras
operações diferentes das 3 operações aritméticas básicas: soma, subtração e multiplicação (+, - e *);
- A utilização de estruturas condicionais NÃO PODE CONTER mais de um teste lógico (por estrutura);
- Não esqueçam de colocar comentários no seu algoritmo