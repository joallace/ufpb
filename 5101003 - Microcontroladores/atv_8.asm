;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*              MODIFICAÇÕES PARA USO COM 12F675                   *
;*                FEITAS PELO PROF. MARDSON                        *
;*                     FEVEREIRO DE 2023                           *
;*                 BASEADO NO EXEMPLO DO LIVRO                     *
;*           Desbravando o PIC. David José de Souza                *
;*-----------------------------------------------------------------*
;*   MODELO PARA O PIC 12F675                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ARQUIVOS DE DEFINIÇÕES                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#INCLUDE <p12f675.inc>	;ARQUIVO PADRÃO MICROCHIP PARA 12F675

	__CONFIG _BODEN_OFF & _CP_OFF & _PWRTE_ON & _WDT_OFF & _MCLRE_ON & _INTRC_OSC_NOCLKOUT

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    PAGINAÇÃO DE MEMÓRIA                         *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;DEFINIÇÃO DE COMANDOS DE USUÁRIO PARA ALTERAÇÃO DA PÁGINA DE MEMÓRIA
#DEFINE	BANK0	BCF STATUS,RP0	;SETA BANK 0 DE MEMÓRIA
#DEFINE	BANK1	BSF STATUS,RP0	;SETA BANK 1 DE MAMÓRIA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                         VARIÁVEIS                               *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DOS NOMES E ENDEREÇOS DE TODAS AS VARIÁVEIS UTILIZADAS 
; PELO SISTEMA

	CBLOCK	0x20	;ENDEREÇO INICIAL DA MEMÓRIA DE
					;USUÁRIO
		W_TEMP		;REGISTRADORES TEMPORÁRIOS PARA USO
		STATUS_TEMP	;JUNTO ÀS INTERRUPÇÕES
		COUNTER		; Contador utilizado para múltiplas aplicacões
		AUX_CHAR	; Caractere auxiliar para impressão no display
		TMR_COUNTER	; Registra se o timer1 completou meio ciclo de 1s
		TEMPERATURE
		HUMIDITY
		CHECKSUM
		DISPLAY_TEN	; Dezena do valor a ser printado (umidade ou temperatura)
		DISPLAY_UNIT	; Unidade do valor a ser printado
		CURRENT_BIT	; Bit utilizado para marcar o bit atual na leitura dos dados do DHT11


		;COLOQUE AQUI SUAS NOVAS VARIÁVEIS
		;NÃO ESQUEÇA COMENTÁRIOS ESCLARECEDORES

	ENDC			;FIM DO BLOCO DE DEFINIÇÃO DE VARIÁVEIS

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                        FLAGS INTERNOS                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODOS OS FLAGS UTILIZADOS PELO SISTEMA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                         CONSTANTES                              *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODAS AS CONSTANTES UTILIZADAS PELO SISTEMA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                           ENTRADAS                              *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODOS OS PINOS QUE SERÃO UTILIZADOS COMO ENTRADA
; RECOMENDAMOS TAMBÉM COMENTAR O SIGNIFICADO DE SEUS ESTADOS (0 E 1)

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                           SAÍDAS                                *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODOS OS PINOS QUE SERÃO UTILIZADOS COMO SAÍDA
; RECOMENDAMOS TAMBÉM COMENTAR O SIGNIFICADO DE SEUS ESTADOS (0 E 1)

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       VETOR DE RESET                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	ORG	0x00			;ENDEREÇO INICIAL DE PROCESSAMENTO
 	GOTO	INICIO
	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    INÍCIO DA INTERRUPÇÃO                        *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; ENDEREÇO DE DESVIO DAS INTERRUPÇÕES. A PRIMEIRA TAREFA É SALVAR OS
