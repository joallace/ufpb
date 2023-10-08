;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*              MODIFICAÇÕES PARA USO COM 12F675                   *
;*                FEITAS PELO PROF. MARDSON                        *
;*                     SETEMBRO DE 2022                            *
;*                 BASEADO NO EXEMPLO DO LIVRO                     *
;*           Desbravando o PIC. David José de Souza                *
;*-----------------------------------------------------------------*
;*   MODELO PARA O PIC 12F675                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ARQUIVOS DE DEFINIÇÕES                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#INCLUDE <p16f628a.inc>	;ARQUIVO PADRÃO MICROCHIP PARA 12F675

	__CONFIG _FOSC_INTOSCCLK & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _BOREN_ON & _LVP_ON & _CPD_OFF & _CP_OFF


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
		DISTANCE	; Distancia lida em binário
		CENTENA		; Centena a a ser mostrada no display
		DEZENA		; Dezena a ser mostrada no display
		UNIDADE		; Unidade a ser mostrada no display
		AUX


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
	CLRF	TMR2	    ; Resetando o Timer2
	BCF	PIR1, 1
	
	CALL	SONIC_READ
	CALL	CONVERT_TIME_TO_DISTANCE
	MOVFW	DISTANCE
	CALL	CONVERT_BIN_TO_DEC
	CALL	CONVERT_TO_ASCII
	
	MOVLW	.128	    ;Movendo o cursor para a posicão inicial
	CALL	PRINT_CHAR
	
	MOVLW	'D'
	CALL	PRINT_CHAR
	MOVLW	'='
	CALL	PRINT_CHAR
	MOVFW	CENTENA
	CALL	PRINT_CHAR
	MOVFW	DEZENA
	CALL	PRINT_CHAR
	MOVFW	UNIDADE
	CALL	PRINT_CHAR
	MOVLW	'c'
	CALL	PRINT_CHAR
	MOVLW	'm'
	CALL	PRINT_CHAR
	

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
	
SONIC_READ
	BCF	PIR1, 0	    ; Reseta o Timer1
	CLRF	TMR1L
	CLRF	TMR1H
	BCF	INTCON, 2
	
	BSF	PORTB, 3    ; Liga o trigger
	MOVLW	.254
	MOVWF	TMR0	    ; Configura o timer 10us
	BTFSS	INTCON, 2   ; Aguarda o timer
	GOTO	$-1
	BCF	PORTB, 3    ; Desliga o trigger
	
	BTFSS	PORTB, 0    ; Aguarda o ECHO subir
	GOTO	$-1
	BSF	T1CON, 0    ; Liga o Timer1 e inicia a contagem
	BTFSC	PORTB, 0
	GOTO	$-1	    ; Aguarda o ECHO descer
	BCF	T1CON, 0    ; Desliga o Timer1
	
	RETURN
	
CONVERT_TIME_TO_DISTANCE
	MOVFW	TMR1H		; Move o byte mais significativo do timer1 para a variável auxiliar
	MOVWF	AUX		; Vamos agora tentar multiplicar esse valor por 4,5 -> 4*tmr + 0,5*tmr
	RLF	AUX, F		; Multplica o valor por 4 ao rotacionar 2x
	RLF	AUX, W
	MOVWF	DISTANCE	; Guarda esse valor na distância
	RRF	TMR1H, W	; Divide o valor do Timer1 por 2
	ADDWF	DISTANCE, F	; E soma à distância
	
	MOVFW	TMR1L		; Move o byte menos significativo do timer1 para a variável auxiliar
	MOVWF	AUX
	MOVLW   .58		; Deixamos 58 no work
	DIV_58			; A parte menos significativa é dividida por 58
	    SUBWF   AUX, F	; Subtrai até ser negativo, incrementando a distância
	    BTFSS   STATUS, 0
	    RETURN
	    INCF    DISTANCE, F
	    GOTO    DIV_58
	    
CONVERT_BIN_TO_DEC
	MOVWF   AUX	    ; Salva valor a converter em REG_AUX
	CLRF    UNIDADE
	CLRF    DEZENA
	CLRF    CENTENA

	MOVF	AUX, F	    ; Fazendo aux=aux apenas para atualizar o status
	BTFSC   STATUS, Z   ; Valor a converter resultou em zero?
	RETURN		    ; Se sim, retorna.

    START_ADJ
	INCF    UNIDADE, F  ; Se não, incrementa unidade
	MOVFW   UNIDADE
	XORLW   .10	    ; Faz um xor da unidade com 10
	BTFSS   STATUS, Z   ; Se não era 10
	GOTO    END_ADJ	    ; Desvia para END_ADJ
						 
	CLRF    UNIDADE	    ; Se sim, zera a unidade
	MOVFW   DEZENA
	XORLW   .9	    ; Faz um xor da dezena com 9
	BTFSS   STATUS, Z   ; Se não era 9
	GOTO    INC_DEZENA  ; Incremeta a dezena
	CLRF    DEZENA	    ; Se sim, zera a dezena
	INCF    CENTENA, F  ; Incrementa a centena
	GOTO    END_ADJ

    INC_DEZENA
	INCF    DEZENA, F

    END_ADJ
	DECFSZ  AUX, F	    ; Se for negativo, terminou a conversão, caso contrário continua
	GOTO    START_ADJ
	RETURN
	
CONVERT_TO_ASCII
	MOVLW	.48
	ADDWF	CENTENA, F
	ADDWF	DEZENA, F
	ADDWF	UNIDADE, F
	RETURN

PRINT_CHAR
	MOVWF	TXREG	    ; Move o conteúdo de work para o registrador de trasmissão
	BANK1
	BTFSS	TXSTA, 1    ; Aguarda a transmissão ser concluída
	GOTO	$-1
	BANK0
	RETURN

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIO DO PROGRAMA                          *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
INICIO
	BCF	STATUS, RP1	; Operando somente nos bancos 0 e 1
	BANK1
	CLRF	OPTION_REG
	CLRF	VRCON
	MOVLW	B'11000000'
	MOVWF	INTCON
	MOVLW	B'00000111'	; RB0 -> echo, RB3 -> trigger
	MOVWF	TRISB		; Como requerido pela USART, definindo RB1 e RB2 como entradas
	BSF	PIE1, 1		; Liga a interrupcão do Timer2
	MOVLW	B'00100110'
	MOVWF	TXSTA	    	; Ligando a transmissão em modo assíncrono, com o High Baud Rate
	MOVLW	.25
	MOVWF	SPBRG		; Definindo o Baud Rate em 9600 (Fosc=4MHz)
	BANK0
	CLRF	PORTB
	MOVLW	B'10000000'
	MOVWF	RCSTA		; Ligando as portas seriais
	MOVLW	B'00000111'
	MOVWF	CMCON		; Desliga o comparador
	MOVLW	B'00000001'
	MOVWF	T1CON		; Liga o Timer1
	MOVLW	B'11111111'	; Liga o Timer2
	MOVWF	T2CON

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZAÇÃO DAS VARIÁVEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
MAIN
	GOTO	MAIN

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       FIM DO PROGRAMA                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	END
