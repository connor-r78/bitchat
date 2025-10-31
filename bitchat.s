.intel_syntax noprefix

.global _input
.global input

.section .data

  PAGE_SIZE: .word 0x1000
  TOKEN_SIZE: .byte 0x04

  msg: .asciz "hello, world\n"

.section .bss

  input: .skip 0x1000

.section .text

_L1:

  // call alloc; push memory address to stack
  call _alloc
  push rax

  // read
  xor rax, rax
  xor rdi, rdi
  lea rsi, [rip + input]
  movzx rdx, WORD PTR [rip + PAGE_SIZE]
  syscall

  // ioctl; flush buffer
  mov rax, 0x10
  mov rsi, 0x540B
  xor rdx, rdx
  syscall

  // pop memory address to rdi; call tokenize
  pop rdi
  call _tokenize

  jmp _activate

_L2:

  mov rax, 0x1
  mov rdi, 0x1
  lea rsi, [rip + msg]
  mov rdx, 0xD
  syscall

  // exit
  mov rax, 0x3C
  xor rdi, rdi
  syscall

/* prompts input and moves into reserved space */
_input:
 
  xor rax, rax
  xor rdi, rdi
  lea rsi, [rip + input]
  mov rdx, 0x1000
  syscall

  // add null terminator
  add rsi, rax
  mov BYTE PTR [rsi], 0

  // ioctl; flush buffer
  mov rax, 0x10
  mov rsi, 0x540B
  xor rdx, rdx
  syscall 

  ret

/* rdi threshold
// returns boolean in rax depending on activation of neural node */
_activate:

  cmp rax, rdi
  jg _L2

  jmp _L2

/* pushes the input buffer to the heap as tokens
// rdi memory address
// returns number of tokens in rax */
_tokenize:

  // copy input to heap
  lea rsi, [rip + input]
  movzx rcx, WORD PTR [rip + PAGE_SIZE]
  rep movsb

  // 

  // write
  mov rax, 0x1
  mov rsi, rbx
  mov rdi, 0x1
  mov rdx, 0x1000
  syscall

  ret

/* allocates one page of memory
// returns starting address of allocation in rax */
_alloc:
 
  // mmap 
  mov rax, 0x9
  xor rdi, rdi
  movzx rsi, WORD PTR [rip + PAGE_SIZE]
  mov rdx, 0x3
  mov r10, 0x22
  mov r8, -0x1
  xor r9, r9
  syscall

  // save memory address in safe register
  mov rbx, rax

  // (rsi src, rdi dest, rcx bytes)
  lea rsi, [rip + msg]
  mov rdi, rbx
  mov rcx, 0xD
  rep movsb

  mov rax, 0x1
  mov rsi, rbx
  mov rdi, 0x1
  mov rdx, 0xD
  syscall

  mov rax, rbx

  ret
