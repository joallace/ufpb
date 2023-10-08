;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*              MODIFICA��ES PARA USO COM 12F675                   *
;*                FEITAS PELO PROF. MARDSON                        *
;*                     SETEMBRO DE 2022                            *
;*                 BASEADO NO EXEMPLO DO LIVRO                     *
;*           Desbravando o PIC. David Jos� de Souza                *
;*-----------------------------------------------------------------*
;*   MODELO PARA O PIC 12F675                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ARQUIVOS DE DEFINI��ES                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#INCLUDE <p16f628a.inc>	;ARQUIVO PADR�O MICROCHIP PARA 12F675

	__CONFIG _FOSC_INTOSCCLK & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _BOREN_ON & _LVP_ON & _CPD_OFF & _CP_OFF


;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    PAGINA��O DE MEM�RIA                         *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;DEFINI��O DE COMANDOS DE USU�RIO PARA ALTERA��O DA P�GINA DE MEM�RIA
#DEFINE	BANK0	BCF STATUS,RP0	;SETA BANK 0 DE MEM�RIA
#DEFINE	BANK1	BSF STATUS,RP0	;SETA BANK 1 DE MAM�RIA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                         VARI�VEIS                               *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINI��O DOS NOMES E ENDERE�OS DE TODAS AS VARI�VEIS UTILIZADAS 
; PELO SISTEMA

	CBLOCK	0x20	;ENDERE�O INICIAL DA MEM�RIA DE
					;USU�RIO
		W_TEMP		;REGISTRADORES TEMPOR�RIOS PARA USO
		STATUS_TEMP	;JUNTO �S INTERRUP��ES
		DISTANCE	; Distancia lida em bin�rio
		CENTENA		; Centena a a ser mostrada no display
		DEZENA		; Dezena a ser mostrada no display
		UNIDADE		; Unidade a ser mostrada no display
		AUX


		;COLOQUE AQUI SUAS NOVAS VARI�VEIS
		;N�O ESQUE�A COMENT�RIOS ESCLARECEDORES

	ENDC			;FIM DO BLOCO DE DEFINI��O DE VARI�VEIS

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                        FLAGS INTERNOS                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINI��O DE TODOS OS FLAGS UTILIZADOS PELO SISTEMA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                         CONSTANTES                              *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINI��O DE TODAS AS CONSTANTES UTILIZADAS PELO SISTEMA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                           ENTRADAS                              *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINI��O DE TODOS OS PINOS QUE SER�O UTILIZADOS COMO ENTRADA
; RECOMENDAMOS TAMB�M COMENTAR O SIGNIFICADO DE SEUS ESTADOS (0 E 1)

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                           SA�DAS                                *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINI��O DE TODOS OS PINOS QUE SER�O UTILIZADOS COMO SA�DA
; RECOMENDAMOS TAMB�M COMENTAR O SIGNIFICADO DE SEUS ESTADOS (0 E 1)

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       VETOR DE RESET                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	ORG	0x00			;ENDERE�O INICIAL DE PROCESSAMENTO
	GOTO	INICIO
	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    IN�CIO DA INTERRUP��O                        *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; ENDERE�O DE DESVIO DAS INTERRUP��ES. A PRIMEIRA TAREFA � SALVAR OS
; VALORES DE "W" E "STATUS" PARA RECUPERA��O FUTURA

	ORG	0x04			;ENDERE�O INICIAL DA INTERRUP��O
	MOVWF	W_TEMP		;COPIA W PARA W_TEMP
	SWAPF	STATUS,W
	MOVWF	STATUS_TEMP	;COPIA STATUS PARA STATUS_TEMP

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    ROTINA DE INTERRUP��O                        *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; AQUI SER�O ESCRITAS AS ROTINAS DE RECONHECIMENTO E TRATAMENTO DAS
; INTERRUP��ES
	CLRF	TMR2	    ; Resetando o Timer2
	BCF	PIR1, 1
	
	CALL	SONIC_READ
	CALL	CONVERT_TIME_TO_DISTANCE
	MOVFW	DISTANCE
	CALL	CONVERT_BIN_TO_DEC
	CALL	CONVERT_TO_ASCII
	
	MOVLW	.128	    ;Movendo o cursor para a posic�o inicial
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
;*                 ROTINA DE SA�DA DA INTERRUP��O                  *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; OS VALORES DE "W" E "STATUS" DEVEM SER RECUPERADOS ANTES DE 
; RETORNAR DA INTERRUP��O

SAI_INT
	SWAPF	STATUS_TEMP,W
	MOVWF	STATUS		;MOVE STATUS_TEMP PARA STATUS
	SWAPF	W_TEMP,F
	SWAPF	W_TEMP,W	;MOVE W_TEMP PARA W
	RETFIE

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*	            	 ROTINAS E SUBROTINAS                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; CADA ROTINA OU SUBROTINA DEVE POSSUIR A DESCRI��O DE FUNCIONAMENTO
; E UM NOME COERENTE �S SUAS FUN��ES.
	
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
	MOVFW	TMR1H		; Move o byte mais significativo do timer1 para a vari�vel auxiliar
	MOVWF	AUX		; Vamos agora tentar multiplicar esse valor por 4,5 -> 4*tmr + 0,5*tmr
	RLF	AUX, F		; Multplica o valor por 4 ao rotacionar 2x
	RLF	AUX, W
	MOVWF	DISTANCE	; Guarda esse valor na dist�ncia
	RRF	TMR1H, W	; Divide o valor do Timer1 por 2
	ADDWF	DISTANCE, F	; E soma � dist�ncia
	
	MOVFW	TMR1L		; Move o byte menos significativo do timer1 para a vari�vel auxiliar
	MOVWF	AUX
	MOVLW   .58		; Deixamos 58 no work
	DIV_58			; A parte menos significativa � dividida por 58
	    SUBWF   AUX, F	; Subtrai at� ser negativo, incrementando a dist�ncia
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
	INCF    UNIDADE, F  ; Se n�o, incrementa unidade
	MOVFW   UNIDADE
	XORLW   .10	    ; Faz um xor da unidade com 10
	BTFSS   STATUS, Z   ; Se n�o era 10
	GOTO    END_ADJ	    ; Desvia para END_ADJ
						 
	CLRF    UNIDADE	    ; Se sim, zera a unidade
	MOVFW   DEZENA
	XORLW   .9	    ; Faz um xor da dezena com 9
	BTFSS   STATUS, Z   ; Se n�o era 9
	GOTO    INC_DEZENA  ; Incremeta a dezena
	CLRF    DEZENA	    ; Se sim, zera a dezena
	INCF    CENTENA, F  ; Incrementa a centena
	GOTO    END_ADJ

    INC_DEZENA
	INCF    DEZENA, F

    END_ADJ
	DECFSZ  AUX, F	    ; Se for negativo, terminou a convers�o, caso contr�rio continua
	GOTO    START_ADJ
	RETURN
	
CONVERT_TO_ASCII
	MOVLW	.48
	ADDWF	CENTENA, F
	ADDWF	DEZENA, F
	ADDWF	UNIDADE, F
	RETURN

PRINT_CHAR
	MOVWF	TXREG	    ; Move o conte�do de work para o registrador de trasmiss�o
	BANK1
	BTFSS	TXSTA, 1    ; Aguarda a transmiss�o ser conclu�da
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
	BSF	PIE1, 1		; Liga a interrupc�o do Timer2
	MOVLW	B'00100110'
	MOVWF	TXSTA	    	; Ligando a transmiss�o em modo ass�ncrono, com o High Baud Rate
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
;*                     INICIALIZA��O DAS VARI�VEIS                 *
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
