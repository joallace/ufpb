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
		COUNTER		; Contador utilizado para m�ltiplas aplicac�es
		RESH		; Cont�m os bits mais signficativos da m�dia da leitura
		RESL		; Cont�m os bits menos signficativos da m�dia da leitura
		VOLTAGE		; Cont�m o valor da tens�o convertido
		VOLTAGE_DECIMAL ; Cont�m a parte decimal do valor convertido
		AUX_CHAR	; Caractere auxiliar para impress�o no display

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
		
	BCF	GPIO, 0	    ; Start printing
	CALL	TMR_WAIT_LCD
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	.128	    ; Ajusta o cursor do LCD para a posic�o apropriada
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa o primeiro d�gito
	MOVWF	COUNTER
	MOVFW	VOLTAGE
	ADDLW	.30
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa a v�rgula
	MOVWF	COUNTER
	MOVLW	'.'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa o segundo d�gito
	MOVWF	COUNTER
	MOVFW	VOLTAGE_DECIMAL
	ADDLW	.30
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	BSF	GPIO, 0	    ; Stop printing
;	CALL	TMR_WAIT_LCD

	MOVLW	B'00000000'
	MOVWF	TMR1H
	BCF	PIR1, 0

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
	
ADJUST_PTR		; Move o ponteiro at� a �ltima posic�o de mem�ria e ajusta o contador para contar 32 bytes
    MOVLW .32
    MOVWF COUNTER
    MOVLW 0x5F
    MOVWF FSR
    RETURN

READ_VALUE
    BSF	    ADCON0, 1   ; Capta o sinal de GP1 para o Conversor A/D
    BTFSC   ADCON0, 1   ; Espera at� o conversor terminar
    GOTO    $-1
    
    MOVFW   ADRESH	; Pega o resultado da convers�o
    MOVWF   INDF	; E insere no endereco de mem�ria apontado
    DECF    FSR		; Move o ponteiro para a pr�xima posic�o
    RETURN
    
SUM_VALUE
    MOVFW RESL
    ADDWF INDF, W
    MOVWF RESL		; Soma o RESL com o work e salva de volta no RESL
    BTFSC STATUS, C	; Caso tenha carry-out
    INCF  RESH		; Incremeta o byte mais significativo (+=256)
    DECF  FSR		; Move o ponteiro para a pr�xima posic�o
    RETURN
    
DIVISION
    BCF STATUS, C
    RRF RESH
    RRF RESL
    RETURN
    
INC_VOLTAGE
    INCF    VOLTAGE
    GOTO    GET_FIRST_DIGIT
    
INC_DECIMAL_VOLTAGE
    INCF    VOLTAGE_DECIMAL
    GOTO    GET_DECIMAL_DIGIT
    
GET_VOLTAGE		    ; Func�o para transformar a tensao digital para o valor anal�gico
    CLRF    VOLTAGE
    CLRF    VOLTAGE_DECIMAL
    
    MOVLW   .51
    GET_FIRST_DIGIT
	SUBWF   RESL, F
	BTFSC   STATUS, 0   ; Subtrai at� o resultado ser negativo
	GOTO	INC_VOLTAGE
	
    ADDWF   RESL, F	    ; Soma novamente para que o n�mero fique positivo
    MOVLW   .9		    ; Multiplica por 10 para a divis�o decimal (Somando 9 vezes)
    MOVWF   COUNTER
    MOVFW   RESL
    ADDWF   RESL
    DECFSZ  COUNTER
    GOTO $-2
    
    MOVLW   .51		    ; Divide novamente para obter a parte decimal
    GET_DECIMAL_DIGIT
	SUBWF   RESL, F
	BTFSC   STATUS, 0
	GOTO	INC_DECIMAL_VOLTAGE    
    
    RETURN
    
TMR_WAIT_LCD		    ; Espera o tempo necess�rio para a leitura do LCD
    MOVLW   .209
    MOVWF   TMR0
    BCF	    INTCON, 2
    BTFSS   INTCON, 2
    GOTO    $-1
    RETURN
    
PRINT_CHAR		    ; Func�o que printa um caractere que esteja no AUX_CHAR
    DECFSZ  COUNTER	    ; � necess�rio ajustar o contador para varrer os 8 bits
    GOTO    $+2
    RETURN
	    
    BTFSS   AUX_CHAR, 0
    GOTO    SET_LOW
    GOTO    SET_HIGH
	
SET_HIGH		    ; Seta o bit e espera o tempo
    BSF	    GPIO, 0
    CALL    TMR_WAIT_LCD
    RRF	    AUX_CHAR
    GOTO    PRINT_CHAR
	
SET_LOW			    ; Limpa o bit e espera o tempo
    BCF	    GPIO, 0
    CALL    TMR_WAIT_LCD
    RRF	    AUX_CHAR
    GOTO    PRINT_CHAR

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIO DO PROGRAMA                          *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
INICIO	
	BANK1				;ALTERA PARA O BANCO 1
	MOVLW	B'00000010'	
	MOVWF	TRISIO		; Configura GP1 como entrada
	MOVLW	B'00010010'
	MOVWF	ANSEL 		; Configura GP1 como entrada anal�gica e o clock do comparador
	MOVLW	B'00000100'
	MOVWF	OPTION_REG	;DEFINE OP��ES DE OPERA��O
	MOVLW	B'11000000'
	MOVWF	INTCON		;DEFINE OP��ES DE INTERRUP��ES
	BSF	PIE1, 0
	CALL	0X3FF
	MOVWF	OSCCAL
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00000111'
	MOVWF	CMCON		; Desliga o Comparador Anal�gico
	MOVLW	B'00000101'	
	MOVWF	ADCON0		; Escolhe GP1 como canal de entrada do Conversor A/D e o liga
	MOVLW	B'00100001'	
	MOVWF	T1CON		; Configura o timer1

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZA��O DAS VARI�VEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
MAIN
	CLRF	RESL
	CLRF	RESH
	
	CALL	ADJUST_PTR
	CALL	READ_VALUE
	DECFSZ	COUNTER
	GOTO	$-2

	CALL	ADJUST_PTR
	CALL	SUM_VALUE
	DECFSZ	COUNTER
	GOTO	$-2
	    
	MOVLW	.5
	MOVWF	COUNTER
	
	CALL	DIVISION
        DECFSZ	COUNTER
	GOTO	$-2
	
	CALL	GET_VOLTAGE

	GOTO	MAIN

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       FIM DO PROGRAMA                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	END
