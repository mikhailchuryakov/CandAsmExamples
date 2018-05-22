section .data use32 class=DATA

buf	times 101 db 0
sz_buf	equ $ - buf	
test1 db "qwe123rtY", 0
test2 db "QWE011rty", 0
test3 db "ABqwe911-0YZ", 0
	
section .text use32 class=CODE

extern gets
extern puts

; 1)
global check
check:
	mov edx, [esp+4]
	mov esi, -1
	
check_cycle_size:
	inc esi
	cmp byte [edx+esi], 0
	jne check_cycle_size
	cmp esi, 0
	je check_cycle_bigletter1
	dec esi
check_cycle_bigletter1:
	cmp esi, 0
	jne check_cycle_bigletter2
		cmp byte [edx+esi], 'A'
		jb check_cycle_bigletter2	
		cmp byte [edx+esi], 'Z'
		ja check_cycle_bigletter2
			jmp exit_check_cycle_bigletteryes
check_cycle_bigletter2:
	cmp byte [edx+esi], 'A'	
	jb exit_check_cycle_bigletterno	
	cmp byte [edx+esi], 'Z'	
	ja exit_check_cycle_bigletterno
	mov byte cl, [edx+esi]
check_cycle_equal:
	dec esi
	cmp [edx+esi], cl
	je exit_check_cycle_bigletterno
	cmp esi, 0
	je	check_cycle_equal
	jmp exit_check_cycle_bigletteryes
exit_check_cycle_bigletterno:
	mov eax, 0
	jmp exit_check
exit_check_cycle_bigletteryes:
	mov eax, 1
exit_check:
	ret



; 4)
global rule1
rule1:
	mov edx, [esp+4]
	mov esi, 0
rule1_cycle:			
	cmp byte [edx+esi], 0
	je exit_rule1_cycle
		cmp byte [edx+esi], 'a'	
		jb exit_rule1_if
		cmp byte [edx+esi], 'z'	
		ja exit_rule1_if
			sub byte [edx+esi], 'a' - 'A'
exit_rule1_if:
	inc esi
	jmp rule1_cycle
exit_rule1_cycle:
	ret
	
; 1)
global rule2
rule2:
	mov edx, [esp+4]
	mov esi, -1
rule2_cycle:
	inc esi
	cmp byte [edx+esi], 0
	je exit_rule2_cycle
		cmp byte [edx+esi], '0'
		jb rule2_cycle
		cmp byte [edx+esi], '9'
		ja rule2_cycle
		mov edi, esi
		inc edi	
rule2_cycle_for:			
			dec edi
			cmp edi, 0
			je rule2_cycle 
				cmp byte [edx+edi-1], '9'	
				ja rule2_cycle_swap
				cmp byte [edx+edi-1], '0'
				jb rule2_cycle_swap
				jmp rule2_cycle_for
rule2_cycle_swap:
				mov cl, [edx+edi]			
				mov ch, [edx+edi-1]
				mov [edx+edi], ch
				mov [edx+edi-1], cl
			jmp rule2_cycle_for
exit_rule2_cycle:
	ret

global test
test:
	mov eax, [esp+4]
	cmp eax, 3
	jl l2
	mov eax, test3
	ret
l2:
	cmp eax, 2
	jl l1
	mov eax, test2
	ret
l1:
	mov eax, test1
	ret
	
global main
main:
	; gets(buf)
	push buf
	call gets
;	add esp, 4

	; puts(buf);
;	push buf
	call puts
;	add esp, 4

;	push buf
	call check
;	add esp, 4
	test eax, eax
	jz do_rule2
;		push buf
		call rule1
;		add esp, 4
		jmp exit_main_check
do_rule2:
;		push buf
		call rule2
;		add esp, 4
exit_main_check:

	; puts(buf);
;	push buf
	call puts
	add esp, 4

	; return 0;
	mov eax, 0
	ret


extern exit

global _start
_start:
	call main

	; exit(ret);
	push eax
	call exit
;	add esp, 4


extern exit

global _start
_start:
	call main

	; exit(ret);
	push eax
	call exit
;	add esp, 4