; VALORES DE "W" E "STATUS" PARA RECUPERAÇÃO FUTURA

	ORG	0x04			;ENDEREÇO INICIAL DA INTERRUPÇÃO
	MOVWF	W_TEMP		;COPIA W PARA W_TEMP
	SWAPF	STATUS,W
	MOVWF	STATUS_TEMP	;COPIA STATUS PARA STATUS_TEMP

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    ROTINA DE INTERRUPÇÃO                        *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; AQUI SERÃO ESCRITAS AS ROTINAS DE RECONHECIMENTO E TRATAMENTO DAS
; INTERRUPÇÕES
	DECFSZ	TMR_COUNTER
	GOTO	TMR_500
	
	BANK1			
	CLRF	OPTION_REG	; Alterando as configuracoes do prescaler do timer 1
	BCF	TRISIO, 2	; GP2 como saída
	BANK0
	
	BCF	GPIO, 2
	MOVLW	.246
	CALL	TMR_WAIT
	BSF	GPIO, 2
	
	BANK1
	BSF	TRISIO, 2	; GP2 como entrada
	BANK0
	
	BTFSC	GPIO, 2		; Aguarda até a porta ser 0
	GOTO	$-1
	
	MOVLW	.215		; Espera por 80us
	CALL	TMR_WAIT
	
	BTFSS	GPIO, 2
	GOTO	TMR_1000	; Caso a GP2 não esteja em alto, ocorreu um erro então aguardaremos 1s até a próxima leitura
	
	MOVLW	.215		; Espera por mais 80us
	CALL	TMR_WAIT
	
	CALL	READ_BYTE
	MOVFW	AUX_CHAR
	MOVWF	HUMIDITY
	
	CALL	READ_BYTE	;  Leitura em vazio, já que não há dados decimais para este sensor
	
	CALL	READ_BYTE
	MOVFW	AUX_CHAR
	MOVWF	TEMPERATURE
	
	CALL	READ_BYTE	;  Leitura em vazio, já que não há dados decimais para este sensor
	
	CALL	READ_BYTE	; Fazendo o checksum para validar os dados
	MOVFW	AUX_CHAR
	MOVWF	CHECKSUM
	
	MOVFW	HUMIDITY
	SUBWF	CHECKSUM, F
	MOVFW	TEMPERATURE
	SUBWF	CHECKSUM, F
	
	BTFSS	STATUS, C
	CALL	READ_ERR	; Caso seja negativo, houve um erro de leitura e vamos invalidar os resultados
		

    TMR_1000
	MOVLW .2	; Faremos o Timer1 rodar 2x, assim chegando à 1s.
	MOVWF TMR_COUNTER
    TMR_500
	BANK1
	MOVLW	B'00000100'
	MOVWF	OPTION_REG	;DEFINE OPÇÕES DE OPERAÇÃO
	BANK0
	BCF PIR1, 0
	MOVLW .11	; Com esse valor no Timer1, conseguimos alcançar 500ms até o timer estourar.
	MOVWF TMR1H

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                 ROTINA DE SAÍDA DA INTERRUPÇÃO                  *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; OS VALORES DE "W" E "STATUS" DEVEM SER RECUPERADOS ANTES DE 
; RETORNAR DA INTERRUPÇÃO

SAI_INT
	SWAPF	STATUS_TEMP,W
	MOVWF	STATUS		;MOVE STATUS_TEMP PARA STATUS
	SWAPF	W_TEMP,F
	SWAPF	W_TEMP,W	;MOVE W_TEMP PARA W
	RETFIE

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*	            	 ROTINAS E SUBROTINAS                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; CADA ROTINA OU SUBROTINA DEVE POSSUIR A DESCRIÇÃO DE FUNCIONAMENTO
; E UM NOME COERENTE ÀS SUAS FUNÇÕES.
	
	
READ_ERR
    CLRF    TEMPERATURE
    CLRF    HUMIDITY
    RETURN
	
READ_BYTE
    MOVLW   .9
    MOVWF   COUNTER
    CLRF    AUX_CHAR	; Variável que será usada como saída
    MOVLW   B'10000000'	; Como o envio é feito a partir do bit mais significativo, iremos
    MOVWF   CURRENT_BIT ; fazer uma soma partindo de 128 e rotacionando o conteúdo a cada iteracão    
    
    READ_ITERATION
	DECFSZ  COUNTER
	GOTO    $+2
	RETURN

	MOVLW   .215		; Espera por 80us (50us + 30us do possível 0)
	CALL    TMR_WAIT

	BTFSS   GPIO, 2		; Checa o valor enviado pelo DHT11
	GOTO    PREP_NEXT_IT	; Caso seja 0, nos preparamos para próxima iteracão
	
	MOVFW	CURRENT_BIT
	ADDWF   AUX_CHAR, F
	BTFSC   GPIO, 2
	GOTO	$-1		; Aguarda até o fim do 1
	PREP_NEXT_IT
	    RRF	    CURRENT_BIT, F
	    GOTO    READ_ITERATION
    
TMR_WAIT
    MOVWF   TMR0
    BCF	    INTCON, 2
    BTFSS   INTCON, 2
    GOTO    $-1
    RETURN
    
