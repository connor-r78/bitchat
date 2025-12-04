.intel_syntax noprefix

.global _printToken

.section .text

/* prints relevant character for token id
// rdi: token id */
_printToken:

  mov rbx, rdi
  mov rax, 456976
  call _parse

  call _printNewLine
  
  ret

/* parses the input
// rbx: token id
// rax: should be set to 456976 (26^4) */
_parse:

  // divide rax by 26; store quotient in rax
  xor edx, edx
  mov rcx, 26
  div rcx

  // if chars remain: print one 
  test rax, rax
  jz .done 

  push rax
  call _print
  pop rax

  jmp _parse

/* calculates relevant char from token; prints it
// rbx: token id
// rax: relevant base 26 int */
_print:

  mov rcx, rax
 
  // isolate the current char in rax
  mov rax, rbx
  xor edx, edx
  div rcx

  // save remainder/new token id to rbx
  mov rbx, rdx

  // convert char to corresponding lowercase letter; store on stack
  add al, 0x61
  sub rsp, 0x8
  mov [rsp], al

  // sys_write; print letter
  mov rax, 0x1
  mov rdi, 0x1
  mov rsi, rsp
  add rsp, 0x8
  mov rdx, 0x1
  syscall

  ret

/* prints new line to stdout
// returns characters printed in rax */
_printNewLine:

  // put new line on stack
  mov al, 0xA
  sub rsp, 0x8
  mov [rsp], al

  // sys_write; print new line
  mov rax, 0x1
  mov rdi, 0x1
  mov rsi, rsp
  add rsp, 0x8 
  mov rdx, 0x1
  syscall

  ret

.done:
  ret
