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
		RESH		; Contém os bits mais signficativos da média da leitura
		RESL		; Contém os bits menos signficativos da média da leitura
		VOLTAGE		; Contém o valor da tensão convertido
		VOLTAGE_DECIMAL ; Contém a parte decimal do valor convertido
		AUX_CHAR	; Caractere auxiliar para impressão no display

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
		
	BCF	GPIO, 0	    ; Start printing
	CALL	TMR_WAIT_LCD
	
	MOVLW	.9
	MOVWF	COUNTER
	MOVLW	.128	    ; Ajusta o cursor do LCD para a posicão apropriada
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa o primeiro dígito
	MOVWF	COUNTER
	MOVFW	VOLTAGE
	ADDLW	.30
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa a vírgula
	MOVWF	COUNTER
	MOVLW	'.'
	MOVWF	AUX_CHAR
	CALL	PRINT_CHAR
	
	MOVLW	.9	    ; Printa o segundo dígito
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
	
ADJUST_PTR		; Move o ponteiro até a última posicão de memória e ajusta o contador para contar 32 bytes
    MOVLW .32
    MOVWF COUNTER
    MOVLW 0x5F
    MOVWF FSR
    RETURN

READ_VALUE
    BSF	    ADCON0, 1   ; Capta o sinal de GP1 para o Conversor A/D
    BTFSC   ADCON0, 1   ; Espera até o conversor terminar
    GOTO    $-1
    
    MOVFW   ADRESH	; Pega o resultado da conversão
    MOVWF   INDF	; E insere no endereco de memória apontado
    DECF    FSR		; Move o ponteiro para a próxima posicão
    RETURN
    
SUM_VALUE
    MOVFW RESL
    ADDWF INDF, W
    MOVWF RESL		; Soma o RESL com o work e salva de volta no RESL
    BTFSC STATUS, C	; Caso tenha carry-out
    INCF  RESH		; Incremeta o byte mais significativo (+=256)
    DECF  FSR		; Move o ponteiro para a próxima posicão
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
    
GET_VOLTAGE		    ; Funcão para transformar a tensao digital para o valor analógico
    CLRF    VOLTAGE
    CLRF    VOLTAGE_DECIMAL
    
    MOVLW   .51
    GET_FIRST_DIGIT
	SUBWF   RESL, F
	BTFSC   STATUS, 0   ; Subtrai até o resultado ser negativo
	GOTO	INC_VOLTAGE
	
    ADDWF   RESL, F	    ; Soma novamente para que o número fique positivo
    MOVLW   .9		    ; Multiplica por 10 para a divisão decimal (Somando 9 vezes)
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
    
TMR_WAIT_LCD		    ; Espera o tempo necessário para a leitura do LCD
    MOVLW   .209
    MOVWF   TMR0
    BCF	    INTCON, 2
    BTFSS   INTCON, 2
    GOTO    $-1
    RETURN
    
PRINT_CHAR		    ; Funcão que printa um caractere que esteja no AUX_CHAR
    DECFSZ  COUNTER	    ; É necessário ajustar o contador para varrer os 8 bits
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
	MOVWF	ANSEL 		; Configura GP1 como entrada analógica e o clock do comparador
	MOVLW	B'00000100'
	MOVWF	OPTION_REG	;DEFINE OPÇÕES DE OPERAÇÃO
	MOVLW	B'11000000'
	MOVWF	INTCON		;DEFINE OPÇÕES DE INTERRUPÇÕES
	BSF	PIE1, 0
	CALL	0X3FF
	MOVWF	OSCCAL
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00000111'
	MOVWF	CMCON		; Desliga o Comparador Analógico
	MOVLW	B'00000101'	
	MOVWF	ADCON0		; Escolhe GP1 como canal de entrada do Conversor A/D e o liga
	MOVLW	B'00100001'	
	MOVWF	T1CON		; Configura o timer1

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZAÇÃO DAS VARIÁVEIS                 *
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
