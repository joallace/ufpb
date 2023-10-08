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
#INCLUDE <p12f675.inc>	;ARQUIVO PADR�O MICROCHIP PARA 12F675

	__CONFIG _BODEN_OFF & _CP_OFF & _PWRTE_ON & _WDT_OFF & _MCLRE_ON & _INTRC_OSC_NOCLKOUT

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
	CALL START_TIMER

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
	
; Func�o para incializac�o do timer1 para estourar com 100ms
START_TIMER
	MOVLW .60
	MOVWF TMR1H
	BCF   PIR1, 0
	RETURN
	
; Cada uma das func�es SET_X liga os LEDS correspondentes ao valor de X
SET_0
	CLRF GPIO
	GOTO MAIN
	
SET_1
	MOVLW B'00000001'
	MOVWF GPIO
	GOTO MAIN
	
SET_2
	MOVLW B'00000100'
	MOVWF GPIO
	GOTO MAIN
	
SET_3
	MOVLW B'00000101'
	MOVWF GPIO
	GOTO MAIN
	
SET_4
	MOVLW B'00010000'
	MOVWF GPIO
	GOTO MAIN
	
SET_5
	MOVLW B'00010001'
	MOVWF GPIO
	GOTO MAIN
	
SET_6
	MOVLW B'00010100'
	MOVWF GPIO
	GOTO MAIN
	
SET_7
	MOVLW B'00010101'
	MOVWF GPIO
	GOTO MAIN
	
SET_8
	MOVLW B'00100000'
	MOVWF GPIO
	GOTO MAIN
	
SET_9
	MOVLW B'00100001'
	MOVWF GPIO
	GOTO MAIN

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIO DO PROGRAMA                          *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
INICIO
	BANK1				;ALTERA PARA O BANCO 1
	MOVLW	B'00000010'	
	MOVWF	TRISIO		; Configura GP1 como entrada
	MOVLW	B'00010010'
	MOVWF	ANSEL 		; Configura GP1 como entrada anal�gica e o clock do comparador
	MOVLW	B'00000000'
	MOVWF	OPTION_REG	;DEFINE OP��ES DE OPERA��O
	MOVLW	B'00000000'
	MOVWF	INTCON		;DEFINE OP��ES DE INTERRUP��ES
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00010001'
	MOVWF	T1CON		; Configura o timer1 para conseguirmos obter um tempo de 100ms
	MOVLW	B'00000111'
	MOVWF	CMCON		; Desliga o Comparador Anal�gico
	MOVLW	B'00000101'	
	MOVWF	ADCON0		; Escolhe GP1 como canal de entrada do Conversor A/D e o liga

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZA��O DAS VARI�VEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	BSF PIR1, 0
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
MAIN
	BSF	ADCON0, 1   ; Capta o sinal de GP1 para o Conversor A/D
	BTFSC	ADCON0, 1   ; Espera at� o conversor terminar
	GOTO $-1
	
	BTFSS	PIR1, 0   ; Espera at� o timer de 100ms estourar
	GOTO $-1
	CALL START_TIMER    ; Quando estoura, reseta e prossegue com a convers�o

	MOVLW	.26	    ; Equivalente digital a 0,5V
	SUBWF	ADRESH,	W   ; Subtrai o valor do work do resultado do conversor
	BTFSS	STATUS, 0   ; Caso seja negativo, i.e., o valor do work � maior, ent�o ligamos os LEDs de acordo com a tabela fornecida
	GOTO	SET_0	    ; Neste caso, 0
	
	; A l�gica � a mesma para os intervalos seguintes, apenas ajustando a refer�ncia
	MOVLW	.51	    ; Equivalente digital a 1V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_1
	
	MOVLW	.77	    ; Equivalente digital a 1,5V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_2
	
	MOVLW	.103	    ; Equivalente digital a 2V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_3
	
	MOVLW	.128	    ; Equivalente digital a 2,5V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_4
	
	MOVLW	.154	    ; Equivalente digital a 3V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_5
	
	MOVLW	.179	    ; Equivalente digital a 3,5V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_6
	
	MOVLW	.205	    ; Equivalente digital a 4V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_7
	
	MOVLW	.230	    ; Equivalente digital a 4,5V
	SUBWF	ADRESH, W
	BTFSS	STATUS, 0
	GOTO	SET_8
	GOTO	SET_9

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       FIM DO PROGRAMA                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	END