TMR_WAIT_LCD		    ; Espera o tempo necessário para a leitura do LCD
    MOVLW   .209
    CALL    TMR_WAIT
    RETURN
    
PRINT_CHAR		    ; Funcão que printa um caractere que esteja no AUX_CHAR
    DECFSZ  COUNTER	    ; É necessário ajustar o contador para varrer os 8 bits
    GOTO    $+2
    RETURN
	    
    BTFSS   AUX_CHAR, 0
    GOTO    SET_LOW
    GOTO    SET_HIGH
	
SET_HIGH		    ; Seta o bit e espera o tempo
    BSF	    GPIO, 1
    CALL    TMR_WAIT_LCD
    RRF	    AUX_CHAR
    GOTO    PRINT_CHAR
	
SET_LOW			    ; Limpa o bit e espera o tempo
    BCF	    GPIO, 1
    CALL    TMR_WAIT_LCD
    RRF	    AUX_CHAR
    GOTO    PRINT_CHAR
    
GET_DECIMAL_NUMBER	    ; Funcão para obter o número decimal a partir do número binário
    CLRF    DISPLAY_TEN
    CLRF    DISPLAY_UNIT
    
    MOVLW   .10
    SUBWF   AUX_CHAR, F	    ; AUX_CHAR contém o valor em binário da temperatura ou umidade
    BTFSS   STATUS, 0	    ; Subtrai até o resultado ser negativo
    GOTO    $+3
    INCF    DISPLAY_TEN	    ; Se não for negativo, incrementamos a dezena
    GOTO    $-4
	
    ADDWF   AUX_CHAR, F	    ; Soma novamente para que o número fique positivo
    MOVFW   AUX_CHAR	    ; Este é o resto, no caso, a unidade
    MOVWF   DISPLAY_UNIT
    
    RETURN


;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIO DO PROGRAMA                          *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
INICIO
	BANK1				;ALTERA PARA O BANCO 1
	MOVLW	B'00000000' ;CONFIGURA TODAS AS PORTAS DO GPIO (PINOS)
	MOVWF	TRISIO		;COMO SAÍDAS
	CLRF	ANSEL 		;DEFINE PORTAS COMO Digital I/O
	MOVLW	B'00000100'
	MOVWF	OPTION_REG	;DEFINE OPÇÕES DE OPERAÇÃO
	MOVLW	B'11000000'
	MOVWF	INTCON		;DEFINE OPÇÕES DE INTERRUPÇÕES
	BSF	PIE1, 0
	MOVWF	0X3FF
	CALL	OSCCAL
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00000111'
	MOVWF	CMCON		;DEFINE O MODO DE OPERAÇÃO DO COMPARADOR ANALÓGICO
	MOVLW	B'00110001'
	MOVWF	T1CON		; Configurações do Timer1

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZAÇÃO DAS VARIÁVEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	MOVLW .11
	MOVWF TMR1H
	MOVLW .2
	MOVWF TMR_COUNTER
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
MAIN
	BCF	GPIO, 1	    ; Start printing
	CALL	TMR_WAIT_LCD
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	.128	    ; Ajusta o cursor do LCD para o comeco da primeira linha
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'J'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'o'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'a'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'o'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	.144	    ; Ajusta o cursor do LCD para a segunda linha
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'T'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'e'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'm'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'p'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'='
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVFW	TEMPERATURE
	MOVWF	AUX_CHAR
	CALL	GET_DECIMAL_NUMBER
	
	MOVLW	.9	    ; Printa a dezena
	MOVWF	COUNTER
	MOVFW	DISPLAY_TEN
	ADDLW	.48	    ; Soma 48 para transformar o número em um caractere ASCII
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa a unidade
	MOVWF	COUNTER
	MOVFW	DISPLAY_UNIT
	ADDLW	.48
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'c'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	' '
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'U'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'R'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'='
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVFW	HUMIDITY
	MOVWF	AUX_CHAR
	CALL	GET_DECIMAL_NUMBER
	
	MOVLW	.9	    ; Printa a dezena
	MOVWF	COUNTER
	MOVFW	DISPLAY_TEN
	ADDLW	.48
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa a unidade
	MOVWF	COUNTER
	MOVFW	DISPLAY_UNIT
	ADDLW	.48
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	'%'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	BSF	GPIO, 1	    ; Stop printing
	CALL	TMR_WAIT_LCD


	GOTO	MAIN

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       FIM DO PROGRAMA                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	END
