;Nome: Fellipe Souto Sampaio Nusp: 7990422
;Nome: Caio Lopes Demario   Nusp:  7991187
;
;MAC0211 - Labratório de programação
;
;Prof: Kelly Rosa Braghetto
;
global	seleciona_armstrongs

;Funções externas usadas ao longo da função
extern	fopen
extern	fscanf
extern	fclose
extern	fprintf


section .text

;Função potencia
_pot:
	mov	eax,[conta]
	mov	[indx],eax
	mov	[indxfix],eax
	mov	ebx,10
	mov	eax,[inteiro]
	mov	ecx,0

;Inicia a potência de um novo digito
bg1:
	mov	edx,0
	div	ebx
	mov	esi,eax
	
	mov	eax,edx
	mov	edi,eax
	dec	word[conta]
	cmp	eax,0
	mov	eax,1
	jne	calc
	


;Laço que cálcula a potência
calc:	
	mul	edi
	dec	dword[indx]
	
	cmp	dword[indxfix],1
	je	calc2
	cmp	dword[indx],0
	jne	calc
	
calc2:
	add	ecx,eax
	jmp	cont

;Comparações lógicas
cont:
	cmp	word[conta],0
	je	endd
	mov	eax,[indxfix]
	mov	[indx],eax
	mov	eax,esi
	jmp	bg1
	

;Retorno da função
endd:
	mov	[flagint],ecx
	ret


;Funcão que analisa se o número é armstrong
_conta:

	mov	word[conta],0
	mov	ebx,10
	mov	eax,[inteiro]

;Descasca o número para saber quantos digitos existem
bg:	
	mov	edx,0
	div	ebx
	
	inc	word[conta]
	
	cmp	eax,0
	jne	bg
	
	call	_pot
	
	cmp	ecx,[inteiro]
	je	earm
	
	ret
	

;Caso o número seja armstrong é chamada a função WRITES que escreve no .txt
earm:	
	call	_WRITES
	ret



;Escreve na saida o número de armstrong
_WRITES:
	push 	ebp
	mov	ebp,esp
	push	dword [inteiro]
	push	dword padrao
	push	dword [out_point]
	call	fprintf
	add	esp,12
	pop	ebp
	inc	dword[armsqnt]
	pop	ebp
	ret

seleciona_armstrongs:
;inicia a execução do programa
init:	
	push 	ebp
	mov	ebp,esp
	
	mov	dword[armsqnt],0
	mov	eax,[ebp+8]
	mov	[file_entrada],eax
	mov	eax,[ebp+12]
	mov	[file_saida],eax
	
	
	
;Abre o arquivo de entrada
open_in:
	push	dword mod_leitura
	push	dword [file_entrada]
	call	fopen
	mov	[int_point],eax
	add	esp,8
;Abre o arquivo de saida
open_out:
	push	dword mod_escrita
	push	dword [file_saida]
	call	fopen
	mov	[out_point],eax
	add	esp,8

;Le o arquivo de entrada
read:
	push	dword inteiro
	push	padrao 
	push	dword [int_point]
	call 	fscanf
	add	esp,12
 	
	
	cmp	eax,-1
	jne	verifica
	jmp	esc
	
;Verifica se o numero lido é número de armstrong
verifica:	
	
	call	_conta
	jmp	read

;Sai do programa
esc:
	mov	eax,dword[armsqnt]
	pop	ebp

	ret	
	

;Variáveis estáticas
section .data

mod_leitura:	db	"r",0x00
mod_escrita:	db	"w",0x00
padrao:		db	"%d ",0
stin:		db	"%s",10,0



;Variáveis dinâmicas
section .bss

file_entrada:	RESB	256
file_saida:	RESB	256
inteiro:	RESD	8
flagint:	RESD	8
lido:		RESD	1
int_point:	RESB	10
out_point:	RESB	10
conta:		RESB	10
indx:		RESB	10
indxfix:	RESB	10
armsqnt:	RESB	10

