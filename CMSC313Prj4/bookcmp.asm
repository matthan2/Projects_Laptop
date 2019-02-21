; Offsets for fields in struct book.
;

%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4
%define BUFLEN 256

;if  the  ESI  register  holds  the  address  of  an  instance  of  struct book
; Essentially ESI should be i
%define TITLE_OFFSET 0			;[ESI+AUTHOR_OFFSET] 32 + 1
%define AUTHOR_OFFSET 33		;[ESI+AUTHOR_OFFSET] 20 + 1
%define SUBJECT_OFFSET 54		;[ESI+SUBJECT_OFFSET] 10 + 1
%define YEAR_OFFSET 68		    ;[ESI+YEAR_OFFSET] can be used to reference the year field of the struct
	;also [ESI+ECX+AUTHOR_OFFSET] can be used to access the i-th character, value of i is stored in ECX


SECTION .bss
;;; Here we declare uninitialized data. We're reserving space (and
;;; potentially associating names with that space) that our code
;;; will use as it executes. Think of these as "global variables"


newstr: resb BUFLEN               ; converted string
readlen: resb	4



SECTION .text                   ; Code section.
global bookcmp
extern book1
extern book2


bookcmp:
	
	push ebp
	mov ebp, esp
	push ebx
	push edx
	push edi 
	push ecx
	
	
	xor ecx, ecx
	xor edx, edx 
	xor ebx, ebx
	xor edi, edi
	
	mov ebx, [book1]
	mov ecx, [book2]
	
	mov eax, [ebx + YEAR_OFFSET] ;book1 year
	mov edx, [ecx + YEAR_OFFSET] ;book2 year
	
	cmp eax, edx  ;book1 year > book2
	jg  .book1Greater
	
	cmp edx, eax ;book2 year > book1 year
	jg 	.book2Greater
	
	cmp edx, eax	;year is the same 
	je 	.theSame
	
	
	.book1Greater:
		xor eax, eax
		mov eax, 1
		jmp .done
	
	.book2Greater:
		xor eax, eax
		mov eax, -1
		jmp .done
	
	.theSame:
	
		.setup:
	xor edx, edx
	xor eax, eax
	xor edi, edi
	mov edi, 0
		.loop:
		cmp edi, 32
		jg .done
		
		mov al, [ebx + edi + TITLE_OFFSET] 	;book1 letter in title
		mov dl, [ecx + edi + TITLE_OFFSET]	;book2 letter in tittle
		
		inc edi
		
		cmp al, dl
		je .loop
		
		cmp al, dl
		jg .book1Greater
		
		cmp al, dl
		jl .book2Greater
		

	.done:
	
	pop ecx
	pop edi
	pop edx 
	pop ebx 
	mov esp, ebp
	pop ebp
	ret
	
	